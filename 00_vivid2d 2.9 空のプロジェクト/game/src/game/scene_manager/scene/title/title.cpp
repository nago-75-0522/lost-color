#include"title.h"
#include"..\..\scene_manager.h"
#include"vivid.h"
#include"../color_select/color_select.h"

CTitle::CTitle()
	:m_Logo_Time(0)
	,m_title_logo_file("data\\logo\\ge-mulogo1.png")
	,m_title_logo_width(1000)
	,m_title_logo_height(500)
{
}

void CTitle::Initialize(void)
{
	
	//画像の位置
	m_TitlePos.x = vivid::WINDOW_WIDTH / 2 - (m_title_logo_width/2);
	m_TitlePos.y = vivid::WINDOW_HEIGHT / 2 - (m_title_logo_height / 2);


}

void CTitle::Update(void)
{
	++m_Logo_Time;

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
	
	vivid::Rect rect = { 0,0,0,0 };
	rect.right = m_title_logo_width;
	rect.bottom = m_title_logo_height;


	//タイトルロゴの表示時間の計算 if(条件)
	if (m_Logo_Time > 10 * 60 )
	{
		/* タイトル動画	 動画再生中にどこかのキーを押すとタイトルに戻る　スペース押すと次の処理行く */
		PlayMovie("data\\db.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);//DX_MOVIEPLAYTYPE_BCANCEL　キー入力あり

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

		else
		{
			//タイマーリセット
			m_Logo_Time = 0;
		}

	}

	vivid::DrawTexture(m_title_logo_file, m_TitlePos);

}

void CTitle::Finalize(void)
{
}

CTitle& CTitle::GetInstance()
{
	static CTitle instace;
	return instace;
}


