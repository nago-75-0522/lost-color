#pragma once
#include"vivid.h"
#include"../race_player.h"

class CRace_Player1 : public IRace_Player
{
public:

	void Update(void) override;

	void Draw(void) override;

	vivid::Vector2 GetPosition() override { return m_Player_Pos; };

	vivid::Vector2 GetDrawPosition() override { return m_Draw_Pos; };

	static CRace_Player1& GetInstance(void);
private:
	CRace_Player1(void);
	~CRace_Player1(void) = default;
	CRace_Player1(const CRace_Player1& rhs) = delete;
	CRace_Player1& operator =(const CRace_Player1 rhs) = delete;
};
