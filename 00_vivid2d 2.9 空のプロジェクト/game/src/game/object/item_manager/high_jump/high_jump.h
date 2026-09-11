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
    void Finalize() override;

    void Draw(const vivid::Vector2& pos);
    void DrawAim(CFall_Player1& player);
    void DrawAim(CFall_Player2& player);
    void Use(CFall_Player1& player);
    void Use(CFall_Player2& player);
    bool Get_Is_Jump_1() { return m_IsJump_1; }
    bool Get_Is_Jump_2() { return m_IsJump_2; }
private:
    static const int m_max_high_jump_charge;
    static const int m_half_high_jump_charge;
    static const vivid::Vector2 m_max_change_num;
    static const vivid::Vector2 m_half_change_num;
    static const vivid::Vector2 m_change_num;
    static const int m_chip_size;

    bool m_IsJump_1;
    bool m_IsJump_2;
    bool m_Old_Trigger_1;
    bool m_Old_Trigger_2;

    vivid::Vector2 m_JumpStart_1;
    vivid::Vector2 m_JumpTarget_1;

    vivid::Vector2 m_JumpStart_2;
    vivid::Vector2 m_JumpTarget_2;

    float m_JumpTimer_1;
    float m_JumpTimer_2;

    static constexpr float m_JumpTime = 20.0f;
    int m_High_Jump_Timer_1;
    int m_High_Jump_Timer_2;
    vivid::Vector2 m_Change_Num;
};