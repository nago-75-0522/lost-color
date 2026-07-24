#include"vivid.h"
#include "stage2.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"


CStage2& CStage2::GetInstance()
{
	static CStage2 instance;
	return instance;

}
CStage2::CStage2()
{

}
void CStage2::Initialize(void)
{
	m_ball_timer.Initialize();
	CMinigame_Manager::GetInstance().SetGame(MINIGAME_ID::BALL);
	CMinigame_Manager::GetInstance().Initialize();
}

void CStage2::Update(void)
{
	m_ball_timer.Update();
	CMinigame_Manager::GetInstance().Update();

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

		CSceneManager::GetInstance().AddStageCount();

		//4回目からリザルト
		if (CSceneManager::GetInstance().FinishStage() >= 3)
		{
			CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
		}
		else//達成してなければステージ選択
		{

			CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
		}

	}
	//コントローラー用
	if (m_ball_timer.IsTimeUp())
	{
		CSceneManager::GetInstance().AddStageCount();

		//4回目からリザルト
		if (CSceneManager::GetInstance().FinishStage() >= 3)
		{
			CSceneManager::GetInstance().Change(SCENE_ID::RESULT);
		}
		else//達成してなければステージ選択
		{

			CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
		}
	}
}

void CStage2::Draw(void)
{
	m_ball_timer.Draw();
	CMinigame_Manager::GetInstance().Draw();

	vivid::DrawText(48, "stage2", { 0.0f,0.0f });
}

void CStage2::Finalize(void)
{
}

