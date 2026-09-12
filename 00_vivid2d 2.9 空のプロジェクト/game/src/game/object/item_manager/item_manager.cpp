#include "item_manager.h"

CItem_Manager::CItem_Manager()
{

}

void CItem_Manager::Initialize()
{
	m_Item_Box.Initialize();
	m_Knock_Back_P1.Initialize();
	m_Knock_Back_P2.Initialize();
	m_High_Jump_P1.Initialize();
	m_High_Jump_P2.Initialize();
	m_Pull_P1.Initialize();
	m_Pull_P2.Initialize();
}

void CItem_Manager::Update()
{
	m_Item_Box.Update();
	m_Knock_Back_P1.Update();
	m_Knock_Back_P2.Update();
}

void CItem_Manager::Draw()
{
	m_Item_Box.Draw();
	m_Knock_Back_P1.Draw();
	m_Knock_Back_P2.Draw();
}

void CItem_Manager::Finalize()
{
	m_Item_Box.Finalize();
}

CItem_Manager& CItem_Manager::GetInstance()
{
	static CItem_Manager instance;
	return instance;
}
