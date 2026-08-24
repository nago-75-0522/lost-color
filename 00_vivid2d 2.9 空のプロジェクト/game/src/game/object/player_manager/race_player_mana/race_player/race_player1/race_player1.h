#pragma once
#include"vivid.h"
#include"../race_player.h"

class CPlayer1 : public IPlayer
{
public:
	
	void Update(void) override;

	void Draw(void) override;

	vivid::Vector2 GetPosition() override { return m_Player_Pos; };

	vivid::Vector2 GetDrawPosition() override { return m_Draw_Pos; };

	static CPlayer1& GetInstance(void);
private:
	CPlayer1(void);
	~CPlayer1(void) = default;
	CPlayer1(const CPlayer1& rhs) = delete;
	CPlayer1& operator =(const CPlayer1 rhs) = delete;

};
