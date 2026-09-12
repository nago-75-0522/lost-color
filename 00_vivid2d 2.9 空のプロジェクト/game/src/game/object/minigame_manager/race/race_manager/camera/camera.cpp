#include"camera.h"
#include"../../../../player_manager/race_player_mana/race_player_mana.h"

#if 0
//必要ない
#else
CCamera::CCamera()
	: m_Camera_Pos(0.0f,0.0f)
{
}

CCamera::CCamera(const CCamera& rhs)
{
	(void)rhs;
}

CCamera& CCamera::operator=(const CCamera& rhs)
{
	(void)rhs;

	return *this;
}

void CCamera::Initialize()
{
	CRace_Player_Manager& pm = CRace_Player_Manager::GetInstance();

	m_Camera_Pos = { pm.GetPosition().x - vivid::WINDOW_WIDTH / 2,0.f };
}

void CCamera::Finalzie()
{
}

void CCamera::SetCameraPos(vivid::Vector2& pos)
{
	m_Camera_Pos = pos;
}

CCamera& CCamera::GetInstance()
{
	static CCamera instance;

	return instance;
}
#endif