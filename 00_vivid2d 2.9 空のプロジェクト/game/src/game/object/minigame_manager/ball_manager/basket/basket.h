#pragma once
#include "vivid.h"
#include"../ball_stageset/ball_stageset.h"
class CBasket
{
public:
    CBasket(void);
    ~CBasket(void) = default;
    void Initialize();
    void Update(const vivid::Vector2& playerPos);
    void Draw();

    vivid::Vector2 GetPosition() const;

    float GetWidth() const;
    float GetHeight() const;

private:

    vivid::Vector2 m_Pos;


    static const float m_basket_width;
    static const float m_basket_height;
};
