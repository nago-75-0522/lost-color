#include"fall_player1.h"
#include"../../../minigame_manager/fall_manager/fall.h"
const int CFall_Player1::m_player1_chara_height = 48;
const int CFall_Player1::m_player1_chara_width = 48;
const int CFall_Player1::m_player1_chara_move_time = 12;
const std::string CFall_Player1::m_player1_boy_path = "data\\character.png";
const vivid::Vector2 CFall_Player1::m_player1_tree_size = { 64.0f,128.0f };
const float CFall_Player1::m_player1_chara_move_speed = (float)CFall::GetInstance().GetMapChipSize() / (float)m_player1_chara_move_time;
const int CFall_Player1::m_player1_chara_center = 24;
const std::string CFall_Player1::m_player1_marker_path = "data/logo/small_pink_1p.png";
const vivid::Vector2 CFall_Player1::m_player1_marker_size = { 64.0f,40.0f };
const int m_item_box_size=50;

CFall_Player1::CFall_Player1()
	: m_Player1_Chara_Pos{ 0.0f,0.0f }
	, m_Player1_Chara_Rect{ 0,0,m_player1_chara_width,m_player1_chara_height }
	, m_Player1_Chara_Speed{ 0.0f,0.0f }
	, m_Player1_Chara_Anime_Frame(0)
	, m_Player1_Chara_Anime_Timer(0)
	, m_Player1_Chara_Move_Timer(0)
	, m_Player1_Chara_Anchor(m_player1_chara_center, m_player1_chara_center)
	, m_Player1_Chara_Scale(1.0, 1.0)
	, m_Player1_Chara_Angle(0)
	,m_Player1_Marker_Pos{0.0f,0.0f}
{
}

void CFall_Player1::Initialize()
{
	m_Player1_Chara_Pos = { 72.0f,69.0f };
	m_Player1_Chara_State = CHARA_STATE::WAIT;
	m_Player1_Chara_Dir = CHARA_DIRECTION::DOWN;
	m_Player1_Chara_Rect={ 0,0,m_player1_chara_width,m_player1_chara_height };
	m_Player1_Chara_Speed={ 0.0f,0.0f };
	m_Player1_Chara_Anime_Frame= 0;
	m_Player1_Chara_Anime_Timer= 0;
	m_Player1_Chara_Move_Timer= 0;
	m_Player1_Chara_Anchor = { m_player1_chara_center, m_player1_chara_center };
	m_Player1_Chara_Scale = { 1.0, 1.0 };
	m_Player1_Chara_Angle= 0;
	m_Player1_Marker_Pos = {m_Player1_Chara_Pos.x,m_Player1_Chara_Pos.y-m_player1_marker_size.y};
	m_Player1_Fall_Sound = true;
}

void CFall_Player1::Update()
{
	switch (m_Player1_Chara_State)
	{
	case CHARA_STATE::WAIT:
		Wait_Character();
		break;
	case CHARA_STATE::MOVE:
		Move_Character();
		break;
	}

	//移動計算
	m_Player1_Chara_Pos.x += m_Player1_Chara_Speed.x;
	m_Player1_Chara_Pos.y += m_Player1_Chara_Speed.y;
	m_Player1_Marker_Pos.x = m_Player1_Chara_Pos.x;
	m_Player1_Marker_Pos.y = m_Player1_Chara_Pos.y-m_player1_marker_size.y;

	int x = (int)((m_Player1_Chara_Pos.x + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());
	int y = (int)((m_Player1_Chara_Pos.y + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());

	if (CFall::GetInstance().CheckEmpty(x,y) && m_Player1_Chara_Scale.x >= 0)
	{
		if (m_Player1_Fall_Sound)
		{
			m_Player1_Fall_Sound = false;
			vivid::PlaySound("data\\sound\\fall.wav", false);
		}
		m_Player1_Chara_Scale.x=m_Player1_Chara_Scale.y= cos((++m_Player1_Chara_Angle %= 720) * 3.14f / 360.0f);
	}
	Hit_Item_Box();
}

void CFall_Player1::Draw()
{
	m_Player1_Chara_Rect.left = m_Player1_Chara_Anime_Frame * m_player1_chara_width;
	m_Player1_Chara_Rect.right = m_Player1_Chara_Rect.left + m_player1_chara_width;
	m_Player1_Chara_Rect.top = (int)m_Player1_Chara_Dir * m_player1_chara_height;
	m_Player1_Chara_Rect.bottom = m_Player1_Chara_Rect.top + m_player1_chara_height;
	vivid::DrawTexture(m_player1_marker_path, m_Player1_Marker_Pos);
	vivid::DrawTexture(m_player1_boy_path, m_Player1_Chara_Pos,0xffffffff,m_Player1_Chara_Rect, m_Player1_Chara_Anchor, m_Player1_Chara_Scale);
}

void CFall_Player1::Finalize()
{
}

void CFall_Player1::Wait_Character()
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	// スティック入力取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);

	const float DEAD_ZONE = 0.5f;
	int x = (int)((m_Player1_Chara_Pos.x + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());
	int y = (int)((m_Player1_Chara_Pos.y + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());


	if (!CFall::GetInstance().CheckEmpty(x,y))
	{
		if (keyboard::Button(keyboard::KEY_ID::W) || stick.y < -DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::UP))
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::UP;

			//自分のいるマス目から一つ上側を調べる。これがfalseなら進める。
			if (!CFall::GetInstance().CheckWall(x, y - 1))
			{
				m_Player1_Chara_Speed.y = -m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}
		else if (keyboard::Button(keyboard::KEY_ID::S) || stick.y > DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::DOWN))
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::DOWN;

			//自分のいるマス目から一つ下側を調べる。
			if (!CFall::GetInstance().CheckWall(x, y + 1))
			{
				m_Player1_Chara_Speed.y = +m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::D) || stick.x > DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::RIGHT;

			if (!CFall::GetInstance().CheckWall(x + 1, y))
			{
				m_Player1_Chara_Speed.x = +m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::A) || stick.x < -DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::LEFT;

			//自分のいるマス目から一つ左側を調べる。
			if (!CFall::GetInstance().CheckWall(x - 1, y))
			{
				m_Player1_Chara_Speed.x = -m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}
	}
}

void CFall_Player1::Move_Character()
{   //移動時間の計算
	if (++m_Player1_Chara_Move_Timer >= m_player1_chara_move_time)
	{
		m_Player1_Chara_Move_Timer = 0;
		m_Player1_Chara_Speed.x = 0;
		m_Player1_Chara_Speed.y = 0;

		//時間が来たら待機状態に戻す
		m_Player1_Chara_State = CHARA_STATE::WAIT;

		return;
	}

	//アニメーションタイマーの更新
	if (++m_Player1_Chara_Anime_Timer > 10)
	{
		m_Player1_Chara_Anime_Timer = 0;
		//アニメーションフレームを更新
		++m_Player1_Chara_Anime_Frame %= 3;
	}
}

bool CFall_Player1::Hit_Item_Box()
{
	for (int i = 0; i < CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_NUM().size(); i++)
	{
		//短形Aの情報
		vivid::Vector2 posA = m_Player1_Chara_Pos;
		int wA = m_player1_chara_width;
		int hA = m_player1_chara_height;
		//短形Bの情報
		vivid::Vector2 posB = CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_Pos(i);
		int wB = CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_Size();
		int hB = CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_Size();

		//短形同士の辺の比較
		if (posA.x<posB.x + wB//Aの左辺とBの右辺
			&& posA.x + wA>posB.x//Aの右辺とBの左辺
			&& posA.y<posB.y + hB//Aの右辺とBの下辺
			&& posA.y + hA>posB.y//Aの下辺とBの上辺
			)
		{
			CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_NUM()
				.erase(CItem_Manager::GetInstance().m_Item_Box.Get_Item_Box_NUM().begin() + i);
			return true;
		}
	}
	return false;
}

vivid::Vector2 CFall_Player1::GetScale()
{
	return m_Player1_Chara_Scale;
}

CFall_Player1& CFall_Player1::GetInstance()
{
	static CFall_Player1 instanse;
	return instanse;
}
