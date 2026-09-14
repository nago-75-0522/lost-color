#include "game_risult.h"
#include"../../scene_manager.h"
#include"../../../object/player_manager/player_manager.h"
#include"../color_select/color_select.h"
#include"../stage_manager/stage2/stage2.h"
#include"../../../object/player_manager/fall_player_mana/fall_player_mana.h"
#include"../../../object/player_manager/race_player_mana/race_player_mana.h"
const int CGame_Result::m_max_score = 999999999;//最大スコア
const int CGame_Result::m_max_score_digiit = 9;//表示桁数
const int CGame_Result::m_digit_width = 112;
const int CGame_Result::m_digit_height = 167;
const vivid::Vector2 CGame_Result::m_player1_double_score_pos = { 400.0f,350.0f };
const vivid::Vector2 CGame_Result::m_player2_double_score_pos = { 870.0f,350.0f };

CGame_Result::CGame_Result()
	:m_Player1_Ready(false)
	, m_Player2_Ready(false)
	, m_ScoreAdded(false)
	, m_Player1_Score(0)
	, m_Player2_Score(0)
{
}

void CGame_Result::Initialize()
{
	m_Player1_Ready = false;
	m_Player2_Ready = false;
	m_ScoreAdded = false;
	vivid::LoadSound("data\\sound\\gamerisult.wav");
	vivid::PlaySound("data\\sound\\gamerisult.wav", true);
}

void CGame_Result::Update()
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B) ||
		keyboard::Trigger(keyboard::KEY_ID::S))
		m_Player1_Ready = true;
	if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::B) ||
		keyboard::Trigger(keyboard::KEY_ID::DOWN))
		m_Player2_Ready = true;

	if (m_Player1_Ready && m_Player2_Ready &&
		CSceneManager::GetInstance().FinishStage() >= 4)
		CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
	else if (m_Player1_Ready && m_Player2_Ready)
	{
		CColor_Select::GetInstance().IniColor();
		CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
	}

	if (CPlayer_Manager::GetInstance().Player1_Win() == true && !CPlayer_Manager::GetInstance().Draw_Battle())
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
	if (CPlayer_Manager::GetInstance().Player1_Win() == false && !CPlayer_Manager::GetInstance().Draw_Battle())
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
	vivid::DrawTexture("data\\title_bg2.png", vivid::Vector2(0.0f, 0.0f));
	vivid::DrawTexture("data\\logo\\black.png", vivid::Vector2{ 330,270 });
	vivid::DrawTexture("data\\logo\\black2.png", vivid::Vector2{ 810,270 });
	vivid::DrawTexture("data\\logo\\score1.png", vivid::Vector2{ 0.0f,0.0f }, 0xff000000);
	if (CPlayer_Manager::GetInstance().Draw_Battle())
		vivid::DrawTexture("data\\logo\\Draw1.png", vivid::Vector2{ 470.0f,160.0f });
	else if (CPlayer_Manager::GetInstance().Player1_Win())
		vivid::DrawTexture("data\\logo\\WIN1.png", vivid::Vector2{ 280.0f,190.0f });
	else if (!CPlayer_Manager::GetInstance().Player1_Win())
		vivid::DrawTexture("data\\logo\\WIN1.png", vivid::Vector2{ 760.0f,190.0f });
	if (m_Player1_Ready)
		vivid::DrawTexture("data\\logo\\ok.png", vivid::Vector2{ 300.0f,500.0f });
	if (m_Player2_Ready)
		vivid::DrawTexture("data\\logo\\ok.png", vivid::Vector2{ 780.0f,500.0f });

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
			pos.x = m_player1_double_score_pos.x -
				m_digit_width * (digit_count - 1);
			pos.y = m_player1_double_score_pos.y;

			vivid::DrawTexture("data\\logo\\number(brack).png", pos, 0xffffffff, rect);

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
			pos.x = m_player2_double_score_pos.x -
				m_digit_width * (digit_count - 1);
			pos.y = m_player2_double_score_pos.y;
			vivid::DrawTexture("data\\logo\\number(brack).png", pos, 0xffffffff, rect);

			m_Player2_Copy_Score /= 10;
			++digit_count;

		} while (m_Player2_Copy_Score > 0 && digit_count <= m_max_score_digiit);
	}
}

void CGame_Result::Finalize()
{
	CPlayer_Manager::GetInstance().Initialize();
	CFall_Player_Manager::GetInstance().Initialize();
	CStage2::GetInstance().gameRisIni();
	CRace_Player_Manager::GetInstance().Initialize();
	vivid::StopSound("data\\sound\\gamerisult.wav");
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
