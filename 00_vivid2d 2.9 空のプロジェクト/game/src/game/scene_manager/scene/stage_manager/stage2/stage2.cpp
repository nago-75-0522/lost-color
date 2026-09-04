#include"vivid.h"
#include "stage2.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"
#include"../../../../object/minigame_manager/ball_manager/ball_score/ball_score.h"
#include"../../../../object/player_manager/player_manager.h"

CStage2& CStage2::GetInstance()
{
	static CStage2 instance;
	return instance;

}

CStage2::CStage2()
	: m_State(STAGE2_STATE::MAIN)
	, m_ResultTimer(0)
	, m_Winner(false)
	, m_Draw(false)
{
}

void CStage2::Initialize(void)
{
	CMinigame_Manager::GetInstance().SetGame(MINIGAME_ID::BALL);
	m_State = STAGE2_STATE::MAIN;
	m_ResultTimer = 0;
	m_Winner = false;
	m_Draw = false;
	m_ball_timer.Initialize();
	CMinigame_Manager::GetInstance().Initialize();
	CPlayer_Manager::GetInstance().Initialize();

	vivid::LoadSound("data\\sound\\BALL_BGM.wav");
	vivid::PlaySound("data\\sound\\BALL_BGM.wav", true);
}

void CStage2::Update(void)
{
	switch (m_State)
	{
	case STAGE2_STATE::MAIN:
		m_ResultTimer = 0;
		m_ball_timer.Update();
		CMinigame_Manager::GetInstance().Update();
		CPlayer_Manager::GetInstance().Update();

		if (m_ball_timer.IsTimeUp())
		{
			if (CBallScore::GetInstance().GetPlayer1Score() == CBallScore::GetInstance().GetPlayer2Score())
				m_Draw = true;
			else if (CBallScore::GetInstance().GetPlayer1Score() > CBallScore::GetInstance().GetPlayer2Score())
				m_Winner = true;
			else if (CBallScore::GetInstance().GetPlayer1Score() < CBallScore::GetInstance().GetPlayer2Score())
				m_Winner = false;
			vivid::StopSound("data\\sound\\BALL_BGM.wav");
			m_State = STAGE2_STATE::RESULT;
			
		}
		break;

	case STAGE2_STATE::RESULT:
		++m_ResultTimer;
		if (m_ResultTimer >= 120
			|| vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE)
			|| vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B)
			|| vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
		{
			vivid::DrawText(100, "ClearCount +1", { 0,50 });
			CSceneManager::GetInstance().AddStageCount();
			CPlayer_Manager::GetInstance().Update();
			CSceneManager::GetInstance().Change(SCENE_ID::GAMERISULT);
		}
		break;
	}

#if 0
	// デバッグ用：Dキーでクリア回数を+1
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		CSceneManager::GetInstance().AddStageCount();
	}
#endif
	
}

void CStage2::Draw(void)
{
	if (m_State == STAGE2_STATE::MAIN)
	{
		CMinigame_Manager::GetInstance().Draw();
		CPlayer_Manager::GetInstance().Draw();
		m_ball_timer.Draw();
	}
	else
	{
		//1p
		CBall::BALL_COLOR color1 = CBall::GetInstance().GetPlayer1Color();
		if (color1 == CBall::BALL_COLOR::MAGENTA) {
			vivid::DrawTexture("data\\logo\\pink1(大).png", { 320.0f, 20.0f });
		}
		else {
			vivid::DrawTexture("data\\logo\\yellow1(大).png", { 320.0f, 20.0f });
		}
		//p2
		CBall::BALL_COLOR color2 = CBall::GetInstance().GetPlayer2Color();
		if (color2 == CBall::BALL_COLOR::CYAN) {
			vivid::DrawTexture("data\\logo\\blue2(大).png", { 900.0f, 20.0f });
		}
		else {
			vivid::DrawTexture("data\\logo\\yellow2(大).png", { 900.0f, 20.0f });
		}

		// 総得点
		vivid::DrawText(50, "総得点", { 50.0f,170.0f });
		CBallScore::GetInstance().Draw({ 320.0f,100.0f }, CBallScore::GetInstance().GetPlayer1Score());
		CBallScore::GetInstance().Draw({ 900.0f,100.0f }, CBallScore::GetInstance().GetPlayer2Score());

		// マゼンタ
		vivid::DrawTexture("data\\ball\\ball.png", { 50.0f, 320.0f }, 0xFFFF00FF);
		CBallScore::GetInstance().Draw({ 360.0f,250.0f }, CBallScore::GetInstance().GetPlayer1Magenta());
		CBallScore::GetInstance().Draw({ 930.0f,250.0f }, CBallScore::GetInstance().GetPlayer2Magenta());

		// シアン
		vivid::DrawTexture("data\\ball\\ball.png", { 50.0f, 470.0f }, 0xFF00FFFF);
		CBallScore::GetInstance().Draw({ 360.0f,400.0f }, CBallScore::GetInstance().GetPlayer1Cyan());
		CBallScore::GetInstance().Draw({ 930.0f,400.0f }, CBallScore::GetInstance().GetPlayer2Cyan());

		// イエロー
		vivid::DrawTexture("data\\ball\\ball.png", { 50.0f, 620.0f }, 0xFFFFFF00);
		CBallScore::GetInstance().Draw({ 360.0f,550.0f }, CBallScore::GetInstance().GetPlayer1Yellow());
		CBallScore::GetInstance().Draw({ 930.0f,550.0f }, CBallScore::GetInstance().GetPlayer2Yellow());
	}
}

void CStage2::Finalize(void)
{
}

bool CStage2::GetWinner()
{
	return m_Winner;
}

bool CStage2::GetDraw()
{
	return m_Draw;
}

void CStage2::RisultIni()
{
	m_Winner=false;
	m_Draw = false;
}
