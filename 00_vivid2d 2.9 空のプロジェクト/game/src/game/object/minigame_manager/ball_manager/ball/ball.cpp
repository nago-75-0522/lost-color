#include"vivid.h"
#include"ball.h"
#include"../ball_score/ball_score.h"
#include"../../../../scene_manager/scene/color_select/color_select.h"

const int			CBall::m_ball_radius = 16.0f;
const int			CBall::m_ball_width = 32;
const int			CBall::m_ball_height = 32;
const int			CBall::m_ball_spawn_interval = 1 * 30;
const float			CBall::m_ball_scale_speed = 1.0f / 15.0f;

//コンストラクタ
CBall::CBall(void)
	:m_BallSpawn(0)
	, m_ColorCount(0)
	, m_BallCenterX(0)
	, m_BallCenterY(0)
	, m_EnableMagenta(true)
	, m_EnableCyan(true)
	, m_EnableYellow(true)
{
}

//初期化
void CBall::Initialize(void)
{
	//全ボールの初期化
	for (int i = 0; i < m_max_ball; i++)
	{
		BALL& ball = m_Balls[i];//参照型に置き換える

		ball.m_pos = vivid::Vector2::ZERO;
		ball.m_oldpos = vivid::Vector2::ZERO;
		ball.m_velocity = vivid::Vector2::ZERO;
		ball.m_radius = m_ball_radius;
		ball.m_activeFlag = false;//無効
		ball.m_isLanding = false;//着地していない
		ball.m_anchor = vivid::Vector2(m_ball_width / 2, m_ball_height / 2);
		ball.m_scale = vivid::Vector2(0.0f, 0.0f);//開始サイズ
		ball.m_state = BALL_STATE::SPAWN;//生成
		ball.m_reboundFlag = false;
	}
	m_BallSpawn = m_ball_spawn_interval;//生成タイマー初期化
}

//更新
void CBall::Update(void)
{
	SpawnBall();

	//各更新(有効なもののみ)
	for (int i = 0; i < m_max_ball; ++i)
	{
		BALL& ball = m_Balls[i];

		if (!ball.m_activeFlag)
			continue;

		UpdateBall(ball);
	}
}

//描画
void CBall::Draw(void)
{
	bool BlueEnable = CColor_Select::GetInstance().GetBlue();
	bool YellowEnable = CColor_Select::GetInstance().GetYellow();
	bool RedEnable = CColor_Select::GetInstance().GetRed();

	vivid::Rect rect = { 0,0,m_ball_width,m_ball_height };

	for (int i = 0; i < m_max_ball; ++i)
	{
		BALL& ball = m_Balls[i];

		if (ball.m_activeFlag == false)
			continue;

		//色ごとに描画色変更
		switch (ball.m_color)
		{
		case BALL_COLOR::MAGENTA:

			if (!RedEnable)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFFFF00FF);
			}
			break;

		case BALL_COLOR::CYAN:

			if (!BlueEnable)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF00FFFF);
			}
			break;

		case BALL_COLOR::YELLOW:

			if (!YellowEnable)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFFFFFF00);
			}
			break;
		}
	}
}
//解放
void CBall::Finalize(void)
{
}


//当たり判定
//内容は(円)と籠(四角)の判定
bool CBall::CheckHit(const CBasket& basket1, const CBasket& basket2)
{
	for (int i = 0; i < m_max_ball; i++)
	{
		BALL& ball = m_Balls[i];

		if (!ball.m_activeFlag)
			continue;

		//ボールの中心座標
		m_BallCenterX = ball.m_pos.x + m_ball_width / 2.0f;
		m_BallCenterY = ball.m_pos.y + m_ball_height / 2.0f;

		//前フレームの位置
		m_OldBallCenterY = ball.m_oldpos.y + m_ball_height / 2.0f;

		//player1のかご判定
		m_Player1BasketCheck =
			m_BallCenterX >= basket1.GetPosition().x &&
			m_BallCenterX <= basket1.GetPosition().x + basket1.GetWidth() &&
			m_OldBallCenterY < basket1.GetPosition().y &&
			m_BallCenterY >= basket1.GetPosition().y;

		//player2のかご判定
		m_Player2BasketCheck =
			m_BallCenterX >= basket2.GetPosition().x &&
			m_BallCenterX <= basket2.GetPosition().x + basket2.GetWidth() &&
			m_OldBallCenterY < basket2.GetPosition().y &&
			m_BallCenterY >= basket2.GetPosition().y;

		if (ball.m_color == BALL_COLOR::MAGENTA)
		{
			// 両方の籠に入った場合はPlayer1優先
			if (m_Player1BasketCheck && m_Player2BasketCheck)
			{
				AddScore(ball, 1);//得点
				ball.m_activeFlag = false;//消滅
			}
			// Player1のみ
			else if (m_Player1BasketCheck)
			{
				AddScore(ball, 1);//得点
				ball.m_activeFlag = false;//消滅
			}
			// Player2のみ
			else if (m_Player2BasketCheck)
			{
				AddScore(ball, 2);
				ball.m_activeFlag = false;
			}
		}
		else if (ball.m_color == BALL_COLOR::CYAN)
		{

			// 両方の籠に入った場合はPlayer2優先
			if (m_Player1BasketCheck && m_Player2BasketCheck)
			{
				AddScore(ball, 2);
				ball.m_activeFlag = false;
			}
			// Player1のみ
			else if (m_Player1BasketCheck)
			{
				AddScore(ball, 1);
				ball.m_activeFlag = false;
			}
			// Player2のみ
			else if (m_Player2BasketCheck)
			{
				AddScore(ball, 2);
				ball.m_activeFlag = false;
			}
		}
		else if (ball.m_color == BALL_COLOR::YELLOW)
		{
			//両方の籠に入った
			if (m_Player1BasketCheck && m_Player2BasketCheck)
			{
				if (ball.m_velocity.y > 0.0f)
				{
					ball.m_velocity.y = -8.0f; //上へ跳ねる
				}
			}
			//Player1のみ
			else if (m_Player1BasketCheck)
			{
				AddScore(ball, 1);
				ball.m_activeFlag = false;
			}
			// Player2のみ
			else if (m_Player2BasketCheck)
			{
				AddScore(ball, 2);
				ball.m_activeFlag = false;
			}
		}
	}
	return false;
}

CBall& CBall::GetInstance()
{
	static CBall instance;
	return instance;
}

void CBall::AddScore(BALL& ball, int playerNo)
{
	switch (ball.m_color)
	{
	case BALL_COLOR::MAGENTA:

		//誰が取っても1Pの得点
		CBallScore::GetInstance().AddPlayer1Score(ball.m_score);
		if (playerNo == 1)
		{
			CBallScore::GetInstance().AddPlayer1Magenta();
		}
		else
		{
			CBallScore::GetInstance().AddPlayer2Magenta();
		}
		break;

	case BALL_COLOR::CYAN:

		//誰が取っても2Pの得点
		CBallScore::GetInstance().AddPlayer2Score(ball.m_score);
		if (playerNo == 1)
		{
			CBallScore::GetInstance().AddPlayer1Cyan();
		}
		else
		{
			CBallScore::GetInstance().AddPlayer2Cyan();
		}
		break;

	case BALL_COLOR::YELLOW:

		//取った人の得点
		if (playerNo == 1)
		{
			CBallScore::GetInstance().AddPlayer1Score(ball.m_score);
			CBallScore::GetInstance().AddPlayer1Yellow();
		}
		else
		{
			CBallScore::GetInstance().AddPlayer2Score(ball.m_score);
			CBallScore::GetInstance().AddPlayer2Yellow();
		}
		break;
	}
}
//球の出現管理
void CBall::SpawnBall(void)
{
	//出現管理
	if (--m_BallSpawn <= 0)
	{
		m_BallSpawn = m_ball_spawn_interval;//タイマーリセット

		for (int i = 0; i < m_max_ball; i++)
		{
			BALL& ball = m_Balls[i];

			if (ball.m_activeFlag == true)//使用中なら次へ
				continue;

			//生成時の値の設定
			ball.m_pos.x = (float)(rand() % (vivid::WINDOW_WIDTH - m_ball_width));
			ball.m_pos.y = 0.0f;
			ball.m_velocity = vivid::Vector2::ZERO;
			ball.m_activeFlag = true;
			ball.m_isLanding = false;
			ball.m_anchor = vivid::Vector2(m_ball_width / 2, m_ball_height / 2);
			ball.m_scale = vivid::Vector2(0.0f, 0.0f);
			ball.m_state = BALL_STATE::SPAWN;
			ball.m_reboundFlag = false;

			//ランダムに色決定
			int type = rand() % 10;
			if (type < 4)
			{
				ball.m_color = BALL_COLOR::MAGENTA;
				ball.m_score = 10;
			}
			else if (type < 8)
			{
				ball.m_color = BALL_COLOR::CYAN;
				ball.m_score = 10;
			}
			else
			{
				ball.m_color = BALL_COLOR::YELLOW;
				ball.m_score = 20;
			}
			// 1個生成したら終了
			break;
		}
	}

}
// 球の更新
void CBall::UpdateBall(BALL& ball)
{
	//生成直後(拡大)
	switch (ball.m_state)
	{
	case BALL_STATE::SPAWN:

		//落下前に大きくする
		ball.m_scale.x += m_ball_scale_speed;
		ball.m_scale.y += m_ball_scale_speed;

		if (ball.m_scale.x >= 1.0f)//元のサイズになったら落下開始
		{
			ball.m_scale.x = 1.0f;
			ball.m_scale.y = 1.0f;
			ball.m_state = BALL_STATE::FALL;//落下処理へ
		}
		break;

		//落下状態(重力落下)
	case BALL_STATE::FALL:

		//重力
		ball.m_velocity.y += m_ball_stageset.Gravity() * 0.2f;//落下速度

		//前フレーム位置保存
		ball.m_oldpos = ball.m_pos;

		//位置の更新
		ball.m_pos += ball.m_velocity;

		//地面の判定
		if (ball.m_pos.y + m_ball_height > m_ball_stageset.GroundLine())
		{
			ball.m_pos.y = m_ball_stageset.GroundLine() - m_ball_height;
			ball.m_velocity.y = 0.0f;
			ball.m_reboundFlag = false;
			ball.m_activeFlag = false;//地面に着いたら消滅
		}
		break;
	}
}

