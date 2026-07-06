/* キャラクター説明 接続
	プレイヤーの表示
*/
#include"option.h"
#include"..\..\scene_manager.h"
#include"vivid.h"

//コンストラクタ
COption::COption()
{
}

//初期化
void COption::Initialize(void)
{
	
}

//更新
void COption::Update(void)
{
	
	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{

		CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	}
}

//描画
void COption::Draw(void)
{
	vivid::DrawText(48, "option", { 0.0f,0.0f });
}

//解放
void COption::Finalize(void)
{
}


