#pragma once
#include"vivid.h"
#include"../race_player.h"

class CPlayer2 : public IPlayer
{
public:

	void Update(void) override;

	void Draw(void) override;

	vivid::Vector2 GetPosition() override { return m_Player_Pos; };

	vivid::Vector2 GetDrawPosition() override { return m_Draw_Pos; };

	static CPlayer2& GetInstance(void);
private:
	CPlayer2(void);
	~CPlayer2() = default;
	CPlayer2(const CPlayer2& rhs) = delete;
	CPlayer2& operator =(const CPlayer2& rhs) = delete;

};
