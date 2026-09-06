#include "basket.h"

const float CBasket::m_basket_width = 100.0f;
const float CBasket::m_basket_height = 70.0f;

CBasket::CBasket(void)
	:m_Pos(0.0f, 0.0f)
	,m_OldPos(0.0f,0.0f)
{
}

void CBasket::Initialize()
{
	vivid::LoadTexture("data\\ball\\basket.png");
}

void CBasket::Update(const vivid::Vector2& playerPos)
{
	//前フレーム座標保存
	m_OldPos = m_Pos;

	// プレイヤーの頭上に配置
	m_Pos.x = playerPos.x - m_basket_width / 2.0f;
	m_Pos.y = playerPos.y - m_basket_height;
}

void CBasket::Draw()
{
	vivid::DrawTexture("data\\ball\\basket.png", m_Pos);
}

vivid::Vector2 CBasket::GetPosition() const
{
	return m_Pos;
}

vivid::Vector2 CBasket::GetOldPosition() const
{
	return m_OldPos;
}

float CBasket::GetWidth() const
{
	return m_basket_width;
}

float CBasket::GetHeight() const
{
	return m_basket_height;
}
