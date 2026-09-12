#include "phase.h"
#include"../../../scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"

const int CPhase::m_start_time = 60 * 4 - 1;
const vivid::Vector2 CPhase::m_logo_pos = { vivid::WINDOW_WIDTH / 2 - 300 / 2 ,vivid::WINDOW_HEIGHT / 2 - 200 / 2 };
const vivid::Vector2 CPhase::m_number_pos = { vivid::WINDOW_WIDTH / 2 ,vivid::WINDOW_HEIGHT / 2 };
const unsigned int CPhase::m_color = 0xffffffff;
const int CPhase::m_digit_width = 32;
const int CPhase::m_digit_height = 48;
const int CPhase::m_max_digit = 9;

CPhase::CPhase()
	: m_Game_State(GAME_STATE::START)
	, m_Start_Timer(0)
{
}

void CPhase::Initialize()
{
	m_Game_State = GAME_STATE::START;
	m_Start_Timer = m_start_time;
	vivid::LoadSound("data\\sound\\finish.wav");
	vivid::LoadSound("data\\sound\\start.wav");
	vivid::LoadSound("data\\sound\\countdown.wav");
	m_Old_Count = -1;
	m_PlayFinishSE = false;
}

void CPhase::Update()
{
	if (m_Game_State == GAME_STATE::FINISH)
	{
		++m_Start_Timer;
		CMinigame_Manager& miniM = CMinigame_Manager::GetInstance();

		if (m_Start_Timer >= 0 && miniM.GetGame() != MINIGAME_ID::BALL)
			CSceneManager::GetInstance().Change(SCENE_ID::GAMERISULT);
		else if (m_Start_Timer >= 0 && miniM.GetGame() == MINIGAME_ID::BALL)
			m_Game_State = GAME_STATE::FINISH_FIN;
	}
	else if (m_Start_Timer >= -60)
		--m_Start_Timer;
	if (m_Start_Timer <= -60)
	{
		m_Game_State = GAME_STATE::MAIN;
	}
}

void CPhase::Draw()
{
	if (m_Game_State == GAME_STATE::FINISH)
	{
		if (m_Game_State == GAME_STATE::FINISH)
		{
			if (!m_PlayFinishSE)
			{
				vivid::PlaySound("data\\sound\\finish.wav", false);
				m_PlayFinishSE = true;
			}
		    vivid::DrawTexture("data/logo/finish.png",m_logo_pos,m_color);
		}
	}

	if (m_Game_State != GAME_STATE::START)
		return;

	int count = m_Start_Timer / 60;

	if (count > 0)
	{
		if (count != m_Old_Count)
		{
			vivid::PlaySound("data\\sound\\countdown.wav", false);
			m_Old_Count = count;
		}

		vivid::Rect rect;
		rect.left = count * m_digit_width;
		rect.right = rect.left + m_digit_width;
		rect.top = 0;
		rect.bottom = m_digit_height;
		vivid::DrawTexture("data/logo/number(黒).png", m_number_pos, m_color, rect);
	}
	if (count <= 0)
	{
		if (m_Old_Count != 0)
		{
			vivid::PlaySound("data\\sound\\start.wav", false);
			m_Old_Count = 0;
		}

      vivid::DrawTexture("data/logo/start.png",m_logo_pos,m_color);
	}
}
void CPhase::Finalize()
{
}