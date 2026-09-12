#include "pull.h"
#include"../../player_manager/fall_player_mana/fall_player_mana.h"
#include "../../minigame_manager/fall_manager/fall.h"

const int CPull::m_half_charge_time = 60 * 0.5;
const int CPull::m_max_charge_time = 60 * 1;
const int CPull::m_map_chip_size = CFall::GetInstance().GetMapChipSize();
CPull::CPull()
    :m_Charge_Timer(0)
{
}

void CPull::Initialize()
{
    m_Charge_Timer = 0;
    m_Pull_Range_1 = 0;
    m_Pull_Range_2 = 0;
    vivid::LoadSound("data\\sound\\wind.wav");
}

void CPull::Update()
{


}

void CPull::Draw()
{
}

void CPull::Draw(const vivid::Vector2& pos)
{
    vivid::DrawTexture("data\\fall\\pull.png", pos);
}
void CPull::DrawAim(CFall_Player1& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER1);
    const float DEAD_ZONE = 0.5f;

    if (!keyboard::Button(keyboard::KEY_ID::F) &&
        !triger > DEAD_ZONE)
    {
        return;
    }
    if (CFall_Player1::GetInstance().GetScale().x < 1 || CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }
    int range = 2;

    if (m_Charge_Timer >= m_max_charge_time)
    {
        range = 4;
    }
    else if (m_Charge_Timer >= m_half_charge_time)
    {
        range = 3;
    }

    int myX =
        (int)((player.GetCharaPos().x + 24) / 64);

    int myY =
        (int)((player.GetCharaPos().y + 24) / 64);

    for (int y = -range; y <= range; y++)
    {
        for (int x = -range; x <= range; x++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            int drawX = myX + x;
            int drawY = myY + y;

            if (drawX < 0 || drawX >= 20 ||
                drawY < 0 || drawY >= 12)
            {
                continue;
            }

            if (CFall::GetInstance().CheckWall(drawX, drawY))
            {
                continue;
            }

            vivid::Vector2 pos;
            pos.x = drawX * 64.0f;
            pos.y = drawY * 64.0f;

            vivid::DrawTexture("data\\fall\\landing_point.png", pos, 0x88ffffff);
        }
    }
}
void CPull::DrawAim(CFall_Player2& player)
{
    namespace controller = vivid::controller;
    namespace keyboard = vivid::keyboard;
    float triger = controller::GetTriggerRight(controller::DEVICE_ID::PLAYER2);
    const float DEAD_ZONE = 0.5f;

    if (!keyboard::Button(keyboard::KEY_ID::L) &&
        !triger > DEAD_ZONE)
    {
        return;
    }
    if (CFall_Player1::GetInstance().GetScale().x < 1 || CFall_Player2::GetInstance().GetScale().x < 1)
    {
        return;
    }
    int range = 2;

    if (m_Charge_Timer >= m_max_charge_time)
    {
        range = 4;
    }
    else if (m_Charge_Timer >= m_half_charge_time)
    {
        range = 3;
    }

    int myX =
        (int)((player.GetCharaPos().x + 24) / 64);

    int myY =
        (int)((player.GetCharaPos().y + 24) / 64);

    for (int y = -range; y <= range; y++)
    {
        for (int x = -range; x <= range; x++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            int drawX = myX + x;
            int drawY = myY + y;

            if (drawX < 0 || drawX >= 20 ||
                drawY < 0 || drawY >= 12)
            {
                continue;
            }

            if (CFall::GetInstance().CheckWall(drawX, drawY))
            {
                continue;
            }

            vivid::Vector2 pos;
            pos.x = drawX * 64.0f;
            pos.y = drawY * 64.0f;

            vivid::DrawTexture("data\\fall\\landing_point.png", pos, 0x88ffffff);
        }
    }
}
void CPull::Finalize()
{
}

void CPull::Use(CFall_Player1& player)
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
        m_Is_Use_1 = true;
        m_Pull_Range_1 = 2;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            m_Pull_Range_1 = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            m_Pull_Range_1 = 3;
        }


        int myx =
            (int)((player.GetCharaPos().x + 24) / 64);

        int myy =
            (int)((player.GetCharaPos().y + 24) / 64);

        int enemyx =
            (int)((CFall_Player2::GetInstance().GetCharaPos().x + 24) / 64);

        int enemyy =
            (int)((CFall_Player2::GetInstance().GetCharaPos().y + 24) / 64);

        int dx = abs(enemyx - myx);
        int dy = abs(enemyy - myy);

        // チャージ量に応じた距離以内なら吸う
        if (dx <= m_Pull_Range_1 && dy <= m_Pull_Range_1)
        {
            int targetx;
            int targety;

            int loop = 0;

            do
            {
                targetx = myx + (rand() % 3) - 1;
                targety = myy + (rand() % 3) - 1;

                if (targetx < 0) targetx = 0;
                if (targetx > 19) targetx = 19;

                if (targety < 0) targety = 0;
                if (targety > 11) targety = 11;

                ++loop;

            } while (
                (
                    CFall::GetInstance().CheckWall(targetx, targety) ||
                    (targetx == myx && targety == myy)
                    )
                &&
                loop < 50
                );

            if (!CFall::GetInstance().CheckWall(targetx, targety))
            {
                auto& enemy = CFall_Player2::GetInstance();

                enemy.ForceStop();

                enemy.SetIsPullMove(true);

                enemy.GetPullTargetPos().x =
                    targetx * m_map_chip_size + 8.0f;

                enemy.GetPullTargetPos().y =
                    targety * m_map_chip_size + 8.0f;

                vivid::PlaySound("data\\sound\\wind.wav", false);


                player.GetItemID() = ITEM_ID::UNKNOW;
            }
        }
        m_Charge_Timer = 0;
    }
}


void CPull::Use(CFall_Player2& player)
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
        m_Is_Use_2 = true;
        m_Pull_Range_2 = 2;

        if (m_Charge_Timer >= m_max_charge_time)
        {
            m_Pull_Range_2 = 4;
        }
        else if (m_Charge_Timer >= m_half_charge_time)
        {
            m_Pull_Range_2 = 3;
        }

        int myx =
            (int)((player.GetCharaPos().x + 24) / 64);

        int myy =
            (int)((player.GetCharaPos().y + 24) / 64);

        int enemyx =
            (int)((CFall_Player1::GetInstance().GetCharaPos().x + 24) / 64);

        int enemyy =
            (int)((CFall_Player1::GetInstance().GetCharaPos().y + 24) / 64);

        int dx = abs(enemyx - myx);
        int dy = abs(enemyy - myy);

        // チャージ量に応じた距離以内なら吸う
        if (dx <= m_Pull_Range_2 && dy <= m_Pull_Range_2)
        {
            int targetx;
            int targety;

            int loop = 0;

            do
            {
                targetx = myx + (rand() % 3) - 1;
                targety = myy + (rand() % 3) - 1;

                if (targetx < 0) targetx = 0;
                if (targetx > 19) targetx = 19;

                if (targety < 0) targety = 0;
                if (targety > 11) targety = 11;

                ++loop;

            } while (
                (
                    CFall::GetInstance().CheckWall(targetx, targety) ||
                    (targetx == myx && targety == myy)
                    )
                &&
                loop < 50
                );

            if (!CFall::GetInstance().CheckWall(targetx, targety))
            {
                auto& enemy = CFall_Player1::GetInstance();

                enemy.ForceStop();

                enemy.SetIsPullMove(true);

                enemy.GetPullTargetPos().x =
                    targetx * m_map_chip_size + 8.0f;

                enemy.GetPullTargetPos().y =
                    targety * m_map_chip_size + 8.0f;

                vivid::PlaySound("data\\sound\\wind.wav", false);

                player.GetItemID() = ITEM_ID::UNKNOW;
            }
        }
        m_Charge_Timer = 0;
    }
}