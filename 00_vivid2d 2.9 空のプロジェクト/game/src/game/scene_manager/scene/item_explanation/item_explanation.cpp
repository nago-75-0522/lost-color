#include "item_explanation.h"
#include"..\stage_select\stage_select.h"
#include"vivid.h"
#include"..\..\scene_manager.h"
#include"..\..\..\object\player_manager\player_manager.h"
#include"..\color_select\color_select.h"
#include"..\..\scene_manager.h"


//インスタンスの取得
CItem_Explanation& CItem_Explanation::GetInstance()
{
	static CItem_Explanation instance;
	return instance;

}

//コンストラクタ
CItem_Explanation::CItem_Explanation(void)
{

}

//初期化
void CItem_Explanation::Initialize(void)
{
	CItem_Explanation::m_StageCount = CSceneManager::GetInstance().FinishStage();

	//保存したIDの取得
	STAGE_ID stageid = CStage_Select::GetInstance().GetStageID();

	switch (stageid)
	{
	case STAGE_ID::STAGE1:
		m_Item_Path = "data\\explanation\\fall_item_ex.png";
		m_Glaph_Handle = LoadGraph("data\\move\\fall_item.mp4");	//説明動画のダウンロード
		PlayMovieToGraph(m_Glaph_Handle);							//動画再生


		break;



	case STAGE_ID::STAGE2:
		m_Item_Path = "data\\explanation\\ball_ex2.png";
		m_Glaph_Handle = LoadGraph("data\\move\\ball_item.mp4");	//説明動画のダウンロード
		PlayMovieToGraph(m_Glaph_Handle);							//動画再生

		break;

	default:
		break;
	}
}

//更新
void CItem_Explanation::Update(void)
{
	if (m_Glaph_Handle != -1)
	{
		if (GetMovieStateToGraph(m_Glaph_Handle) == 0)
		{
			SeekMovieToGraph(m_Glaph_Handle, 0);
			PlayMovieToGraph(m_Glaph_Handle);
		}
	}

	//呼び出し
	BackChengeScene();
	NextChangeScene();

}

//描画
void CItem_Explanation::Draw(void)
{
	
	vivid::DrawTexture(m_Item_Path, vivid::Vector2::ZERO);
	DrawExtendGraph(690, 200, 1251, 654, m_Glaph_Handle, true);
}


//解放
void CItem_Explanation::Finalize(void)
{
}


//進む処理
void CItem_Explanation::NextChangeScene(void)
{
	//ステージ回数によって処理を変える
	if (m_StageCount == 0)//一回目
	{
		/* キーボード用 */
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
		{
			//カラーセレクトに行く
			CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
		}

		/* コントローラー用 */
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B)) //||vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
		{
			//カラーセレクトに行く
			CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);

		}
	}

	//二回以上の時
	else if (m_StageCount >= 1)
	{

		//プレイヤー1が勝ったのでプレイヤー2が操作
		if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		{
			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

		}
		else//プレイヤー1が捜査
		{
			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			}
		}
	}

}


//戻る処理
void CItem_Explanation::BackChengeScene(void)
{
	//ステージ回数によって処理を変える
	if (m_StageCount == 0)//一回目
	{
		/* キーボード用 */
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W) || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::UP))
		{
			//カラーセレクトに行く
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}

		/* コントローラー用 */
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A)) //||vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
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
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::A))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}

		}
		else//プレイヤー1が捜査
		{
			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))
			{
				//ステージ説明
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_EXPLANATION);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A))
			{
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_EXPLANATION);
			}
		}
	}

}

