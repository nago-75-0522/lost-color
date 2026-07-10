#pragma once

class CPlayer_Manager
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	static CPlayer_Manager& GetInstance();
private:
	CPlayer_Manager(void);
	//コピーコンストラクタ
	CPlayer_Manager(const CPlayer_Manager& rhp) = delete;

	CPlayer_Manager& operator=(const CPlayer_Manager& rhp) = delete;

	~CPlayer_Manager(void) = default;
};