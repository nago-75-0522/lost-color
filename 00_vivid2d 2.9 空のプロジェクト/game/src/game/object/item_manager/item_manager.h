#pragma once
#include"item_box/item_box.h"
#include"item_id.h"
#include"high_jump/high_jump.h"
#include"knock_back/knock_back.h"
#include"pull/pull.h"
class CItem_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	static CItem_Manager& GetInstance();
	CItem_Box m_Item_Box;
	CHigh_Jump m_High_Jump_P1;
	CHigh_Jump m_High_Jump_P2;

private:

	CItem_Manager();
	~CItem_Manager() = default;
	CItem_Manager(const CItem_Manager& rhs);

};