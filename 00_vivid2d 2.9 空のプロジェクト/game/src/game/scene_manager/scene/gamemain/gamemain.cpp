//ステージ選択
#include"gamemain.h"
#include"..\..\scene_manager.h"
#include"../../../object/player_manager/player_manager.h"

//定数
const vivid::Vector2 CGamemain::m_bg_pos(0.0f, 0.0f);			//
const int CGamemain::m_button_x[] = { 100,490 };//},880 };			//ステージの配置位置***
const int CGamemain::m_button_y(100);							//ステージの配置高さ
const int CGamemain::m_finger_width(100);						//選択やじるし
const std::string CGamemain::m_button_file[] =
{ "data\\stage1.png","data\\stage2.png" };//,"data\\stage3.png" };//ステージ画像***

const unsigned int CGamemain::m_select_button_color(0xff0000cd);




//インスタンス取得
CGamemain& CGamemain::GetInstance()
{
	static CGamemain instance;
	return instance;
}

CGamemain::CGamemain()
	: m_Now_Select(STAGE_SELECT::MAX)
{
}



//初期化
void CGamemain::Initialize(void)
{

	namespace controller = vivid::controller;

	m_Now_Select = STAGE_SELECT::STAGE1;//stage1選択スタート

	m_Button_Pos = vivid::Vector2::ZERO;//位置

	//ｘは配列に合わせるため
	m_Finger_Pos.x = m_button_x[(int)m_Now_Select] - m_finger_width;//指のｘ座標の初期化
	//矢印yは選択中ボタンの高さと変わらないため
	m_Finger_Pos.y = m_button_y;									//指のy座標の初期化
	
	//左スティック入力取得
	m_Player1_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);
	m_Player2_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);

	//音声
	vivid::LoadSound("data\\sound\\select.mp3");
	vivid::LoadSound("data\\sound\\click.mp3");
	vivid::LoadSound("data\\sound\\title_bgm.mp3");
	vivid::PlaySound("data\\sound\\title_bgm.mp3", true);
}

//更新
void CGamemain::Update(void)
{
	
	namespace controller = vivid::controller;
	// スティック入力取得
	 m_Player1_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);
	 m_Player2_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);
	/* ステージカウントが1～3の時 */
	//ステージ選択中処理
	StageSelect();


	
}

//描画
void CGamemain::Draw(void)
{
	vivid::DrawText(48, "gamemain", { 0.0f,0.0f });

	//背景画像
	vivid::DrawTexture("data\\select_bg.png", { 0.0f,0.0f });

	//vivid::DrawTexture("data\\arrow.png", m_Finger_Pos); 指



	for (int i = 0; i < (int)STAGE_SELECT::MAX; i++)
	{
		//ボタン座標を入れる
		m_Button_Pos = vivid::Vector2(m_button_x[i], m_button_y);



		//ボタンの描画

		if (i == (int)m_Now_Select)
		{
			//選択しているボタンを灰色にする
			vivid::DrawTexture(m_button_file[i], m_Button_Pos, m_select_button_color);
		}
		else
		{
			vivid::DrawTexture(m_button_file[i], m_Button_Pos);
		}
	}
}

//解放
void CGamemain::Finalize(void)
{
}

//選択処理
void CGamemain::StageSelect(void)
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	/* コントローラの実装 */
		//デッドゾーンの設定
	const float DEAD_ZONE = 0.7f;

	//前フレームのスティックXを保持
	static float player1_prev_stick_x = 0.0f;
	static float player2_prev_stick_x = 0.0f;

	if (CPlayer_Manager::GetInstance().Player1_Win() == false)
	{
		StagePic();
		//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
		if (player1_prev_stick_x <= DEAD_ZONE && m_Player1_Stick.x > DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);

		}

		// 左に倒した瞬間
		else if (player1_prev_stick_x >= -DEAD_ZONE && m_Player1_Stick.x < -DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);
			
		}

		/* 十字キー実装 */
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT)||
			keyboard::Trigger(keyboard::KEY_ID::D))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);
		}

		else if (controller::Trigger(controller::DEVICE_ID::PLAYER1,controller::BUTTON_ID::LEFT)||
			keyboard::Trigger(keyboard::KEY_ID::A))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);
		}
	}

	else if (CPlayer_Manager::GetInstance().Player1_Win() == true) 
	{
		StagePic();
		//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
		if (player2_prev_stick_x <= DEAD_ZONE && m_Player2_Stick.x > DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);
		}

		// 左に倒した瞬間
		else if (player2_prev_stick_x >= -DEAD_ZONE && m_Player2_Stick.x < -DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);
		}

		/* 十字キー実装 */
		if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::RIGHT)||
			keyboard::Trigger(keyboard::KEY_ID::RIGHT))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);
		}

		else if (controller::Trigger(controller::DEVICE_ID::PLAYER2,controller::BUTTON_ID::LEFT)||
			keyboard::Trigger(keyboard::KEY_ID::LEFT))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);
		}
	}
	// 現在の値を保存
	player1_prev_stick_x = m_Player1_Stick.x;
	player2_prev_stick_x = m_Player2_Stick.x;
}

//ステージ決定
void CGamemain::StagePic(void)
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	//コントローラー用
	if (CPlayer_Manager::GetInstance().Player1_Win() == false)
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B)||
			keyboard::Trigger(keyboard::KEY_ID::S))
	{
		switch (m_Now_Select)
		{
		case STAGE_SELECT::STAGE1:

			vivid::StopSound("data\\sound\\title_bgm.mp3");
			CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			break;

		case STAGE_SELECT::STAGE2:

			vivid::PlaySound("data\\sound\\click.mp3", false);
			vivid::StopSound("data\\sound\\title_bgm.mp3");

			CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			break;

			/*
		case STAGE_SELECT::STAGE3:
			CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
			break;
			*///*********

		case STAGE_SELECT::MAX:
			break;
		default:
			break;
		}
	}

	//コントローラー用
	if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER2, vivid::controller::BUTTON_ID::B)||
			keyboard::Trigger(keyboard::KEY_ID::DOWN))
		{
			switch (m_Now_Select)
			{
			case STAGE_SELECT::STAGE1:
				vivid::PlaySound("data\\sound\\click.mp3", false);
				vivid::StopSound("data\\sound\\title_bgm.mp3");
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				break;

			case STAGE_SELECT::STAGE2:
				vivid::PlaySound("data\\sound\\click.mp3", false);
				vivid::StopSound("data\\sound\\title_bgm.mp3");

				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				break;

				/*
			case STAGE_SELECT::STAGE3:
				CSceneManager::GetInstance().Change(SCENE_ID::COLOR_SELECT);
				break;
				*///******

			case STAGE_SELECT::MAX:
				break;
			default:
				break;
			}
		}
	


}

STAGE_SELECT CGamemain::GetStageSelect()
{
	return m_Now_Select;
}

