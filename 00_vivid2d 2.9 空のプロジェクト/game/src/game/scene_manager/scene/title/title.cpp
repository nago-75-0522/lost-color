#include"title.h"
#include"..\..\scene_manager.h"
#include"vivid.h"
#include"../color_select/color_select.h"
#include"../game_risult/game_risult.h"
#include"../../../object/player_manager/player_manager.h"
#include"..\option_character\option.h"
#include"../../../object/minigame_manager/ball_manager/ball/ball.h"
#include"../../../object/minigame_manager/fall_manager/fall.h"
#include"../../../object/minigame_manager/race/race_manager/race_manager.h"

const int CTitle::m_logo_limit_timer = 60 * 500;
CTitle::CTitle()
	:m_Logo_Time(0)
	,m_title_logo_file("data\\logo\\title.png")
	, m_start_logo_file("data\\logo\\startUI.png")
	,m_title_logo_width(1000)
	,m_title_logo_height(500)
	,m_start_logo_width(420)
	,m_start_logo_height(180)
	, m_title_movie_play(false)
	, m_Start_Alpha_State(START_ALPHA::DUMMY)
	, m_fade_speed(5)
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

	m_title_move_handle = LoadGraph("data\\move\\title_move.mp4");	//ロード

	m_Start_Alpha_State = START_ALPHA::SUBTRACT;
	m_Start_Color = 0xffffffff;
}

void CTitle::Update(void)
{
	++m_Logo_Time;

	CSceneManager::GetInstance().ResetStageCount();//カウントリセット

	//動画再生 設定した時間を超えたら再生
	if (m_Logo_Time > m_logo_limit_timer && m_title_movie_play == false)
	{
		//動画を最初に戻す
		SeekMovieToGraph(m_title_move_handle, 0);
		PlayMovieToGraph(m_title_move_handle);
		m_title_movie_play = true;
	}

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		vivid::PlaySound("data\\sound\\click.mp3", false);
		vivid::StopSound("data\\sound\\title_bgm.mp3");
		CGame_Result::GetInstance().IniScore();
		CColor_Select::GetInstance().IniColor();
		CPlayer_Manager::GetInstance().Win_Ini();
		CFall::GetInstance().IniOld();
		CBall::GetInstance().IniOld();
		CRace_Manager::GetInstance().Ini_Old();
		PauseMovieToGraph(m_title_move_handle);
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
		CFall::GetInstance().IniOld();
		CBall::GetInstance().IniOld();
		CRace_Manager::GetInstance().Ini_Old();
		CSceneManager::GetInstance().Change(SCENE_ID::OPTION);

	}

#if 0
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
#endif 0
}

void CTitle::Draw(void)
{
	//タイトル背景
	vivid::DrawTexture("data\\title_bg2.png", { 0.0f,0.0f });
	
	vivid::Rect rect = { 0,0,0,0 };
	rect.right = m_title_logo_width;
	rect.bottom = m_title_logo_height;

	//動画再生中
	if(m_title_movie_play == true)
	{
		

		DrawExtendGraph(0, 0, 1280, 720, m_title_move_handle, true);//動画サイズの拡縮
		vivid::DrawTexture(m_start_logo_file, { (float)vivid::WINDOW_WIDTH - (float)m_start_logo_width,(float)vivid::WINDOW_HEIGHT -(float)m_start_logo_height});

		//動画終了
		if(GetMovieStateToGraph(m_title_move_handle) == 0)
		{
			SeekMovieToGraph(m_title_move_handle, 0);
			m_title_movie_play = false;
			m_Logo_Time = 0;

		}


		return;
	}

	int alpha = (m_Start_Color & 0xff000000) >> 24;
	
	if (m_Start_Alpha_State == START_ALPHA::ADD)
		alpha += m_fade_speed;
	else
		alpha -= m_fade_speed;

	if (alpha <= 0)
		m_Start_Alpha_State = START_ALPHA::ADD;
	else if (alpha >= 0xff)
		m_Start_Alpha_State = START_ALPHA::SUBTRACT;

	m_Start_Color = (alpha << 24) | (m_Start_Color & 0x00ffffff);

	//タイトルロゴ
	vivid::DrawTexture(m_title_logo_file, m_TitlePos);

	//スタートロゴ
	vivid::DrawTexture(m_start_logo_file, m_StartPos,m_Start_Color);
	


}

void CTitle::Finalize(void)
{
}

CTitle& CTitle::GetInstance()
{
	static CTitle instace;
	return instace;
}


