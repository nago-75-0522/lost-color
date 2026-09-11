#pragma once
#include "vivid.h"

class CBasket
{
public:
    CBasket(void);
    ~CBasket(void) = default;
    void Initialize();
    void Update(const vivid::Vector2& playerPos, int attackTimer, bool isRight);
    void Draw();

    vivid::Vector2 GetPosition() const;
    vivid::Vector2 GetOldPosition() const;

    float GetWidth() const;
    float GetHeight() const;

    float GetLeft() const;
    float GetRight() const;
    float GetTop() const;
    float GetBottom() const;

private:

    vivid::Vector2 m_Pos;
    vivid::Vector2 m_OldPos;

    static const float m_basket_width;
    static const float m_basket_height;
    static const float m_pi;//円周率

    float m_Angle;//回転角度
};
