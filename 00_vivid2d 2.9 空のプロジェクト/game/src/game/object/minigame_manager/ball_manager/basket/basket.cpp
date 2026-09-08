#include "basket.h"

const float CBasket::m_basket_width = 100.0f;
const float CBasket::m_basket_height = 70.0f;

CBasket::CBasket(void)
	:m_Pos(0.0f, 0.0f)
	,m_OldPos(0.0f,0.0f)
	,m_Angle(90.0f)
{
}

void CBasket::Initialize()
{
	vivid::LoadTexture("data\\ball\\basket.png");
}

void CBasket::Update(const vivid::Vector2& playerPos, int attackTimer, bool isRight)
{
	//前フレーム座標保存
	m_OldPos = m_Pos;

    vivid::Vector2 pivot = playerPos;

    const float radius = 80.0f;//キャラとの間

    if (attackTimer <= 0)
    {
        m_Angle = 90.0f;
    }
    else
    {
        float rate = 1.0f - (float)attackTimer / 15.0f;

        if (isRight)
        {
            // 90°→0°
            m_Angle = 90.0f - rate * 90.0f;
        }
        else
        {
            // 90°→180°
            m_Angle = 90.0f + rate * 90.0f;
        }
    }

    float rad = m_Angle * 3.14f / 180.0f;

    m_Pos.x = pivot.x + cosf(rad) * radius - m_basket_width / 2.0f;
    m_Pos.y = pivot.y - sinf(rad) * radius;
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

float CBasket::GetLeft() const
{
    return m_Pos.x;
}

float CBasket::GetRight() const
{
    return m_Pos.x + m_basket_width;
}

float CBasket::GetTop() const
{
    return m_Pos.y;
}

float CBasket::GetBottom() const
{
    return m_Pos.y + m_basket_height;
}