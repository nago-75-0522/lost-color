#include "ball_player_mana.h"
#include"../../minigame_manager/ball_manager/ball/ball.h"

CBall_Player_Manager& CBall_Player_Manager::GetInstance(void)
{
    static CBall_Player_Manager instance;
    return instance;
}

void CBall_Player_Manager::Initialize(void)
{
    player1.Initialize();
    player2.Initialize();
}

void CBall_Player_Manager::Update(void)
{
    player1.Update();
    player2.Update();

    //プレイヤー同士の当たり判定
    CheckPlayerHit();
    //カゴの攻撃
    CheckBasketAttack();
    //ボールとカゴの判定
    CBall::GetInstance().CheckHit(player1.GetBasket(), player2.GetBasket());
}

void CBall_Player_Manager::Draw(void)
{
    player1.Draw();
    player2.Draw();
}

void CBall_Player_Manager::Finalize(void)
{
    player1.Finalize();
    player2.Finalize();
}

CBall_Player_Manager::CBall_Player_Manager(void)
{
}

//プレイヤー同士の当たり判定
void CBall_Player_Manager::CheckPlayerHit()
{
    // 矩形判定
    bool hit =
        player1.GetRight() > player2.GetLeft() &&
        player1.GetLeft() < player2.GetRight() &&
        player1.GetBottom() > player2.GetTop() &&
        player1.GetTop() < player2.GetBottom();
    //当たってなければ終了
    if (!hit)
        return;

    // 横方向のめり込み量
    // P1がP2の左側にいる場合の重なり量
    float overlapLeft = player1.GetRight() - player2.GetLeft();
    // P1がP2の右側にいる場合の重なり量
    float overlapRight = player2.GetRight() - player1.GetLeft();
    //最短距離の方向へ押し戻す
    float overlap = 0.0f;
    if (overlapLeft < overlapRight)
    {
        overlap = overlapLeft;
    }
    else
    {
        overlap = overlapRight;
    }

    // 左右へ押し戻す
    // Player1 が左側にいる場合
    if (player1.GetCenterPosition().x <
        player2.GetCenterPosition().x)
    {
        // 半分ずつ反対方向へ移動
        player1.AddPos({ -overlap * 0.5f, 0.0f });
        player2.AddPos({ overlap * 0.5f, 0.0f });
    }
    // Player1 が右側にいる場合
    else
    {
        // 半分ずつ反対方向へ移動
        player1.AddPos({ overlap * 0.5f, 0.0f });
        player2.AddPos({ -overlap * 0.5f, 0.0f });
    }
}
//カゴの攻撃
void CBall_Player_Manager::CheckBasketAttack()
{
    //p1->p2
    bool hit1 = player1.GetBasket().GetRight() > player2.GetLeft() &&
        player1.GetBasket().GetLeft() < player2.GetRight() &&
        player1.GetBasket().GetBottom() > player2.GetTop() &&
        player1.GetBasket().GetTop() < player2.GetBottom();

    if (player1.IsAttack() && hit1)
    {
        player1.SetAttackHit(true);
        if (player1.GetCenterPosition().x < player2.GetCenterPosition().x)
            player2.AddPos({ 200.0f,-60.0f });//横=200、上＝60
        else
            player2.AddPos({ -200.0f, -60.0f });
    }

    //p2->p1
    bool hit2 = player2.GetBasket().GetRight() > player1.GetLeft() &&
        player2.GetBasket().GetLeft() < player1.GetRight() &&
        player2.GetBasket().GetBottom() > player1.GetTop() &&
        player2.GetBasket().GetTop() < player1.GetBottom();

    if (player2.IsAttack() && hit2)
    {
        player2.SetAttackHit(true);
        if (player2.GetCenterPosition().x < player1.GetCenterPosition().x)
            player1.AddPos({ 200.0f,-60.0f });
        else
            player1.AddPos({ -200.0f, -60.0f });
    }
}