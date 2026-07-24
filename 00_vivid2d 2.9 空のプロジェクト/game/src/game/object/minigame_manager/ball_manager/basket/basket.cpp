#include "basket.h"

const float CBasket::m_basket_width = 100.0f;
const float CBasket::m_basket_height = 70.0f;

CBasket::CBasket(void)
	:m_Pos(0.0f, 0.0f)
{
}

void CBasket::Initialize()
{
	vivid::LoadTexture("data\\basket.png");
}

void CBasket::Update(const vivid::Vector2& playerPos)
{
	// プレイヤーの頭上に配置
	m_Pos.x = playerPos.x - m_basket_width / 2.0f;
	m_Pos.y = playerPos.y - m_basket_height;
}

void CBasket::Draw()
{
	vivid::DrawTexture("data\\basket.png", m_Pos);
}

vivid::Vector2 CBasket::GetPosition() const
{
	return m_Pos;
}

float CBasket::GetWidth() const
{
	return m_basket_width;
}

float CBasket::GetHeight() const
{
	return m_basket_height;
}
