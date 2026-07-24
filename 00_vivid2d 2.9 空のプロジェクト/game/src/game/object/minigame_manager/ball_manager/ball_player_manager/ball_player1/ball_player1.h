#pragma once
#include "vivid.h"
#include"../../ball_stageset/ball_stageset.h"
#include"../../basket/basket.h"


class CBallPlayer1
{
public:
	CBallPlayer1(void);
	~CBallPlayer1(void) = default;

	CBallPlayer1(const CBallPlayer1& rhp) = delete;
	CBallPlayer1& operator=(const CBallPlayer1& rhp) = delete;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	// キャラクター中心位置
	vivid::Vector2 GetCenterPosition(void);

	float GetRadius(void);	// 半径取得

	CBasket& GetBasket(); //カゴ

	static CBallPlayer1& GetInstance();

private:

	// キャラクターアニメーション
	enum class ANIME_ID
	{
		STAND,
		RUN,
	};

	// キャラクター向き
	enum class CHARACTER_DIR
	{
		LEFT = 1,
		RIGHT = -1,
	};

	void ChangeAnime(ANIME_ID next);// アニメーションの切り替え

	CBallStageSet	m_stageset;
	CBasket		m_basket;

	// 定数
	static const int   m_width;		// 幅(フレーム)
	static const int   m_height;	// 高さ(フレーム)
	static const float m_radius;	// 半径(当たり判定用)
	static const float m_speed;		// 移動速度

	static const int   m_anime_frame[];
	static const int   m_anime_time[];

	// 変数
	vivid::Vector2 m_Pos;			//位置
	vivid::Vector2 m_Velocity;		//速さ	
	CHARACTER_DIR  m_Direction;		//向き
	CHARACTER_DIR  m_DirectionNext;	//次の向き
	ANIME_ID       m_AnimeID;		//アニメタイマー
	int            m_AnimeFrame;	//フレーム
	int            m_AnimeTimer;	//タイマー
	bool		   m_MoveInput;		//ボタン判定
};