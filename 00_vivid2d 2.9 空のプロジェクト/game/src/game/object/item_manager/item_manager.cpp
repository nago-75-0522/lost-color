#include "item_manager.h"

CItem_Manager::CItem_Manager()
{

}

void CItem_Manager::Initialize()
{
	m_Item_Box.Initialize();
}

void CItem_Manager::Update()
{
	m_Item_Box.Update();
}

void CItem_Manager::Draw()
{
	m_Item_Box.Draw();
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
