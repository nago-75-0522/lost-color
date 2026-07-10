#include"title.h"
#include"..\..\scene_manager.h"
#include"vivid.h"


CTitle::CTitle()
{
}

void CTitle::Initialize(void)
{
	
}

void CTitle::Update(void)
{
	CSceneManager::GetInstance().ResetStageCount();//カウントリセット
	
	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);
	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);
	}
}

void CTitle::Draw(void)
{
	vivid::DrawText(48, "title", { 0.0f,0.0f });
	vivid::DrawTexture("data\\title_lf.png", {100,vivid::WINDOW_HEIGHT * 1 / 5 });
}

void CTitle::Finalize(void)
{
}


