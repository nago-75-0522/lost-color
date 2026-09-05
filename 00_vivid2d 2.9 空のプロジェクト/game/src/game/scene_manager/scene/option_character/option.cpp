/* キャラクター説明 接続
	プレイヤーの表示
*/
#include"option.h"
#include"..\..\scene_manager.h"
#include"vivid.h"

namespace controller = vivid::controller;
namespace keyboard = vivid::keyboard;

//インスタンス取得
COption& COption::GetInstance()
{
	static COption instance;
	return instance;
}

//コンストラクタ
COption::COption(void)
	:m_Player1_Select(CHARACTER_ID::CHARA1)
	, m_Player2_Select(CHARACTER_ID::CHARA1)
	,m_select_button_color(0xff0000cd)
{
	
}

//キャラクターデータ
Character g_CharacterData[(int)CHARACTER_ID::MAX] =
{
	//CHARACTER_ID::CHARA1
	{
		"data\\debug\\cha1.png",
		1,
		100.0f,
		100.0f,
	},

	//CHARACTER_ID::CHARA2
	{
		"data\\debug\\cha2.png",
		2,
		400.0f,
		100.0f,
	},

//CHARACTER_ID::CHARA3
	{
		"data\\debug\\cha3.png",
		3,
		700.0f,
		100.0f,
	},

	//CHARACTER_ID::CHARA4
	{
		"data\\debug\\cha4.png",
		4,
		1000.0f,
		100.0f,
	}
};


//初期化
void COption::Initialize(void)
{


	namespace controller = vivid::controller;

	

	//m_Button_Pos = vivid::Vector2::ZERO;//位置

#if 0
	//ｘは配列に合わせるため
	m_Finger_Pos.x = m_button_x[(int)m_Now_Select] - m_finger_width;//指のｘ座標の初期化
	//矢印yは選択中ボタンの高さと変わらないため
	m_Finger_Pos.y = m_button_y;									//指のy座標の初期化

#endif 0
	//左スティック入力取得
	m_Player1_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);
	m_Player2_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);

	vivid::LoadSound("data\\sound\\click.mp3");
	vivid::PlaySound("data\\sound\\title_bgm.mp3",true);

	COption::m_player1_ok = false;
	COption::m_player2_ok = false;

}

//更新
void COption::Update(void)
{
	namespace controller = vivid::controller;
	// スティック入力取得
	m_Player1_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);
	m_Player2_Stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);


	
	SelectCharacter();	//選択中
	CharacterPic();
	SetCharacter();		//準備完了シーン切り替え
	


	
}

//描画
void COption::Draw(void)
{


	vivid::DrawTexture("data\\debug\\option_bg.png", { 0.0f,0.0f });
	vivid::DrawText(48, "キャラクターを選択してね", { 0.0f,0.0f });

	//キャラクターを表示
	for (int i = 0; i < (int)CHARACTER_ID::MAX; i++)
	{

		if (m_player1_ok == false)
		{
			m_Now_Select = m_Player1_Select;//プレイヤー１選択中
		}

		else
		{
			m_Now_Select = m_Player2_Select;
		}

		//選択中のキャラクター
		if (i == (int)m_Now_Select)
		{
			vivid::DrawTexture(g_CharacterData[i].file, { g_CharacterData[i].posX,g_CharacterData[i].posY });
		}

		else
		{
			vivid::DrawTexture(g_CharacterData[i].file, { g_CharacterData[i].posX,g_CharacterData[i].posY },m_select_button_color);

		}
	}

	//ロゴ
	vivid::DrawTexture("data\\logo\\black.png", { 50.0f,600.0f });
	vivid::DrawTexture("data\\logo\\black2.png", { (vivid::WINDOW_WIDTH / 2) + 50.0f,600.0f });

	DrawPlayer1();//プレイヤー1関係描画
	DrawPlayer2();//プレイヤー2関係描画


	//キャラクター決定後
	if(m_player1_ok == true && m_player2_ok == true)
	{
			vivid::DrawTexture("data\\logo\\startUI.png", { (vivid::WINDOW_WIDTH / 2) - 210.0f, (vivid::WINDOW_HEIGHT / 2 - 54) });
			//もう一度Bを押したらステージ選択へ
			if(controller::Trigger(controller::DEVICE_ID::PLAYER1,controller::BUTTON_ID::B) ||keyboard::Trigger(keyboard::KEY_ID::SPACE))
			{
				vivid::PlaySound("data\\sound\\click.mp3", false);

				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}
		}

};

//解放
void COption::Finalize(void)
{
}

//準備完了後シーン切り替え処理
void COption::SetCharacter(void)
{

	//二人ともが準備Ｏｋになったら
	if (m_player1_ok == true && m_player2_ok == true)
	{
		/* シーンチェンジ処理 */
		//キーボード用
		if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::S))
		{
			vivid::PlaySound("data\\sound\\click.mp3", false);
			vivid::StopSound("data\\sound\\title_bgm.mp3");
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}

		//コントローラー用
		if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
		{
			vivid::PlaySound("data\\sound\\click.mp3", false);
			vivid::StopSound("data\\sound\\title_bgm.mp3");
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
		}

	}
}

//プレイヤー1描画処理
void COption::DrawPlayer1(void)
{
	if (m_player1_ok == true)
		vivid::DrawTexture("data\\ok.png", { 250.0f,600.0f });
	else
	{
		vivid::DrawText(48, "選択中", { 250.0f,600.0f });
	}
}

//プレイヤー２描画処理
void COption::DrawPlayer2(void)
{
	if (m_player2_ok == true)
		vivid::DrawTexture("data\\ok.png", { (vivid::WINDOW_WIDTH / 2) + 246.0f,600.0f });
	else
	{
		vivid::DrawText(48, "選択中", { (vivid::WINDOW_WIDTH / 2) + 246.0f,600.0f });
	}
}
;

//決定処理
void COption::CharacterPic(void)
{
	//プレイヤー１決定処理
	if (m_player1_ok == false)
	{

		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B) || keyboard::Trigger(keyboard::KEY_ID::S))
		{
			m_player1_ok = true;
			vivid::PlaySound("data\\sound\\click.mp3", false);
		}
	}
	
	//プレイヤー２決定処理
	else if (m_player2_ok == false)
	{
		if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::B) || keyboard::Trigger(keyboard::KEY_ID::DOWN))
		{
			m_player2_ok = true;
			vivid::PlaySound("data\\sound\\click.mp3", false);
		}
	}
}


//選択中の処理
void COption::SelectCharacter(void)
{


	/* コントローラの実装 */
		//デッドゾーンの設定
	const float DEAD_ZONE = 0.7f;

	//前フレームのスティックXを保持
	static float player1_prev_stick_x = 0.0f;
	static float player2_prev_stick_x = 0.0f;

	//プレイヤー1が選んでいない
	if (m_player1_ok == false)
	{
		/* プレイヤー1 */
	//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
		if (player1_prev_stick_x <= DEAD_ZONE && m_Player1_Stick.x > DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player1_Select = (CHARACTER_ID)(((int)m_Player1_Select + 1) % (int)CHARACTER_ID::MAX);
		}

		// 左に倒した瞬間
		else if (player1_prev_stick_x >= -DEAD_ZONE && m_Player1_Stick.x < -DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player1_Select = (CHARACTER_ID)((((int)m_Player1_Select - 1) + (int)CHARACTER_ID::MAX) % (int)CHARACTER_ID::MAX);
		}

		/* 十字キー実装 */
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT) ||
			keyboard::Trigger(keyboard::KEY_ID::D))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player1_Select = (CHARACTER_ID)(((int)m_Player1_Select + 1) % (int)CHARACTER_ID::MAX);
		}

		else if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT) ||
			keyboard::Trigger(keyboard::KEY_ID::A))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player1_Select = (CHARACTER_ID)((((int)m_Player1_Select - 1) + (int)CHARACTER_ID::MAX) % (int)CHARACTER_ID::MAX);
		}
	}

//プレイヤー1がOKにならないと動かせない
	if (m_player1_ok == true && m_player2_ok == false)
	{
		/* プレイヤー2 */
		//右に倒した瞬間（前フレームはデッドゾーン内、現在のフレームは超えた）
		if (player2_prev_stick_x <= DEAD_ZONE && m_Player2_Stick.x > DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player2_Select = (CHARACTER_ID)(((int)m_Player2_Select + 1) % (int)CHARACTER_ID::MAX);
		}

		// 左に倒した瞬間
		else if (player2_prev_stick_x >= -DEAD_ZONE && m_Player2_Stick.x < -DEAD_ZONE)
		{
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player2_Select = (CHARACTER_ID)((((int)m_Player2_Select - 1) + (int)CHARACTER_ID::MAX) % (int)CHARACTER_ID::MAX);
		}

		/* 十字キー実装 */
		if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::RIGHT) ||
			keyboard::Trigger(keyboard::KEY_ID::RIGHT))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player2_Select = (CHARACTER_ID)(((int)m_Player2_Select + 1) % (int)CHARACTER_ID::MAX);
		}

		else if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::LEFT) ||
			keyboard::Trigger(keyboard::KEY_ID::LEFT))
		{
			//選択ボタンの変更
			vivid::PlaySound("data\\sound\\select.mp3", false);
			m_Player2_Select = (CHARACTER_ID)((((int)m_Player2_Select - 1) + (int)CHARACTER_ID::MAX) % (int)CHARACTER_ID::MAX);
		}
	}

	// 現在の値を保存
	player1_prev_stick_x = m_Player1_Stick.x;
	player2_prev_stick_x = m_Player2_Stick.x;
}


