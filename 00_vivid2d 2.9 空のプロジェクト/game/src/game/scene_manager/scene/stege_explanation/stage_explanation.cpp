#include "stage_explanation.h"
#include"..\stage_select\stage_select.h"
#include"vivid.h"
#include"..\..\scene_manager.h"
#include"..\..\..\object\player_manager\player_manager.h"
#include"..\color_select\color_select.h"
#include"..\..\scene_manager.h"
#include"..\item_explanation\item_explanation.h"


//インスタンスの取得
CStage_Explanation& CStage_Explanation::GetInstance()
{
	static CStage_Explanation instance;
	return instance;

}

//コンストラクタ
CStage_Explanation::CStage_Explanation(void)
{

}

//初期化
void CStage_Explanation::Initialize(void)
{
	CStage_Explanation::m_StageCount = CSceneManager::GetInstance().FinishStage();
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
	//保存したIDの取得
	STAGE_ID stageid = CStage_Select::GetInstance().GetStageID();

	//ステージ回数によって処理を変える
	if (m_StageCount == 0)//一回目
	{

		switch (stageid)
		{
		case STAGE_ID::STAGE1:

			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
				vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}
			break;


		case STAGE_ID::STAGE2:

			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
				vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}
			break;


		case STAGE_ID::STAGE3:

			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
				vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}
			break;


		default:
			break;
		}
		
	}

	//二回以上の時
	else if (m_StageCount >= 1)
	{

		//プレイヤー1が勝ったのでプレイヤー2が操作
		if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		{

			switch (stageid)
			{
			case STAGE_ID::STAGE1:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}
				break;


			case STAGE_ID::STAGE2:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}
				break;


			case STAGE_ID::STAGE3:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				}
				break;
			}
		}
		else//プレイヤー1が捜査
		{

			switch (stageid)
			{
			case STAGE_ID::STAGE1:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}
				break;


			case STAGE_ID::STAGE2:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
				}
				break;


			case STAGE_ID::STAGE3:

				/* キーボード用 */
				if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				}

				/* コントローラー用 */
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B) ||
					vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				}
				break;
			}
		}
	}

}


//戻る処理
void CStage_Explanation::BackChengeScene(void)
{
	//ステージ回数によって処理を変える
	if (m_StageCount == 0)//一回目
	{
		/* キーボード用 */
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::UP))
		{
			//ステージ選択
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}

		/* コントローラー用 */
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A) ||
			vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::A))
		{
			//カラーセレクトに行く
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}
	}

	//二回以上の時
	else if (m_StageCount >= 1)
	{

		//プレイヤー1が勝ったのでプレイヤー2が操作
		if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		{
			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::UP))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::A))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

		}
		else//プレイヤー1が捜査
		{
			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}
		}
	}
}

