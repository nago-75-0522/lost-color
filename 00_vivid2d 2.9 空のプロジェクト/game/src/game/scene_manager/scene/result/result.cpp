#include"vivid.h"
#include "Result.h"
#include"..\..\scene_manager.h"
#include"../color_select/color_select.h"
#include"../../../object/minigame_manager/minigame_manager.h"
#include"../game_risult/game_risult.h"
#include"..\stage_manager\stage2\stage2.h"

const int CResult::m_win_width = 700;
const int CResult::m_win_height = 144;
const vivid::Vector2 CResult::m_win_pos = { vivid::WINDOW_WIDTH / 2 - m_win_width / 2,vivid::WINDOW_HEIGHT / 2 - m_win_height / 2 };
const int CResult::m_draw_width = 650;
const int CResult::m_draw_height = 144;
const vivid::Vector2 CResult::m_draw_pos = { vivid::WINDOW_WIDTH / 2 - m_draw_width / 2,vivid::WINDOW_HEIGHT / 2 - m_draw_height / 2 };

//インスタンス取得
CResult& CResult::GetInstance()
{
	static CResult instance;
	return instance;

}

CResult::CResult()
{
}

//初期化
void CResult::Initialize(void)
{
	vivid::LoadSound("data\\sound\\result.mp3");
	vivid::PlaySound("data\\sound\\result.mp3", true);
}

//更新
void CResult::Update(void)
{
	//キーボード用
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		CColor_Select::GetInstance().IniColor();//色初期化
		CColor_Select::GetInstance().IniChosen();
		CFall::GetInstance().IniOld();
		CBall::GetInstance().IniOld();
		CStage2::GetInstance().RisultIni();
		vivid::StopSound("data\\sound\\result.mp3");
		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);

	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CColor_Select::GetInstance().IniColor();
		CColor_Select::GetInstance().IniChosen();
		CFall::GetInstance().IniOld();
		CBall::GetInstance().IniOld();
		CStage2::GetInstance().RisultIni();
		vivid::StopSound("data\\sound\\result.mp3");
		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);
	}
}

//描画
void CResult::Draw(void)
{
	vivid::DrawTexture("data\\result_bg.png", vivid::Vector2::ZERO);
	if (CGame_Result::GetInstance().Get_Player1_Score() == CGame_Result::GetInstance().Get_Player2_Score())
	{
		vivid::DrawTexture("data\\logo\\draw.png", m_win_pos);
	}
	else if (CGame_Result::GetInstance().Get_Player1_Score() > CGame_Result::GetInstance().Get_Player2_Score())
	{
		vivid::DrawTexture("data\\logo\\1p_win.png", m_win_pos);
	}
	if (CGame_Result::GetInstance().Get_Player1_Score() < CGame_Result::GetInstance().Get_Player2_Score())
	{
		vivid::DrawTexture("data\\logo\\2p_win.png", m_win_pos);
	}
}

//解放
void CResult::Finalize(void)
{
}

