#pragma once
#include"vivid.h"
#include"../race_player.h"

class CRace_Player2 : public IRace_Player
{
public:

	void Update(void) override;

	void Draw(void) override;

	vivid::Vector2 GetPosition() override { return m_Player_Pos; };

	vivid::Vector2 GetDrawPosition() override { return m_Draw_Pos; };

	static CRace_Player2& GetInstance(void);
private:
	CRace_Player2(void);
	~CRace_Player2() = default;
	CRace_Player2(const CRace_Player2& rhs) = delete;
	CRace_Player2& operator =(const CRace_Player2& rhs) = delete;

};
