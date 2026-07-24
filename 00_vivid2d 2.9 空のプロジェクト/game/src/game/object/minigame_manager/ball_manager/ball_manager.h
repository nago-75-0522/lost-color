#pragma once
#pragma once
#include"ball/ball.h"
#include"ball_player_manager/ball_player1/ball_player1.h"
#include"ball_player_manager/ball_player2/ball_player2.h"


class CBallManager
{
public:
	//初期化
	void Initialize(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);
	//インスタンス呼び出す
	static CBallManager& GetInstance();
private:
	CBallManager(void);
	//コピーコンストラクタ
	CBallManager(const CBallManager& rhp) = delete;

	CBallManager& operator=(const CBallManager& rhp) = delete;

	~CBallManager(void) = default;

	CBallPlayer1 m_ball_player1;
	CBallPlayer2 m_ball_player2;
	CBall        m_ball;
};