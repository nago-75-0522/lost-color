#include"vivid.h"
#include "stage1.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"
#include"../../../../object/player_manager/player_manager.h"
#include"../../../../object/player_manager/player1/player1.h"
#include"../../../../object/player_manager/player2/player2.h"
CStage1& CStage1::GetInstance()
{
	static CStage1 instance;
	return instance;

}

CStage1::CStage1()
{

}

void CStage1::Initialize(void)
{
	CMinigame_Manager::GetInstance().Initialize();
	CPlayer_Manager::GetInstance().Initialize();
}

void CStage1::Update(void)
{
	CMinigame_Manager::GetInstance().Update();
	CPlayer_Manager::GetInstance().Update();

#if 0
	// デバッグ用：Dキーでクリア回数を+1
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		CSceneManager::GetInstance().AddStageCount();

		vivid::DrawText(100, "ClearCount +1", { 0,50 });
	}
#endif

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{

#if 1
		//CSceneManager::GetInstance().AddStageCount();//加算
		//4回目からリザルト
		if (CSceneManager::GetInstance().FinishStage() >= 3)
		{
			CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
		}
		else//達成してなければステージ選択
		{
			CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
		}

#endif 

	}
	//コントローラー用
	if (CPlayer2_Character::GetInstance().GetScale().x <= 0 || CPlayer1_Character::GetInstance().GetScale().x <= 0)
	{
		CSceneManager::GetInstance().AddStageCount();

		vivid::DrawText(100, "ClearCount +1", { 0,50 });
		//4回目からリザルト
		if (CSceneManager::GetInstance().FinishStage() >= 3)
		{
			CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
		}
		else//達成してなければステージ選択
		{
			CSceneManager::GetInstance().Change(SCENE_ID::GAMERISULT);
		}
	}
}

void CStage1::Draw(void)
{
	CMinigame_Manager::GetInstance().Draw();
	CPlayer_Manager::GetInstance().Draw();
	vivid::DrawText(48, "stage1", { 0.0f,0.0f });
}

void CStage1::Finalize(void)
{
}

