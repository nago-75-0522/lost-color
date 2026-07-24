#pragma once

enum class MINIGAME_ID
{
	NONE,
	FALL,//ステージ１
	BALL,//ステージ２
	RUN,//ステージ３
};

class CMinigame_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void SetGame(MINIGAME_ID game);
	static CMinigame_Manager& GetInstance();

private:
	CMinigame_Manager(void);
	//コピーコンストラクタ
	CMinigame_Manager(const CMinigame_Manager& rhp) = delete;

	CMinigame_Manager& operator=(const CMinigame_Manager& rhp) = delete;

	~CMinigame_Manager(void) = default;

	MINIGAME_ID m_Game = MINIGAME_ID::NONE;
};