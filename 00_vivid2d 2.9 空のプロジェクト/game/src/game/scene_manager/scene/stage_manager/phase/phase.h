#pragma once
#pragma once
#include"vivid.h"
class CPhase
{
public:
	CPhase();
	~CPhase() = default;
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	enum class GAME_STATE
	{
		START,
		MAIN,
		FINISH,
		FINISH_FIN,
	};

	GAME_STATE& Get_Game_State() { return m_Game_State; }
private:
	static const int m_start_time;
	static const unsigned int m_color;
	static const vivid::Vector2 m_logo_pos;
	static const vivid::Vector2 m_number_pos;
	static const int m_digit_width;
	static const int m_digit_height;
	static const int m_max_digit;
	int m_Start_Timer;

	GAME_STATE m_Game_State;
};