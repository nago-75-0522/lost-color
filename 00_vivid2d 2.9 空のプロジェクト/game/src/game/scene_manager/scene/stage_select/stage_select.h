#pragma once
#include"..\..\scene\scene.h"
#include"vivid.h"
#include"stage_id.h"

class CStage_Select :public IScene
{
public:

	//インスタンス呼び出す
	static CStage_Select& GetInstance();

	//初期化
	void Initialize(void)override;//多重定義

	//更新
	void Update(void)override;

	//描画
	void Draw(void)override;

	//解放
	void Finalize(void)override;

	//選択処理
	void StageSelect(void);

	//決定処理
	void StagePic(void);

	//IDの保存処理
	static void SetSelectStage(STAGE_ID id);

	//IDの取得処理
	static STAGE_ID GetStageID(void);

private:
	CStage_Select(void);
	//コピーコンストラクタ
	CStage_Select(const CStage_Select& rhp) = delete;

	CStage_Select& operator=(const CStage_Select& rhp) = delete;

	~CStage_Select(void) = default;
#if 1
	/* 選択ボタン系 */
	//定数
	static const int m_finger_width;								//選択印(指)の幅
	static const unsigned int m_select_button_color;				//選択中用の色
	static const vivid::Vector2 m_bg_pos;						//タイトル画面の画像位置
	static const std::string m_button_file[(int)STAGE_ID::MAX];//ボタン画像名
	static STAGE_ID  stage_id;//ステージ保存用id


	//変数
	vivid::Vector2 m_Button_Pos;	//選択中のボタンの座標
	vivid::Vector2 m_Finger_Pos;	//選択印(指)の座標
	//STAGE_ID m_Now_Select = STAGE_ID::MAX;	//選択中のボタン


	/*	キーボード */
	static const int m_button_x[(int)STAGE_ID::MAX];			//ボタンのx座標
	static const int m_button_y;									//ボタンのy座標

	/* コントローラー */
	vivid::Vector2 m_Player1_Stick;//スティックx左右 y上下
	vivid::Vector2 m_Player2_Stick;//スティックx左右 y上下
	STAGE_ID m_Now_Select;//選択中のボタン
#endif

};