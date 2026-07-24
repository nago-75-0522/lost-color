#pragma once
#include"vivid.h"
#include"../number_def.h"

class CBallScore
{
public:
	//シングルトンインスタンス取得
	static CBallScore& GetInstance();

	void Initialize(void);
	void Draw(const vivid::Vector2& position, int m_score);
	void Finalize(void);

	//スコアの加算
	void AddPlayer1Score(int m_score) { m_Player1Score += m_score; };
	void AddPlayer2Score(int m_score) { m_Player2Score += m_score; };
	//色ごとの取得数加算
	void AddPlayer1Magenta() { m_Player1Magenta++; };
	void AddPlayer1Cyan() { m_Player1Cyan++; };
	void AddPlayer1Yellow() { m_Player1Yellow++; };

	void AddPlayer2Magenta() { m_Player2Magenta++; };
	void AddPlayer2Cyan() { m_Player2Cyan++; };
	void AddPlayer2Yellow() { m_Player2Yellow++; };

	// スコアの取得(リザルト画面で使用)
	int GetPlayer1Score() const { return m_Player1Score; };
	int GetPlayer2Score() const { return m_Player2Score; };
	//色ごとの取得数を取得(リザルト画面で使用)
	int GetPlayer1Magenta() const { return m_Player1Magenta; };
	int GetPlayer1Cyan() const { return m_Player1Cyan; };
	int GetPlayer1Yellow() const { return m_Player1Yellow; };

	int GetPlayer2Magenta() const { return m_Player2Magenta; };
	int GetPlayer2Cyan() const { return m_Player2Cyan; };
	int GetPlayer2Yellow() const { return m_Player2Yellow; };


private:
	CBallScore(void);
	~CBallScore(void) = default;

	CBallScore(const CBallScore&) = default;//コピーコンストラクタ禁止
	CBallScore& operator = (const CBallScore&) = default;//代入演算子禁止

	//定数
	static const int m_max_score;		//最大スコア
	static const int m_max_score_digit;	//表示桁数

	//変数
	int m_Player1Score;//プレイヤー１総スコア
	int m_Player2Score;//プレイヤー２総スコア

	int m_Player1Magenta;//プレイヤー1のマゼンタ取得数
	int m_Player1Cyan;//プレイヤー1のシアン取得数
	int m_Player1Yellow;//プレイヤー1のイエロー取得数

	int m_Player2Magenta;//プレイヤー2のマゼンタ取得数
	int m_Player2Cyan;//プレイヤー2のシアン取得数
	int m_Player2Yellow;//プレイヤー2のイエロー取得数

};
