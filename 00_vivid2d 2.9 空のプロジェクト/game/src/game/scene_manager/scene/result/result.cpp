#include"vivid.h"
#include "Result.h"
#include"..\..\scene_manager.h"

//インスタンス取得
CResult& CResult::GetInstance()
{
	static CResult instance;
	return instance;

}

//初期化
void CResult::Initialize(void)
{

}

//更新
void CResult::Update(void)
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

//描画
void CResult::Draw(void)
{
	vivid::DrawTexture("data\\result.png", { 0.0f,0.0f });
	vivid::DrawText(48, "Result", { 0.0f,0.0f });
}

//解放
void CResult::Finalize(void)
{
}

