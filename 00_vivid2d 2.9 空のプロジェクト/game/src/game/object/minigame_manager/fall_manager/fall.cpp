#include "fall.h"
#include"../../player_manager/fall_player_mana/fall_player1/fall_player1.h"
#include"../../player_manager/fall_player_mana/fall_player2/fall_player2.h"
#include"../../../scene_manager/scene/color_select/color_select.h"



//定数
const int CFall::m_map_chip_size = 64;//１マスの大きさ
const int CFall::m_map_chip_count_width = vivid::WINDOW_WIDTH / m_map_chip_size;//マス（横）の数
const int CFall::m_map_chip_count_height = vivid::WINDOW_HEIGHT / m_map_chip_size + 1;//マス（縦）高さ
const char* CFall::m_map_path = "data\\fall\\fall.csv";//マップのパス
const std::string CFall::m_fall_chip_path = "data\\fall\\fall_chip.png";//マス目の画像
const int CFall::m_floor_time = 60 * 2;//同じマスにずっと乗ってたら床の色が変わる
const int CFall::m_chara_center = 24;//キャラの中心
const int CFall::m_map_width = 20;//横のマスの数
const int CFall::m_map_height = 12;//縦のマスの数

//コンストラクタ
CFall::CFall()
	:m_Map(0)
	, m_Now_Map(0)
	, m_Old_Cyan(true)
	, m_Old_Yellow(true)
	, m_Old_Magenta(true)
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
	m_Map_Chip_ID = MAP_CHIP_ID::CYAN;
	m_Floor_Timer[0] = m_floor_time;
	m_Floor_Timer[1] = m_floor_time;
	m_Cyan = CColor_Select::GetInstance().GetCyan();
	m_Yellow = CColor_Select::GetInstance().GetYellow();
	m_Magenta = CColor_Select::GetInstance().GetMagenta();
	if (!m_Old_Cyan)
		m_Cyan = m_Old_Cyan;
	if (!m_Old_Yellow)
		m_Yellow = m_Old_Yellow;
	if (!m_Old_Magenta)
		m_Magenta = m_Old_Magenta;
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

	if (CColor_Select::GetInstance().GetCyan() == false)
	{
		for (int i = 1; i < m_map_chip_count_height - 1; ++i)
		{
			for (int k = 1; k < m_map_chip_count_width - 1; ++k)
			{
				m_Now_Map[i][k] = (unsigned char)(MAP_CHIP_ID::CYAN);
				m_Map[i][k] = (unsigned char)MAP_CHIP_ID::GLAY;
			}
		}
	}
	CItem_Manager::GetInstance().Initialize();
}

//更新
void CFall::Update()
{
	CItem_Manager::GetInstance().Update();
	
#if 0
	if (m_Old_Cyan)
		m_Old_Cyan = CColor_Select::GetInstance().GetCyan();
	if (m_Old_Yellow)
		m_Old_Yellow = CColor_Select::GetInstance().GetYellow();
	if (m_Old_Magenta)
		m_Old_Magenta = CColor_Select::GetInstance().GetMagenta();


	//配列で1P,2Pの位置を記憶
	int x[2] =
	{
		(int)(CFall_Player1::GetInstance().GetCharaPos().x + m_chara_center) / m_map_chip_size,
		(int)(CFall_Player2::GetInstance().GetCharaPos().x + m_chara_center) / m_map_chip_size
	};

	int y[2] =
	{
		(int)(CFall_Player1::GetInstance().GetCharaPos().y + m_chara_center) / m_map_chip_size,
		(int)(CFall_Player2::GetInstance().GetCharaPos().y + m_chara_center) / m_map_chip_size
	};

	for (int i = 0; i < 2; i++)
	{
		if (x[i] != m_Old_X[i] || y[i] != m_Old_Y[i] || --m_Floor_Timer[i] < 0)
		{

			m_Floor_Timer[i] = m_floor_time;
				if (i == 0)
				{
					if (!CItem_Manager::GetInstance().m_High_Jump_P1.Get_Is_Jump_1() &&
						!CFall_Player1::GetInstance().GetIsPullMove())
					{
						ChangeFloor(x[i], y[i]);
					}
				}

			if (i == 1)
			{
				if (!CItem_Manager::GetInstance().m_High_Jump_P2.Get_Is_Jump_2() &&
					!CFall_Player2::GetInstance().GetIsPullMove())
				{
					ChangeFloor(x[i], y[i]);
				}
			}
			m_Old_X[i] = x[i];
			m_Old_Y[i] = y[i];
		}
	}
#endif
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

	CItem_Manager::GetInstance().Draw();

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

void CFall::ChangeFloor(int x, int y)
{
	switch ((MAP_CHIP_ID)m_Map[y][x])
	{
	case MAP_CHIP_ID::CYAN:

		if (!m_Yellow)
		{
			m_Now_Map[y][x] =
				(unsigned char)MAP_CHIP_ID::YELLOW;

			m_Map[y][x] =
				(unsigned char)MAP_CHIP_ID::GLAY;

			break;
		}

		m_Map[y][x] =
			(unsigned char)MAP_CHIP_ID::YELLOW;

		break;

	case MAP_CHIP_ID::YELLOW:

		if (!m_Magenta)
		{
			m_Now_Map[y][x] =
				(unsigned char)MAP_CHIP_ID::MAGENTA;

			m_Map[y][x] =
				(unsigned char)MAP_CHIP_ID::GLAY;

			break;
		}

		m_Map[y][x] =
			(unsigned char)MAP_CHIP_ID::MAGENTA;

		break;

	case MAP_CHIP_ID::MAGENTA:

		m_Map[y][x] =
			(unsigned char)MAP_CHIP_ID::EMPTY;

		break;

	case MAP_CHIP_ID::GLAY:

		if (m_Now_Map[y][x] ==
			(unsigned char)MAP_CHIP_ID::CYAN)
		{
			if (!m_Yellow)
			{
				m_Now_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::YELLOW;

				m_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::GLAY;
			}
			else
			{
				m_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::YELLOW;
			}
		}
		else if (m_Now_Map[y][x] ==
			(unsigned char)MAP_CHIP_ID::YELLOW)
		{
			if (!m_Magenta)
			{
				m_Now_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::MAGENTA;

				m_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::GLAY;
			}
			else
			{
				m_Map[y][x] =
					(unsigned char)MAP_CHIP_ID::MAGENTA;
			}
		}
		else if (m_Now_Map[y][x] ==
			(unsigned char)MAP_CHIP_ID::MAGENTA)
		{
			m_Map[y][x] =
				(unsigned char)MAP_CHIP_ID::EMPTY;
		}

		break;

	case MAP_CHIP_ID::EMPTY:
		break;

	case MAP_CHIP_ID::TREE:
		break;
	}
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

void CFall::IniOld()
{
	m_Old_Cyan = true;
	m_Old_Yellow = true;
	m_Old_Magenta = true;
}

//IDを取得
MAP_CHIP_ID CFall::GetMapChipID()
{
	return m_Map_Chip_ID;
}

