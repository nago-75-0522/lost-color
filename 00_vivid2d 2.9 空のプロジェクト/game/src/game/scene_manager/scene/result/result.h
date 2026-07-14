#pragma once
#include"..\..\scene\scene.h"

class CResult :public IScene
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
	static CResult& GetInstance();
private:
	CResult(void);
	//コピーコンストラクタ
	CResult(const CResult& rhp) = delete;

	CResult& operator=(const CResult& rhp) = delete;

	~CResult(void) = default;

};