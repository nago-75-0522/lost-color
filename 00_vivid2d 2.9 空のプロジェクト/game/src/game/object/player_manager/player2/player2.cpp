#include "player2.h"
#include"../../minigame_manager/fall/fall.h"
const int CPlayer2_Character::m_player2_chara_height = 48;
const int CPlayer2_Character::m_player2_chara_width = 48;
const int CPlayer2_Character::m_player2_chara_move_time = 12;
const std::string CPlayer2_Character::m_player2_boy_path = "data\\character.png";
const vivid::Vector2 CPlayer2_Character::m_player2_tree_size = { 64.0f,128.0f };
const float CPlayer2_Character::m_player2_chara_move_speed = (float)CFall::GetInstance().GetMapChipSize()/ (float)m_player2_chara_move_time;
const int CPlayer2_Character::m_player2_chara_center = 24;
const std::string CPlayer2_Character::m_player2_marker_path = "data/logo/small_blue_2p.png";
const vivid::Vector2 CPlayer2_Character::m_player2_marker_size = { 64.0f,40.0f };

CPlayer2_Character::CPlayer2_Character()
	: m_Player2_Chara_Pos{ 0.0f,0.0f }
	, m_Player2_Chara_Rect{ 0,0,m_player2_chara_width,m_player2_chara_height }
	, m_Player2_Chara_Speed{ 0.0f,0.0f }
	, m_Player2_Chara_Anime_Frame(0)
	, m_Player2_Chara_Anime_Timer(0)
	, m_Player2_Chara_Move_Timer(0)
	, m_Player2_Chara_Anchor(m_player2_chara_center, m_player2_chara_center)
	, m_Player2_Chara_Scale(1.0, 1.0)
	, m_Player2_Chara_Angle(0)
	, m_Player2_Marker_Pos{ 0.0f,0.0f }
{
}

void CPlayer2_Character::Initialize()
{
	m_Player2_Chara_Pos = { 1159.0f,647.0f };
	m_Player2_Chara_State = CHARA_STATE::WAIT;
	m_Player2_Chara_Dir = CHARA_DIRECTION::DOWN;
	m_Player2_Chara_Rect = { 0,0,m_player2_chara_width,m_player2_chara_height };
	m_Player2_Chara_Speed = { 0.0f,0.0f };
	m_Player2_Chara_Anime_Frame = (0);
	m_Player2_Chara_Anime_Timer = (0);
	m_Player2_Chara_Move_Timer = (0);
	m_Player2_Chara_Anchor = { m_player2_chara_center, m_player2_chara_center };
	m_Player2_Chara_Scale = { 1.0, 1.0 };
	m_Player2_Chara_Angle = (0);
	m_Player2_Marker_Pos={ m_Player2_Chara_Pos.x,m_Player2_Chara_Pos.y - m_player2_marker_size.y };
}

void CPlayer2_Character::Update()
{
	switch (m_Player2_Chara_State)
	{
	case CHARA_STATE::WAIT:
		WaitCharacter();
		break;
	case CHARA_STATE::MOVE:
		MoveCharacter();
		break;
	}

	//移動計算
	m_Player2_Chara_Pos.x += m_Player2_Chara_Speed.x;
	m_Player2_Chara_Pos.y += m_Player2_Chara_Speed.y;
	//プレイヤーマーカー
	m_Player2_Marker_Pos.x = m_Player2_Chara_Pos.x;
	m_Player2_Marker_Pos.y = m_Player2_Chara_Pos.y - m_player2_marker_size.y;

	int x = (int)((m_Player2_Chara_Pos.x + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());
	int y = (int)((m_Player2_Chara_Pos.y + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());

	if (CFall::GetInstance().CheckEmpty(x,y) && m_Player2_Chara_Scale.x >= 0 )
	{
		m_Player2_Chara_Scale.x = m_Player2_Chara_Scale.y = cos((++m_Player2_Chara_Angle %= 720) * 3.14f / 360.0f);
	}
}

void CPlayer2_Character::Draw()
{
	m_Player2_Chara_Rect.left = m_Player2_Chara_Anime_Frame * m_player2_chara_width;
	m_Player2_Chara_Rect.right = m_Player2_Chara_Rect.left + m_player2_chara_width;
	m_Player2_Chara_Rect.top = (int)m_Player2_Chara_Dir * m_player2_chara_height;
	m_Player2_Chara_Rect.bottom = m_Player2_Chara_Rect.top + m_player2_chara_height;
	vivid::DrawTexture(m_player2_marker_path, m_Player2_Marker_Pos);

	vivid::DrawTexture(m_player2_boy_path, m_Player2_Chara_Pos, 0xffffffff, m_Player2_Chara_Rect, m_Player2_Chara_Anchor, m_Player2_Chara_Scale);
}

void CPlayer2_Character::Finalize()
{
}

void CPlayer2_Character::WaitCharacter()
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	// スティック入力取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);

	const float DEAD_ZONE = 0.5f;
	int x = (int)((m_Player2_Chara_Pos.x + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());
	int y = (int)((m_Player2_Chara_Pos.y + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());


	if (!CFall::GetInstance().CheckEmpty(x,y))
	{
		if (keyboard::Button(keyboard::KEY_ID::UP) || stick.y < -DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::UP))
		{
			m_Player2_Chara_Dir = CHARA_DIRECTION::UP;

			//自分のいるマス目から一つ上側を調べる。これがfalseなら進める。
			if (!CFall::GetInstance().CheckWall(x, y - 1))
			{
				m_Player2_Chara_Speed.y = -m_player2_chara_move_speed;
				m_Player2_Chara_State = CHARA_STATE::MOVE;
			}
		}
		else if (keyboard::Button(keyboard::KEY_ID::DOWN) || stick.y > DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::DOWN))
		{
			m_Player2_Chara_Dir = CHARA_DIRECTION::DOWN;

			//自分のいるマス目から一つ下側を調べる。
			if (!CFall::GetInstance().CheckWall(x, y + 1))
			{
				m_Player2_Chara_Speed.y = +m_player2_chara_move_speed;
				m_Player2_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::RIGHT) || stick.x > DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::RIGHT))
		{
			m_Player2_Chara_Dir = CHARA_DIRECTION::RIGHT;

			if (!CFall::GetInstance().CheckWall(x + 1, y))
			{
				m_Player2_Chara_Speed.x = +m_player2_chara_move_speed;
				m_Player2_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::LEFT) || stick.x < -DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::LEFT))
		{
			m_Player2_Chara_Dir = CHARA_DIRECTION::LEFT;

			//自分のいるマス目から一つ左側を調べる。
			if (!CFall::GetInstance().CheckWall(x - 1, y))
			{
				m_Player2_Chara_Speed.x = -m_player2_chara_move_speed;
				m_Player2_Chara_State = CHARA_STATE::MOVE;
			}
		}
	}
}

void CPlayer2_Character::MoveCharacter()
{//移動時間の計算
	if (++m_Player2_Chara_Move_Timer >= m_player2_chara_move_time)
	{
		m_Player2_Chara_Move_Timer = 0;
		m_Player2_Chara_Speed.x = 0;
		m_Player2_Chara_Speed.y = 0;

		//時間が来たら待機状態に戻す
		m_Player2_Chara_State = CHARA_STATE::WAIT;

		return;
	}

	//アニメーションタイマーの更新
	if (++m_Player2_Chara_Anime_Timer > 10)
	{
		m_Player2_Chara_Anime_Timer = 0;
		//アニメーションフレームを更新
		++m_Player2_Chara_Anime_Frame %= 3;
	}
}

vivid::Vector2 CPlayer2_Character::GetScale()
{
	return m_Player2_Chara_Scale;
}

CPlayer2_Character& CPlayer2_Character::GetInstance()
{
	static CPlayer2_Character instance;
	return instance;
}
