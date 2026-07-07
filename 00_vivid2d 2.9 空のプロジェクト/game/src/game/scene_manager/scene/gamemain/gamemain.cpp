//ステージ選択
#include"gamemain.h"
#include"..\..\scene_manager.h"
#include"..\stage\stage1\stage1.h"

 
//定数
const vivid::Vector2 CGamemain::m_bg_pos(0.0f, 0.0f);			//
const int CGamemain::m_button_x[] = { 100,490,880 };			//ステージの配置位置
const int CGamemain::m_button_y(100);							//ステージの配置高さ
const int CGamemain::m_finger_width(100);						//選択やじるし
const std::string CGamemain::m_button_file[] =
{ "data\\stage1.png","data\\stage2.png","data\\stage3.png" };//ステージ画像

const unsigned int CGamemain::m_select_button_color(0xff0000cd);




//インスタンス取得
CGamemain& CGamemain::GetInstance()
{
	static CGamemain instance;
	return instance;
}

//初期化
void CGamemain::Initialize(void)
{
	m_Now_Select = STAGE_SELECT::STAGE1;//stage1選択スタート

	m_Button_Pos = vivid::Vector2::ZERO;//位置

	//ｘは配列に合わせるため
	m_Finger_Pos.x = m_button_x[(int)m_Now_Select] - m_finger_width;//指のｘ座標の初期化
	//矢印yは選択中ボタンの高さと変わらないため
	m_Finger_Pos.y = m_button_y;									//指のy座標の初期化


	vivid::Vector2 m_Stick = vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1);//スティック

}

//更新
void CGamemain::Update(void)
{

	/* ステージカウントが1～3の時 */
	//ステージ選択中処理
	StageSelect();

	//ステージ決定時の処理
	StagePic();
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

	/* コントローラの実装 */
		//デッドゾーンの設定
	const float DEAD_ZONE = 0.7f;

	//前フレームのスティックXを保持
	static float prev_stick_x = 0.0f;

	//左スティック入力取得
	vivid::Vector2 m_stick = vivid::controller::GetAnalogStickLeft(vivid::controller::DEVICE_ID::PLAYER1);

	//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
	if (prev_stick_x <= DEAD_ZONE && m_stick.x > DEAD_ZONE)
	{
		m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);
	}

	// 左に倒した瞬間
	else if (prev_stick_x >= -DEAD_ZONE && m_stick.x < -DEAD_ZONE)
	{
		m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);
	}

	// 現在の値を保存
	prev_stick_x = m_stick.x;



	/* 十字キー実装 */
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::RIGHT))
	{
		//選択ボタンの変更
		m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);

		//指の位置変更
		//m_Finger_Pos = vivid::Vector2(m_button_x[(int)m_Now_Select] - m_finger_width, m_button_y);

	}

	else if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::LEFT))
	{
		//選択ボタンの変更
		m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);

		//指の位置変更
		//m_Finger_Pos = vivid::Vector2(m_button_x[(int)m_Now_Select] - m_finger_width, m_button_y);

	}



	/* 選択中 */
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::RIGHT))
	{
		//選択ボタンの変更
		m_Now_Select = (STAGE_SELECT)(((int)m_Now_Select + 1) % (int)STAGE_SELECT::MAX);

		//指の位置変更
		//m_Finger_Pos = vivid::Vector2(m_button_x[(int)m_Now_Select] - m_finger_width, m_button_y);

	}

	else if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::LEFT))
	{
		//選択ボタンの変更
		m_Now_Select = (STAGE_SELECT)((((int)m_Now_Select - 1) + (int)STAGE_SELECT::MAX) % (int)STAGE_SELECT::MAX);

		//指の位置変更
		//m_Finger_Pos = vivid::Vector2(m_button_x[(int)m_Now_Select] - m_finger_width, m_button_y);
	}

}

//ステージ決定
void CGamemain::StagePic(void)
{

	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		switch (m_Now_Select)
		{
		case STAGE_SELECT::STAGE1:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);
			break;

		case STAGE_SELECT::STAGE2:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE2);
			break;

		case STAGE_SELECT::STAGE3:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE3);
			break;


		case STAGE_SELECT::MAX:
			break;
		default:
			break;
		}
	}

	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		switch (m_Now_Select)
		{
		case STAGE_SELECT::STAGE1:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);
			break;

		case STAGE_SELECT::STAGE2:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE2);
			break;

		case STAGE_SELECT::STAGE3:
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE3);
			break;


		case STAGE_SELECT::MAX:
			break;
		default:
			break;
		}
	}


}

