#include "high_jump.h"
#include"../../player_manager/fall_player_mana/fall_player_mana.h"
#include"../../minigame_manager/fall_manager/fall.h"
const int CHigh_Jump::m_max_high_jump_charge = 60 * 1;
const int CHigh_Jump::m_half_high_jump_charge = 60 * 0.5;
const vivid::Vector2 CHigh_Jump::m_half_change_num = { 192.0f,192.0f };
const vivid::Vector2 CHigh_Jump::m_max_change_num = { 256.0f,256.0f };
const vivid::Vector2 CHigh_Jump::m_change_num = { 128.0f,128.0f };
const int CHigh_Jump::m_chip_size = CFall::GetInstance().GetMapChipSize();

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
    m_Is_Jump_1 = false;
    m_Is_Jump_2 = false;
    m_Old_Trigger_1 = false;
    m_Old_Trigger_2 = false;
    m_Jump_Timer_1 = 0.0f;
    m_Jump_Timer_2 = 0.0f;
    vivid::LoadSound("data\\sound\\high_jump.wav");
    vivid::LoadSound("data\\sound\\half_jump.wav");
    vivid::LoadSound("data\\sound\\max_jump.wav");
}

void CHigh_Jump::Update()
{// Player1
    if (m_Is_Jump_1)
    {
        m_Jump_Timer_1++;

        float t = m_Jump_Timer_1 / m_JumpTime;

        if (t >= 1.0f)
        {
            t = 1.0f;

            CFall_Player1::GetInstance().GetCharaPos() =
                m_Jump_Target_1;

            CFall_Player1::GetInstance().ForceStop();

            int x =
                (int)((m_Jump_Target_1.x + 24) / 64);

            int y =
                (int)((m_Jump_Target_1.y + 24) / 64);

            CFall::GetInstance().ChangeFloor(x, y);

            m_Is_Jump_1 = false;

            return;    // ← これを追加
        }

        vivid::Vector2 pos;
        pos.x =
            m_Jump_Start_1.x +
            (m_Jump_Target_1.x - m_Jump_Start_1.x) * t;

        pos.y =
            m_Jump_Start_1.y +
            (m_Jump_Target_1.y - m_Jump_Start_1.y) * t;

        pos.y -= 80.0f * 4.0f * t * (1.0f - t);

        CFall_Player1::GetInstance().GetCharaPos() = pos;
    }

    // Player2

    if (m_Is_Jump_2)
    {
        m_Jump_Timer_2++;

        float t = m_Jump_Timer_2 / m_JumpTime;

        if (t >= 1.0f)
        {
            t = 1.0f;

            CFall_Player2::GetInstance().GetCharaPos() =
                m_Jump_Target_2;

            CFall_Player2::GetInstance().ForceStop();

            int x =
                (int)((m_Jump_Target_2.x + 24) / 64);

            int y =
                (int)((m_Jump_Target_2.y + 24) / 64);

            CFall::GetInstance().ChangeFloor(x, y);

            m_Is_Jump_2 = false;

            return;    // ← これを追加
        }

        vivid::Vector2 pos;

        pos.x =
            m_Jump_Start_2.x +
            (m_Jump_Target_2.x - m_Jump_Start_2.x) * t;

        pos.y =
            m_Jump_Start_2.y +
            (m_Jump_Target_2.y - m_Jump_Start_2.y) * t;

        pos.y -= 80.0f * 4.0f * t * (1.0f - t);

        CFall_Player2::GetInstance().GetCharaPos() = pos;
    }
}

void CHigh_Jump::Finalize()
{
}

void CHigh_Jump::Draw(const vivid::Vector2& pos)
{
    vivid::DrawTexture("data\\fall\\high_jump.png", pos);
}

//予測線を出す
void CHigh_Jump::DrawAim(CFall_Player1& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER1);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player1::GetInstance().GetScale().x < 1 ||
        CFall_Player2::GetInstance().GetScale().x >= 1)
    {
        if ((!keyboard::Button(keyboard::KEY_ID::F) &&
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

            if (i == count)
            {
                vivid::DrawTexture("data\\fall\\landing_point.png", pos, 0xaaffffff);
            }
            else
            {
                vivid::DrawTexture("data\\fall\\red_rine.png", pos, 0xaaffffff);
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
    if (CFall_Player1::GetInstance().GetScale().x < 1 ||
        CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }
    if ((!keyboard::Button(keyboard::KEY_ID::L) &&
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
            vivid::DrawTexture("data\\fall\\landing_point.png", pos, 0xaaffffff);
        }
        else
        {
            vivid::DrawTexture("data\\fall\\red_rine.png", pos, 0xaaffffff);
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

    bool now_trigger = (triger > DEAD_ZONE);
    bool trigger_release = (m_Old_Trigger_1 && !now_trigger);

    m_Old_Trigger_1 = now_trigger;

    // チャージ
    if (keyboard::Button(keyboard::KEY_ID::F) || now_trigger)
    {
        ++m_High_Jump_Timer_1;

        if (m_High_Jump_Timer_1 > m_max_high_jump_charge)
        {
            m_High_Jump_Timer_1 = m_max_high_jump_charge;
        }
    }

    // 発動
    if (keyboard::Released(keyboard::KEY_ID::F) || trigger_release)
    {
        int jump_count = 2;

        if (m_High_Jump_Timer_1 >= m_max_high_jump_charge)
        {
            jump_count = 4;
        }
        else if (m_High_Jump_Timer_1 >= m_half_high_jump_charge)
        {
            jump_count = 3;
        }

        int nowX =
            (int)((player.GetCharaPos().x + 24) / m_chip_size);

        int nowY =
            (int)((player.GetCharaPos().y + 24) / m_chip_size);

        int targetX = nowX;
        int targetY = nowY;

        for (int i = 1; i <= jump_count; i++)
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
            m_Is_Jump_1 = true;
            m_Jump_Timer_1 = 0.0f;
            m_Jump_Start_1 = player.GetCharaPos();
            CFall_Player1::GetInstance().ForceStop();
            
                if (jump_count == 2)
                {
                    vivid::PlaySound("data\\sound\\high_jump.wav", false);
                }
                else if (jump_count == 4)
                {
                    vivid::PlaySound("data\\sound\\max_jump.wav", false);
                }
                else if (jump_count == 3)
                {
                    vivid::PlaySound("data\\sound\\half_jump.wav", false);
                }
            // プレイヤーを中央へ
            m_Jump_Target_1.x = targetX * m_chip_size + 8.0f;
            m_Jump_Target_1.y = targetY * m_chip_size + 8.0f;

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

    bool now_trigger = (triger > DEAD_ZONE);
    bool trigger_release = (m_Old_Trigger_2 && !now_trigger);

    m_Old_Trigger_2 = now_trigger;

    // チャージ
    if (keyboard::Button(keyboard::KEY_ID::L) || now_trigger)
    {
        ++m_High_Jump_Timer_2;

        if (m_High_Jump_Timer_2 > m_max_high_jump_charge)
        {
            m_High_Jump_Timer_2 = m_max_high_jump_charge;
        }
    }

    // 発動
    if (keyboard::Released(keyboard::KEY_ID::L) || trigger_release)
    {
        int jump_count = 2;

        if (m_High_Jump_Timer_2 >= m_max_high_jump_charge)
        {
            jump_count = 4;
        }
        else if (m_High_Jump_Timer_2 >= m_half_high_jump_charge)
        {
            jump_count = 3;
        }

        int nowX =
            (int)((player.GetCharaPos().x + 24) / m_chip_size);

        int nowY =
            (int)((player.GetCharaPos().y + 24) / m_chip_size);

        int targetX = nowX;
        int targetY = nowY;

        for (int i = 1; i <= jump_count; i++)
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
            m_Is_Jump_2 = true;
            m_Jump_Timer_2 = 0.0f;
            m_Jump_Start_2 = player.GetCharaPos();

            CFall_Player2::GetInstance().ForceStop();
            if (jump_count == 2)
            {
                vivid::PlaySound("data\\sound\\high_jump.wav", false);
            }
            else if (jump_count == 4)
            {
                vivid::PlaySound("data\\sound\\max_jump.wav", false);
            }
            else if (jump_count == 3)
            {
                vivid::PlaySound("data\\sound\\half_jump.wav", false);
            }
            // プレイヤーを中央に
            m_Jump_Target_2.x = targetX * m_chip_size + 8.0f;
            m_Jump_Target_2.y = targetY * m_chip_size + 8.0f;

            player.GetItemID() = ITEM_ID::UNKNOW;
        }

        m_High_Jump_Timer_2 = 0;
    }
}

