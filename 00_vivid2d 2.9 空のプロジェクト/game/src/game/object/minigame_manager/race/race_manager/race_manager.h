#pragma once
#include"vivid.h"
#include"race_id.h"
//ミニゲームマネージャーで管理する用のクラス

class CRace_Manager
{
public:
	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	static CRace_Manager& GetInstance(void);

	bool GetOldMagenta() { return m_Old_Magenta; }
	bool GetOldCyan() { return m_Old_Cyan; }
	bool GetOldYellow() { return m_Old_Yellow; }

	RACE_STATE GetRaceState(void) { return m_Race_State; }
private:
	CRace_Manager(void);
	~CRace_Manager(void) = default;
	CRace_Manager(const CRace_Manager& rhs);
	CRace_Manager& operator =(const CRace_Manager& rhs);

	void Chose_Accele(void);

	void Presentation(void);

	RACE_STATE m_Race_State;

	bool m_Cyan;
	bool m_Yellow;
	bool m_Magenta;

	bool m_Old_Magenta;
	bool m_Old_Cyan;
	bool m_Old_Yellow;

	static const int m_win_color_size;
	static const int m_chara_count; //文字数
	static const int m_move_start_time; //動き始めるまでの時間

	int m_Win_Color;//当たりの色
	vivid::Vector2 m_Win_Color_Pos; //当たりの色を表示する場所
	vivid::Vector2 m_Win_Color_Velocity;
	int m_Move_Start_Timer; //動き始めるまでの制限時間

};

