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
	vivid::DrawTexture("data\\abe.png", { 0.0f,0.0f });
}

void CTitle::Finalize(void)
{
}


