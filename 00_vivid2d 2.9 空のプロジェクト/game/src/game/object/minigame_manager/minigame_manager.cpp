#include "minigame_manager.h"
#include"fall/fall.h"
CMinigame_Manager::CMinigame_Manager()
{
}

void CMinigame_Manager::Initialize()
{
	CFall::GetInstance().Initialize();
}

void CMinigame_Manager::Update()
{
	CFall::GetInstance().Update();
}

void CMinigame_Manager::Draw()
{
	CFall::GetInstance().Draw();
}

void CMinigame_Manager::Finalize()
{
	CFall::GetInstance().Finalize();
}

CMinigame_Manager& CMinigame_Manager::GetInstance()
{
	static CMinigame_Manager instance;
	return instance;
}
