#pragma once

#include"..\scene.h"

class CItem_Explanation :public IScene
{
public:
	//インスタンスの取得
	static CItem_Explanation& GetInstance();

	//初期化
	void Initialize(void)override;//多重定義

	//更新
	void Update(void)override;

	//描画
	void Draw(void)override;

	//解放
	void Finalize(void)override;

	//決定処理
	void NextChangeScene(void);

	//戻る処理
	void BackChengeScene(void);



private:
	//コンストラクタ
	CItem_Explanation(void);

	//デストラクタ
	~CItem_Explanation(void) = default;

	//コピーコンストラクタ
	CItem_Explanation(const CItem_Explanation& rhp) = delete;

	//代入演算子
	CItem_Explanation& operator=(const CItem_Explanation& rhp) = delete;

	int m_StageCount;//何回終わったかの判定


};