#pragma once
#include"item_box/item_box.h"
class CItem_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	static CItem_Manager& GetInstance();
	CItem_Box m_Item_Box;

private:

	CItem_Manager();
	~CItem_Manager() = default;
	CItem_Manager(const CItem_Manager& rhs);

};