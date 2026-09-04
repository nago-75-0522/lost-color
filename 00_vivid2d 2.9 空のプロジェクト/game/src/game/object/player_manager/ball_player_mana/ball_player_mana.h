#pragma once
#include"ball_player1/ball_player1.h"
#include"ball_player2/ball_player2.h"

class CBall_Player_Manager
{
public:
	static CBall_Player_Manager& GetInstance(void);

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

private:
	CBall_Player_Manager(void);
	~CBall_Player_Manager(void) = default;
	CBall_Player_Manager(const CBall_Player_Manager& rhs) = delete;
	CBall_Player_Manager& operator =(const CBall_Player_Manager& rhs) = delete;

	void CheckPlayerHit();

	CBallPlayer1 player1;
	CBallPlayer2 player2;
};

