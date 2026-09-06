#pragma once
#pragma once
#include"vivid.h"
#include"../item/item.h"

class CFall_Player1;
class CFall_Player2;

class CPull :public Iitem
{
public:
	CPull();
	~CPull() = default;
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	void Draw(const vivid::Vector2& pos);

	void DrawAim(CFall_Player1& player);

	void DrawAim(CFall_Player2& player);

	void Use(CFall_Player1& player);
	void Use(CFall_Player2& player);
	bool Get_Is_Use_1() { return m_Is_Use_1; }
	bool Get_Is_Use_2() { return m_Is_Use_2; }
private:
	static const int m_max_charge_time;
	static const int m_half_charge_time;
	static const int m_map_chip_size;
	enum class LANDING_SPOT
	{
		UPPER_LEFT,
		UP,
		UPPER_RIGHT,
		RIGHT,
		LOWER_RIGHT,
		DOWN,
		LOWER_LEFT,
		LEFT,
		MAX,
	};
	LANDING_SPOT m_Landing_Spot;
	int m_Charge_Timer;
	int m_Pull_Range_1;
	int m_Pull_Range_2;
	bool m_Old_Trigger_1;
	bool m_Old_Trigger_2;
	bool m_Is_Use_1;
	bool m_Is_Use_2;

};