//ステージ選択

#include"gamemain.h"
#include"..\..\scene_manager.h"
#include"..\stage\stage1\stage1.h"



CGamemain& CGamemain::GetInstance()
{
	static CGamemain instance;
	return instance;

}



//初期化
void CGamemain::Initialize(void)
{

}

//更新
void CGamemain::Update(void)
{

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{

		
	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	}
}

//描画
void CGamemain::Draw(void)
{
	vivid::DrawText(48, "gamemain", { 0.0f,0.0f });
}

//解放
void CGamemain::Finalize(void)
{
}

//選択処理
void CGamemain::Selct(void)
{
}


