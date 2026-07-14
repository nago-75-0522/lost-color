#include"title.h"
#include"..\..\scene_manager.h"
#include"vivid.h"
#include"../color_select/color_select.h"

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
		CColor_Select::GetInstance().IniColor();
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);
	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CColor_Select::GetInstance().IniColor();
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);
	}
}

void CTitle::Draw(void)
{
	vivid::DrawText(48, "title", { 0.0f,0.0f });
}

void CTitle::Finalize(void)
{
}

CTitle& CTitle::GetInstance()
{
	static CTitle instace;
	return instace;
}


