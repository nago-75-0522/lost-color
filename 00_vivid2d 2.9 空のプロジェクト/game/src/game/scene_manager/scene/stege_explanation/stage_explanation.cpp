#include "stage_explanation.h"
#include"..\stage_select\stage_select.h"
#include"vivid.h"
#include"..\..\scene_manager.h"


//インスタンスの取得
CStage_Explanation& CStage_Explanation::GetInstance()
{
	static CStage_Explanation instance;
	return instance;

}

CStage_Explanation::CStage_Explanation(void)
{
}

//初期化
void CStage_Explanation::Initialize(void)
{
}

//更新
void CStage_Explanation::Update(void)
{
	//呼び出し
	BackChengeScene();
	NextChangeScene();
}

//描画
void CStage_Explanation::Draw(void)
{
	//保存したIDの取得
	STAGE_ID stageid = CStage_Select::GetInstance().GetStageID();

	switch (stageid)
	{
	case STAGE_ID::STAGE1:
		vivid::DrawText(48, "説明1", { 0.0f,0.0f });
		break;

	case STAGE_ID::STAGE2:
		vivid::DrawText(48, "説明2", { 0.0f,0.0f });
		break;


	case STAGE_ID::STAGE3:
		vivid::DrawText(48, "説明3", { 0.0f,0.0f });
		break;

	

	default:
		break;
	}

}


//解放
void CStage_Explanation::Finalize(void)
{
}

//進む処理
void CStage_Explanation::NextChangeScene(void)
{
	/* キーボード用 */
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
	{
		//カラーセレクトに行く
		CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
	}

	/* コントローラー用 */
	if(vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B)||
		vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
	{
		//カラーセレクトに行く
		CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
	}
	
}

//戻る処理
void CStage_Explanation::BackChengeScene(void)
{

	/* コントローラー用 */
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A) ||
		vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::A))
	{
		//ステージセレクトに行く
		CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
	}

	/* キーボード用 */
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::UP))
	{
		//カラーセレクトに行く
		CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
	}


}

