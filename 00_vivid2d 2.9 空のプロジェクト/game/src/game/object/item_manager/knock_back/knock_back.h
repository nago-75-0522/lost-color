#pragma once
#pragma once
#include "../item/item.h"
#include"vivid.h"
class CFall_Player1;
class CFall_Player2;

class CKnock_Back :public Iitem
{
public:
	CKnock_Back();
	~CKnock_Back() = default;
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Draw(const vivid::Vector2& pos);

	void Finalize()override;
	void DrawAim(CFall_Player1& player);
	void DrawAim(CFall_Player2& player);

	void Use(CFall_Player1& player);
	void Use(CFall_Player2& player);
	void Check_Hit();
private:

	struct KNOCK_BACK
	{
		bool m_Active_Flag;
		vivid::Vector2 m_Knock_Back_Pos;
		vivid::Vector2 m_Knock_Back_Velocity;
		int m_Duration;
		int m_Owner; // 1=P1 2=P2
		bool m_LeftOwnerTile;
		unsigned int m_Color;
	};

	enum class KNOCK_BACK_STATE
	{
		ON,
		OFF,
	};

	static const int m_max_charge_time;
	static const int m_half_charge_time;
	static const int m_duration_time;
	static const int m_max_knock_back_num;
	static const int m_chip_size;
	static const int m_blinking_time;
	static const unsigned int m_color;
	static const unsigned int m_invisible_color;
	int m_Charge_Timer;
	int m_Old_Trigger_1;
	int m_Old_Trigger_2;
	KNOCK_BACK* m_Knock_Back;
	vivid::Vector2 m_Knock_Back_Pos_1;
	vivid::Vector2 m_Knock_Back_Pos_2;
	vivid::Vector2 m_Now_Pos_1;
	vivid::Vector2 m_Now_Pos_2;
	KNOCK_BACK_STATE m_Knock_Back_State;
	int m_Blinking_Timer;
};