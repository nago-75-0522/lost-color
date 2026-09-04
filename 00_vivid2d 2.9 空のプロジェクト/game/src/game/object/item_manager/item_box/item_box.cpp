#include "item_box.h"
const int CItem_Box::m_random_time = 60 * 5;
const int CItem_Box::m_floor_size = 64;
const int CItem_Box::m_item_box_size = 50;
CItem_Box::CItem_Box()
	: m_(0)
	, m_2(0)
	, m_Random_Timer(0)
	, m_Battle_Timer(0)
{
}

void CItem_Box::Initialize()
{
	m_Random_Timer = m_random_time;
	m_ = 0;
	m_2 = 0;
	m_Battle_Timer = 0;
	m_Max_Item_Box = 2;
	v.clear();
}

void CItem_Box::Update()
{
	if (--m_Random_Timer <= 0)
	{
		m_Random_Timer = m_random_time;
		if (m_Battle_Timer >= 60 * 20)
			m_Max_Item_Box = 4;
		Lottery();
	}


	m_Battle_Timer += 1;

}

void CItem_Box::Draw()
{
	for (int i = 0; i < v.size(); ++i)
	{
		vivid::DrawTexture("data/item_box5.png", v[i]);
	}
	vivid::DrawTexture("data\\frame.png", vivid::Vector2(0.0f, 0.0f));
	vivid::DrawTexture("data\\frame.png", vivid::Vector2(1216.0f, 0.0f));

}

void CItem_Box::Finalize()
{
}

int CItem_Box::Get_Item_Box_Size()
{
	return m_item_box_size;
}
void CItem_Box::Lottery()
{
	for (int i = 0; i < m_Max_Item_Box; ++i)
	{
		m_ = (rand() % 18) + 1;//横抽選
		m_2 = (rand() % 10) + 1;//縦抽選
		m_Chosen_Square.x = m_ * m_floor_size + 11;//
		m_Chosen_Square.y = m_2 * m_floor_size + 12;
		bool Duplicate = false;
		for (int k = 0; k < v.size(); k++)
			if (m_Chosen_Square == v[k])
				break;
		int n = rand() % 5;
		if (n == 1)
			v.push_back(m_Chosen_Square);
	}

}

vivid::Vector2 CItem_Box::Get_Item_Box_Pos(int i)
{

	return v[i];
}

std::vector<vivid::Vector2>& CItem_Box::Get_Item_Box_NUM()
{
	return v;
}

