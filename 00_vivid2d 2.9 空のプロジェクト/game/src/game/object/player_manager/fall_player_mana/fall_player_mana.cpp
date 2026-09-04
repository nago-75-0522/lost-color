#include "fall_player_mana.h"
#include"../../../scene_manager/scene/stage_manager/stage2/stage2.h"
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
	CFall_Player1::GetInstance().Initialize();
	CFall_Player2::GetInstance().Initialize();

	m_Draw = false;
}

void CFall_Player_Manager::Update(void)
{
	CFall_Player1::GetInstance().Update();
	CFall_Player2::GetInstance().Update();

	if (CFall_Player1::GetInstance().GetScale().x <= 0 &&
		CFall_Player2::GetInstance().GetScale().x <= 0)
	{
		m_Draw = true;
	}
	else if (CFall_Player2::GetInstance().GetScale().x <= 0)
	{
		m_Player1_Win = true;
	}
	else if (CFall_Player1::GetInstance().GetScale().x <= 0)
	{
		m_Player1_Win = false;
	}
}

void CFall_Player_Manager::Draw(void)
{
	CFall_Player1::GetInstance().Draw();
	CFall_Player2::GetInstance().Draw();
}

void CFall_Player_Manager::Finalize(void)
{
	CFall_Player1::GetInstance().Finalize();
	CFall_Player2::GetInstance().Finalize();
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
