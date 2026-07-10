#pragma once
class CMinigame_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	static CMinigame_Manager& GetInstance();

private:
	CMinigame_Manager(void);
	//コピーコンストラクタ
	CMinigame_Manager(const CMinigame_Manager& rhp) = delete;

	CMinigame_Manager& operator=(const CMinigame_Manager& rhp) = delete;

	~CMinigame_Manager(void) = default;
};