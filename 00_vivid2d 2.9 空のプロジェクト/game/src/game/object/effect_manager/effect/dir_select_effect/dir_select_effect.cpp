#include "dir_select_effect.h"
#include"vivid.h"

const int CDirSelectEffect::m_width = 64;
const int CDirSelectEffect::m_height = 64;
const int CDirSelectEffect::m_fade_speed = 8;

CDirSelectEffect::CDirSelectEffect(void)
	: IEffect(m_width, m_height)
{
}

void CDirSelectEffect::Initialize(const vivid::Vector2& pos, unsigned int color, float rotation)
{
	IEffect::Initialize(pos, color, rotation);
}

void CDirSelectEffect::Update(void)
{
	int alpha = (m_Color & 0xff000000) >> 24;

	alpha -= m_fade_speed;

	if (alpha < 0)
	{
		alpha = 0;
		m_ActiveFlage = false;
	}

	m_Color = (alpha << 24) | (m_Color & 0x00ffffff);

	m_Scale.x = 1.3f;
	m_Scale.y = 1.3f;
}

void CDirSelectEffect::Draw(void)
{
	vivid::DrawTexture("data\\race\\car_effect.png", m_Pos, m_Color,
		m_Rect, m_Anchor, m_Scale, m_Rotation, vivid::ALPHABLEND::ADD);
}
