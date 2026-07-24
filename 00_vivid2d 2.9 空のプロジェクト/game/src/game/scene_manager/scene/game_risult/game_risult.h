#pragma once
#include"../scene.h"
class CGame_Result :public IScene
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	//インスタンス呼び出す
	static CGame_Result& GetInstance();
private:
	CGame_Result(void);
	//コピーコンストラクタ
	CGame_Result(const CGame_Result& rhp) = delete;

	CGame_Result& operator=(const CGame_Result& rhp) = delete;

	~CGame_Result(void) = default;
};