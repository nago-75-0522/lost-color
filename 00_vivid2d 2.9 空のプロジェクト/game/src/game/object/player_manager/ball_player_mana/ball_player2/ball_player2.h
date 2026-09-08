#pragma once
#include "vivid.h"
#include"../../../minigame_manager/ball_manager/ball_stageset/ball_stageset.h"
#include"../../../minigame_manager/ball_manager/basket/basket.h"

class CBallPlayer2
{
public:
	CBallPlayer2(void);
	~CBallPlayer2(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	//キャラクターの矩形情報
	float GetLeft() const;
	float GetRight() const;
	float GetTop() const;
	float GetBottom() const;

	// キャラクター中心位置
	vivid::Vector2 GetCenterPosition(void);
	//カゴ取得
	CBasket& GetBasket();
	//位置変更
	void AddPos(const vivid::Vector2& move);
	//攻撃判定中か
	bool IsAttack()const;
	//攻撃ヒットフラグ設定
	void SetAttackHit(bool hit);
private:

	// キャラクターアニメーション
	enum class ANIME_ID
	{
		STAND,//待機
		RUN,  //移動
	};

	// キャラクター向き
	enum class CHARACTER_DIR
	{
		LEFT = 1,  //左向き
		RIGHT = -1,//右向き
	};

	// アニメーションの切り替え
	void ChangeAnime(ANIME_ID next);

	CBallStageSet	m_stageset;
	CBasket		m_basket;

	// 定数
	static const int   m_width;		// 幅(フレーム)
	static const int   m_height;	// 高さ(フレーム)
	static const float m_speed;		// 移動速度
	static const float m_jump_power;//ジャンプ力
	static const vivid::Vector2 m_player2_marker_size;//マーカーサイズ

	//アニメーション情報
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
	int			   m_AttackTimer;	//攻撃タイマー
	bool		   m_AttackHit;		//攻撃があたったか

	vivid::Vector2 m_Player2MarkerPos;//2P表示
};