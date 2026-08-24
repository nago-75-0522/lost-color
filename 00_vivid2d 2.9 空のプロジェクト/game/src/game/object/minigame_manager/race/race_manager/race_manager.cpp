#include "race_manager.h"
#include"map/map.h"
#include"camera/camera.h"
#include"../../../../scene_manager/scene/color_select/color_select.h"


CRace_Manager::CRace_Manager(void)
	: m_Old_Magenta(true)
	, m_Old_Cyan(true)
	, m_Old_Yellow(true)
{
}

void CRace_Manager::Initialize(void)
{
	m_Cyan = CColor_Select::GetInstance().GetCyan();
	m_Yellow = CColor_Select::GetInstance().GetYellow();
	m_Magenta = CColor_Select::GetInstance().GetMagenta();
	if (!m_Old_Cyan)
		m_Cyan = m_Old_Cyan;
	if (!m_Old_Yellow)
		m_Yellow = m_Old_Yellow;
	if (!m_Old_Magenta)
		m_Magenta = m_Old_Magenta;

	CMap::GetInstance().Inisitalize();
	CCamera::GetInstance().Initialize();
	
}

void CRace_Manager::Update(void)
{
	if (m_Old_Cyan)
		m_Old_Cyan = CColor_Select::GetInstance().GetCyan();
	if (m_Old_Yellow)
		m_Old_Yellow = CColor_Select::GetInstance().GetYellow();
	if (m_Old_Magenta)
		m_Old_Magenta = CColor_Select::GetInstance().GetMagenta();

	CMap::GetInstance().Update();
}

void CRace_Manager::Draw(void)
{
	CMap::GetInstance().Draw();
}

void CRace_Manager::Finalize(void)
{
	CMap::GetInstance().Finalize();
}

CRace_Manager& CRace_Manager::GetInstance(void)
{
	static CRace_Manager instance;

	return instance;
}


CRace_Manager::CRace_Manager(const CRace_Manager& rhs)
{
	(void)rhs;
}

CRace_Manager& CRace_Manager::operator=(const CRace_Manager& rhs)
{
	(void)rhs;

	return *this;
}
