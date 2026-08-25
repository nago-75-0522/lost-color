#include "ball_player_mana.h"
#include"../../minigame_manager/ball_manager/ball/ball.h"

CBall_Player_Manager& CBall_Player_Manager::GetInstance(void)
{
	static CBall_Player_Manager instance;

	return instance;
}

void CBall_Player_Manager::Initialize(void)
{
	player1.Initialize();
	player2.Initialize();
}

void CBall_Player_Manager::Update(void)
{
	player1.Update();
	player2.Update();
	CBall::GetInstance().CheckHit(player1.GetBasket(), player2.GetBasket());
}

void CBall_Player_Manager::Draw(void)
{
	player1.Draw();
	player2.Draw();
}

void CBall_Player_Manager::Finalize(void)
{
	player1.Finalize();
	player2.Finalize();
}

CBall_Player_Manager::CBall_Player_Manager(void)
{
}
