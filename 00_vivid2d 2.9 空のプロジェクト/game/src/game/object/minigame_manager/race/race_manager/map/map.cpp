#include "map.h"
#include"../camera/camera.h"
#include"../../../../player_manager/race_player_mana/race_player_mana.h"

const int CMap::m_map_width = 187;// 1280 / 64 * 2 (マップの横マスの数）
const int CMap::m_map_height = 12;// 720 / 64
const int CMap::m_size = 64; //タイルサイズ
const vivid::Vector2 CMap::m_distance = { m_map_width * m_size - vivid::WINDOW_WIDTH, 0.0f };

CMap::CMap()
	: m_Map(0)
	, m_Chara_Num(0)
	, m_Up_Num(0)
	, m_Player1_Num(0)
	, m_Player2_Num(0)
	, m_Color_Win_Num(0)
	, m_Color_Lose_Num(0)
{
}

void CMap::Inisitalize(void)
{
	//配列作成
	m_Map = std::vector<std::vector<unsigned char>>(m_map_height, std::vector<unsigned char>(m_map_width));

	//マップ生成
	/*** ファイル操作 ***/
	FILE* fp = nullptr;

	//ファイルを開く 「r」は読み取り
	fopen_s(&fp, "data\\race_map.csv", "r");

	//サイズを調べる
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//サイズ分だけの大きさの入れ物を用意する（一時的なデータ）
	char* buf = new char[size + 1];

	// データ（csvファイル内の文字列）を読み込む
	fread(buf, size, 1, fp);

	buf[size] = '\0';

	//ファイルを閉じる（しないと消せなくなる）
	fclose(fp);

	/*** データの解析 ***/
	//データのサイズ分繰り返し
	for (int i = 0, k = 0; i < size; ++i)
	{
		//文字の０～３であれば、数値に変換する
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			char* end;

			//10～の２桁以上の数字も読み込む
			int value = strtol(&buf[i], &end, 10);

			//データ入力
			m_Map[k / m_map_width][k % m_map_width] = (unsigned char)value;

			++k;

			//読み込んだ数字の最後までiを進める
			i = (int)(end - buf) - 1;
		}
	}

	//一時的なデータを削除
	delete[] buf;
	/*************************************************/

	m_Chara_Num = 0;
	m_Up_Num = 0;

	//仮
	m_Player1_Num = 0;
	m_Player2_Num = 0;

	m_Color_Win_Num = 0;
	m_Color_Lose_Num = 0;
}

void CMap::Update(void)
{
	CRace_Player_Manager& pm = CRace_Player_Manager::GetInstance();
	CCamera& camera = CCamera::GetInstance();

	//カメラの場所を決める
	camera.SetCameraPos(pm.GetPosition());

	//全部見る
	for (int y = 0; y < m_map_height; y++)
	{
		for (int x = 0; x < m_map_width; x++)
		{
			vivid::Vector2 pos;

			pos.x = x * m_size - camera.GetCameraPos().x - m_distance.x;
			pos.y = y * m_size - camera.GetCameraPos().y;

			float camera_posX = camera.GetCameraPos().x;

			isCharaNumNow(pos, x, y, camera_posX);  //該当する升目の値を返すために計算

			//左から現れたマス
			if (pos.x == 0.f)
			{
				//3と4が出てきたときに、上にいるほうを変数にいれる
				if (m_Map[y][x] == 4)
				{
					//3の場所が半分より上かどうか
					if (pos.y < m_map_height / 2 * m_size)
						m_Up_Num = 4;
					else
						m_Up_Num = 5;
				}

				//一番左のマスだったら
				if (x == 0)
				{
					//スピードをゼロにする（背景移動を止める）
					pm.SetSpeed(0.f);
				}
			}
		}
	}

}

//描画
void CMap::Draw(void)
{
	CCamera& camera = CCamera::GetInstance();

	for (int y = 0; y < m_map_height; y++)
	{
		for (int x = 0; x < m_map_width; x++)
		{
			vivid::Vector2 pos;

			//背景描画する場所決め
			pos.x = x * m_size - camera.GetCameraPos().x - m_distance.x;//これにより表示される初期位置が変わる
			pos.y = y * m_size - camera.GetCameraPos().y;

			vivid::Rect rect;

			rect.left = m_Map[y][x] * m_size;
			rect.right = rect.left + m_size;
			rect.top = 0;
			rect.bottom = m_size;

			vivid::Rect color_rect;
			int color_rect_num;

			//加速レーンかそうじゃないかを表す色を表示するために使う数
			switch (m_Map[y][x])
			{
			case 4:
				color_rect_num = m_Color_Win_Num;
				break;

			case 5:
				color_rect_num = m_Color_Lose_Num;
				break;

			default:
				color_rect_num = 0;
				break;
			}

			color_rect.left = color_rect_num * m_size;
			color_rect.right = color_rect.left + m_size;
			color_rect.top = 0;
			color_rect.bottom = m_size;

			vivid::DrawTexture("data\\map.png", pos, 0xffffffff, rect);
			vivid::DrawTexture("data\\color_map.png", pos, 0xffffffff, color_rect);
		}
	}
	//vivid::DrawText(40, "charaNum:" + std::to_string(m_Chara_Num), { 0.f,240.f }, 0xff000000);

#if 0
	vivid::DrawText(40, "1pNum:" + std::to_string(m_Player1_Num), { 0.0f,160.f }, 0xffff0000);
	vivid::DrawText(40, "2pNum:" + std::to_string(m_Player2_Num), { 0.0f,200.f }, 0xff0000ff);
#endif 


}

void CMap::Finalize(void)
{
}

int CMap::isUpNum(void)
{
	return m_Up_Num; //3or4
}

void CMap::SetNum(int num, PLAYER_CATEGORY category)
{
	if (category == PLAYER_CATEGORY::PLAYER1)
		m_Player1_Num = num;
	else if (category == PLAYER_CATEGORY::PLAYER2)
		m_Player2_Num = num;
}

//該当する升目の値を返すために計算する関数
void CMap::isCharaNumNow(vivid::Vector2& pos, float x, float y, float camera_posX)
{
	CRace_Player_Manager& pm = CRace_Player_Manager::GetInstance();

	//1P
	const int CENTER_P1 = 296; //真ん中の場所
	const int UP_P1 = 176; //上の時の場所
	const int DOWN_P1 = 416; //下の時の場所
	//2P
	const int CENTER_P2 = 360; //真ん中の時の場所
	const int UP_P2 = 240; //上の時の場所
	const int DOWN_P2 = 480; //下の時の場所

	//1P	
	//1pの描画されている場所のX座標
	int player1_pos_x = (int)pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER1).x;

	//真ん中の座標にきたマスの番号を返す
	if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER1).y == CENTER_P1)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player1_Num >= player1_pos_x - 8; //8の誤差
		bool xOK2 = (int)pos.x + m_Player1_Num <= player1_pos_x + 8;
		bool yOK1 = pos.y > 256.f;
		bool yOK2 = pos.y < 448.f;

		float camera_pos_x = camera_posX;

		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER1, m_Chara_Num);
		}
	}
	//上に来た時のマスの番号を返す
	else if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER1).y == UP_P1)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player1_Num >= player1_pos_x - 8;
		bool xOK2 = (int)pos.x + m_Player1_Num <= player1_pos_x + 8;
		bool yOK1 = pos.y > 128.f;
		bool yOK2 = pos.y < 320.f;

		float camera_pos_x = camera_posX;

		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER1, m_Chara_Num);
		}
	}
	//下に来た時の番号を返す
	else if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER1).y == DOWN_P1)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player1_Num >= player1_pos_x - 8;
		bool xOK2 = (int)pos.x + m_Player1_Num <= player1_pos_x + 8;
		bool yOK1 = pos.y > 384.f;
		bool yOK2 = pos.y < 576.f;

		float camera_pos_x = camera_posX;

		//** 二回目上のif分は通る。**//
		//*** 二回目下のif分が通らない。べつに値が変わってるわけでもなさそうなのに... ***//
		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER1, m_Chara_Num);
		}


	}


	//2P	
	//2pの描画されている場所のX座標
	int player2_pos_x = (int)pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER2).x;

	//真ん中の座標にきたマスの番号を返す
	if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER2).y == CENTER_P2)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player2_Num >= player2_pos_x - 8;
		bool xOK2 = (int)pos.x + m_Player2_Num <= player2_pos_x + 8;
		bool yOK1 = pos.y > 256.f;
		bool yOK2 = pos.y < 448.f;

		float camera_pos_x = camera_posX;

		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER2, m_Chara_Num);
		}

	}
	//上に来た時のマスの番号を返す
	else if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER2).y == UP_P2)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player2_Num >= player2_pos_x - 8;
		bool xOK2 = (int)pos.x + m_Player2_Num <= player2_pos_x + 8;
		bool yOK1 = pos.y > 128.f;
		bool yOK2 = pos.y < 320.f;

		float camera_pos_x = camera_posX;

		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER2, m_Chara_Num);
		}
	}
	//下に来た時の番号を返す
	else if (pm.GetDrawPosition(PLAYER_CATEGORY::PLAYER2).y == DOWN_P2)
	{
		//実験用
		bool xOK1 = (int)pos.x + m_Player2_Num >= player2_pos_x - 8;
		bool xOK2 = (int)pos.x + m_Player2_Num <= player2_pos_x + 8;
		bool yOK1 = pos.y > 384.f;
		bool yOK2 = pos.y < 576.f;

		float camera_pos_x = camera_posX;

		if (xOK1 && xOK2 && yOK1 && yOK2)
		{
			m_Chara_Num = m_Map[y][x];
			pm.SetNowNumMap(PLAYER_CATEGORY::PLAYER2, m_Chara_Num);
		}

	}

}


void CMap::SetColorRectNum(int win, int lose)
{
	m_Color_Win_Num = win;
	m_Color_Lose_Num = lose;
}

CMap& CMap::GetInstance()
{
	static CMap instance;

	return instance;
}

CMap::CMap(const CMap& rhs)
{
	(void)rhs;
}

CMap& CMap::operator=(const CMap& rhs)
{
	(void)rhs;

	return *this;
}



