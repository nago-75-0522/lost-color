#include"ball_player2.h"

const int CBallPlayer2::m_width = 280;
const int CBallPlayer2::m_height = 140;
const float CBallPlayer2::m_radius = 70.0f;
const float CBallPlayer2::m_speed = 5.0;

//デバック用
std::string Player2ID[] = { "STAND","RUN" };

//各アニメーションのフレーム数
const int CBallPlayer2::m_anime_frame[] = { 4,6 };
//各アニメーションの切り替え時間
const int CBallPlayer2::m_anime_time[] = { 10,10 };

CBallPlayer2::CBallPlayer2(void)
	:m_Pos(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Direction(CHARACTER_DIR::LEFT)
	, m_DirectionNext(CHARACTER_DIR::LEFT)
	, m_AnimeID(ANIME_ID::STAND)
	, m_AnimeFrame(0)
	, m_AnimeTimer(0)
	, m_MoveInput(false)
{
}

void CBallPlayer2::ChangeAnime(ANIME_ID next)
{
	if (m_AnimeID == next)
		return;

	m_AnimeID = next;
	m_AnimeFrame = 0;
	m_AnimeTimer = 0;
}

void CBallPlayer2::Initialize(void)
{
	m_basket.Initialize();

	// 画像の読み込み
	vivid::LoadTexture("data\\character1.png");

	// 初期位置
	m_Pos.x = vivid::GetWindowWidth() / 2.0f;
	m_Pos.y = m_stageset.GroundLine() - m_height;
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f));

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

void CBallPlayer2::Update(void)
{
#if 0
	namespace controller = vivid::controller;

	// 左スティック取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);

	// デッドゾーン設定
	const float DEAD_ZONE = 0.7f;

	// 移動方法
	if (controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::RIGHT))
	{
		m_MoveInput = true;

		m_Velocity.x = m_speed;
		m_DirectionNext = CHARACTER_DIR::RIGHT;
	}
	else if (controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::LEFT))
	{
		m_MoveInput = true;

		if (m_SpeedCount <= m_speed)
			m_SpeedCount += 0.1f;

		m_Velocity.x = -m_speed;
		m_DirectionNext = CHARACTER_DIR::LEFT;
	}

	// 左スティック
	if (stick.x > DEAD_ZONE)
	{
		m_MoveInput = true;
		m_Velocity.x += m_speed * stick.x;
		m_DirectionNext = CHARACTER_DIR::RIGHT;
	}
	else if (stick.x < -DEAD_ZONE)
	{
		m_MoveInput = true;
		m_Velocity.x += m_speed * stick.x;
		m_DirectionNext = CHARACTER_DIR::LEFT;
	}
#endif
	// 移動方法
	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D))
	{
		m_Velocity.x = m_speed;
		m_DirectionNext = CHARACTER_DIR::RIGHT;
	}
	else if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
	{
		m_Velocity.x = -m_speed;
		m_DirectionNext = CHARACTER_DIR::LEFT;
	}
	else
	{
		m_Velocity.x = 0.0f;
	}

	// 向き変更時(スピードを０に)
	if (m_Direction != m_DirectionNext)
	{
		m_Direction = m_DirectionNext;
	}

	// 位置更新
	m_Pos += m_Velocity;

	//カゴ
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f));

	//壁判定 
	if (m_Pos.x > vivid::WINDOW_WIDTH - (m_width / 2 + m_radius / 2))
	{
		m_Pos.x = vivid::WINDOW_WIDTH - (m_width / 2 + m_radius / 2);
		m_Velocity.x = 0.0f;
	}
	if (m_Pos.x < 0.0f - (m_width / 2 - m_radius / 2))
	{
		m_Pos.x = 0.0f - (m_width / 2 - m_radius / 2);
		m_Velocity.x = 0.0f;
	}
	if (m_Pos.y + m_height > m_stageset.GroundLine())
	{
		m_Pos.y = m_stageset.GroundLine() - m_height;
		m_Velocity.y = 0.0f;

	}
#if 0
	// アニメーション
	if (m_MoveInput)
	{
		ChangeAnime(ANIME_ID::RUN);
	}
	else
	{
		ChangeAnime(ANIME_ID::STAND);
	}
#endif
	// アニメーション

	if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::D) ||
		vivid::keyboard::Button(vivid::keyboard::KEY_ID::A))
	{
		ChangeAnime(ANIME_ID::RUN);
	}
	else
	{
		ChangeAnime(ANIME_ID::STAND);
	}

	//アニメーション更新
	++m_AnimeTimer;

	if (m_AnimeTimer > m_anime_time[(int)m_AnimeID])
	{
		m_AnimeTimer = 0;

		++m_AnimeFrame;

		if (m_AnimeFrame >= m_anime_frame[(int)m_AnimeID])
		{
			m_AnimeFrame = 0;
		}
	}
}

void CBallPlayer2::Draw(void)
{
	m_basket.Draw();

	vivid::Rect rect = {};
	vivid::Vector2 m_anchor(m_width / 2.0f, 0.0f);
	vivid::Vector2 m_scale((float)m_Direction, 1.0f);

	rect.left = m_AnimeFrame * m_width;
	rect.right = rect.left + m_width;
	rect.top = (int)m_AnimeID * m_height;
	rect.bottom = rect.top + m_height;

	//vivid::DrawTexture("data\\kagami_shadow.png", m_ShadowPos);
	vivid::DrawTexture("data\\character1.png", m_Pos, 0xffffffff, rect, m_anchor, m_scale);

#ifdef _DEBUG/*デバックビルドのときのみ有効*/
	vivid::DrawText(40, Player2ID[(int)m_AnimeID], vivid::Vector2(0.0f, 100.0f));//表示アニメーション

	vivid::DrawText(40, std::to_string(m_Velocity.x), { 0.0f, 50.0f });//速さ
#endif
}

void CBallPlayer2::Finalize(void)
{
}

vivid::Vector2 CBallPlayer2::GetCenterPosition(void)
{
	return m_Pos + vivid::Vector2(m_width / 2.0f, m_height / 2.0f);
}

float CBallPlayer2::GetRadius(void)
{
	return m_radius;
}

CBallPlayer2& CBallPlayer2::GetInstance()
{
	static CBallPlayer2 instanse;
	return instanse;
}

CBasket& CBallPlayer2::GetBasket()
{
	return m_basket;
}
