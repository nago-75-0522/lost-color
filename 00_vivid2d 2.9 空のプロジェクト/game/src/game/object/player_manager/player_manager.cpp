#include "player_manager.h"
CPlayer_Manager::CPlayer_Manager()
	:m_Player1_Win(true)
	,m_Player2_Win(false)
	,m_Draw(false)
{
}
void CPlayer_Manager::Initialize()
{
	CPlayer1_Character::GetInstance().Initialize();
	CPlayer2_Character::GetInstance().Initialize();
	
	m_Draw = false;
}

void CPlayer_Manager::Update()
{
	CPlayer1_Character::GetInstance().Update();
	CPlayer2_Character::GetInstance().Update();

	if (CPlayer1_Character::GetInstance().GetScale().x <= 0 &&
		CPlayer2_Character::GetInstance().GetScale().x <= 0)
	{
		m_Draw = true;
		return;
	}
	else if (CPlayer2_Character::GetInstance().GetScale().x <= 0)
	{
		m_Player2_Win = false;
		m_Player1_Win = true;
	}
	else if (CPlayer1_Character::GetInstance().GetScale().x <= 0)
	{

		m_Player1_Win = false;
		m_Player2_Win = true;
	}
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
	static CPlayer_Manager instance;
	return instance;
}

bool CPlayer_Manager::Player1_Win()
{
	return m_Player1_Win;
}

bool CPlayer_Manager::Player2_Win()
{
	return m_Player2_Win;
}

bool CPlayer_Manager::Draw_Battle()
{
	return m_Draw;
}

