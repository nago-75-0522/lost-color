#pragma once
#include"fall_player1/fall_player1.h"
#include"fall_player2/fall_player2.h"

class CFall_Player_Manager
{
public:
	static CFall_Player_Manager& GetInstance(void);

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	bool Player1_Win() { return m_Player1_Win; }
	bool Draw_Battle() { return m_Draw; }

private:
	CFall_Player_Manager(void);
	~CFall_Player_Manager(void) = default;
	CFall_Player_Manager(const CFall_Player_Manager& rhs);
	CFall_Player_Manager& operator =(const CFall_Player_Manager& rhs);

	//変数
	bool m_Player1_Win;
	bool m_Draw;
};