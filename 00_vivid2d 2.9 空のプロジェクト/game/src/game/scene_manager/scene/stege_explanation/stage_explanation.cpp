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

	
	//どのステージの動画をロードスイッチ画像も画像は文字列だけ受け取って受け取ってある変数の値で描画
	switch (stageid)
	{
	case STAGE_ID::STAGE1:
		m_Explanation_Path = "data\\explanation\\fall_ex.png";		//画像の読み込み
		m_Bg_Path = "data\\stage_bg.png";		//画像の読み込み
		m_Glaph_Handle = LoadGraph("data\\move\\fall.mp4");	//説明動画のダウンロード
		PlayMovieToGraph(m_Glaph_Handle);							//動画再生
		
		break;

	case STAGE_ID::STAGE2:
		m_Bg_Path = "data\\explanation\\race_bg.png";		//画像の読み込み
		m_Glaph_Handle = LoadGraph("data\\move\\ball.mp4");	//説明動画のダウンロード
		m_Explanation_Path = "data\\explanation\\ball_ex.png";		//画像の読み込み
		PlayMovieToGraph(m_Glaph_Handle);							//動画再生
		break;

	case STAGE_ID::STAGE3:
		m_Bg_Path = "data\\explanation\\race_bg.png";		//画像の読み込み
		m_Glaph_Handle = LoadGraph("data\\move\\race2.mp4");	//説明動画のダウンロード
		m_Explanation_Path = "data\\explanation\\race_ex.png";		//画像の読み込み
		PlayMovieToGraph(m_Glaph_Handle);							//動画再生
		break;

	default:
		break;
	}
}

//更新
void CStage_Explanation::Update(void)
{
	if(m_Glaph_Handle != -1)
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
void CStage_Explanation::Draw(void)
{


	

	//保存したIDの取得 ステージ1の時だけ動画を前にする
	STAGE_ID stageid = CStage_Select::GetInstance().GetStageID();
	switch (stageid)
	{
	case STAGE_ID::STAGE1:

		vivid::DrawTexture(m_Bg_Path, { 0.0f,0.0f });//背景画像


		//描画するだけ画像と動画イニシャライズで受け取った値を描画する
		DrawExtendGraph(476, 177, 1213, 553, m_Glaph_Handle, true);
		vivid::DrawTexture(m_Explanation_Path, { 0.0f,0.0f });//説明画像

		break;

	case STAGE_ID::STAGE2:

		vivid::DrawTexture(m_Bg_Path, { 0.0f,0.0f });//背景画像

		//描画するだけ画像と動画イニシャライズで受け取った値を描画する
		DrawExtendGraph(460, 164, 1232, 558, m_Glaph_Handle, true);

		vivid::DrawTexture(m_Explanation_Path, { 0.0f,0.0f });//説明画像

		break;

	case STAGE_ID::STAGE3:


		vivid::DrawTexture(m_Bg_Path, { 0.0f,0.0f });//背景画像

		//描画するだけ画像と動画イニシャライズで受け取った値を描画する
		DrawExtendGraph(473, 200, 1243, 524, m_Glaph_Handle, true);

		vivid::DrawTexture(m_Explanation_Path, { 0.0f,0.0f });//説明画像



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

