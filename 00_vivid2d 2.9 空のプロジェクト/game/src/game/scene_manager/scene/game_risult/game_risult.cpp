#include "game_risult.h"
#include"../../scene_manager.h"
#include"../../../object/player_manager/player_manager.h"
#include"../color_select/color_select.h"

	const int CGame_Result::m_max_score=999999999;//最大スコア
	const int CGame_Result::m_max_score_digiit=9;//表示桁数
	const int CGame_Result::m_digit_width=32;
	const int CGame_Result::m_digit_height=48;

CGame_Result::CGame_Result()
	:m_Player1_Ready(false)
	,m_Player2_Ready(false)
	, m_ScoreAdded (false)
	,m_Player1_Score(0)
	,m_Player2_Score(0)
{
}

void CGame_Result::Initialize()
{
	m_Player1_Ready = false;
	m_Player2_Ready = false;
	m_Player1_Score_Pos = { 200,300 };
	m_Player2_Score_Pos = {680,300};
	m_ScoreAdded = false;


}

void CGame_Result::Update()
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	

	
	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B)||
		keyboard::Trigger(keyboard::KEY_ID::S))
		m_Player1_Ready = true;
	if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::B) || 
		keyboard::Trigger(keyboard::KEY_ID::DOWN))
		m_Player2_Ready = true;

	if (m_Player1_Ready && m_Player2_Ready &&
		CSceneManager::GetInstance().FinishStage() >= 3)
		CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
	else if (m_Player1_Ready && m_Player2_Ready)
	{
		CColor_Select::GetInstance().IniColor();
		CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	}
	
	if (CPlayer_Manager::GetInstance().Player1_Win() == true&&!CPlayer_Manager::GetInstance().Draw_Battle())
	{
		if (!CColor_Select::GetInstance().GetCyan() &&
			!CColor_Select::GetInstance().GetYellow() &&
			!CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player1_Score += 30;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan() && !CColor_Select::GetInstance().GetYellow())
		{
			if (m_ScoreAdded)return;
			m_Player1_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan() && !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player1_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetYellow() && !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player1_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan()
			|| !CColor_Select::GetInstance().GetYellow()
			|| !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player1_Score += 10;
			m_ScoreAdded = true;

		}
	}
	if (CPlayer_Manager::GetInstance().Player1_Win() == false&&!CPlayer_Manager::GetInstance().Draw_Battle())
	{
		if (!CColor_Select::GetInstance().GetCyan() &&
			!CColor_Select::GetInstance().GetYellow() &&
			!CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player2_Score += 30;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan() && !CColor_Select::GetInstance().GetYellow())
		{
			if (m_ScoreAdded)return;
			m_Player2_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan() && !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player2_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetYellow() && !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player2_Score += 20;
			m_ScoreAdded = true;
		}
		else if (!CColor_Select::GetInstance().GetCyan()
			|| !CColor_Select::GetInstance().GetYellow()
			|| !CColor_Select::GetInstance().GetMagenta())
		{
			if (m_ScoreAdded)return;
			m_Player2_Score += 10;
			m_ScoreAdded = true;

		}
	}
	
}

void CGame_Result::Draw()
{
	vivid::DrawText(40, "1P", vivid::Vector2{ 300,250 });
	vivid::DrawText(40, "2P", vivid::Vector2{ 780,250 });

	if (CPlayer_Manager::GetInstance().Draw_Battle())
		vivid::DrawText(40, "DRAW", vivid::Vector2{ vivid::WINDOW_WIDTH * 0.5,vivid::WINDOW_HEIGHT * 0.5 });
	 else if (CPlayer_Manager::GetInstance().Player1_Win())
		vivid::DrawText(40,"WIN", vivid::Vector2{ 350,250 });
	 else if(!CPlayer_Manager::GetInstance().Player1_Win())
		vivid::DrawText(40,"WIN", vivid::Vector2{830,250 });

	if (m_Player1_Ready)
		vivid::DrawText(40, "1POK", vivid::Vector2{ 350,350 });
	if (m_Player2_Ready)
		vivid::DrawText(40, "2POK", vivid::Vector2{ 830,350 });
	

	// 1P
	{
		m_Player1_Copy_Score = m_Player1_Score;
		int digit_count = 1;

		do
		{
			int digit = m_Player1_Copy_Score % 10;

			vivid::Rect rect;
			rect.left = digit * m_digit_width;
			rect.right = rect.left + m_digit_width;
			rect.top = 0;
			rect.bottom = m_digit_height;

			vivid::Vector2 pos;
			pos.x = m_Player1_Score_Pos.x +
				m_digit_width * (m_max_score_digiit - digit_count);
			pos.y = m_Player1_Score_Pos.y;

			vivid::DrawTexture("data/number.png", pos, 0xffffffff, rect);

			m_Player1_Copy_Score /= 10;
			++digit_count;

		} while (m_Player1_Copy_Score > 0 && digit_count <= m_max_score_digiit);
	}

	// 2P
	{
		 m_Player2_Copy_Score = m_Player2_Score;
		int digit_count = 1;

		do
		{
			int digit = m_Player2_Copy_Score % 10;

			vivid::Rect rect;
			rect.left = digit * m_digit_width;
			rect.right = rect.left + m_digit_width;
			rect.top = 0;
			rect.bottom = m_digit_height;

			vivid::Vector2 pos;
			pos.x = m_Player2_Score_Pos.x +
				m_digit_width * (m_max_score_digiit - digit_count);
			pos.y = m_Player2_Score_Pos.y;

			vivid::DrawTexture("data/number.png", pos, 0xffffffff, rect);

			m_Player2_Copy_Score /= 10;
			++digit_count;

		} while (m_Player2_Copy_Score > 0 && digit_count <= m_max_score_digiit);
	}
	
	
}

void CGame_Result::Finalize()
{
}

void CGame_Result::IniScore()
{
	m_Player1_Score = 0;
	m_Player2_Score = 0;
}

CGame_Result& CGame_Result::GetInstance()
{
	static CGame_Result instance;
	return instance;
}
