#pragma once
#include"vivid.h"
#include"../ball_stageset/ball_stageset.h"
#include"../basket/basket.h"

class CBall
{
public:
	CBall(void);
	~CBall(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);
	//当たり判定
	bool CheckHit(const CBasket& basket1, const CBasket& basket2);
	static CBall& GetInstance();

private:

	//コピーコンストラクタ
	CBall(const CBall& rhp) = delete;

	CBall& operator=(const CBall& rhp) = delete;



	// ボールの色
	enum class BALL_COLOR
	{
		MAGENTA,
		CYAN,
		YELLOW,
		MAX,
	};

	//ボールの状態
	enum BALL_STATE
	{
		SPAWN,	//生成
		FALL,	//落下
	};

	//ボール構造体
	struct BALL
	{
		vivid::Vector2 m_pos;		  //位置
		vivid::Vector2 m_oldpos;	  //前フレームの位置
		vivid::Vector2 m_velocity;	  //速さ
		float          m_radius;	  //半径
		bool           m_activeFlag;  //有効・無効
		int            m_score;		  //スコア
		bool           m_isLanding;	  //着地フラグ(地面についているか)
		vivid::Vector2 m_anchor;	  //基準点
		vivid::Vector2 m_scale;		  //拡大率
		BALL_COLOR	   m_color;		  //色
		BALL_STATE     m_state;		  //状態
		bool		   m_reboundFlag; //跳ね返りフラグ
	};

	CBallStageSet m_ball_stageset;

	//スコア加算
	void AddScore(BALL& ball, int playerNo);
	//球の出現管理
	void SpawnBall(void);
	//球の更新
	void UpdateBall(BALL& ball);

	//定数
	static const int	m_max_ball = 50;		//最大数
	static const int    m_color_ratio = 10;
	static const int	m_ball_radius;			//半径
	static const int	m_ball_width;			//幅
	static const int	m_ball_height;			//高さ
	static const int	m_ball_spawn_interval;	//発生間隔
	static const int	m_ball_default_score;	//デフォルトスコア
	static const float	m_ball_scale_speed;		//拡大スピード


	//変数
	BALL  m_Balls[m_max_ball];//ボールの配列(存在する全ボール)
	BALL_COLOR m_ColorList[m_color_ratio];//生成候補色リスト
	int   m_BallSpawn;//出現タイマー
	int   m_ColorCount;//候補色数
	float m_BallCenterX;//ボールの中心座標x
	float m_BallCenterY;//ボールの中心座標y
	float m_OldBallCenterY;//前フレームの中心座標y
	bool  m_Player1BasketCheck;//player1のかご判定
	bool  m_Player2BasketCheck;//player2のかご判定
	bool  m_EnableMagenta;//マゼンタ生成判定
	bool  m_EnableCyan;//シアン生成判定
	bool  m_EnableYellow;//イエロー生成判定
};