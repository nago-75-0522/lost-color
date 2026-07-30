#pragma once
#include"../scene.h"
#include"vivid.h"
class CColor_Select :public IScene
{
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	//選択処理
	void ColorSel(void);

	//決定処理
	void ColorPic(void);
	void IniChosen();
	void IniColor();
	bool GetCyan() { return m_Cyan; }
	bool GetMagenta() { return m_Magenta; }
	bool GetYellow() { return m_Yellow; }
	static CColor_Select& GetInstance();

	enum class COLOR
	{
		CYAN,
		YELLOW,
		MAGENTA,
		MAX,
	};

	bool IsEnableColor(COLOR color);

private:

	

	CColor_Select(void);
	//コピーコンストラクタ
	CColor_Select(const CColor_Select& rhp) = delete;

	CColor_Select& operator=(const CColor_Select& rhp) = delete;

	~CColor_Select(void) = default;

	//定数
	static const int m_finger_width;								//選択印(指)の幅
	static const unsigned int m_select_color;				//選択中の色用
	static const vivid::Vector2 m_panel_pos;						    //画像位置
	static const std::string m_button_file[(int)COLOR::MAX];//ボタン画像名
	static const int m_button_x[(int)COLOR::MAX];			//ボタンのx座標
	static const int m_button_y;						    //ボタンのy座標
	static const vivid::Vector2 m_Cyan_Pos;
	static const vivid::Vector2 m_Yellow_Pos;
	static const vivid::Vector2 m_Magenta_Pos;
	static const unsigned int m_selected_color;//一回選ばれたことのある色用
	
	//変数
	vivid::Vector2 m_color_pos;
	bool m_Cyan;
	bool m_Yellow;
	bool m_Magenta;
	vivid::Vector2 m_Button_Pos;//選択中のボタンの座標
	vivid::Vector2 m_Finger_Pos;//選択印(指)の座標
	vivid::Vector2 m_Player1_Stick;//スティックx左右 y上下
	vivid::Vector2 m_Player2_Stick;//スティックx左右 y上下
	COLOR m_Now_Color;//選択中のボタン
	
	bool m_Stage1_Chosen;
	bool m_Stage2_Chosen;
	bool m_Stage3_Chosen;
};