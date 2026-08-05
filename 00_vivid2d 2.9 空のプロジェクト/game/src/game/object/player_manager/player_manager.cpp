#include "player_manager.h"
#include"../../scene_manager/scene/stage/stage2/stage2.h"
#include"../minigame_manager/minigame_manager.h"
CPlayer_Manager::CPlayer_Manager()
	:m_Player1_Win(false)
	,m_Draw(false)
{
}
void CPlayer_Manager::Initialize()
{
	vivid::LoadSound("data\\sound\\fall.wav");
	CPlayer1_Character::GetInstance().Initialize();
	CPlayer2_Character::GetInstance().Initialize();
	
	m_Draw = false;
}

void CPlayer_Manager::Update()
{
	if (CMinigame_Manager::GetInstance().GetGame() == MINIGAME_ID::FALL)
	{
		CPlayer1_Character::GetInstance().Update();
		CPlayer2_Character::GetInstance().Update();
	}
	if (CPlayer1_Character::GetInstance().GetScale().x <= 0 &&
		CPlayer2_Character::GetInstance().GetScale().x <= 0 ||
		CStage2::GetInstance().GetDraw()==true)
	{
		m_Draw = true;
	}
	else if (CPlayer2_Character::GetInstance().GetScale().x <= 0||
		CStage2::GetInstance().GetWinner()==true)
	{
		m_Player1_Win = true;
	}
	else if (CPlayer1_Character::GetInstance().GetScale().x <= 0||
		CStage2::GetInstance().GetWinner() == false)
	{
		m_Player1_Win = false;
	}
}

void CPlayer_Manager::Draw()
{
	if (CMinigame_Manager::GetInstance().GetGame() == MINIGAME_ID::FALL)
	{
		CPlayer1_Character::GetInstance().Draw();
		CPlayer2_Character::GetInstance().Draw();
	}
}

void CPlayer_Manager::Finalize()
{
	if (CMinigame_Manager::GetInstance().GetGame() == MINIGAME_ID::FALL)
	{
		CPlayer1_Character::GetInstance().Finalize();
		CPlayer2_Character::GetInstance().Finalize();
	}
}

CPlayer_Manager& CPlayer_Manager::GetInstance()
{
	static CPlayer_Manager instance;
	return instance;
}


