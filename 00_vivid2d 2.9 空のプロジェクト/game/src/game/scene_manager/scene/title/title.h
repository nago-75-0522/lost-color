#pragma once
#include"..\..\scene\scene.h"



class CTitle :public IScene
{
public:

	//コンストラクタ
	CTitle();

	//デストラクタ
	~CTitle() = default;

	//初期化
	void Initialize(void)override;//多重定義
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Finalize(void)override;

private:
	//ロゴスタートの位置
	 vivid::Vector2 m_start_logo;
};