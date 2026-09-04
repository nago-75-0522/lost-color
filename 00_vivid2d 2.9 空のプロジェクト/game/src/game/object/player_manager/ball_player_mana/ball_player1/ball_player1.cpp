#include"ball_player1.h"
#include"../../../minigame_manager/ball_manager/ball/ball.h"

const int CBallPlayer1::m_width = 280;
const int CBallPlayer1::m_height = 140;
const float CBallPlayer1::m_radius = 70.0f;
const float CBallPlayer1::m_speed = 5.0f;
const float CBallPlayer1::m_jump_power = -15.0f;
const vivid::Vector2 CBallPlayer1::m_player1_marker_size = { 64.0f,40.0f };

//各アニメーションのフレーム数
const int CBallPlayer1::m_anime_frame[] = { 4,6 };
//各アニメーションの切り替え時間
const int CBallPlayer1::m_anime_time[] = { 10,10 };

CBallPlayer1::CBallPlayer1(void)
	: m_Pos(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(CHARACTER_DIR::LEFT)
	, m_DirectionNext(CHARACTER_DIR::LEFT)
	, m_AnimeID(ANIME_ID::STAND)
	, m_AnimeFrame(0)
	, m_AnimeTimer(0)
	, m_MoveInput(false)
{
}

void CBallPlayer1::ChangeAnime(ANIME_ID next)
{
	if (m_AnimeID == next)
		return;

	m_AnimeID = next;
	m_AnimeFrame = 0;
	m_AnimeTimer = 0;
}

void CBallPlayer1::Initialize(void)
{
	m_basket.Initialize();

	// 画像の読み込み
	vivid::LoadTexture("data\\ball\\character1.png");

	// 初期位置
	m_Pos.x = vivid::GetWindowWidth() / 4.0f;
	m_Pos.y = m_stageset.GroundLine() - m_height;
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f));
	m_Player1MarkerPos.x = m_Pos.x + m_width / 2 - m_player1_marker_size.x / 2;
	m_Player1MarkerPos.y = m_stageset.GroundLine();

	// 速さ
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;

	// アニメーション
	m_AnimeID = ANIME_ID::STAND;
	m_AnimeFrame = 0;
	m_AnimeTimer = 0;

	m_Direction = CHARACTER_DIR::LEFT;
	m_DirectionNext = CHARACTER_DIR::LEFT;
}

void CBallPlayer1::Update(void)
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	// 左スティック取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER1);

	// デッドゾーン設定
	const float DEAD_ZONE = 0.5f;

	m_MoveInput = false;

	// 移動方法
	//右
	if (keyboard::Button(keyboard::KEY_ID::D) || stick.x > DEAD_ZONE ||
		controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::RIGHT))
	{
		m_MoveInput = true;
		if (stick.x > DEAD_ZONE)
		{
			m_Velocity.x = m_speed * stick.x;
		}
		else
		{
			m_Velocity.x = m_speed;
		}
		m_DirectionNext = CHARACTER_DIR::RIGHT;
	}
	//左
	else if (keyboard::Button(keyboard::KEY_ID::A) || stick.x < -DEAD_ZONE ||
		controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::LEFT))
	{
		m_MoveInput = true;
		if (stick.x < -DEAD_ZONE)
		{
			m_Velocity.x = m_speed * stick.x;
		}
		else
		{
			m_Velocity.x = -m_speed;
		}
		m_DirectionNext = CHARACTER_DIR::LEFT;
	}
	//静止
	else
	{
		m_Velocity.x = 0.0f;
	}

	//ジャンプ
	if (keyboard::Button(keyboard::KEY_ID::W) || stick.x < -DEAD_ZONE ||
		controller::Button(controller::DEVICE_ID::PLAYER1, controller::BUTTON_ID::A))
	{
		//地面にいる時のみ
		if (m_Pos.y + m_height >= m_stageset.GroundLine())
			m_Velocity.y = m_jump_power;
	}


	// 向き変更時(スピードを０に)
	if (m_Direction != m_DirectionNext)
	{
		m_Direction = m_DirectionNext;
	}

	//重力処理
	m_Velocity.y += m_stageset.Gravity();

	// 位置更新
	m_Pos += m_Velocity;

	//マーカーの位置
	m_Player1MarkerPos.x = m_Pos.x + m_width / 2 - m_player1_marker_size.x / 2;
	m_Player1MarkerPos.y = m_stageset.GroundLine();

	//カゴ
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f));

	//壁判定 
	float m_BasketLeft = m_basket.GetPosition().x;	//カゴの左端
	float m_BasketRight = m_BasketLeft + m_basket.GetWidth();//カゴの右端

	// 左壁
	if (m_BasketLeft < 0.0f)
	{
		m_Pos.x -= m_BasketLeft;
		m_Velocity.x = 0.0f;
	}
	// 右壁
	if (m_BasketRight > vivid::WINDOW_WIDTH)
	{
		m_Pos.x -= m_BasketRight - vivid::WINDOW_WIDTH;
		m_Velocity.x = 0.0f;
	}
	//地面
	if (m_Pos.y + m_height > m_stageset.GroundLine())
	{
		m_Pos.y = m_stageset.GroundLine() - m_height;
		m_Velocity.y = 0.0f;
	}

	// アニメーション
	if (m_MoveInput)
	{
		ChangeAnime(ANIME_ID::RUN);
	}
	else
	{
		ChangeAnime(ANIME_ID::STAND);
	}

	//アニメーション更新
	//タイマー－の更新
	++m_AnimeTimer;

	if (m_AnimeTimer > m_anime_time[(int)m_AnimeID])
	{
		//タイマーリセット
		m_AnimeTimer = 0;
		++m_AnimeFrame;

		//フレーム番号＊１フレームの幅(アニメーションフレーム×幅)
		if (m_AnimeFrame >= m_anime_frame[(int)m_AnimeID])
		{
			m_AnimeFrame = 0;
		}
	}
}

void CBallPlayer1::Draw(void)
{
	m_basket.Draw();

	vivid::Rect rect = {};
	vivid::Vector2 m_anchor(m_width / 2.0f, 0.0f);
	vivid::Vector2 m_scale((float)m_Direction, 1.0f);

	rect.left = m_AnimeFrame * m_width;
	rect.right = rect.left + m_width;
	rect.top = (int)m_AnimeID * m_height;
	rect.bottom = rect.top + m_height;

	//マーク
	switch (CBall::GetInstance().GetPlayer1Color())
	{
	case CBall::BALL_COLOR::MAGENTA:
		vivid::DrawTexture("data\\logo\\small_pink_1p.png", m_Player1MarkerPos);
		break;

	case CBall::BALL_COLOR::YELLOW:
		vivid::DrawTexture("data\\logo\\small_yellow_1p.png", m_Player1MarkerPos);
		break;
	}

	vivid::DrawTexture("data\\ball\\character1.png", m_Pos, 0xffffffff, rect, m_anchor, m_scale);
}

void CBallPlayer1::Finalize(void)
{
}

//キャラクター情報
const vivid::Vector2& CBallPlayer1::GetPosition() const
{
	return m_Pos;
}
float CBallPlayer1::GetLeft() const
{
	return m_Pos.x + 90.0f;
}
float CBallPlayer1::GetRight() const
{
	return m_Pos.x + 190.0f;
}
float CBallPlayer1::GetTop() const
{
	return m_Pos.y;
}
float CBallPlayer1::GetBottom() const
{
	return m_Pos.y + m_height;
}


void CBallPlayer1::AddPos(const vivid::Vector2& move)
{
	m_Pos += move;
}

vivid::Vector2 CBallPlayer1::GetCenterPosition(void)
{
	return m_Pos + vivid::Vector2(m_width / 2.0f, m_height / 2.0f);
}

float CBallPlayer1::GetRadius(void)
{
	return m_radius;
}

CBasket& CBallPlayer1::GetBasket()
{
	return m_basket;
}
