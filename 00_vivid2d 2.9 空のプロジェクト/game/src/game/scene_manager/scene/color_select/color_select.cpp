#include "color_select.h"
#include"../gamemain/gamemain.h"
#include"../../scene_manager.h"
//定数
const vivid::Vector2 CColor_Select::m_panel_pos(0.0f, 0.0f);			//
const int CColor_Select::m_button_x[] = { 100,490,880 };			//ステージの配置位置
const int CColor_Select ::m_button_y(100);							//ステージの配置高さ
const int CColor_Select::m_finger_width(100);						//選択やじるし
const std::string CColor_Select::m_button_file[] =
{ "data\\B.png","data\\Y.png","data\\R.png" };//色のパネル画像
const unsigned int CColor_Select::m_select_color(0xff4c444d);
const const unsigned int CColor_Select::m_selected_color(0xff000000);
const vivid::Vector2 CColor_Select::m_Blue_Pos = { (float)m_button_x[0],(float)m_button_y };
const vivid::Vector2 CColor_Select::m_Yellow_Pos = { (float)m_button_x[1],(float)m_button_y };
const vivid::Vector2 CColor_Select::m_Red_Pos = { (float)m_button_x[2],(float)m_button_y };

bool CColor_Select::IsEnableColor(COLOR color)
{

	switch (color)
	{
	case COLOR::BLUE:   return m_Blue;
	case COLOR::YELLOW: return m_Yellow;
	case COLOR::RED:    return m_Red;
	default:            return false;
	}

}

CColor_Select::CColor_Select()
	:m_color_pos{ 0.0f,100.0f }
{
}

void CColor_Select::Initialize()
{
	if (!m_Blue && !m_Yellow)
		m_Now_Color = COLOR::RED;
	else if (!m_Blue)
		m_Now_Color = COLOR::YELLOW;
	else if (m_Blue)
		m_Now_Color = COLOR::BLUE;//stage1選択スタート
	
	m_Button_Pos = vivid::Vector2::ZERO;//位置

	//ｘは配列に合わせるため
	m_Finger_Pos.x = m_button_x[(int)m_Now_Color] - m_finger_width;//指のｘ座標の初期化
	//矢印yは選択中ボタンの高さと変わらないため
	m_Finger_Pos.y = m_button_y;									//指のy座標の初期化

	//左スティック入力取得
	m_Stick = vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1);
}

void CColor_Select::Update()
{
	//左スティック入力取得
	m_Stick = vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1);
	ColorSel();

	ColorPic();
}

//描画
void CColor_Select::Draw()
{
	vivid::DrawText(40, "Color_Select", { 0.0f,0.0f });

	//背景画像
	vivid::DrawTexture("data\\select_bg.png", { 0.0f,0.0f });
	for (int i = 0; i < (int)STAGE_SELECT::MAX; i++)
	{
		//ボタン座標を入れる
		m_Button_Pos = vivid::Vector2(m_button_x[i], m_button_y);

		//ボタンの描画
		if (i == (int)m_Now_Color)
		{
			//選択しているボタンを灰色にする
			vivid::DrawTexture(m_button_file[i], m_Button_Pos, m_select_color);
		}
		else
		{
			vivid::DrawTexture(m_button_file[i], m_Button_Pos);
		}
	}
	if (!m_Blue)
		vivid::DrawTexture(m_button_file[0], m_Blue_Pos,m_selected_color);
	if(!m_Yellow)
		vivid::DrawTexture(m_button_file[1], m_Yellow_Pos, m_selected_color);
	if(!m_Red)
		vivid::DrawTexture(m_button_file[2], m_Red_Pos, m_selected_color);


}

//解放
void CColor_Select::Finalize()
{
}

void CColor_Select::ColorSel(void)
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;
	/* コントローラの実装 */
		//デッドゾーンの設定
	const float DEAD_ZONE = 0.5f;

	//前フレームのスティックXを保持
	static float prev_stick_x = 0.0f;

	//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
	if (prev_stick_x <= DEAD_ZONE && m_Stick.x > DEAD_ZONE ||
		controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		m_Now_Color = (COLOR)(((int)m_Now_Color + 1) % (int)COLOR::MAX);
	}

	// 左に倒した瞬間
	else if (prev_stick_x >= -DEAD_ZONE && m_Stick.x < -DEAD_ZONE ||
		     controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		m_Now_Color = (COLOR)((((int)m_Now_Color - 1) + (int)COLOR::MAX) % (int)COLOR::MAX);
	}

	// 現在の値を保存
	prev_stick_x = m_Stick.x;

	if (keyboard::Trigger(keyboard::KEY_ID::RIGHT))
	{
		int color = (int)m_Now_Color;

		for (int i = 0; i < (int)COLOR::MAX; i++)
		{
			color = (color + 1) % (int)COLOR::MAX;

			if (IsEnableColor((COLOR)color))
			{
				m_Now_Color = (COLOR)color;
				break;
			}
		}
	}
	else if (keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
	{
		int color = (int)m_Now_Color;

		for (int i = 0; i < (int)COLOR::MAX; i++)
		{
			color = (color - 1 + (int)COLOR::MAX) % (int)COLOR::MAX;

			if (IsEnableColor((COLOR)color))
			{
				m_Now_Color = (COLOR)color;
				break;
			}
		}
	}

}

void CColor_Select::ColorPic(void)
{
	namespace controller = vivid::controller;
	
	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE)
		|| controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B))
	{
		switch (m_Now_Color)
		{
		case COLOR::BLUE:
			if (!m_Blue)return;
			m_Blue = false;
			if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);			
			break;

		case COLOR::YELLOW:
			if (!m_Yellow)return;
			m_Yellow = false;
			if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);			
			break;

		case COLOR::RED:
			if (!m_Red)return;
			m_Red = false;
			if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);			
			break;


		case COLOR::MAX:
			break;
		default:
			break;
		}
	}

}

//色の初期化
void CColor_Select::IniColor()
{
	m_Blue = true;
	m_Yellow = true;
	m_Red = true;
}

CColor_Select& CColor_Select::GetInstance()
{
	static CColor_Select instance;
	return instance;
}


