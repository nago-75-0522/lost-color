#include"race_player1.h"
#include"../race_player_id.h"

CPlayer1& CPlayer1::GetInstance(void)
{
	static CPlayer1 instance;

	return instance;
}

CPlayer1::CPlayer1(void)
	: IPlayer(PLAYER_CATEGORY::PLAYER1)
{
}

void CPlayer1::Update(void)
{
	namespace keyboard = vivid::keyboard;

	if (keyboard::Trigger(keyboard::KEY_ID::W))
	{
		//キーが押されてなかったら押した判定にする
		if (!m_isPush)
			m_isPush = true;

		m_isUp_Move = true;
	}
	
	if (keyboard::Trigger(keyboard::KEY_ID::S))
	{
		//キーが押されてなかったら押した判定にする
		if (!m_isPush)
			m_isPush = true;

		m_isDown_Move = true;
	}

	IPlayer::Update();
}

void CPlayer1::Draw()
{	
	m_Draw_Pos.x = m_Camera_Copy_Pos.x + vivid::WINDOW_WIDTH / 2 - m_size / 2 + m_Move_Pos.x;
	m_Draw_Pos.y =	m_Camera_Copy_Pos.y + vivid::WINDOW_HEIGHT / 2 - m_size + m_Move_Pos.y;

	vivid::DrawTexture("data\\logo\\small_pink_1p.png", { m_Draw_Pos.x + m_size, m_Draw_Pos.y + m_size - 40.f });
	vivid::DrawTexture("data\\abe.png", m_Draw_Pos);

	//vivid::DrawText(40, "Accele:" + std::to_string(m_isAccele), { 0.0f,0.0f }, 0xffff0000);

	//vivid::DrawText(40, "NowNum:" + std::to_string(m_Now_Num_Map), { 0.0f,80.f }, 0xffff0000);
	//vivid::DrawText(40, "KeepNum:" + std::to_string(m_Keep_Num), { 0.0f,160.f }, 0xffff0000);
	//vivid::DrawText(40, "Velocity.x:" + std::to_string((int)m_Velocity.x) + "Velocity.y:" + std::to_string((int)m_Velocity.y), { 0.0f,80.0f },0xffff0000);
	//vivid::DrawText(40, "Timer:" + std::to_string(m_Move_Timer), { 0.0f,120.f },0xff000000);

	//vivid::DrawText(40, "MovePos.x:" + std::to_string((int)m_Player_Pos.x) + "MovePos.y:" + std::to_string((int)m_Player_Pos.y), { 0.0f,160.0f }, 0xffff0000);
	//vivid::DrawText(40, "Up:" + std::to_string(m_isUp_Move) + "Down:" + std::to_string(m_isDown_Move), { 0.0f,0.0f }, 0xffff0000);
	//vivid::DrawText(40, "UpLane:" + std::to_string(m_isUp_Lane) + "DownLane:" + std::to_string(m_isDown_Lane), { 0.0f,0.0f }, 0xffff0000);
	//vivid::DrawText(40, "DrawPos.x:" + std::to_string((int)m_Draw_Pos.x) + "DrawPos.y:" + std::to_string((int)m_Draw_Pos.y), { 0.0f,120.0f }, 0xffff0000);
	//vivid::DrawText(40, "BackCount:" + std::to_string(m_Back_Count), { 0.0f,160.f }, 0xffff0000);
	
	//１P描画位置　デバッグ
#if 0
	//描画位置　デバッグ
	vivid::DrawText(40, "x:" + std::to_string(m_Draw_Pos.x) +
		"y:" + std::to_string(m_Draw_Pos.y), { 0.0f,0.f },0xffff0000);
#endif
}

