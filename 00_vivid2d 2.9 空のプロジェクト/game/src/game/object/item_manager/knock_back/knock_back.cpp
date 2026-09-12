#include "knock_back.h"
#include"../../player_manager/fall_player_mana/fall_player_mana.h"
#include"../../minigame_manager/fall_manager/fall.h"
const int CKnock_Back::m_max_charge_time = 60 * 1;
const int CKnock_Back::m_half_charge_time = 60 * 0.5;
const int CKnock_Back::m_duration_time = 60 * 5;
const int CKnock_Back::m_max_knock_back_num = 100;
const int CKnock_Back::m_chip_size = CFall::GetInstance().GetMapChipSize();
const int CKnock_Back::m_blinking_time = 10;
const unsigned int CKnock_Back::m_invisible_color = 0x00ffffff;
const unsigned int CKnock_Back::m_color = 0xffffffff;
CKnock_Back::CKnock_Back()
    :m_Knock_Back(nullptr)
    , m_Charge_Timer(0)
{
}

void CKnock_Back::Initialize()
{
    m_Knock_Back = new KNOCK_BACK[m_max_knock_back_num];
    for (int i = 0; i < m_max_knock_back_num; ++i)
    {
        KNOCK_BACK& banana = m_Knock_Back[i]; //参照型に置き換え
        banana.m_Knock_Back_Pos = { 0.0f,0.0f };
        banana.m_Duration = m_duration_time;
        banana.m_Knock_Back_Velocity = { 0.0f,0.0f };
        banana.m_Active_Flag = false;
        banana.m_Owner = 0;
        banana.m_LeftOwnerTile = false;
        banana.m_Color = m_color;
        banana.m_IsFlying = false;
        banana.m_FlyT = 0.0f;
        banana.m_StartPos = { 0.0f,0.0f };
        banana.m_TargetPos = { 0.0f,0.0f };
    }
    m_Charge_Timer = 0;
    m_Knock_Back_Pos_1 = { 0.0f,0.0f };
    m_Knock_Back_Pos_2 = { 0.0f,0.0f };
    m_Knock_Back_State = KNOCK_BACK_STATE::ON;
    m_Blinking_Timer = m_blinking_time;
    vivid::LoadSound("data\\sound\\max_jump.wav");
    vivid::LoadSound("data\\sound\\slip.wav");
    vivid::LoadSound("data\\sound\\put.wav");
}

void CKnock_Back::Update()
{
    for (int i = 0; i < m_max_knock_back_num; i++)
    {
        KNOCK_BACK& banana = m_Knock_Back[i]; //参照型に置き換え
        if (banana.m_Active_Flag == true)
        {
            // 飛行中
            if (banana.m_IsFlying)
            {
                banana.m_FlyT += 0.08f;

                if (banana.m_FlyT >= 1.0f)
                {
                    banana.m_FlyT = 1.0f;
                    banana.m_IsFlying = false;
                }

                float t = banana.m_FlyT;

                banana.m_Knock_Back_Pos.x =
                    banana.m_StartPos.x +
                    (banana.m_TargetPos.x - banana.m_StartPos.x) * t;

                banana.m_Knock_Back_Pos.y =
                    banana.m_StartPos.y +
                    (banana.m_TargetPos.y - banana.m_StartPos.y) * t;

                continue;
            }

            --banana.m_Duration;

            if (banana.m_Duration < 3 * 60)
            {
                switch (m_Knock_Back_State)
                {
                case CKnock_Back::KNOCK_BACK_STATE::ON:
                    banana.m_Color = m_color;

                    if (--m_Blinking_Timer <= 0)
                    {
                        m_Blinking_Timer = m_blinking_time;
                        m_Knock_Back_State = KNOCK_BACK_STATE::OFF;
                    }
                    break;

                case CKnock_Back::KNOCK_BACK_STATE::OFF:
                    banana.m_Color = m_invisible_color;

                    if (--m_Blinking_Timer <= 0)
                    {
                        m_Blinking_Timer = m_blinking_time;
                        m_Knock_Back_State = KNOCK_BACK_STATE::ON;
                    }
                    break;
                }
            }

            if (banana.m_Duration <= 0)
            {
                banana.m_Duration = m_duration_time;
                banana.m_Active_Flag = false;
            }
        }
    }
    Check_Hit();
}

void CKnock_Back::Draw()
{
    for (int i = 0; i < m_max_knock_back_num; i++)
    {
        KNOCK_BACK& banana = m_Knock_Back[i]; //参照型に置き換え

        if (!banana.m_Active_Flag)
        {
            continue;
        }


        vivid::Vector2 drawPos = banana.m_Knock_Back_Pos;

        if (banana.m_IsFlying)
        {
            float t = banana.m_FlyT;

            float height =
                sinf(t * 3.141592f) * 80.0f;

            drawPos.y -= height;
        }

        vivid::DrawTexture("data\\fall\\knock_back.png",drawPos,banana.m_Color);
    }
}


void CKnock_Back::Draw(const vivid::Vector2& pos)
{
    vivid::DrawTexture("data\\fall\\knock_back.png", pos);
}

void CKnock_Back::Finalize()
{
}

void CKnock_Back::DrawAim(CFall_Player1& player)
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

        int count = 0;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            count = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            count = 2;
        }
        if (count == 0)
        {
            vivid::DrawTexture("data\\fall\\landing_point.png", player.GetCharaPos(), 0xaafffffff);
            return;
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
                pos.x -= i * 64.0;
                break;

            case CFall_Player1::CHARA_DIRECTION::RIGHT:
                pos.x += i * 64.0f;
                break;
            }
            // 短押し(足元設置)
            if (count == 0)
            {
                vivid::DrawTexture("data\\fall\\landing_point.png", pos, 0xaafffffff);
                return;
            }

            else if (i == count)
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
void CKnock_Back::DrawAim(CFall_Player2& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player2::GetInstance().GetScale().x >= 1)
    {
        if (CFall_Player1::GetInstance().GetScale().x < 1 ||
            (!keyboard::Button(keyboard::KEY_ID::L) &&
                !(triger > DEAD_ZONE)))
        {
            return;
        }
        int count = 0;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            count = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            count = 2;
        }
        if (count == 0)
        {
            vivid::DrawTexture("data\\fall\\landing_point.png", player.GetCharaPos(), 0xaafffffff);
            return;
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
                pos.x -= i * 64.0f;
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

    }
}

void CKnock_Back::Use(CFall_Player1& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER1);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player1::GetInstance().GetScale().x < 1 || CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }
    bool nowTrigger = (triger > DEAD_ZONE);
    bool triggerRelease = (m_Old_Trigger_1 && !nowTrigger);

    m_Old_Trigger_1 = nowTrigger;
    if (keyboard::Button(keyboard::KEY_ID::F) || nowTrigger)
    {
        ++m_Charge_Timer;
    }
    if (keyboard::Released(keyboard::KEY_ID::F) || triggerRelease)
    {
        int range = 0;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            range = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            range = 2;
        }
        else
        {
            range = 0; // 足元
        }
        m_Now_Pos_1.x =
            (int)((player.GetCharaPos().x + 24) / m_chip_size);

        m_Now_Pos_1.y =
            (int)((player.GetCharaPos().y + 24) / m_chip_size);

        m_Knock_Back_Pos_1.x = m_Now_Pos_1.x;
        m_Knock_Back_Pos_1.y = m_Now_Pos_1.y;

        for (int i = 1; i <= range; i++)
        {
            int checkX = m_Now_Pos_1.x;
            int checkY = m_Now_Pos_1.y;

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

            m_Knock_Back_Pos_1.x = checkX;
            m_Knock_Back_Pos_1.y = checkY;
        }
        for (int i = 0; i < m_max_knock_back_num; i++)
        {
            KNOCK_BACK& banana = m_Knock_Back[i];

            if (!banana.m_Active_Flag)
            {
                banana.m_Active_Flag = true;
                banana.m_StartPos = player.GetCharaPos();

                banana.m_TargetPos =
                {
                    m_Knock_Back_Pos_1.x * m_chip_size + 8.0f,
                    m_Knock_Back_Pos_1.y * m_chip_size + 8.0f
                };

                if (range == 0)
                {
                    banana.m_Knock_Back_Pos = banana.m_TargetPos;
                    banana.m_IsFlying = false;
                    banana.m_FlyT = 1.0f;
                }
                else
                {
                    banana.m_Knock_Back_Pos = banana.m_StartPos;
                    banana.m_IsFlying = true;
                    banana.m_FlyT = 0.0f;
                }
               
                banana.m_Duration = m_duration_time;

                banana.m_Owner = 1;
                banana.m_LeftOwnerTile = false;
                banana.m_Color = m_color;
                m_Knock_Back_State = KNOCK_BACK_STATE::ON;
                m_Blinking_Timer = m_blinking_time;
                if (range == 0)
                    vivid::PlaySound("data\\sound\\put.wav", false);
                else if(range>=2)
                vivid::PlaySound("data\\sound\\max_jump.wav", false);
                player.GetItemID() = ITEM_ID::UNKNOW;

                break;
            }
        }

        m_Charge_Timer = 0;
    }
}

void CKnock_Back::Use(CFall_Player2& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);
    const float DEAD_ZONE = 0.5f;
    if (CFall_Player1::GetInstance().GetScale().x < 1 || CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }
    bool nowTrigger = (triger > DEAD_ZONE);
    bool triggerRelease = (m_Old_Trigger_2 && !nowTrigger);

    m_Old_Trigger_2 = nowTrigger;
    if (keyboard::Button(keyboard::KEY_ID::L) || nowTrigger)
    {
        ++m_Charge_Timer;
    }
    if (keyboard::Released(keyboard::KEY_ID::L) || triggerRelease)
    {
        int range = 0;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            range = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            range = 2;
        }
        else
        {
            range = 0; // 足元
        }
        m_Now_Pos_2.x =
            (int)((player.GetCharaPos().x + 24) / m_chip_size);

        m_Now_Pos_2.y =
            (int)((player.GetCharaPos().y + 24) / m_chip_size);

        m_Knock_Back_Pos_2.x = m_Now_Pos_2.x;
        m_Knock_Back_Pos_2.y = m_Now_Pos_2.y;

        for (int i = 1; i <= range; i++)
        {
            int checkX = m_Now_Pos_2.x;
            int checkY = m_Now_Pos_2.y;

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

            m_Knock_Back_Pos_2.x = checkX;
            m_Knock_Back_Pos_2.y = checkY;
        }
        for (int i = 0; i < m_max_knock_back_num; i++)
        {
            KNOCK_BACK& banana = m_Knock_Back[i];

            if (!banana.m_Active_Flag)
            {
                banana.m_Active_Flag = true;
                banana.m_StartPos = player.GetCharaPos();

                banana.m_TargetPos =
                {
                    m_Knock_Back_Pos_2.x * m_chip_size + 8.0f,
                    m_Knock_Back_Pos_2.y * m_chip_size + 8.0f
                };

                if (range == 0)
                {
                    banana.m_Knock_Back_Pos = banana.m_TargetPos;
                    banana.m_IsFlying = false;
                    banana.m_FlyT = 1.0f;
                }
                else
                {
                    banana.m_Knock_Back_Pos = banana.m_StartPos;
                    banana.m_IsFlying = true;
                    banana.m_FlyT = 0.0f;
                }
                
                banana.m_Duration = m_duration_time;

                banana.m_Owner = 2;
                banana.m_LeftOwnerTile = false;
                banana.m_Color = m_color;

                m_Knock_Back_State = KNOCK_BACK_STATE::ON;
                m_Blinking_Timer = m_blinking_time;

                if(range==0)
                    vivid::PlaySound("data\\sound\\put.wav", false);
                else if (range >= 2)
                    vivid::PlaySound("data\\sound\\max_jump.wav", false);

                player.GetItemID() = ITEM_ID::UNKNOW;

                break;
            }
        }
        m_Charge_Timer = 0;
    }
}

void CKnock_Back::Check_Hit()
{


    for (int i = 0; i < m_max_knock_back_num; i++)
    {
        KNOCK_BACK& banana = m_Knock_Back[i]; //参照型に置き換え
        int bx =
            (int)((banana.m_Knock_Back_Pos.x + 24) / m_chip_size);

        int by =
            (int)((banana.m_Knock_Back_Pos.y + 24) / m_chip_size);
        CFall_Player1& player =
            CFall_Player1::GetInstance();
        int p1x =
            (int)((player.GetCharaPos().x + 24) / m_chip_size);

        int p1y =
            (int)((player.GetCharaPos().y + 24) / m_chip_size);
        int p2x =
            (int)((CFall_Player2::GetInstance().GetCharaPos().x + 24)
                / m_chip_size);

        int p2y =
            (int)((CFall_Player2::GetInstance().GetCharaPos().y + 24)
                / m_chip_size);

        if (!banana.m_Active_Flag|| banana.m_IsFlying)
        {
            continue;
        }
        
        if (banana.m_Owner == 1)
        {
            if (!(bx == p1x && by == p1y))
            {
                banana.m_LeftOwnerTile = true;
            }
        }

        if (banana.m_Owner == 2)
        {
            if (!(bx == p2x && by == p2y))
            {
                banana.m_LeftOwnerTile = true;
            }
        }
        if (CItem_Manager::GetInstance().m_High_Jump_P1.Get_Is_Jump_1())
        {
            continue;
        }
        if (!CFall_Player1::GetInstance().GetIsPullMove() && bx == p1x && by == p1y)
        {
            if (banana.m_Owner == 1 &&
                !banana.m_LeftOwnerTile)
            {
                continue;
            }

            vivid::PlaySound("data\\sound\\slip.wav", false);

            CFall_Player1& player =
                CFall_Player1::GetInstance();


            int targetX = p1x;
            int targetY = p1y;

            for (int i = 0; i < 3; i++)
            {
                int nextX = targetX;
                int nextY = targetY;

                switch (player.GetCharaDirection())
                {
                case CFall_Player1::CHARA_DIRECTION::UP:
                    --nextY;
                    break;

                case CFall_Player1::CHARA_DIRECTION::DOWN:
                    ++nextY;
                    break;

                case CFall_Player1::CHARA_DIRECTION::LEFT:
                    --nextX;
                    break;

                case CFall_Player1::CHARA_DIRECTION::RIGHT:
                    ++nextX;
                    break;
                }

                if (nextX < 0 || nextX >= 20 ||
                    nextY < 0 || nextY >= 12)
                {
                    break;
                }

                if (CFall::GetInstance().CheckWall(nextX, nextY))
                {
                    break;
                }

                targetX = nextX;
                targetY = nextY;

            }

            player.GetKnockTargetPos() =
            {
                (float)(targetX * m_chip_size + 8),
                (float)(targetY * m_chip_size + 8)
            };


            player.GetIsKnockMove() = true;

            banana.m_Active_Flag = false;
        }
        if (CItem_Manager::GetInstance().m_High_Jump_P2.Get_Is_Jump_2())
        {
            continue;
        }
        if (!CFall_Player2::GetInstance().GetIsPullMove() && bx == p2x && by == p2y)
        {

            if (banana.m_Owner == 2 &&
                !banana.m_LeftOwnerTile)
            {
                continue;
            }

            vivid::PlaySound("data\\sound\\slip.wav", false);

            CFall_Player2& player =
                CFall_Player2::GetInstance();

            int targetX = p2x;
            int targetY = p2y;

            for (int i = 0; i < 3; i++)
            {
                int nextX = targetX;
                int nextY = targetY;

                switch (player.GetCharaDirection())
                {
                case CFall_Player2::CHARA_DIRECTION::UP:
                    --nextY;
                    break;

                case CFall_Player2::CHARA_DIRECTION::DOWN:
                    ++nextY;
                    break;

                case CFall_Player2::CHARA_DIRECTION::LEFT:
                    --nextX;
                    break;

                case CFall_Player2::CHARA_DIRECTION::RIGHT:
                    ++nextX;
                    break;
                }

                if (nextX < 0 || nextX >= 20 ||
                    nextY < 0 || nextY >= 12)
                {
                    break;
                }

                if (CFall::GetInstance().CheckWall(nextX, nextY))
                {
                    break;
                }

                targetX = nextX;
                targetY = nextY;
            }
            player.GetKnockTargetPos() =
            {
                (float)(targetX * m_chip_size + 8),
                (float)(targetY * m_chip_size + 8)
            };


            player.GetIsKnockMove() = true;

            banana.m_Active_Flag = false;
        }
    }
}