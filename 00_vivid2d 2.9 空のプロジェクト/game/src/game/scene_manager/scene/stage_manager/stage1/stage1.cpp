#include"vivid.h"
#include "stage1.h"
#include"..\..\..\scene_manager.h"
#include"../../../../object/minigame_manager/minigame_manager.h"
#include"../../../../object/player_manager/player_manager.h"
#include"../../../../object/player_manager/fall_player_mana/fall_player1/fall_player1.h"
#include"../../../../object/player_manager/fall_player_mana/fall_player2/fall_player2.h"
CStage1& CStage1::GetInstance()
{
	static CStage1 instance;
	return instance;

}

CStage1::CStage1()
{

}

void CStage1::Initialize(void)
{
	CMinigame_Manager::GetInstance().SetGame(MINIGAME_ID::FALL);
	CMinigame_Manager::GetInstance().Initialize();
	CPlayer_Manager::GetInstance().Initialize();
	vivid::LoadSound("data\\sound\\FALL_BGM.wav");
	vivid::PlaySound("data\\sound\\FALL_BGM.wav", true);
}

void CStage1::Update(void)
{
	CMinigame_Manager::GetInstance().Update();
	CPlayer_Manager::GetInstance().Update();

#if 0
	// デバッグ用：Dキーでクリア回数を+1
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		CSceneManager::GetInstance().AddStageCount();

		vivid::DrawText(100, "ClearCount +1", { 0,50 });
	}
#endif

	//コントローラー用
	if (CPlayer1_Character::GetInstance().GetScale().x <= 0||CPlayer2_Character::GetInstance().GetScale().x <= 0)
	{
		vivid::DrawText(100, "ClearCount +1", { 0,50 });
		CSceneManager::GetInstance().AddStageCount();
		vivid::StopSound("data\\sound\\FALL_BGM.wav");
		CSceneManager::GetInstance().Change(SCENE_ID::GAMERISULT);
	}
}

void CStage1::Draw(void)
{
	vivid::DrawTexture("data\\stage_bg.png", { 0.0f,0.0f });
	CMinigame_Manager::GetInstance().Draw();
	CPlayer_Manager::GetInstance().Draw();
	vivid::DrawText(48, "stage1", { 0.0f,0.0f });
	
}

void CStage1::Finalize(void)
{
}

