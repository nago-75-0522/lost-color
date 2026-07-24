#pragma once
#include"..\..\..\scene\scene.h"
#include"../../../../object/minigame_manager/ball_manager/ball_timer/ball_timer.h"



class CStage2 :public IScene
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
	static CStage2& GetInstance();
private:
	CStage2(void);
	//コピーコンストラクタ
	CStage2(const CStage2& rhp) = delete;

	CStage2& operator=(const CStage2& rhp) = delete;

	~CStage2(void) = default;

	CBallTimer   m_ball_timer;

};