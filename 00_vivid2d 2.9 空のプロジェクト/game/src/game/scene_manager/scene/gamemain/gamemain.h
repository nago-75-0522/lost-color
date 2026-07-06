#pragma once
#include"..\..\scene\scene.h"
#include"vivid.h"

class CGamemain :public IScene
{
public:
	//インスタンス呼び出す
	static CGamemain& GetInstance();

	//コンストラクタ
	//CGamemain() = default;

	//デストラクタ
	~CGamemain() = default;
	

	//初期化
	void Initialize(void)override;//多重定義

	//更新
	void Update(void)override;

	//描画
	void Draw(void)override;

	//解放
	void Finalize(void)override;

	//選択できるステージ
	enum class STAGE_SELECT
	{
		STAGE1,//止まるな危険
		STAGE2,//玉入れ
		STAGE3,//レース
		MAX,
	};

	//選択中
	STAGE_SELECT m_NowSelect = STAGE_SELECT::MAX;

	//選択処理
	void Selct(void);

private:
	
#if 0
	/* 選択ボタン系 */
	//定数

	static const int m_finger_width;								//選択印(指)の幅
	static const unsigned int m_select_button_color;				//選択中用の色
	static const vivid::Vector2 m_button;	//ボタンの座標
	static const vivid::Vector2 m_bg_pos;						//タイトル画面の画像位置


	//変数
	static const std::string m_Button_Image[(int)STAGE_SELECT::MAX];//ボタン画像名
	vivid::Vector2 m_Finger_Pos;	//選択印(指)の座標


	/*	キーボード */
	static const int m_Button_x[(int)STAGE_SELECT::MAX];			//ボタンのx座標
	//static const int m_Button_y;									//ボタンのy座標

	/* コントローラー */
	vivid::Vector2 m_Stic;//スティックx左右 y上下

#endif
	
};