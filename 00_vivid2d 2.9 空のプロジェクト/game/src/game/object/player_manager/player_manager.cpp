#include "player_manager.h"
#include"../minigame_manager/minigame_manager.h"
#include"fall_player_mana/fall_player_mana.h"
#include"ball_player_mana/ball_player_mana.h"
#include"race_player_mana/race_player_mana.h"
#include"../../scene_manager/scene/stage_manager/stage2/stage2.h"

CPlayer_Manager::CPlayer_Manager()
{
}

void CPlayer_Manager::Initialize()
{
	switch (CMinigame_Manager::GetInstance().GetGame())
	{
	case MINIGAME_ID::FALL:
		CFall_Player_Manager::GetInstance().Initialize();
		break;
	case MINIGAME_ID::BALL:
		CBall_Player_Manager::GetInstance().Initialize();
		break;
	case MINIGAME_ID::RACE:
		CRace_Player_Manager::GetInstance().Initialize();
		break;
	}
}

void CPlayer_Manager::Update()
{
	switch (CMinigame_Manager::GetInstance().GetGame())
	{
	case MINIGAME_ID::FALL:
		CFall_Player_Manager::GetInstance().Update();
		break;
	case MINIGAME_ID::BALL:
		CBall_Player_Manager::GetInstance().Update();
		break;
	case MINIGAME_ID::RACE:
		CRace_Player_Manager::GetInstance().Update();
		break;
	}

	if (CFall_Player_Manager::GetInstance().isFallDraw() ||
		CStage2::GetInstance().GetDraw() == true ||
		CRace_Player_Manager::GetInstance().isRaceWinner() == 3)
	{
		m_Draw = true;
	}
	else if (CFall_Player_Manager::GetInstance().isFallPlayer1Win() ||
		CStage2::GetInstance().GetWinner() == true ||
		CRace_Player_Manager::GetInstance().isRaceWinner() == 1)
	{
		m_Player1_Win = true;
	}
	else if (!CFall_Player_Manager::GetInstance().isFallPlayer1Win() ||
		CStage2::GetInstance().GetWinner() == false ||
		CRace_Player_Manager::GetInstance().isRaceWinner() == 2)
	{
		m_Player1_Win = false;
	}
}

void CPlayer_Manager::Draw()
{
	switch (CMinigame_Manager::GetInstance().GetGame())
	{
	case MINIGAME_ID::FALL:
		CFall_Player_Manager::GetInstance().Draw();
		break;
	case MINIGAME_ID::BALL:
		CBall_Player_Manager::GetInstance().Draw();
		break;
	case MINIGAME_ID::RACE:
		CRace_Player_Manager::GetInstance().Draw();
		break;
	}

}

void CPlayer_Manager::Finalize()
{
	switch (CMinigame_Manager::GetInstance().GetGame())
	{
	case MINIGAME_ID::FALL:
		CFall_Player_Manager::GetInstance().Finalize();
		break;
	case MINIGAME_ID::BALL:
		CBall_Player_Manager::GetInstance().Finalize();
		break;
	case MINIGAME_ID::RACE:
		CRace_Player_Manager::GetInstance().Finalize();
		break;
	}

}



bool CPlayer_Manager::GameFinish()
{
	switch (CMinigame_Manager::GetInstance().GetGame())
	{
	case MINIGAME_ID::FALL:
		break;
	case MINIGAME_ID::BALL:
		break;
	case MINIGAME_ID::RACE:
		return CRace_Player_Manager::GetInstance().isFinish();
		break;
	}
}

CPlayer_Manager& CPlayer_Manager::GetInstance()
{
	static CPlayer_Manager instance;
	return instance;
}


