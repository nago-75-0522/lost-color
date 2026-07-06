#include"vivid.h"
#include "stage1.h"
#include"..\..\..\scene_manager.h"


CStage1& CStage1::GetInstance()
{
	static CStage1 instance;
	return instance;

}

void CStage1::Initialize(void)
{

}

void CStage1::Update(void)
{

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{

		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);
	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);
	}
}

void CStage1::Draw(void)
{
	vivid::DrawText(48, "stage", { 0.0f,0.0f });
}

void CStage1::Finalize(void)
{
}

