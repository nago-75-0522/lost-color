#include "minigame_manager.h"
#include"fall/fall.h"
#include"ball_manager/ball_manager.h"

CMinigame_Manager::CMinigame_Manager()
{
}

void CMinigame_Manager::Initialize()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: CFall::GetInstance().Initialize(); break;
	case MINIGAME_ID::BALL: CBallManager::GetInstance().Initialize(); break;
	}
}

void CMinigame_Manager::Update()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: CFall::GetInstance().Update(); break;
	case MINIGAME_ID::BALL: CBallManager::GetInstance().Update(); break;
	}
}

void CMinigame_Manager::Draw()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: CFall::GetInstance().Draw(); break;
	case MINIGAME_ID::BALL: CBallManager::GetInstance().Draw(); break;
	}
}

void CMinigame_Manager::Finalize()
{
	switch (m_Game)
	{
	case MINIGAME_ID::FALL: CFall::GetInstance().Finalize(); break;
	case MINIGAME_ID::BALL: CBallManager::GetInstance().Finalize(); break;
	}
}

void CMinigame_Manager::SetGame(MINIGAME_ID game)
{
	m_Game = game;
}

CMinigame_Manager& CMinigame_Manager::GetInstance()
{
	static CMinigame_Manager instance;
	return instance;
}
