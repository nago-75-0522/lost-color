#pragma once
#include"..\..\..\scene\scene.h"



class CStage1 :public IScene
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

	static CStage1& GetInstance();
private:

	CStage1(void);
	//コピーコンストラクタ
	CStage1(const CStage1& rhp) = delete;

	CStage1& operator=(const CStage1& rhp) = delete;

	~CStage1(void) = default;

};