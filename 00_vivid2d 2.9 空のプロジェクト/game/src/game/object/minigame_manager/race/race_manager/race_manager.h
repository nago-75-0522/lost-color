#pragma once
#include"vivid.h"
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

	int GetWinColor(void) { return m_Win_Color; }
private:
	CRace_Manager(void);
	~CRace_Manager(void) = default;
	CRace_Manager(const CRace_Manager& rhs);
	CRace_Manager& operator =(const CRace_Manager& rhs);

	void Chose_Accele(void);

	bool m_Cyan;
	bool m_Yellow;
	bool m_Magenta;

	bool m_Old_Magenta;
	bool m_Old_Cyan;
	bool m_Old_Yellow;

	int m_Win_Color;//当たりの色

};

