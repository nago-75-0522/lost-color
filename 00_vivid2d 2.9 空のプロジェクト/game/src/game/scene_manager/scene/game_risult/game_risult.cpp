#include "game_risult.h"
#include"../../scene_manager.h"
#include"../../../object/player_manager/player_manager.h"
CGame_Result::CGame_Result()
{

}

void CGame_Result::Initialize()
{
}

void CGame_Result::Update()
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;
	if (keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	}
	if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		if (controller::Trigger(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::B))
			CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
	 if (CPlayer_Manager::GetInstance().Player2_Win() == true)
		if (controller::Trigger(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::B))
			CSceneManager::GetInstance().Change(SCENE_ID::GAMEMAIN);
}

void CGame_Result::Draw()
{
	if (CPlayer_Manager::GetInstance().Draw_Battle() == true)
		vivid::DrawText(40, "DRAW", vivid::Vector2{ vivid::WINDOW_WIDTH * 0.5,vivid::WINDOW_HEIGHT * 0.5 });
	 else if (CPlayer_Manager::GetInstance().Player1_Win() == true)
		vivid::DrawText(40,"1PWIN", vivid::Vector2{ 350,250 });
	 else if(CPlayer_Manager::GetInstance().Player2_Win() == true)
		vivid::DrawText(40,"2PWIN", vivid::Vector2{830,250 });
}

void CGame_Result::Finalize()
{
}

CGame_Result& CGame_Result::GetInstance()
{
	static CGame_Result instance;
	return instance;
}
