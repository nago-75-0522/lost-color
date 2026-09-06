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
    m_IsJump_1 = false;
    m_IsJump_2 = false;
    m_Old_Trigger_1 = false;
    m_Old_Trigger_2 = false;
    m_JumpTimer_1 = 0.0f;
    m_JumpTimer_2 = 0.0f;
}

void CHigh_Jump::Update()
{// Player1
    if (m_IsJump_1)
    {
        m_JumpTimer_1++;

        float t = m_JumpTimer_1 / m_JumpTime;

        if (t >= 1.0f)
        {
            t = 1.0f;

            CFall_Player1::GetInstance().GetCharaPos()
                = m_JumpTarget_1;

            m_IsJump_1 = false;
        }

        vivid::Vector2 pos;

        pos.x =
            m_JumpStart_1.x +
            (m_JumpTarget_1.x - m_JumpStart_1.x) * t;

        pos.y =
            m_JumpStart_1.y +
            (m_JumpTarget_1.y - m_JumpStart_1.y) * t;

        pos.y -= 80.0f * 4.0f * t * (1.0f - t);

        CFall_Player1::GetInstance().GetCharaPos() = pos;
    }

    // Player2

    if (m_IsJump_2)
    {
        m_JumpTimer_2++;

        float t = m_JumpTimer_2 / m_JumpTime;

        if (t >= 1.0f)
        {
            t = 1.0f;

            CFall_Player2::GetInstance().GetCharaPos()
                = m_JumpTarget_2;

            m_IsJump_2 = false;
        }

        vivid::Vector2 pos;

        pos.x =
            m_JumpStart_2.x +
            (m_JumpTarget_2.x - m_JumpStart_2.x) * t;

        pos.y =
            m_JumpStart_2.y +
            (m_JumpTarget_2.y - m_JumpStart_2.y) * t;

        pos.y -= 80.0f * 4.0f * t * (1.0f - t);

        CFall_Player2::GetInstance().GetCharaPos() = pos;
    }
}

void CHigh_Jump::Finalize()
{
}

void CHigh_Jump::Draw(const vivid::Vector2& pos)
{
    vivid::DrawTexture("data\\high_jump.png", pos);
}

//予測線を出す
void CHigh_Jump::DrawAim(CFall_Player1& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER1);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player1::GetInstance().GetScale().x >= 1)
    {
        if (CFall_Player2::GetInstance().GetScale().x < 1 ||
            (!keyboard::Button(keyboard::KEY_ID::F) &&
                !(triger > DEAD_ZONE)))
        {
            return;
        }
        int count = 2;

        if (m_High_Jump_Timer_1 >= m_max_high_jump_charge)
        {
            count = 4;
        }
        else if (m_High_Jump_Timer_1 >= m_half_high_jump_charge)
        {
            count = 3;
        }

        for (int i = 1; i <= count; i++)
        {
            vivid::Vector2 pos = player.GetCharaPos();

            switch (player.GetCharaDirection())
            {
            case CFall_Player1::CHARA_DIRECTION::UP:
                pos.y -= i * 64.0f;
                break;

            case CFall_Player1::CHARA_DIRECTION::DOWN:
                pos.y += i * 64.0f;
                break;

            case CFall_Player1::CHARA_DIRECTION::LEFT:
                pos.x -= i * 64.0f;
                break;

            case CFall_Player1::CHARA_DIRECTION::RIGHT:
                pos.x += i * 64.0f;
                break;
            }

            vivid::Vector2 pos_gap;


            if (i == count)
            {
                vivid::DrawTexture("data\\landing_point.png", pos, 0xaaffffff);
            }
            else
            {
                vivid::DrawTexture("data\\red_rine.png", pos, 0xaaffffff);
            }
        }

    }
}
//予測線を出す
void CHigh_Jump::DrawAim(CFall_Player2& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player2::GetInstance().GetScale().x < 1 ||
        (!keyboard::Button(keyboard::KEY_ID::L) &&
            !(triger > DEAD_ZONE)))
    {
        return;
    }

    int count = 2;

    if (m_High_Jump_Timer_2 >= m_max_high_jump_charge)
    {
        count = 4;
    }
    else if (m_High_Jump_Timer_2 >= m_half_high_jump_charge)
    {
        count = 3;
    }

    for (int i = 1; i <= count; i++)
    {
        vivid::Vector2 pos = player.GetCharaPos();

        switch (player.GetCharaDirection())
        {
        case CFall_Player2::CHARA_DIRECTION::UP:
            pos.y -= i * 64.0f;
            break;

        case CFall_Player2::CHARA_DIRECTION::DOWN:
            pos.y += i * 64.0f;
            break;

        case CFall_Player2::CHARA_DIRECTION::LEFT:
            pos.x -= i * 64.0;
            break;

        case CFall_Player2::CHARA_DIRECTION::RIGHT:
            pos.x += i * 64.0f;
            break;
        }

        if (i == count)
        {
            vivid::DrawTexture("data\\landing_point.png", pos, 0xaaffffff);
        }
        else
        {
            vivid::DrawTexture("data\\red_rine.png", pos, 0xaaffffff);
        }
    }

};


//1P着地点決め
void CHigh_Jump::Use(CFall_Player1& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;

    float triger =
        controller::GetTriggerRight(controller::DEVICE_ID::PLAYER1);

    const float DEAD_ZONE = 0.5f;

    if (CFall_Player1::GetInstance().GetScale().x < 1 ||
        CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }

    bool nowTrigger = (triger > DEAD_ZONE);
    bool triggerRelease = (m_Old_Trigger_1 && !nowTrigger);

    m_Old_Trigger_1 = nowTrigger;

    // チャージ
    if (keyboard::Button(keyboard::KEY_ID::F) || nowTrigger)
    {
        ++m_High_Jump_Timer_1;

        if (m_High_Jump_Timer_1 > m_max_high_jump_charge)
        {
            m_High_Jump_Timer_1 = m_max_high_jump_charge;
        }
    }

    // 発動
    if (keyboard::Released(keyboard::KEY_ID::F) || triggerRelease)
    {
        int jumpCount = 2;

        if (m_High_Jump_Timer_1 >= m_max_high_jump_charge)
        {
            jumpCount = 4;
        }
        else if (m_High_Jump_Timer_1 >= m_half_high_jump_charge)
        {
            jumpCount = 3;
        }

        const int chipSize =
            CFall::GetInstance().GetMapChipSize();

        int nowX =
            (int)((player.GetCharaPos().x + 24) / chipSize);

        int nowY =
            (int)((player.GetCharaPos().y + 24) / chipSize);

        int targetX = nowX;
        int targetY = nowY;

        for (int i = 1; i <= jumpCount; i++)
        {
            int checkX = nowX;
            int checkY = nowY;

            switch (player.GetCharaDirection())
            {
            case CFall_Player1::CHARA_DIRECTION::UP:
                checkY -= i;
                break;

            case CFall_Player1::CHARA_DIRECTION::DOWN:
                checkY += i;
                break;

            case CFall_Player1::CHARA_DIRECTION::LEFT:
                checkX -= i;
                break;

            case CFall_Player1::CHARA_DIRECTION::RIGHT:
                checkX += i;
                break;
            }

            if (checkX < 0 || checkX >= 20 ||
                checkY < 0 || checkY >= 12)
            {
                break;
            }

            if (CFall::GetInstance().CheckWall(checkX, checkY))
            {
                break;
            }

            targetX = checkX;
            targetY = checkY;
        }

        if (targetX != nowX || targetY != nowY)
        {
            m_IsJump_1 = true;
            m_JumpTimer_1 = 0.0f;

            m_JumpStart_1 = player.GetCharaPos();
            CFall_Player1::GetInstance().ForceStop();

            // プレイヤーを中央へ
            m_JumpTarget_1.x = targetX * chipSize + 8.0f;
            m_JumpTarget_1.y = targetY * chipSize + 8.0f;

            player.GetItemID() = ITEM_ID::UNKNOW;
        }

        m_High_Jump_Timer_1 = 0;
    }
}

//2P着地点決め
void CHigh_Jump::Use(CFall_Player2& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;

    float triger =
        controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);

    const float DEAD_ZONE = 0.5f;

    if (CFall_Player1::GetInstance().GetScale().x < 1 ||
        CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }

    bool nowTrigger = (triger > DEAD_ZONE);
    bool triggerRelease = (m_Old_Trigger_2 && !nowTrigger);

    m_Old_Trigger_2 = nowTrigger;

    // チャージ
    if (keyboard::Button(keyboard::KEY_ID::L) || nowTrigger)
    {
        ++m_High_Jump_Timer_2;

        if (m_High_Jump_Timer_2 > m_max_high_jump_charge)
        {
            m_High_Jump_Timer_2 = m_max_high_jump_charge;
        }
    }

    // 発動
    if (keyboard::Released(keyboard::KEY_ID::L) || triggerRelease)
    {
        int jumpCount = 2;

        if (m_High_Jump_Timer_2 >= m_max_high_jump_charge)
        {
            jumpCount = 4;
        }
        else if (m_High_Jump_Timer_2 >= m_half_high_jump_charge)
        {
            jumpCount = 3;
        }

        const int chipSize =
            CFall::GetInstance().GetMapChipSize();

        int nowX =
            (int)((player.GetCharaPos().x + 24) / chipSize);

        int nowY =
            (int)((player.GetCharaPos().y + 24) / chipSize);

        int targetX = nowX;
        int targetY = nowY;

        for (int i = 1; i <= jumpCount; i++)
        {
            int checkX = nowX;
            int checkY = nowY;

            switch (player.GetCharaDirection())
            {
            case CFall_Player2::CHARA_DIRECTION::UP:
                checkY -= i;
                break;

            case CFall_Player2::CHARA_DIRECTION::DOWN:
                checkY += i;
                break;

            case CFall_Player2::CHARA_DIRECTION::LEFT:
                checkX -= i;
                break;

            case CFall_Player2::CHARA_DIRECTION::RIGHT:
                checkX += i;
                break;
            }

            if (checkX < 0 || checkX >= 20 ||
                checkY < 0 || checkY >= 12)
            {
                break;
            }

            if (CFall::GetInstance().CheckWall(checkX, checkY))
            {
                break;
            }

            targetX = checkX;
            targetY = checkY;
        }

        if (targetX != nowX || targetY != nowY)
        {
            m_IsJump_2 = true;
            m_JumpTimer_2 = 0.0f;
            m_JumpStart_2 = player.GetCharaPos();

            CFall_Player2::GetInstance().ForceStop();

            // プレイヤーを中央に
            m_JumpTarget_2.x = targetX * chipSize + 8.0f;
            m_JumpTarget_2.y = targetY * chipSize + 8.0f;

            player.GetItemID() = ITEM_ID::UNKNOW;
        }

        m_High_Jump_Timer_2 = 0;
    }
}