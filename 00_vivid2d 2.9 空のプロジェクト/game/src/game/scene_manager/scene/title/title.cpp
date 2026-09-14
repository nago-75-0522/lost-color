#include"title.h"
#include"..\..\scene_manager.h"
#include"vivid.h"
#include"../color_select/color_select.h"
#include"../game_risult/game_risult.h"
#include"../../../object/player_manager/player_manager.h"
#include"..\option_character\option.h"

const int CTitle::m_logo_limit_timer =60*500;

CTitle::CTitle()
	:m_Logo_Time(0)
	,m_title_logo_file("data\\logo\\ge-mulogo1.png")
	, m_start_logo_file("data\\logo\\startUI.png")
	,m_title_logo_width(1000)
	,m_title_logo_height(500)
	,m_start_logo_width(420)
	,m_start_logo_height(180)
	, m_title_movie_play(false)
{
}

void CTitle::Initialize(void)
{
	
	//キャラクター選択をリセット呼び出し
	COption::GetInstance().ResetCharacterSelect();

	//画像の位置
	m_TitlePos.x = vivid::WINDOW_WIDTH / 2 - (m_title_logo_width/2);
	m_TitlePos.y = vivid::WINDOW_HEIGHT * 2 / 5 - (m_title_logo_height / 2);

	m_StartPos.x = vivid::WINDOW_WIDTH / 2 - (m_start_logo_width / 2);
	m_StartPos.y = (vivid::WINDOW_HEIGHT * 2 / 3);

	//音声
	vivid::LoadSound("data\\sound\\title_bgm.mp3");
	vivid::PlaySound("data\\sound\\title_bgm.mp3", true);
	vivid::LoadSound("data\\sound\\click.mp3");

	m_title_move_handle = LoadGraph("data\\explanation\\title_move.mp4");	//説明動画のダウンロード

	// 動画再生開始
	PlayMovieToGraph(m_title_move_handle);



}

void CTitle::Update(void)
{
	++m_Logo_Time;

	CSceneManager::GetInstance().ResetStageCount();//カウントリセット

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		vivid::PlaySound("data\\sound\\click.mp3", false);
		vivid::StopSound("data\\sound\\title_bgm.mp3");
		CGame_Result::GetInstance().IniScore();
		CColor_Select::GetInstance().IniColor();
		CPlayer_Manager::GetInstance().Win_Ini();
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);
	}

	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		vivid::PlaySound("data\\sound\\click.mp3", false);
		vivid::StopSound("data\\sound\\title_bgm.mp3");
		CGame_Result::GetInstance().IniScore();
		CColor_Select::GetInstance().IniColor();
		CPlayer_Manager::GetInstance().Win_Ini();
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);

	}

}

void CTitle::Draw(void)
{

	vivid::DrawText(48, "title", { 0.0f,0.0f });

	//タイトル背景
	vivid::DrawTexture("data\\title_bg2.png", { 0.0f,0.0f });
	
	vivid::Rect rect = { 0,0,0,0 };
	rect.right = m_title_logo_width;
	rect.bottom = m_title_logo_height;


	if (m_Logo_Time > m_logo_limit_timer)
	{
		if (m_title_movie_play == false)
		{
			PlayMovieToGraph(m_title_move_handle);
			m_title_movie_play = true;
		}

		//拡縮
		DrawExtendGraph(0, 0, 1280, 720, m_title_move_handle, true);
		
	
		//動画が終了したらタイトル画面に戻す
		if(GetMovieStateToGraph(m_title_move_handle) == 0)
		{
			m_Logo_Time = 0;
		}


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

	

	//タイトルロゴ
	vivid::DrawTexture(m_title_logo_file, m_TitlePos);

	//スタートロゴ
	vivid::DrawTexture(m_start_logo_file, m_StartPos);


}

void CTitle::Finalize(void)
{
}

CTitle& CTitle::GetInstance()
{
	static CTitle instace;
	return instace;
}


