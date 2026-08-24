#include "race_player2.h"
#include"../race_player_id.h"

CPlayer2& CPlayer2::GetInstance(void)
{
	static CPlayer2 instance;

	return instance;
}

CPlayer2::CPlayer2(void)
	: IPlayer(PLAYER_CATEGORY::PLAYER2)
{
}


void CPlayer2::Update(void)
{
	namespace keyboard = vivid::keyboard;

#if 1
	if (keyboard::Button(keyboard::KEY_ID::UP))
	{
		//キーが押されてなかったら押した判定にする
		if (!m_isPush)
			m_isPush = true;

		m_isUp_Move = true;
	}

	if (keyboard::Button(keyboard::KEY_ID::DOWN))
	{
		//キーが押されてなかったら押した判定にする
		if (!m_isPush)
			m_isPush = true;

		m_isDown_Move = true;
	}
#endif

	IPlayer::Update();

}

void CPlayer2::Draw()
{
	m_Draw_Pos.x =	m_Camera_Copy_Pos.x + vivid::WINDOW_WIDTH / 2 - m_size / 2 + m_Move_Pos.x;
	m_Draw_Pos.y = m_Camera_Copy_Pos.y + vivid::WINDOW_HEIGHT / 2 + m_Move_Pos.y;

	vivid::DrawTexture("data\\logo\\small_blue_2p.png", { m_Draw_Pos.x + m_size, m_Draw_Pos.y + m_size - 40.f });
	vivid::DrawTexture("data\\abe.png", m_Draw_Pos,0xff00ffff);

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
		"y:" + std::to_string(m_Draw_Pos.y), { 0.0f,40.f },0xff0000ff);
#endif
}

