#pragma once
#include"..\..\scene\scene.h"

//キャラクター選択
enum class CHARACTER_ID
{
	CHARA1,
	CHARA2,
	CHARA3,
	CHARA4,
	MAX,
};

//キャラクター構造体
struct Character
{
	//データファイル
	std::string file;

	//キャラクターのテクスチャID
	int texterID;

	//position
	float posX;
	float posY;

};

class COption :public IScene
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
	static COption& GetInstance();

	void SetCharacter(void);//二人ともが準備完了したら


private:
	//コンストラクタ・デストラクタ
	COption(void);
	~COption(void) = default;
	
	//コピーコンストラクタ
	COption(const COption& rhp) = delete;
	//代入演算子
	COption& operator=(const COption& rhp) = delete;

	
	//文字関連
	static int m_select_width;//選んでねの画像幅
	static int m_select_height;//選んでねの画像高さ

	static int m_ok_width;//ok幅
	static int m_ok_height;//ok高さ

	
	//キャラクター関係
	bool m_player1_ok;
	bool m_player2_ok;




	/*	キーボード */
	static const int m_button_x[(int)CHARACTER_ID::MAX];			//ボタンのx座標
	static const int m_button_y;									//ボタンのy座標

	/* コントローラー */
	vivid::Vector2 m_Player1_Stick;//スティックx左右 y上下
	vivid::Vector2 m_Player2_Stick;//スティックx左右 y上下
	CHARACTER_ID m_Now_Select;//選択中のボタン
};