#include"vivid.h"
#include "stage3.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"
#include"../../../../object/player_manager/player_manager.h"


CStage3& CStage3::GetInstance()
{
	static CStage3 instance;
	return instance;

}

CStage3::CStage3()
{

}
void CStage3::Initialize(void)
{
	CMinigame_Manager::GetInstance().SetGame(MINIGAME_ID::RACE);
	CMinigame_Manager::GetInstance().Initialize();
	CPlayer_Manager::GetInstance().Initialize();
}

void CStage3::Update(void)
{
	CMinigame_Manager::GetInstance().Update();
	CPlayer_Manager::GetInstance().Update();

#if 0
	//デバッグ用：Dキーでクリア回数を+1
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		CSceneManager::GetInstance().AddStageCount();

		vivid::DrawText(100, "ClearCount +1", { 0,50 });
	}
#endif

	if (CPlayer_Manager::GetInstance().GameFinish())
	{
		CSceneManager::GetInstance().AddStageCount();
		CSceneManager::GetInstance().Change(SCENE_ID::GAMERISULT);
	}
}

void CStage3::Draw(void)
{
	CMinigame_Manager::GetInstance().Draw();
	CPlayer_Manager::GetInstance().Draw();
	vivid::DrawText(48, "stage3", { 0.0f,0.0f });
}

void CStage3::Finalize(void)
{
}

