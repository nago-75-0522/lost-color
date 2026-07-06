#pragma once
#include"..\..\scene\scene.h"



class COption :public IScene
{
public:

	//コンストラクタ
	COption();

	//デストラクタ
	~COption() = default;

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