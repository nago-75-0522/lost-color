#include"ball_player2.h"
#include"../../../minigame_manager/ball_manager/ball/ball.h"
#include"../../../minigame_manager/ball_manager/ball_score/ball_score.h"
#include"../../../minigame_manager/ball_manager/effect_manager/effect_manager.h"

const int CBallPlayer2::m_width = 280;
const int CBallPlayer2::m_height = 140;
const float CBallPlayer2::m_speed = 5.0;
const float CBallPlayer2::m_jump_power = -15.0f;
const vivid::Vector2 CBallPlayer2::m_player2_marker_size = { 64.0f,40.0f };

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
	, m_AttackTimer(0)
	, m_AttackHit(false)
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
	vivid::LoadTexture("data\\ball\\character2.png");

	// 初期位置
	m_Pos.x = vivid::GetWindowWidth() / 2.0f;
	m_Pos.y = m_stageset.GroundLine() - m_height;
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f), m_AttackTimer, m_Direction == CHARACTER_DIR::RIGHT);
	m_Player2MarkerPos.x = m_Pos.x + m_width / 2 - m_player2_marker_size.x / 2;
	m_Player2MarkerPos.y = m_stageset.GroundLine();

	// 速さ
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;

	// アニメーション
	m_AnimeID = ANIME_ID::STAND;
	m_AnimeFrame = 0;
	m_AnimeTimer = 0;

	m_Direction = CHARACTER_DIR::LEFT;
	m_DirectionNext = CHARACTER_DIR::LEFT;

	m_AttackTimer = 0;
	m_AttackHit = false;
}

void CBallPlayer2::Update(void)
{
	namespace controller = vivid::controller;
	namespace keyboard = vivid::keyboard;

	// 左スティック取得
	vivid::Vector2 stick = controller::GetAnalogStickLeft(controller::DEVICE_ID::PLAYER2);
	float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);

	// デッドゾーン設定
	const float DEAD_ZONE = 0.5f;

	m_MoveInput = false;

	// 移動方法
	//右
	if (keyboard::Button(keyboard::KEY_ID::RIGHT) || stick.x > DEAD_ZONE ||
		controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::RIGHT))
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
	else if (keyboard::Button(keyboard::KEY_ID::LEFT) || stick.x < -DEAD_ZONE ||
		controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::LEFT))
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
	if (keyboard::Button(keyboard::KEY_ID::UP) ||
		controller::Button(controller::DEVICE_ID::PLAYER2, controller::BUTTON_ID::A))
	{
		//地面にいる時のみ
		if (m_Pos.y + m_height >= m_stageset.GroundLine())
			m_Velocity.y = m_jump_power;
	}

	//攻撃
	if ((keyboard::Trigger(keyboard::KEY_ID::DOWN) ||
		(triger > DEAD_ZONE)) && m_AttackTimer <= 0)
	{
		m_AttackTimer = 15;
		//攻撃開始時はヒットフラグをリセット
		m_AttackHit = false;
	}

	if (m_AttackTimer > 0)
	{
		m_AttackTimer--;
		//攻撃終了時
		if (m_AttackTimer == 0)
		{
			//1度も相手に当たらなかった
			if (!m_AttackHit)
			{
				//空振りペナルティ
				CBallScore::GetInstance().AddPlayer2Score(-10);
				unsigned int color;
				if (CBall::GetInstance().GetPlayer1Color() == CBall::BALL_COLOR::CYAN)
					color = 0xff00ffff;//シアン
				else
					color = 0xffffff00;//イエロー

				//位置
				vivid::Vector2 effectPos;
				effectPos.x = m_Pos.x + m_width * 0.5f;
				effectPos.y = m_Pos.y + m_height * 0.5f;
				//エフェクト生成
				CEffectManager::GetInstance().Create(EFFECT_ID::DROP, effectPos, color, 0.0f);
			}
		}
	}

	// 向き変更時
	if (m_Direction != m_DirectionNext)
	{
		m_Direction = m_DirectionNext;
	}

	//重力
	m_Velocity.y += m_stageset.Gravity();

	// 位置更新
	m_Pos += m_Velocity;

	//マーカーの位置
	m_Player2MarkerPos.x = m_Pos.x + m_width / 2 - m_player2_marker_size.x / 2;
	m_Player2MarkerPos.y = m_stageset.GroundLine();

	//カゴ
	m_basket.Update(m_Pos + vivid::Vector2(m_width / 2.0f, 0.0f), m_AttackTimer, m_Direction == CHARACTER_DIR::RIGHT);

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

	//マーク
	switch (CBall::GetInstance().GetPlayer2Color())
	{
	case CBall::BALL_COLOR::CYAN:
		vivid::DrawTexture("data\\logo\\small_blue_2p.png", m_Player2MarkerPos);
		break;

	case CBall::BALL_COLOR::YELLOW:
		vivid::DrawTexture("data\\logo\\small_yellow_2p.png", m_Player2MarkerPos);
		break;
	}

	vivid::DrawTexture("data\\ball\\character2.png", m_Pos, 0xffffffff, rect, m_anchor, m_scale);
}

void CBallPlayer2::Finalize(void)
{
}

//当たり判定用矩形
//左端
float CBallPlayer2::GetLeft() const
{
	return m_Pos.x + 90.0f;
}
//右端
float CBallPlayer2::GetRight() const
{
	return m_Pos.x + 190.0f;
}
//上
float CBallPlayer2::GetTop() const
{
	return m_Pos.y;
}
//下
float CBallPlayer2::GetBottom() const
{
	return m_Pos.y + m_height;
}
//位置変更
void CBallPlayer2::AddPos(const vivid::Vector2& move)
{
	m_Pos += move;
}
//攻撃判定
//攻撃アニメーション中の有効フレームのみtrue
bool CBallPlayer2::IsAttack() const
{
	return m_AttackTimer >= 5 && m_AttackTimer <= 10;
}
//攻撃ヒットフラグの設定
void CBallPlayer2::SetAttackHit(bool hit)
{
	m_AttackHit = hit;
}
//キャラクター中心座標取得
vivid::Vector2 CBallPlayer2::GetCenterPosition(void)
{
	return m_Pos + vivid::Vector2(m_width / 2.0f, m_height / 2.0f);
}
//カゴ取得
CBasket& CBallPlayer2::GetBasket()
{
	return m_basket;
}