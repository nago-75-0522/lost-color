#include "high_jump.h"
#include"../../player_manager/fall_player_mana/fall_player_mana.h"
#include"../../minigame_manager/fall_manager/fall.h"
const int CHigh_Jump::m_max_high_jump_charge = 60 * 1;
const int CHigh_Jump::m_half_high_jump_charge = 60 * 0.5;
const vivid::Vector2 CHigh_Jump::m_half_change_num = { 192.0f,192.0f };
const vivid::Vector2 CHigh_Jump::m_max_change_num = { 256.0f,256.0f };
const vivid::Vector2 CHigh_Jump::m_change_num = { 128.0f,128.0f };

CHigh_Jump::CHigh_Jump()
    :m_High_Jump_Timer_1(0)
    , m_High_Jump_Timer_2(0)
    , m_Change_Num(0.0f, 0.0f)
{
}

void CHigh_Jump::Initialize()
{
    m_High_Jump_Timer_1 = 0;
    m_High_Jump_Timer_2 = 0;
    m_Change_Num = { 0.0f,0.0f };
}

void CHigh_Jump::Update()
{


}

void CHigh_Jump::Draw()
{
}

void CHigh_Jump::Finalize()
{
}

void CHigh_Jump::Draw(const vivid::Vector2& pos)
{
    vivid::DrawTexture("data\\high_jump.png", pos);
}

void CHigh_Jump::Use(CFall_Player1& player)
{

    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::F))
    {
        ++m_High_Jump_Timer_1;
    }

    if (vivid::keyboard::Released(vivid::keyboard::KEY_ID::F))
    {
        if (m_High_Jump_Timer_1 >= m_max_high_jump_charge)
        {
            m_Change_Num = m_max_change_num;
        }
        else if (m_High_Jump_Timer_1 >= m_half_high_jump_charge)
        {
            m_Change_Num = m_half_change_num;
        }
        else
        {
            m_Change_Num = m_change_num;
        }

        vivid::Vector2 nextPos = player.GetCharaPos();

        switch (player.GetCharaDirection())
        {
        case CFall_Player1::CHARA_DIRECTION::UP:
            nextPos.y -= m_Change_Num.y;
            break;

        case CFall_Player1::CHARA_DIRECTION::DOWN:
            nextPos.y += m_Change_Num.y;
            break;

        case CFall_Player1::CHARA_DIRECTION::LEFT:
            nextPos.x -= m_Change_Num.x;
            break;

        case CFall_Player1::CHARA_DIRECTION::RIGHT:
            nextPos.x += m_Change_Num.x;
            break;
        }

        int nextX =
            (int)(nextPos.x / CFall::GetInstance().GetMapChipSize());

        int nextY =
            (int)(nextPos.y / CFall::GetInstance().GetMapChipSize());

        if (nextX >= 0 &&
            nextX < 20 &&
            nextY >= 0 &&
            nextY < 12)
        {
            player.GetCharaPos() = nextPos;
            player.GetItemID() = ITEM_ID::UNKNOW;
        }

        m_High_Jump_Timer_1 = 0;
    }
}

void CHigh_Jump::Use(CFall_Player2& player)
{

    if (vivid::keyboard::Button(vivid::keyboard::KEY_ID::L))
    {
        ++m_High_Jump_Timer_2;
    }

    if (vivid::keyboard::Released(vivid::keyboard::KEY_ID::L))
    {
        if (m_High_Jump_Timer_2 >= m_max_high_jump_charge)
        {
            m_Change_Num = m_max_change_num;
        }
        else if (m_High_Jump_Timer_2 >= m_half_high_jump_charge)
        {
            m_Change_Num = m_half_change_num;
        }
        else
        {
            m_Change_Num = m_change_num;
        }

        vivid::Vector2 nextPos = player.GetCharaPos();

        switch (player.GetCharaDirection())
        {
        case CFall_Player2::CHARA_DIRECTION::UP:
            nextPos.y -= m_Change_Num.y;
            break;

        case CFall_Player2::CHARA_DIRECTION::DOWN:
            nextPos.y += m_Change_Num.y;
            break;

        case CFall_Player2::CHARA_DIRECTION::LEFT:
            nextPos.x -= m_Change_Num.x;
            break;

        case CFall_Player2::CHARA_DIRECTION::RIGHT:
            nextPos.x += m_Change_Num.x;
            break;
        }

        int nextX =
            (int)(nextPos.x / CFall::GetInstance().GetMapChipSize());

        int nextY =
            (int)(nextPos.y / CFall::GetInstance().GetMapChipSize());

        if (nextX >= 0 &&
            nextX < 20 &&
            nextY >= 0 &&
            nextY < 12)
        {
            player.GetCharaPos() = nextPos;
            player.GetItemID() = ITEM_ID::UNKNOW;
        }

        m_High_Jump_Timer_2 = 0;
    }
}


