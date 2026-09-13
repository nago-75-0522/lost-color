#include "stage_explanation.h"
#include"..\stage_select\stage_select.h"
#include"vivid.h"
#include"..\..\scene_manager.h"
#include"..\..\..\object\player_manager\player_manager.h"
#include"..\color_select\color_select.h"
#include"..\..\scene_manager.h"
#include"..\item_explanation\item_explanation.h"

const float CStage_Explanation::m_move_pos_x = vivid::WINDOW_WIDTH / 2;
const float CStage_Explanation::m_move_pos_y = vivid::WINDOW_HEIGHT / 2;

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

	//保存したIDの取得
	STAGE_ID stageid = CStage_Select::GetInstance().GetStageID();

	
	//どのステージの動画をロード　スイッチ　画像も　画像は文字列だけ受け取って受け取ってある変数の値で描画
	switch (stageid)
	{
	case STAGE_ID::STAGE1:
		m_glaph_handle = LoadGraph("data\\explanation\\0911.mp4");	//説明動画のダウンロード
		m_explanation_path ="data\\explanation\\stage1ex.png";		//画像の読み込み
		PlayMovieToGraph(m_glaph_handle);							//動画再生
		
		break;

	case STAGE_ID::STAGE2:
		m_glaph_handle = LoadGraph("data\\explanation\\0911.mp4");	//説明動画のダウンロード
		m_explanation_path = "data\\explanation\\stage2ex.png";		//画像の読み込み
		PlayMovieToGraph(m_glaph_handle);							//動画再生
		break;

	case STAGE_ID::STAGE3:
		m_glaph_handle = LoadGraph("data\\explanation\\0911.mp4");	//説明動画のダウンロード
		m_explanation_path = "data\\explanation\\stage1ex.png";		//画像の読み込み
		PlayMovieToGraph(m_glaph_handle);							//動画再生
		break;

	default:
		break;
	}
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

	//描画するだけ 画像と動画　イニシャライズで受け取った値を描画する
	DrawExtendGraph(400, 130, 1280, 620, m_glaph_handle, true);
	vivid::DrawTexture(m_explanation_path, { 0.0f,0.0f });//画像
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
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S)) //|| vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}
			//||(vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))

			break;


		case STAGE_ID::STAGE2:

			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))// || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}


			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::ITEM_EXPLANATION);
			}
			//||(vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
			break;


		case STAGE_ID::STAGE3:

			/* キーボード用 */
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))// || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::DOWN))
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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B))
				{
					//カラーセレクトに行く
					CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				}
				break;
			}
		}

		//プレイヤー1が捜査
		else {

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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
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
				if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
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
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))// || vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::UP))
		{
			//ステージ選択
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}

		/* コントローラー用 */
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A))
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
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}

			/* コントローラー用 */
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::A))
			{
				//カラーセレクトに行く
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}
		}
	}
}

