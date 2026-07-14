#pragma once
#include"..\..\..\scene\scene.h"

class CStage3 :public IScene
{
public:

	//初期化
	void Initialize(void)override;//多重定義
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Finalize(void)override;
	//インスタンス呼び出す
	static CStage3& GetInstance();
private:
	CStage3(void);
	//コピーコンストラクタ
	CStage3(const CStage3& rhp) = delete;

	CStage3& operator=(const CStage3& rhp) = delete;

	~CStage3(void) = default;
};