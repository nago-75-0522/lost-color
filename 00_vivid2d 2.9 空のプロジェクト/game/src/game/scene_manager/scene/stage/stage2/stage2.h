#pragma once
#include"..\..\..\scene\scene.h"



class CStage2 :public IScene
{
public:

	//インスタンス呼び出す
	static CStage2& GetInstance();

	//コンストラクタ
	CStage2() = default;

	//デストラクタ
	~CStage2() = default;

	//初期化
	void Initialize(void)override;//多重定義
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Finalize(void)override;

private:

};