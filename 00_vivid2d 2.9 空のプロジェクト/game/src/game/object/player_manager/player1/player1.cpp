#include "../player1/player1.h"
#include"../../minigame_manager/fall/fall.h"
const int CPlayer1_Character::m_player1_chara_height = 48;
const int CPlayer1_Character::m_player1_chara_width = 48;
const int CPlayer1_Character::m_player1_chara_move_time = 12;
const std::string CPlayer1_Character::m_player1_boy_path = "data\\character.png";
const vivid::Vector2 CPlayer1_Character::m_player1_tree_size = { 64.0f,128.0f };
const float CPlayer1_Character::m_player1_chara_move_speed = (float)CFall::GetInstance().GetMapChipSize() / (float)m_player1_chara_move_time;
const int CPlayer1_Character::m_player1_chara_center = 24;

CPlayer1_Character::CPlayer1_Character()
	: m_Player1_Chara_Pos{ 0.0f,0.0f }
	, m_Player1_Chara_Rect{ 0,0,m_player1_chara_width,m_player1_chara_height }
	, m_Player1_Chara_Speed{ 0.0f,0.0f }
	, m_Player1_Chara_Anime_Frame(0)
	, m_Player1_Chara_Anime_Timer(0)
	, m_Player1_Chara_Move_Timer(0)
	, m_Player1_Chara_Anchor(m_player1_chara_center, m_player1_chara_center)
	, m_Player1_Chara_Scale(1.0, 1.0)
	, m_Player1_Chara_Angle(0)
{
}

void CPlayer1_Character::Initialize()
{
	m_Player1_Chara_Pos = { 72.0f,69.0f };
	m_Player1_Chara_State = CHARA_STATE::WAIT;
	m_Player1_Chara_Dir = CHARA_DIRECTION::DOWN;
	m_Player1_Chara_Rect={ 0,0,m_player1_chara_width,m_player1_chara_height };
	m_Player1_Chara_Speed={ 0.0f,0.0f };
	m_Player1_Chara_Anime_Frame=(0);
	m_Player1_Chara_Anime_Timer=(0);
	m_Player1_Chara_Move_Timer=(0);
	m_Player1_Chara_Anchor = { m_player1_chara_center, m_player1_chara_center };
	m_Player1_Chara_Scale = { 1.0, 1.0 };
	m_Player1_Chara_Angle=(0);
}

void CPlayer1_Character::Update()
{
	switch (m_Player1_Chara_State)
	{
	case CHARA_STATE::WAIT:
		WaitCharacter();
		break;
	case CHARA_STATE::MOVE:
		MoveCharacter();
		break;
	}

	//移動計算
	m_Player1_Chara_Pos.x += m_Player1_Chara_Speed.x;
	m_Player1_Chara_Pos.y += m_Player1_Chara_Speed.y;
	int x = (int)((m_Player1_Chara_Pos.x + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());
	int y = (int)((m_Player1_Chara_Pos.y + 0.5f) / (float)CFall::GetInstance().GetMapChipSize());

	if (CFall::GetInstance().CheckEmpty(x,y) && m_Player1_Chara_Scale.x >= 0)
	{
		m_Player1_Chara_Scale.x=m_Player1_Chara_Scale.y= cos((++m_Player1_Chara_Angle %= 720) * 3.14f / 360.0f);
	}
	
}

void CPlayer1_Character::Draw()
{
	m_Player1_Chara_Rect.left = m_Player1_Chara_Anime_Frame * m_player1_chara_width;
	m_Player1_Chara_Rect.right = m_Player1_Chara_Rect.left + m_player1_chara_width;
	m_Player1_Chara_Rect.top = (int)m_Player1_Chara_Dir * m_player1_chara_height;
	m_Player1_Chara_Rect.bottom = m_Player1_Chara_Rect.top + m_player1_chara_height;

	vivid::DrawTexture(m_player1_boy_path, m_Player1_Chara_Pos,0xffffffff,m_Player1_Chara_Rect, m_Player1_Chara_Anchor, m_Player1_Chara_Scale);
}

void CPlayer1_Character::Finalize()
{
}

void CPlayer1_Character::WaitCharacter()
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
		if (keyboard::Button(keyboard::KEY_ID::W) || stick.y < -DEAD_ZONE)
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::UP;

			//自分のいるマス目から一つ上側を調べる。これがfalseなら進める。
			if (!CFall::GetInstance().CheckWall(x, y - 1))
			{
				m_Player1_Chara_Speed.y = -m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}
		else if (keyboard::Button(keyboard::KEY_ID::S) || stick.y > DEAD_ZONE)
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::DOWN;

			//自分のいるマス目から一つ下側を調べる。
			if (!CFall::GetInstance().CheckWall(x, y + 1))
			{
				m_Player1_Chara_Speed.y = +m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::D) || stick.x > DEAD_ZONE)
		{
			m_Player1_Chara_Dir = CHARA_DIRECTION::RIGHT;

			if (!CFall::GetInstance().CheckWall(x + 1, y))
			{
				m_Player1_Chara_Speed.x = +m_player1_chara_move_speed;
				m_Player1_Chara_State = CHARA_STATE::MOVE;
			}
		}

		else if (keyboard::Button(keyboard::KEY_ID::A) || stick.x < -DEAD_ZONE)
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

void CPlayer1_Character::MoveCharacter()
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

vivid::Vector2 CPlayer1_Character::GetScale()
{
	return m_Player1_Chara_Scale;
}

CPlayer1_Character& CPlayer1_Character::GetInstance()
{
	static CPlayer1_Character instanse;
	return instanse;
}
