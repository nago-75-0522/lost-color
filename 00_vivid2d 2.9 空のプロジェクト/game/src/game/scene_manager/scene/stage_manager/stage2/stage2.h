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

	bool GetWinner();
	bool GetDraw();
	void RisultIni();
private:
	CStage2(void);
	//コピーコンストラクタ
	CStage2(const CStage2& rhp) = delete;

	CStage2& operator=(const CStage2& rhp) = delete;

	~CStage2(void) = default;

	enum class STAGE2_STATE
	{
		MAIN,// ゲームメイン
		RESULT,// リザルト
	};
	STAGE2_STATE m_State;

	CBallTimer   m_ball_timer;

	int m_ResultTimer;//画面切り替え時間
	bool m_Winner;
	bool m_Draw;
};