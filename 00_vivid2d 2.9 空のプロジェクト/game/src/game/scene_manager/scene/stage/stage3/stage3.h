#pragma once
#include"..\..\..\scene\scene.h"

class CStage3 :public IScene
{
public:

	//インスタンス呼び出す
	static CStage3& GetInstance();

	//コンストラクタ
	CStage3() = default;

	//デストラクタ
	~CStage3() = default;

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