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

	static const int m_win_width;
	static const int m_win_height;
	static const vivid::Vector2 m_win_pos;
	static const int m_draw_width;
	static const int m_draw_height;
	static const vivid::Vector2 m_draw_pos;
};