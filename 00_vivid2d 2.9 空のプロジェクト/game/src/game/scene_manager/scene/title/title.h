#pragma once
#include"..\..\scene\scene.h"



class CTitle :public IScene
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

	static CTitle& GetInstance();
private:
	CTitle(void);
	//コピーコンストラクタ
	CTitle(const CTitle& rhp) = delete;

	CTitle& operator=(const CTitle& rhp) = delete;

	~CTitle(void) = default;
	//ロゴスタートの位置
	vivid::Vector2 m_start_logo;
};