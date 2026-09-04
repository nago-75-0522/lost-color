#pragma once

class CFall_Player_Manager
{
public:
	static CFall_Player_Manager& GetInstance(void);

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	bool isFallPlayer1Win(void) { return m_Player1_Win; }
	bool isFallDraw(void) { return m_Draw; }
private:
	CFall_Player_Manager(void);
	~CFall_Player_Manager(void) = default;
	CFall_Player_Manager(const CFall_Player_Manager& rhs);
	CFall_Player_Manager& operator =(const CFall_Player_Manager& rhs);

	//変数
	bool m_Player1_Win; //1pが勝ったかどうか
	bool m_Draw; //引分けかどうか
};