#include "fall_player_mana.h"
#include"../../../scene_manager/scene/stage/stage2/stage2.h"
#include"fall_player1/fall_player1.h"
#include"fall_player2/fall_player2.h"

CFall_Player_Manager& CFall_Player_Manager::GetInstance(void)
{
	static CFall_Player_Manager instance;

	return instance;
}

void CFall_Player_Manager::Initialize(void)
{
	vivid::LoadSound("data\\sound\\fall.wav");
	CPlayer1_Character::GetInstance().Initialize();
	CPlayer2_Character::GetInstance().Initialize();

	m_Draw = false;
}

void CFall_Player_Manager::Update(void)
{
	CPlayer1_Character::GetInstance().Update();
	CPlayer2_Character::GetInstance().Update();

	if (CPlayer1_Character::GetInstance().GetScale().x <= 0 &&
		CPlayer2_Character::GetInstance().GetScale().x <= 0 ||
		CStage2::GetInstance().GetDraw() == true)
	{
		m_Draw = true;
	}
	else if (CPlayer2_Character::GetInstance().GetScale().x <= 0 ||
		CStage2::GetInstance().GetWinner() == true)
	{
		m_Player1_Win = true;
	}
	else if (CPlayer1_Character::GetInstance().GetScale().x <= 0 ||
		CStage2::GetInstance().GetWinner() == false)
	{
		m_Player1_Win = false;
	}
}

void CFall_Player_Manager::Draw(void)
{
	CPlayer1_Character::GetInstance().Draw();
	CPlayer2_Character::GetInstance().Draw();
}

void CFall_Player_Manager::Finalize(void)
{
	CPlayer1_Character::GetInstance().Finalize();
	CPlayer2_Character::GetInstance().Finalize();
}

CFall_Player_Manager::CFall_Player_Manager(void)
	: m_Player1_Win(false)
	, m_Draw(false)
{
}

CFall_Player_Manager::CFall_Player_Manager(const CFall_Player_Manager& rhs)
{
	(void)rhs;
}

CFall_Player_Manager& CFall_Player_Manager::operator=(const CFall_Player_Manager& rhs)
{
	(void)rhs;

	return *this;
}
