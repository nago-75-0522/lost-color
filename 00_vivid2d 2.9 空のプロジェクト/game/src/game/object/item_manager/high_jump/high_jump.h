#pragma once
#pragma once
#include "../item/item.h"
#include "vivid.h"

class CFall_Player1;
class CFall_Player2;

class CHigh_Jump : public Iitem
{
public:
    CHigh_Jump();
    ~CHigh_Jump() = default;

    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Finalize() override;

    void Draw(const vivid::Vector2& pos);
    void Use(CFall_Player1& player);
    void Use(CFall_Player2& player);

private:
    static const int m_max_high_jump_charge;
    static const int m_half_high_jump_charge;

    static const vivid::Vector2 m_max_change_num;
    static const vivid::Vector2 m_half_change_num;
    static const vivid::Vector2 m_change_num;

    int m_High_Jump_Timer_1;
    int m_High_Jump_Timer_2;
    vivid::Vector2 m_Change_Num;
};