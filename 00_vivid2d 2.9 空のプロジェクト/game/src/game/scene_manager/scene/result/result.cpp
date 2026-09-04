#include"vivid.h"
#include "Result.h"
#include"..\..\scene_manager.h"
#include"../color_select/color_select.h"
#include"../../../object/minigame_manager/minigame_manager.h"
#include"../game_risult/game_risult.h"
#include"..\stage_manager\stage2\stage2.h"

const vivid::Vector2 CResult::m_ScorePos = {420,300};

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
		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);
		vivid::StopSound("data\\sound\\result.mp3");

	}
	//コントローラー用
	if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
	{
		CColor_Select::GetInstance().IniColor();
		CColor_Select::GetInstance().IniChosen();
		CFall::GetInstance().IniOld();
		CBall::GetInstance().IniOld();
		CStage2::GetInstance().RisultIni();
		CSceneManager::GetInstance().Change(SCENE_ID::TITLE);
		vivid::StopSound("data\\sound\\result.mp3");
	}
}

//描画
void CResult::Draw(void)
{
	vivid::DrawText(48, "Result", { 0.0f,0.0f });
	if (CGame_Result::GetInstance().Get_Player1_Score() == CGame_Result::GetInstance().Get_Player2_Score())
		vivid::DrawText(110, "DRAW!!", { m_ScorePos });
	else if(CGame_Result::GetInstance().Get_Player1_Score()> CGame_Result::GetInstance().Get_Player2_Score())
		vivid::DrawText(110, "1PWIN!!", { m_ScorePos });
	if (CGame_Result::GetInstance().Get_Player1_Score() < CGame_Result::GetInstance().Get_Player2_Score())
		vivid::DrawText(110, "2PWIN!!", { m_ScorePos });
}

//解放
void CResult::Finalize(void)
{
}

