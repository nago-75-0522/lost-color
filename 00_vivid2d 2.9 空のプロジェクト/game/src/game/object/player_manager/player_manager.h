#pragma once

class CPlayer_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();

	bool GameFinish(); //ゲームが終わったかどうか

	bool Player1_Win() { return m_Player1_Win; }
	bool Draw_Battle() { return m_Draw; }

	static CPlayer_Manager& GetInstance();
private:
	CPlayer_Manager(void);
	//コピーコンストラクタ
	CPlayer_Manager(const CPlayer_Manager& rhp) = delete;

	CPlayer_Manager& operator=(const CPlayer_Manager& rhp) = delete;

	~CPlayer_Manager(void) = default;

	bool m_Player1_Win; //プレイヤー１が勝ったかどうか
	bool m_Draw; //引分けかどうか
};