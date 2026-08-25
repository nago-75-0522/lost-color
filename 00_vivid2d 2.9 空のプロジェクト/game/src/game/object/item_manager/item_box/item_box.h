#pragma once
#pragma once
#include"vivid.h"
#include<vector>
class  CItem_Box
{
public:
	CItem_Box();
	~CItem_Box() = default;
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	int Get_Item_Box_Size();
	void Lottery();
	vivid::Vector2 Get_Item_Box_Pos(int i);
	std::vector<vivid::Vector2>& Get_Item_Box_NUM();
private:
	static const int m_random_time;
	static const int m_floor_size;
	static const int m_item_box_size;

	int m_Random_Timer;
	int m_;
	int m_2;
	int m_Battle_Timer;
	int m_Max_Item_Box;
	std::vector<vivid::Vector2>v;
	vivid::Vector2 m_Chosen_Square;
	bool m_Judge;
};