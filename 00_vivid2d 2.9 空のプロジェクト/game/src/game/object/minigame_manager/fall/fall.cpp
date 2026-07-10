#include "fall.h"
#include"../../player_manager/player1/player1.h"
#include"../../player_manager/player2/player2.h"
//定数
const int CFall::m_map_chip_size = 64;
const int CFall::m_map_chip_count_width= vivid::WINDOW_WIDTH / m_map_chip_size;
const int CFall::m_map_chip_count_height = vivid::WINDOW_HEIGHT / m_map_chip_size+1;
const char* CFall::m_map_path = "data\\fall.csv";
const std::string CFall::m_fall_chip_path = "data\\fall_chip.png";
const int CFall::m_floor_time = 60 * 2;
const int CFall::m_chara_center = 24;
const int CFall::m_map_width = 20;
const int CFall::m_map_height = 12;

CFall::CFall()
:m_Map(0)
,m_Empty(false)
{
}

void CFall::Initialize()
{
	m_Map = std::vector<std::vector<unsigned char>>(m_map_height, std::vector<unsigned char>(m_map_width));
	//m_Floor_Timer = m_floor_time;
	m_Map_Chip_ID = MAP_CHIP_ID::FLOOR1;
	m_Empty = false;
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
}

void CFall::Update()
{
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

	static int oldX[2] = { -1, -1 };//前回のxを保存
	static int oldY[2] = { -1, -1 };//前回のyを保存
	static int floorTimer[2] = { m_floor_time, m_floor_time };

	for (int i = 0; i < 2; i++)
	{
		if (x[i] != oldX[i] || y[i] != oldY[i] || --floorTimer[i] < 0)
		{
			floorTimer[i] = m_floor_time;

			switch ((MAP_CHIP_ID)m_Map[y[i]][x[i]])
			{
			case MAP_CHIP_ID::FLOOR1:
				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::FLOOR2;
				break;

			case MAP_CHIP_ID::FLOOR2:
				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::FLOOR3;
				break;

			case MAP_CHIP_ID::FLOOR3:
				m_Map[y[i]][x[i]] = (unsigned char)MAP_CHIP_ID::EMPTY;
				break;
			}

			oldX[i] = x[i];
			oldY[i] = y[i];
		}
	}
}

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

void CFall::Finalize()
{
}

void CFall::ChangeFloor(int x, int y)
{
	{

	}

}



int CFall::GetMapChipSize(void)
{
	return m_map_chip_size;
}



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

MAP_CHIP_ID CFall::GetMapChipID()
{
	return m_Map_Chip_ID;
}

