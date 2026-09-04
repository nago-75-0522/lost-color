#pragma once
#include"..\..\..\scene\scene.h"
#include"stage3_id.h"
#include"../phase/phase.h"

class CStage3 :public IScene
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
	static CStage3& GetInstance();
private:
	CStage3(void);
	//コピーコンストラクタ
	CStage3(const CStage3& rhp) = delete;

	CStage3& operator=(const CStage3& rhp) = delete;

	~CStage3(void) = default;

	void Presentation(void);

	static const int m_win_color_size;
	static const int m_chara_count; //文字数
	static const int m_move_start_time; //動き始めるまでの時間

	vivid::Vector2 m_Win_Color_Pos; //当たりの色を表示する場所
	vivid::Vector2 m_Win_Color_Velocity;
	int m_Move_Start_Timer; //動き始めるまでの制限時間

	RACE_STATE m_Race_State;
	CPhase m_Phase;
	bool m_Added; //足したかどうか

};