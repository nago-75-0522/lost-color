#include "player_manager.h"
#include"player1/player1.h"
#include"player2/player2.h"
CPlayer_Manager::CPlayer_Manager()
{

}
void CPlayer_Manager::Initialize()
{
	CPlayer1_Character::GetInstance().Initialize();
	CPlayer2_Character::GetInstance().Initialize();
}

void CPlayer_Manager::Update()
{
	CPlayer1_Character::GetInstance().Update();
	CPlayer2_Character::GetInstance().Update();
}

void CPlayer_Manager::Draw()
{
	CPlayer1_Character::GetInstance().Draw();
	CPlayer2_Character::GetInstance().Draw();
}

void CPlayer_Manager::Finalize()
{
	CPlayer1_Character::GetInstance().Finalize();
	CPlayer2_Character::GetInstance().Finalize();
}

CPlayer_Manager& CPlayer_Manager::GetInstance()
{
	static CPlayer_Manager instanse;
	return instanse;
}
