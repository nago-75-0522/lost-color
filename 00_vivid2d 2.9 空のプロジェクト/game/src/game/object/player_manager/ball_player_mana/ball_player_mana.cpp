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
    float overlapLeft =
        player1.GetRight() - player2.GetLeft();
    // P1がP2の右側にいる場合の重なり量
    float overlapRight =
        player2.GetRight() - player1.GetLeft();
    //最短距離の方向へ押し戻す
    float overlap =
        (overlapLeft < overlapRight)
        ? overlapLeft
        : overlapRight;

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
    //衝突したら横移動停止
    player1.StopMove();
    player2.StopMove();
#ifdef _DEBUG
    vivid::DrawText(30, "HIT", { 500, 100 });
#endif
}