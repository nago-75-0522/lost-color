#pragma once
#include"../scene.h"
class CGame_Result :public IScene
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void IniScore();
	int Get_Player1_Score() { return m_Player1_Score; }
	int Get_Player2_Score() { return m_Player2_Score; }
	//インスタンス呼び出す
	static CGame_Result& GetInstance();
	
private:
	CGame_Result(void);
	//コピーコンストラクタ
	CGame_Result(const CGame_Result& rhp) = delete;

	CGame_Result& operator=(const CGame_Result& rhp) = delete;

	~CGame_Result(void) = default;

	//定数
	static	const int m_max_score;//最大スコア
	static	const int m_max_score_digiit;//表示桁数
	static	const int m_digit_width;
	static	const int m_digit_height;

	//変数
	bool m_Player1_Ready;
	bool m_Player2_Ready;
	int m_Player1_Score;
	int m_Player2_Score;
	vivid::Vector2 m_Player1_Score_Pos;
	vivid::Vector2 m_Player2_Score_Pos;
	int m_Player1_Copy_Score;
	int m_Player2_Copy_Score;
	bool m_ScoreAdded;

};