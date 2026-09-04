#include "drop_effect.h"

const int CDropEffect::m_width = 32;
const int CDropEffect::m_height = 32;
const float CDropEffect::m_scale = 0.6f;

CDropEffect::CDropEffect(void)
	:IEffect(m_width, m_height)
	, m_Velocity(0.0f, 0.0f)
	, m_IsBound(false)
{
}

CDropEffect::~CDropEffect(void)
{
}

void CDropEffect::Initialize(const vivid::Vector2& pos, unsigned int color, float rotation)
{
	IEffect::Initialize(pos, color, rotation);
	m_IsBound = false;

	//左右に散らす
	m_Velocity.x = (float)(rand() % 5 - 2);
	//上にとばす
	m_Velocity.y = -2.0f;
}

void CDropEffect::Update(void)
{
	//重力
	m_Velocity.y += m_ball_stageset.Gravity();
	//移動
	m_Pos += m_Velocity;

	const float ground = m_ball_stageset.GroundLine() - (m_Height * m_scale);

	//地面に接触
	if (m_Pos.y >= ground)
	{
		m_Pos.y = ground;
		//初回だけバウンド
		if (!m_IsBound)
		{
			m_Velocity.y *= -0.3f;//小さく跳ねる
			m_IsBound = true;
		}
		else
		{
			//2回目に地面に来たら消滅
			m_ActiveFlage = false;

		}
	}
}

void CDropEffect::Draw(void)
{
	vivid::Vector2 scale(m_scale, m_scale);

	vivid::DrawTexture("data\\ball\\ball.png", m_Pos, m_Color, m_Rect, m_Anchor, scale, m_Rotation);
}
