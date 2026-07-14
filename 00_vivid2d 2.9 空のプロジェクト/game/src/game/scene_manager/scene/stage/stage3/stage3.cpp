#include"vivid.h"
#include "stage3.h"
#include"..\..\..\scene_manager.h"


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

}

void CStage3::Update(void)
{

	//CSceneManager::GetInstance().AddStageCount();//加算

	//デバッグ用：Dキーでクリア回数を+1
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		CSceneManager::GetInstance().AddStageCount();

		vivid::DrawText(100, "ClearCount +1", { 0,50 });
	}

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{

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
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
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

void CStage3::Draw(void)
{
	vivid::DrawText(48, "stage3", { 0.0f,0.0f });
}

void CStage3::Finalize(void)
{
}

