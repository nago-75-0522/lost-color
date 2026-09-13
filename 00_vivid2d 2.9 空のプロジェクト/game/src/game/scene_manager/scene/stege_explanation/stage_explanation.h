#pragma once
#include"..\scene.h"

class CStage_Explanation :public IScene
{
public:
	//インスタンスの取得
	static CStage_Explanation& GetInstance();

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
	CStage_Explanation(void);

	//デストラクタ
	~CStage_Explanation(void) = default;

	//コピーコンストラクタ
	CStage_Explanation(const CStage_Explanation& rhp) = delete;

	//代入演算子
	CStage_Explanation& operator=(const CStage_Explanation& rhp) = delete;

	int m_StageCount;//何回終わったかの判定
	
	static const float m_move_pos_x;
	static const float m_move_pos_y;

	std::string m_explanation_path;	//画像データを入れる配列
	int			m_glaph_handle;		//動画ハンドル　ハンドルは識別番号的なもの

};