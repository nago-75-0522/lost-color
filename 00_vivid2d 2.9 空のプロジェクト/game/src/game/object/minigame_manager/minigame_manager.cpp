#include "minigame_manager.h"


CMinigame_Manager::CMinigame_Manager()
{
}

void CMinigame_Manager::Initialize()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: 
		CFall::GetInstance().Initialize(); 
		break;
	case MINIGAME_ID::BALL: 
		CBallManager::GetInstance().Initialize(); 
		break;
	case MINIGAME_ID::RACE:
		CRace_Manager::GetInstance().Initialize();
		break;
	}
}

void CMinigame_Manager::Update()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: 
		CFall::GetInstance().Update();
		break;
	case MINIGAME_ID::BALL: 
		CBallManager::GetInstance().Update(); 
		break;
	case MINIGAME_ID::RACE:
		CRace_Manager::GetInstance().Update();
		break;
	}
}

void CMinigame_Manager::Draw()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: 
		CFall::GetInstance().Draw(); 
		break;
	case MINIGAME_ID::BALL: 
		CBallManager::GetInstance().Draw(); 
		break;
	case MINIGAME_ID::RACE:
		CRace_Manager::GetInstance().Draw();
		break;

	}
}

void CMinigame_Manager::Finalize()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: 
		CFall::GetInstance().Finalize();
		break;
	case MINIGAME_ID::BALL: 
		CBallManager::GetInstance().Finalize(); 
		break;
	case MINIGAME_ID::RACE:
		CRace_Manager::GetInstance().Finalize();
		break;

	}
}

void CMinigame_Manager::SetGame(MINIGAME_ID game)
{
	m_Game = game;
}

MINIGAME_ID CMinigame_Manager::GetGame()
{
	return m_Game;
}

CMinigame_Manager& CMinigame_Manager::GetInstance()
{
	static CMinigame_Manager instance;
	return instance;
}

int CMinigame_Manager::GetRaceWinColor(void)
{
	if (m_Game == MINIGAME_ID::RACE)
		return CRace_Manager::GetInstance().GetWinColor();
}
