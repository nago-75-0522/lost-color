#include "race_manager.h"
#include"map/map.h"
#include"camera/camera.h"
#include"../../../../scene_manager/scene/color_select/color_select.h"

CRace_Manager::CRace_Manager(void)
	: m_Old_Magenta(true)
	, m_Old_Cyan(true)
	, m_Old_Yellow(true)
	, m_Win_Color(0)
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

	m_Win_Color = 0;

	CMap::GetInstance().Inisitalize();
	Chose_Accele();
	CCamera::GetInstance().Initialize();
}

void CRace_Manager::Update(void)
{
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

void CRace_Manager::Chose_Accele(void)
{
	if (m_Old_Cyan)
		m_Old_Cyan = CColor_Select::GetInstance().GetCyan();
	if (m_Old_Yellow)
		m_Old_Yellow = CColor_Select::GetInstance().GetYellow();
	if (m_Old_Magenta)
		m_Old_Magenta = CColor_Select::GetInstance().GetMagenta();

	//1or2or3 シアンorイエローorマゼンタ
	int winLane = 0; //当たりのレーン
	int loseLane = 0; //はずれのレーン

	//全色無効
	if (!m_Magenta && !m_Cyan && !m_Yellow)
	{
		winLane = loseLane = 4; //両方灰色
		m_Win_Color = (rand() % 3) + 1; //前色の中からランダム
	}

	int disableCount = (!m_Magenta ? 1 : 0) +
		(!m_Cyan ? 1 : 0) + (!m_Yellow ? 1 : 0);

	//1色消滅
	if (disableCount == 1)
	{
		if (!m_Magenta)//マゼンタが消えた場合
		{
			winLane = (rand() % 2) + 1; //マゼンタ以外からランダム

			loseLane = (winLane == 1) ? 2 : 1; //winと逆

		}
		if (!m_Cyan)//シアンが消えた場合
		{
			winLane = rand() % 2; //0or1

			winLane = (winLane == 0) ? 2 : 3; //イエローorマゼンタ

			loseLane = (winLane == 2) ? 3 : 2; //winと逆
		}
		if (!m_Yellow)//イエローが消えた場合
		{
			winLane = rand() % 2; //0or1

			winLane = (winLane == 0) ? 1 : 3; //シアンorマゼンタ

			loseLane = (winLane == 1) ? 3 : 1; //winと逆
		}

		m_Win_Color = winLane;
	}

	//2色消滅
	if (disableCount == 2)
	{
		winLane = (rand() % 3) + 1; //前色の中からランダム

		m_Win_Color = winLane;

		//はずれのレーンの数を求めて、あたりとはずれの値が違くなるまで繰り返す
		do { loseLane = (rand() % 3) + 1; } while (winLane == loseLane);

		if (!m_Magenta)//マゼンタが消えた場合
		{
			if (winLane == 3)
				winLane = 4;
			else if (loseLane == 3)
				loseLane = 4;
		}
		if (!m_Cyan)//シアンが消えた場合
		{
			if (winLane == 1)
				winLane = 4;
			else if (loseLane == 1)
				loseLane = 4;
		}
		if (!m_Yellow)//イエローが消えた場合
		{
			if (winLane == 2)
				winLane = 4;
			else if (loseLane == 2)
				loseLane = 4;
		}
	}

	CMap::GetInstance().SetColorRectNum(winLane, loseLane);
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

