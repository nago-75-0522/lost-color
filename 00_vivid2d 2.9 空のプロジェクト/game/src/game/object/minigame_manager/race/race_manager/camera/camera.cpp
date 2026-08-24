#include"camera.h"

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
	m_Camera_Pos = { 0.0f,0.0f };
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