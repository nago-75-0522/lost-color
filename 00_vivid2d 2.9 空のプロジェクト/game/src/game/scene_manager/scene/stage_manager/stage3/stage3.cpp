#include"vivid.h"
#include "stage3.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"
#include"../../../../object/player_manager/player_manager.h"

const int CStage3::m_win_color_size = 64;
const int CStage3::m_chara_count = 4;
const int CStage3::m_move_start_time = 2 * 60; //2秒

CStage3& CStage3::GetInstance()
{
	static CStage3 instance;
	return instance;

}

CStage3::CStage3()
	: m_Win_Color_Pos(vivid::Vector2::ZERO)
	, m_Win_Color_Velocity(vivid::Vector2::ZERO)
	, m_Move_Start_Timer(0)
	, m_Added(false)
	, m_Race_State(RACE_STATE::PRESENTATION)
{
}

void CStage3::Initialize(void)
{
	CMinigame_Manager::GetInstance().SetGame(MINIGAME_ID::RACE);
	CMinigame_Manager::GetInstance().Initialize();
	CPlayer_Manager::GetInstance().Initialize();

	m_Win_Color_Pos.x = vivid::WINDOW_WIDTH / 2 - m_win_color_size * m_chara_count / 2;
	m_Win_Color_Pos.y = vivid::WINDOW_HEIGHT / 2 - m_win_color_size / 2;
	m_Win_Color_Velocity = { 0.0f,0.0f };

	m_Move_Start_Timer = m_move_start_time;
	m_Phase.Initialize();
	m_Added = false;

	m_Race_State = RACE_STATE::PRESENTATION;
}

void CStage3::Update(void)
{
	switch (m_Race_State)
	{
	case RACE_STATE::PRESENTATION:
		Presentation();
		break;

	case RACE_STATE::MAIN:
		m_Phase.Update();

		if (m_Phase.Get_Game_State() == CPhase::GAME_STATE::MAIN)
		{
			CMinigame_Manager::GetInstance().Update();
			CPlayer_Manager::GetInstance().Update();

			if (CPlayer_Manager::GetInstance().GameFinish())
			{
				if (!m_Added)
				{
					CSceneManager::GetInstance().AddStageCount();
					m_Added = true;
				}
				m_Phase.Get_Game_State() = CPhase::GAME_STATE::FINISH;
			}
		}
		break;
	}
}

void CStage3::Draw(void)
{
	CMinigame_Manager::GetInstance().Draw();
	CPlayer_Manager::GetInstance().Draw();
	//vivid::DrawText(48, "stage3", { 0.0f,0.0f });

	vivid::Rect rect;

	rect.left = CMinigame_Manager::GetInstance().GetRaceWinColor() * m_win_color_size;
	rect.right = rect.left + m_win_color_size;
	rect.top = 0;
	rect.bottom = m_win_color_size;

	vivid::DrawTexture("data\\win_color.png", m_Win_Color_Pos, 0xffffffff, rect); //当たりの色表示
	vivid::DrawText(64, "select", { m_Win_Color_Pos.x + m_win_color_size,m_Win_Color_Pos.y }, 0xff000000);

	if (m_Race_State == RACE_STATE::MAIN)
		m_Phase.Draw();

}

void CStage3::Finalize(void)
{
}

void CStage3::Presentation(void)
{
	const float MOVE_SPEED = 4.f; //動く速さ
	const float STOP_POS_Y = 64.f; //止まる場所

	if (--m_Move_Start_Timer <= 0)
	{
		m_Move_Start_Timer = 0;
		m_Win_Color_Velocity.y = MOVE_SPEED;

		if (m_Win_Color_Pos.y > STOP_POS_Y)
			m_Win_Color_Pos.y -= m_Win_Color_Velocity.y;
		else
			m_Race_State = RACE_STATE::MAIN;
	}
}


