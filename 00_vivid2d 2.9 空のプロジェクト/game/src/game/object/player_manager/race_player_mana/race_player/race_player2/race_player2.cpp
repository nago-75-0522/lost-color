#include "race_player2.h"
#include"../race_player_id.h"

CRace_Player2& CRace_Player2::GetInstance(void)
{
	static CRace_Player2 instance;

	return instance;
}

CRace_Player2::CRace_Player2(void)
	: IRace_Player(PLAYER_CATEGORY::PLAYER2)
{
}


void CRace_Player2::Update(void)
{
	namespace keyboard = vivid::keyboard;
	namespace controller = vivid::controller;

	// スティック入力取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);

	const float DEAD_ZONE = 0.5f;

	if (m_Now_Num_Map == 0)
	{
		if (keyboard::Button(keyboard::KEY_ID::UP) || stick.y < -DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::UP))
		{
			//キーが押されてなかったら押した判定にする
				//キーが押されてなかったら押した判定にする
			if (!m_isPush)
			{
				m_isPush = true;
				m_isUp_Move = true;
			}
		}

		if (keyboard::Button(keyboard::KEY_ID::DOWN) || stick.y > DEAD_ZONE ||
			controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::DOWN))
		{
			//キーが押されてなかったら押した判定にする
			if (!m_isPush)
			{
				m_isPush = true;
				m_isDown_Move = true;
			}
		}
	}

	IRace_Player::Update();

}

void CRace_Player2::Draw()
{
	m_Draw_Pos.x = m_Camera_Copy_Pos.x + vivid::WINDOW_WIDTH / 2 - m_size / 2 + m_Move_Pos.x;
	m_Draw_Pos.y = m_Camera_Copy_Pos.y + vivid::WINDOW_HEIGHT / 2 + m_Move_Pos.y;

	vivid::DrawTexture("data\\logo\\small_blue_2p.png", { m_Draw_Pos.x + m_size, m_Draw_Pos.y + m_size - 40.f });
	vivid::DrawTexture("data\\cyan_car.png", m_Draw_Pos, 0xffffffff);

	//vivid::DrawText(40, "Up:" + std::to_string(m_isUp_Move) + "Down:" + std::to_string(m_isDown_Move), { 0.0f,0.0f }, 0xff0000ff);
	//vivid::DrawText(40, "UpLane:" + std::to_string(m_isUp_Lane) + "DownLane:" + std::to_string(m_isDown_Lane), { 0.0f,40.0f }, 0xff0000ff);
	//vivid::DrawText(40, "Accele:" + std::to_string(m_isAccele), { 0.0f,120.0f }, 0xff0000ff);
	//vivid::DrawText(40, "BackCount:" + std::to_string(m_Back_Count), { 0.0f,200.f }, 0xff0000ff);
	//vivid::DrawText(40, "NowNum:" + std::to_string(m_Now_Num_Map), { 0.0f,80.f }, 0xff0000ff);
	//vivid::DrawText(40, "KeepNum:" + std::to_string(m_Keep_Num), { 0.0f,120.f }, 0xff0000ff);
	//vivid::DrawText(40, "isBack:" + std::to_string(m_isBack), { 0.0f,200.f }, 0xff0000ff);
	//vivid::DrawText(40, "BackCount:" + std::to_string(m_Back_Count), { 0.0f,240.f }, 0xff0000ff);


	//2P描画位置　デバッグ
#if 0
	vivid::DrawText(40, "x:" + std::to_string(m_Draw_Pos.x) +
		"y:" + std::to_string(m_Draw_Pos.y), { 0.0f,40.f }, 0xff0000ff);
#endif
}

