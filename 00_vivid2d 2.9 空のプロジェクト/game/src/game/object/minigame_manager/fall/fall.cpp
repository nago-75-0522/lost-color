#include "fall.h"
#include"../../player_manager/player1/player1.h"
#include"../../player_manager/player2/player2.h"
#include"../../../scene_manager/scene/color_select/color_select.h"
//定数
const int CFall::m_map_chip_size = 64;//１マスの大きさ
const int CFall::m_map_chip_count_width = vivid::WINDOW_WIDTH / m_map_chip_size;//マス（横）の数
const int CFall::m_map_chip_count_height = vivid::WINDOW_HEIGHT / m_map_chip_size + 1;//マス（縦）高さ
const char* CFall::m_map_path = "data\\fall.csv";//マップのパス
const std::string CFall::m_fall_chip_path = "data\\fall_chip.png";//マス目の画像
const int CFall::m_floor_time = 60 * 2;//同じマスにずっと乗ってたら床の色が変わる
const int CFall::m_chara_center = 24;//キャラの中心
const int CFall::m_map_width = 20;//横のマスの数
const int CFall::m_map_height = 12;//縦のマスの数

//コンストラクタ
CFall::CFall()
	:m_Map(0)
	,m_Now_Map(0)
{
}

//初期化
void CFall::Initialize()
{
	m_Old_X[0] = { -1 };//前回のxを保存
	m_Old_X[1] = { -1 };//前回のxを保存
	m_Old_Y[0] = { -1 };//前回のyを保存
	m_Old_Y[1] = { -1 };//前回のyを保存
	m_Map = std::vector<std::vector<unsigned char>>(m_map_height, std::vector<unsigned char>(m_map_width));
	m_Now_Map = std::vector<std::vector<unsigned char>>(m_map_height, std::vector<unsigned char>(m_map_width));
	m_Map_Chip_ID = MAP_CHIP_ID::BLUE;
	m_Floor_Timer[0] = m_floor_time;
	m_Floor_Timer[1] = m_floor_time;
	/*** ファイル操作 ***/
	FILE* fp = nullptr;

	fopen_s(&fp, m_map_path, "r");



	//サイズを調べる
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//サイズ分だけの大きさの入れ物を用意する（一時的なデータ）
	char* buf = new char[size];

	// データ（csvファイル内の文字列）を読み込む
	fread(buf, size, 1, fp);

	//ファイルを閉じる（しないと消せなくなる）
	fclose(fp);

	/*** データの解析 ***/
	//データのサイズ分繰り返し
	for (int i = 0, k = 0; i < size; ++i)
	{
		//文字の０～３であれば、数値に変換する
		if (buf[i] >= '0' && buf[i] <= '5')
		{
			char t = buf[i];

			//データ入力
			m_Map[k / m_map_chip_count_width][k % m_map_chip_count_width]
				= (unsigned char)atoi(&t);

			++k;
		}
	}

	//一時的なデータを削除
	delete[] buf;

	if (CColor_Select::GetInstance().GetBlue() == false)
	{
		for (int i = 1; i < m_map_chip_count_height - 1; ++i)
		{
			for (int k = 1; k < m_map_chip_count_width - 1; ++k)
			{
				m_Now_Map[i][k] = (unsigned char)(MAP_CHIP_ID::BLUE);
				m_Map[i][k] = (unsigned char)MAP_CHIP_ID::GLAY;
			}
		}
	}
}

//更新
void CFall::Update()
{

	bool Get_Floor_Color[3] = { CColor_Select::GetInstance().GetBlue(),
								CColor_Select::GetInstance().GetYellow(),
								CColor_Select::GetInstance().GetRed() };


	//配列で1P,2Pの位置を記憶
	int x[2] =
	{
		(int)(CPlayer1_Character::GetInstance().GetCharaPos().x + m_chara_center) / m_map_chip_size,
		(int)(CPlayer2_Character::GetInstance().GetCharaPos().x + m_chara_center) / m_map_chip_size
	};

	int y[2] =
	{
		(int)(CPlayer1_Character::GetInstance().GetCharaPos().y + m_chara_center) / m_map_chip_size,
		(int)(CPlayer2_Character::GetInstance().GetCharaPos().y + m_chara_center) / m_map_chip_size
	};

	

	for (int i = 0; i < 2; i++)
	{
		if (x[i] != m_Old_X[i] || y[i] != m_Old_Y[i] || --m_Floor_Timer[i] < 0)
		{

			m_Floor_Timer[i] = m_floor_time;

			switch ((MAP_CHIP_ID)m_Map[y[i]][x[i]])
			{
			case MAP_CHIP_ID::BLUE:
				//黄色が消されているなら
				if (Get_Floor_Color[1] == false)
				{
					m_Now_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::YELLOW;//次の色が黄色であることを保存
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::GLAY;//見た目は灰色
					break;
				}
				//何もなければ黄色
				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::YELLOW;//
				break;

			case MAP_CHIP_ID::YELLOW:
				//赤が消されてるなら
				if (Get_Floor_Color[2] == false)
				{
					m_Now_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::RED;//次の色が赤であることを保存
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::GLAY;//見た目は灰色
					break;
				}
				//何もなければ赤
				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::RED;
				break;

			case MAP_CHIP_ID::RED:

				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::EMPTY;
				break;

			case MAP_CHIP_ID::GLAY:
				//青と黄色がない場合　青から黄色
				if (m_Now_Map[y[i]][x[i]] == (unsigned char)(MAP_CHIP_ID::BLUE) && Get_Floor_Color[1] == false)
				{
					m_Now_Map[y[i]][x[i]] = (unsigned char)(MAP_CHIP_ID::YELLOW);
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::GLAY;
				}
				//青がない場合に黄色に変える
				else if (m_Now_Map[y[i]][x[i]] == (unsigned char)(MAP_CHIP_ID::BLUE))
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::YELLOW;
				//黄色と赤がない場合　黄色から赤
				else if (m_Now_Map[y[i]][x[i]] == (unsigned char)(MAP_CHIP_ID::YELLOW) && Get_Floor_Color[2] == false)
				{
					m_Now_Map[y[i]][x[i]] = (unsigned char)(MAP_CHIP_ID::RED);
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::GLAY;
				}
				//黄色がない場合に赤に変える
				else if (m_Now_Map[y[i]][x[i]] == (unsigned char)(MAP_CHIP_ID::YELLOW))
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::RED;
				//赤が無い場合　床を消す
				else if (m_Now_Map[y[i]][x[i]] == (unsigned char)(MAP_CHIP_ID::RED))
					m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::EMPTY;

			}
			m_Old_X[i] = x[i];
			m_Old_Y[i] = y[i];
		}
	}

}

//描画
void CFall::Draw()
{
	// 要素数分繰り返す
	for (int i = 0; i < m_map_chip_count_height; ++i)
	{
		for (int k = 0; k < m_map_chip_count_width; ++k)
		{
			//位置を求める
			vivid::Vector2 pos;

			pos.x = (float)(k * m_map_chip_size);
			pos.y = (float)(i * m_map_chip_size);

			//読み込み範囲を求める
			vivid::Rect rect;

			rect.left = m_Map[i][k] * m_map_chip_size;
			rect.right = rect.left + m_map_chip_size;
			rect.top = 0;
			rect.bottom = m_map_chip_size;

			//描画
			vivid::DrawTexture(m_fall_chip_path, pos, 0xffffffff, rect);
		}
	}
}

//解放
void CFall::Finalize()
{
}



//１マスの大きさを取得
int CFall::GetMapChipSize(void)
{
	return m_map_chip_size;
}


//床がない場所を返す
bool CFall::CheckEmpty(int x, int y)
{
	if (x < 0)
		x = 0;
	if (x > m_map_chip_count_width)
		x = m_map_chip_count_width - 1;
	if (y < 0)
		y = 0;
	if (y > m_map_chip_count_height)
		y = m_map_chip_count_height - 1;


	if (m_Map[y][x] == (unsigned char)MAP_CHIP_ID::EMPTY)
		return true;
	return false;
}



//壁のあるとこを返す
bool CFall::CheckWall(int x, int y)
{
	if (x < 0)
		x = 0;
	if (x > m_map_chip_count_width)
		x = m_map_chip_count_width - 1;
	if (y < 0)
		y = 0;
	if (y > m_map_chip_count_height)
		y = m_map_chip_count_height - 1;

	//IDが木なら進めない
	if (m_Map[y][x] == (unsigned char)MAP_CHIP_ID::TREE)
		return true;
	return false;
}

CFall& CFall::GetInstance()
{
	static CFall instance;
	return instance;
}

//IDを取得
MAP_CHIP_ID CFall::GetMapChipID()
{
	return m_Map_Chip_ID;
}

