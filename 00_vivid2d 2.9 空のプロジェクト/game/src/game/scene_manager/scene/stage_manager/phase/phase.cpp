#include "phase.h"
#include"../../../scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"

const int CPhase::m_start_time = 60 * 3;
const vivid::Vector2 CPhase::m_logo_pos = { 300.0f,400.0f };
const vivid::Vector2 CPhase::m_number_pos = { 300.0f,400.0f };
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
		if (m_Start_Timer < 0)
			vivid::DrawTexture("data/finish.png", m_logo_pos, m_color);
	}

	if (m_Game_State != GAME_STATE::START)
		return;

	int count = m_Start_Timer / 60;

	if (count > 0)
	{
		vivid::Rect rect;
		rect.left = count * m_digit_width;
		rect.right = rect.left + m_digit_width;
		rect.top = 0;
		rect.bottom = m_digit_height;

		vivid::DrawTexture("data/number.png", m_number_pos, m_color, rect);
	}
	else if (count <= 0)
	{
		vivid::DrawTexture("data/start.png", m_logo_pos, m_color);
	}
}

void CPhase::Finalize()
{
}