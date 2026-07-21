#pragma once
#include"..\..\scene\scene.h"
#include"vivid.h"

//選択できるステージ
enum class STAGE_SELECT
{
	STAGE1,//止まるな危険
	STAGE2,//玉入れ
	STAGE3,//レース
	MAX,
};

class CGamemain :public IScene
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

	//選択処理
	void StageSelect(void);

	//決定処理
	void StagePic(void);

	STAGE_SELECT GetStageSelect();

	//インスタンス呼び出す
	static CGamemain& GetInstance();


private:
	CGamemain(void);
	//コピーコンストラクタ
	CGamemain(const CGamemain& rhp) = delete;

	CGamemain& operator=(const CGamemain& rhp) = delete;

	~CGamemain(void) = default;
#if 1
	/* 選択ボタン系 */
	//定数
	static const int m_finger_width;								//選択印(指)の幅
	static const unsigned int m_select_button_color;				//選択中用の色
	static const vivid::Vector2 m_bg_pos;						//タイトル画面の画像位置
	static const std::string m_button_file[(int)STAGE_SELECT::MAX];//ボタン画像名


	//変数
	vivid::Vector2 m_Button_Pos;	//選択中のボタンの座標
	vivid::Vector2 m_Finger_Pos;	//選択印(指)の座標
	//STAGE_SELECT m_Now_Select = STAGE_SELECT::MAX;	//選択中のボタン


	/*	キーボード */
	static const int m_button_x[(int)STAGE_SELECT::MAX];			//ボタンのx座標
	static const int m_button_y;									//ボタンのy座標

	/* コントローラー */
	vivid::Vector2 m_Player1_Stick;//スティックx左右 y上下
	vivid::Vector2 m_Player2_Stick;//スティックx左右 y上下
	STAGE_SELECT m_Now_Select;//選択中のボタン


#endif

};