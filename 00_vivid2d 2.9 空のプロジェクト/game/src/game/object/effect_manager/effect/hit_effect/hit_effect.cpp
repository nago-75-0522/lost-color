#include"hit_effect.h"

const int	CHitEffect::m_width = 110;
const int	CHitEffect::m_height = 80;
const int   CHitEffect::m_max_alpha = 255;
const float CHitEffect::m_start_scale = 0.1f;
const float CHitEffect::m_max_scale = 1.5f;
const float CHitEffect::m_scale_speed = 0.05f;


CHitEffect::CHitEffect(void)
	:IEffect(m_width, m_height)
	, m_Alpha(0)
	, m_IsShrink(false)
{
}

CHitEffect::~CHitEffect(void)
{
}

void CHitEffect::Initialize(const vivid::Vector2& pos, unsigned int color, float rotation)
{
	IEffect::Initialize(pos, color, rotation);
	m_Alpha = 0;
	m_Scale = vivid::Vector2(m_start_scale, m_start_scale);
	m_Rotation = rotation;
	m_IsShrink = false;
}

void CHitEffect::Update(void)
{
	// 拡大
	float scale = m_Scale.x;
	if (!m_IsShrink)
	{
		//フェードイン＋拡大
		scale += m_scale_speed;
		float rate = scale / m_max_scale;
		rate *= rate; // 2乗
		m_Alpha = static_cast<int>(m_max_alpha * rate);
		if (m_Alpha > m_max_alpha)
			m_Alpha = m_max_alpha;

		if (scale >= m_max_scale)
		{
			scale = m_max_scale;
			m_IsShrink = true;//縮小開始
		}
	}
	else
	{
		//フェードアウト＋縮小
		scale -= m_scale_speed;
		float rate = scale / m_max_scale;
		rate *= rate; // 2乗
		m_Alpha = static_cast<int>(m_max_alpha * rate);
		if (m_Alpha <= 0)
		{
			m_Alpha = 0;
			SetActive(false);
		}
	}
	m_Scale = vivid::Vector2(scale, scale);
}

void CHitEffect::Draw(void)
{
	unsigned int color = (m_Alpha << 24) | (m_Color & 0x00ffffff);

	vivid::DrawTexture("data\\ball\\hit_effect.png", m_Pos, color, m_Rect, m_Anchor, m_Scale, m_Rotation);
}