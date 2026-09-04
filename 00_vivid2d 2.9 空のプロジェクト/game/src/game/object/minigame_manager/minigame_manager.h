#pragma once
#include"../../object/minigame_manager/fall_manager/fall.h"
#include"ball_manager/ball_manager.h"
#include"race/race_manager/race_manager.h"

enum class MINIGAME_ID
{
	NONE,
	FALL,//ステージ１
	BALL,//ステージ２
	RACE,//ステージ３
};

class CMinigame_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void SetGame(MINIGAME_ID game);
	MINIGAME_ID GetGame();
	static CMinigame_Manager& GetInstance();

	int GetRaceWinColor(void);
private:
	CMinigame_Manager(void);
	//コピーコンストラクタ
	CMinigame_Manager(const CMinigame_Manager& rhp) = delete;

	CMinigame_Manager& operator=(const CMinigame_Manager& rhp) = delete;

	~CMinigame_Manager(void) = default;

	MINIGAME_ID m_Game = MINIGAME_ID::NONE;
};