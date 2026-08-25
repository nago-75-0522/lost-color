#include"vivid.h"
#include"ball.h"
#include"../ball_score/ball_score.h"
#include"../../../../scene_manager/scene/color_select/color_select.h"

const int			CBall::m_ball_radius = 16;
const int			CBall::m_ball_width = 32;
const int			CBall::m_ball_height = 32;
const int			CBall::m_ball_spawn_interval = 1 * 30;
const float			CBall::m_ball_scale_speed = 1.0f / 15.0f;

//コンストラクタ
CBall::CBall(void)
	: m_BallSpawn(0)
	, m_ColorCount(0)
	, m_BallCenterX(0)
	, m_BallCenterY(0)
	, m_Old_Magenta(true)
	, m_Old_Cyan(true)
	, m_Old_Yellow(true)
#ifdef _DEBUG
	, m_BombCount1(0)
	, m_BombCount2(0)
#endif
{
}

//初期化
void CBall::Initialize(void)
{
#ifdef _DEBUG
	m_BombCount1 = 0;
	m_BombCount2 = 0;
#endif

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
	}
	m_BallSpawn = m_ball_spawn_interval;//生成タイマー初期化

	//SEの読み込み
	vivid::LoadSound("data\\sound\\ball.wav");//ballキャッチ時

	m_Cyan = CColor_Select::GetInstance().GetCyan();
	m_Yellow = CColor_Select::GetInstance().GetYellow();
	m_Magenta = CColor_Select::GetInstance().GetMagenta();
	if (!m_Old_Cyan)
		m_Cyan = m_Old_Cyan;
	if (!m_Old_Yellow)
		m_Yellow = m_Old_Yellow;
	if (!m_Old_Magenta)
		m_Magenta = m_Old_Magenta;

}

//更新
void CBall::Update(void)
{
	if (m_Old_Cyan)
		m_Old_Cyan = CColor_Select::GetInstance().GetCyan();
	if (m_Old_Yellow)
		m_Old_Yellow = CColor_Select::GetInstance().GetYellow();
	if (m_Old_Magenta)
		m_Old_Magenta = CColor_Select::GetInstance().GetMagenta();

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
	vivid::DrawTexture("data\\ball_bg.png", { 0.0f,0.0f });
	m_ball_stageset.Draw();
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

			if (!m_Magenta)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFFFF00FF);
			}
			break;

		case BALL_COLOR::CYAN:

			if (!m_Cyan)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF00FFFF);
			}
			break;

		case BALL_COLOR::YELLOW:

			if (!m_Yellow)
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFF808080);
			}
			else
			{
				vivid::DrawTexture("data\\ball.png", ball.m_pos, 0xFFFFFF00);
			}
			break;

		case BALL_COLOR::BOMB:
			vivid::DrawTexture("data\\bomb.png", ball.m_pos);
			break;
		}
	}
#ifdef _DEBUG/*デバックビルドのときのみ有効*/
	//vivid::DrawText(30, ("Save C=" + std::to_string(m_Old_Cyan)+ " Y=" + std::to_string(m_Old_Yellow) 
		//+ " M=" + std::to_string(m_Old_Magenta)).c_str(), {100,100});
	//vivid::DrawText(30, ("Now C=" + std::to_string(m_Cyan)
		//+ " Y=" + std::to_string(m_Yellow) + " M=" + std::to_string(m_Magenta)).c_str(), { 100, 150 });

	vivid::DrawText(30, ("m =" + std::to_string(CBallScore::GetInstance().GetPlayer1Magenta())
		+ "c=" + std::to_string(CBallScore::GetInstance().GetPlayer1Cyan())
		+ "y=" + std::to_string(CBallScore::GetInstance().GetPlayer1Yellow())
		+ "b=" + std::to_string(m_BombCount1)).c_str(), { 50, 200 });
	vivid::DrawText(30, ("m =" + std::to_string(CBallScore::GetInstance().GetPlayer2Magenta())
		+ "c=" + std::to_string(CBallScore::GetInstance().GetPlayer2Cyan())
		+ "y=" + std::to_string(CBallScore::GetInstance().GetPlayer2Yellow())
		+ "b=" + std::to_string(m_BombCount2)).c_str(), { 50, 250 });

#endif
}
//解放
void CBall::Finalize(void)
{
}

void CBall::IniOld()
{
	m_Old_Cyan = true;
	m_Old_Yellow = true;
	m_Old_Magenta = true;
}


//当たり判定
//内容は(円)と(矩形)の判定
void CBall::CheckHit(const CBasket& basket1, const CBasket& basket2)
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

		if (m_Player1BasketCheck)
		{
			vivid::PlaySound("data\\sound\\ball.wav", false);
			AddScore(ball, 1);
			ball.m_activeFlag = false;
		}
		else if (m_Player2BasketCheck)
		{
			vivid::PlaySound("data\\sound\\ball.wav", false);
			AddScore(ball, 2);
			ball.m_activeFlag = false;
		}
	}
}

CBall& CBall::GetInstance()
{
	static CBall instance;
	return instance;
}

void CBall::AddScore(BALL& ball, int playerNo)
{
	//爆弾
	if (ball.m_color == BALL_COLOR::BOMB)
	{
#ifdef _DEBUG
		if (playerNo == 1)
			++m_BombCount1;
		else
			++m_BombCount2;
#endif
		if (playerNo == 1)
		{
			CBallScore::GetInstance().AddPlayer1Score(-10);
		}
		else
		{
			CBallScore::GetInstance().AddPlayer2Score(-10);
		}
		return;
	}

	//個数
	if (playerNo == 1)
	{
		switch (ball.m_color)
		{
		case BALL_COLOR::MAGENTA:
			CBallScore::GetInstance().AddPlayer1Magenta();
			break;
		case BALL_COLOR::CYAN:
			CBallScore::GetInstance().AddPlayer1Cyan();
			break;
		case BALL_COLOR::YELLOW:
			CBallScore::GetInstance().AddPlayer1Yellow();
			break;
		}
	}
	else
	{
		switch (ball.m_color)
		{
		case BALL_COLOR::MAGENTA:
			CBallScore::GetInstance().AddPlayer2Magenta();
			break;
		case BALL_COLOR::CYAN:
			CBallScore::GetInstance().AddPlayer2Cyan();
			break;
		case BALL_COLOR::YELLOW:
			CBallScore::GetInstance().AddPlayer2Yellow();
			break;
		}

	}

	//点数
	COLOR_ROLE role = GetColorRole(ball.m_color);

	//共通色のみ20点
	int score = 10;
	if (role == COLOR_ROLE::COMMON)
		score = 20;

	switch (role)
	{
	case COLOR_ROLE::PLAYER1:

		//誰が取っても1Pの得点
		CBallScore::GetInstance().AddPlayer1Score(score);
		break;

	case COLOR_ROLE::PLAYER2:

		//誰が取っても2Pの得点
		CBallScore::GetInstance().AddPlayer2Score(score);
		break;

	case COLOR_ROLE::COMMON:

		//取った人の得点
		if (playerNo == 1)
		{
			CBallScore::GetInstance().AddPlayer1Score(score);
		}
		else
		{
			CBallScore::GetInstance().AddPlayer2Score(score);
		}
		break;
	}
}

CBall::COLOR_ROLE CBall::GetColorRole(BALL_COLOR color)
{
	//全色無効
	if (!m_Magenta && !m_Cyan && !m_Yellow)
	{
		if (color == BALL_COLOR::MAGENTA)
			return COLOR_ROLE::PLAYER1;//マゼンタは1p用
		if (color == BALL_COLOR::CYAN)
			return COLOR_ROLE::PLAYER2;//シアンは2p用

		return COLOR_ROLE::COMMON;//残り(イエロー)は共通
	}

	int disableCount = (!m_Magenta ? 1 : 0) +
		(!m_Cyan ? 1 : 0) + (!m_Yellow ? 1 : 0);

	//全色有効
	if (disableCount == 0)
	{
		if (color == BALL_COLOR::MAGENTA)
			return COLOR_ROLE::PLAYER1;
		if (color == BALL_COLOR::CYAN)
			return COLOR_ROLE::PLAYER2;

		return COLOR_ROLE::COMMON;
	}

	//1色消滅
	if (disableCount == 1)
	{
		if (!m_Magenta)//マゼンタが消えた場合
		{
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::COMMON;//マゼンタを共通色に
			if (color == BALL_COLOR::YELLOW)
				return COLOR_ROLE::PLAYER1;//イエローを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
		if (!m_Cyan)//シアンが消えた場合
		{
			if (color == BALL_COLOR::CYAN)
				return COLOR_ROLE::COMMON;//シアンを共通色に
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::PLAYER1;//マゼンタを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
		if (!m_Yellow)//イエローが消えた場合
		{
			if (color == BALL_COLOR::YELLOW)
				return COLOR_ROLE::COMMON;//イエローを共通色に
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::PLAYER1;//マゼンタを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
	}

	//2色消滅
	if (disableCount == 2)
	{
		if (m_Yellow)//イエローが残った場合
		{
			if (color == BALL_COLOR::YELLOW)
				return COLOR_ROLE::COMMON;//イエローを共通色に
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::PLAYER1;//マゼンタを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
		if (m_Cyan)//シアンが残った場合
		{
			if (color == BALL_COLOR::CYAN)
				return COLOR_ROLE::COMMON;//シアンを共通色に
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::PLAYER1;//マゼンタを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
		if (m_Magenta)//マゼンタが残った場合
		{
			if (color == BALL_COLOR::MAGENTA)
				return COLOR_ROLE::COMMON;//マゼンタを共通色に
			if (color == BALL_COLOR::YELLOW)
				return COLOR_ROLE::PLAYER1;//イエローを1p用に

			return COLOR_ROLE::PLAYER2;//残りを2p用に
		}
	}

	return COLOR_ROLE::COMMON;
}
//1pの画像色
CBall::BALL_COLOR CBall::GetPlayer1Color()
{
	if (GetColorRole(BALL_COLOR::MAGENTA) == COLOR_ROLE::PLAYER1)
		return BALL_COLOR::MAGENTA;

	return BALL_COLOR::YELLOW;
}
//2pの画像色
CBall::BALL_COLOR CBall::GetPlayer2Color()
{
	if (GetColorRole(BALL_COLOR::CYAN) == COLOR_ROLE::PLAYER2)
		return BALL_COLOR::CYAN;

	return BALL_COLOR::YELLOW;
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

			//ランダムに色決定
			int type = rand() % 100;
			if (type < 45)
			{
				ball.m_color = GetPlayer1Color();
			}
			else if (type < 90)
			{
				ball.m_color = GetPlayer2Color();
			}
			else if (type < 98)
			{
				//共通色
				if (GetColorRole(BALL_COLOR::MAGENTA) == COLOR_ROLE::COMMON)
					ball.m_color = BALL_COLOR::MAGENTA;
				else if (GetColorRole(BALL_COLOR::CYAN) == COLOR_ROLE::COMMON)
					ball.m_color = BALL_COLOR::CYAN;
				else
					ball.m_color = BALL_COLOR::YELLOW;
			}
			else
			{
				ball.m_color = BALL_COLOR::BOMB;
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
			ball.m_activeFlag = false;//地面に着いたら消滅
		}
		break;
	}
}