#include "effect.h"

IEffect::IEffect(void)
	:m_Width(0)
	, m_Height(0)
	, m_Pos(vivid::Vector2(0.0f, 0.0f))
	, m_Color(0xffffffff)
	, m_Anchor(vivid::Vector2(0.0f, 0.0f))
	, m_Rect({ 0,0,0,0 })
	, m_Scale(vivid::Vector2(1.0f, 1.0f))
	, m_Rotation(0.0f)
	, m_ActiveFlage(true)
{
}

IEffect::IEffect(int width, int height)
	:m_Width(width)
	, m_Height(height)
	, m_Pos(vivid::Vector2(0.0f, 0.0f))
	, m_Color(0xffffffff)
	, m_Anchor(vivid::Vector2((float)m_Width / 2.0f, (float)m_Height / 2.0f))
	, m_Rect({ 0,0,m_Width,m_Height })
	, m_Scale(vivid::Vector2(1.0f, 1.0f))
	, m_Rotation(0.0f)
	, m_ActiveFlage(true)
{
}

IEffect::~IEffect(void)
{
}

void IEffect::Initialize(const vivid::Vector2& pos, unsigned int color, float rotation)
{
	m_Pos = pos;
	m_Color = color;
	m_Rotation = rotation;
	m_ActiveFlage = true;
}

void IEffect::Update(void)
{
}

void IEffect::Draw(void)
{
}

void IEffect::Finalize(void)
{
}

vivid::Vector2 IEffect::GetPosition(void)
{
	return m_Pos;
}

void IEffect::SetPosition(const vivid::Vector2& pos)
{
	m_Pos = pos;
}

bool IEffect::GetActive(void)
{
	return m_ActiveFlage;
}

void IEffect::SetActive(bool active)
{
	m_ActiveFlage = active;
}
