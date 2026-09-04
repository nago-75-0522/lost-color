#include "race_player.h"
#include"../../../minigame_manager/race/race_manager/camera/camera.h"
#include"../../../minigame_manager/race/race_manager/map/map.h"
#include"../../../minigame_manager/race/race_manager/race_manager.h"

const vivid::Vector2 IRace_Player::m_speed = { 8.0f,8.0f };
const int IRace_Player::m_size = 64;
const float IRace_Player::m_move_time = 120.f / m_speed.y;
const int IRace_Player::m_back_time = 1 * 60; //1秒

IRace_Player::IRace_Player(PLAYER_CATEGORY category)
	: m_Player_Pos(0.0f, 0.0f)
	, m_Draw_Pos(0.0f, 0.0f)
	, m_Move_Pos(0.0f, 0.0f)
	, m_Velocity(0.0f, 0.0f)
	, m_Camera_Copy_Pos(CCamera::GetInstance().GetCameraPos())
	, m_Active_Flag(true)
	, m_isAccele(false)
	, m_isPush(false)
	, m_isUp_Move(false)
	, m_isDown_Move(false)
	, m_isUp_Lane(false)
	, m_isDown_Lane(false)
	, m_Move_Timer(0.0f)
	, m_Back_Timer(0)
	, m_Now_Num_Map(0)
	, m_Keep_Num(0)
	, m_Back_Count(0)
	, m_isBack_Category(false)
	, m_isBack(false)
	, m_isBack_Cnt_Pull(false)
	, m_isGoal(false)
	, m_Category(category)
{
}

void IRace_Player::Initialize()
{
	m_Player_Pos = { 0.0f,0.0f };
	m_Draw_Pos = { 0.0f,0.0f };
	m_Move_Pos = { 0.0f,0.0f };
	m_Velocity.x = m_speed.x;
	m_Velocity.y = m_speed.y;
	m_Active_Flag = true;
	m_isAccele = false;
	m_isPush = false;

	m_isUp_Move = false;
	m_isDown_Move = false;
	m_isUp_Lane = false;
	m_isDown_Lane = false;

	m_Move_Timer = m_move_time;
	m_Back_Timer = m_back_time;
	m_Now_Num_Map = 0;
	m_Keep_Num = 0;

	m_Back_Count = 0;
	m_isBack_Category = false;
	m_isBack = false;
	m_isBack_Cnt_Pull = false;

	m_isGoal = false;
}

void IRace_Player::Update(void)
{
	CMap& map = CMap::GetInstance();

	m_Player_Pos.x -= m_Velocity.x;
#if 1
	switch (m_Now_Num_Map)
	{
	case 0:
		if (!m_isPush)
		{
			m_isUp_Move = false;
			m_isDown_Move = false;
		}
		break;
	case 3:
		//3番のところまで上も下も押されなかった時の処理
		if (!m_isUp_Move && !m_isDown_Move)
		{
			//どっちが加速レーンにつながるか判断する
			if (map.isUpNum() == 4)
				m_isDown_Move = true;
			else if (map.isUpNum() == 5)
				m_isUp_Move = true;

		}

		if (m_isUp_Move)
			m_isUp_Move = true;
		else
			m_isDown_Move = true;

		m_Back_Timer = m_back_time;

		break;
	case 4:
		m_Keep_Num = 4; //保存
		break;
	case 5:
		m_Keep_Num = 5; //保存
		break;
	case 6:
		//** 真ん中に戻り始める場所 **//
		m_isDown_Move = true;
		m_isPush = false;
		break;
	case 7:
		m_isUp_Move = true;
		m_isPush = false;
		break;
	case 8:
		m_isAccele = true;
		break;
	case 9:
		m_isGoal = true; //ゴールした
		break;

	default:
		break;
	}
#endif

	//** 上や下に移動する処理 **//
	if (m_Now_Num_Map == 3 || m_Now_Num_Map == 6 || m_Now_Num_Map == 7)
	{
		m_Velocity.y = m_speed.y;
		m_Keep_Num = m_Now_Num_Map;

		if (m_isUp_Move)
		{
			//上に移動 
			if (--m_Move_Timer >= 0)
			{
				m_Move_Pos.y -= m_Velocity.y;
			}

		}
		else if (m_isDown_Move)
		{
			//下に移動 14->0 計15回通る
			if (--m_Move_Timer >= 0)
			{
				m_Move_Pos.y += m_Velocity.y;
			}
		}

		//** 代入 **//
		m_isUp_Lane = m_isUp_Move;
		m_isDown_Lane = m_isDown_Move;
	}

	if (m_Move_Timer < 0)
	{
		//リセット
		m_Move_Timer = m_move_time;
		//m_Move_Timer = 0; //デバッグ用
		m_isUp_Move = false;
		m_isDown_Move = false;
		m_Velocity.y = 0.f;

	}
}

void IRace_Player::Finalize()
{
}

bool IRace_Player::isOffscreen(void)
{
	//画面外に出た
	if (m_Draw_Pos.x >= vivid::WINDOW_WIDTH)
		return true;

	return false;
}


//後ろに下がるときに入れる用、もしくは元の場所に戻す用
void IRace_Player::SetMovePosX(float x)
{
	if (--m_Back_Timer > 0)
	{
		//後ろに下がった回数を記録
		if (!m_isBack && !m_isAccele && m_isBack_Category) //自分が下がる対象者だった場合のみ
		{
			m_Back_Count++; //下がった回数
			m_isBack = true;
		}

		m_Move_Pos.x += x; //前か後ろに動かす
	}
	else
	{
		x = 0.f;
		m_Move_Pos.x = m_Move_Pos.x; //その位置で固定
		m_isBack = false;
	}
}

void IRace_Player::SetIsAccele(bool flg)
{
	m_isAccele = flg; //セット
}

void IRace_Player::SetBackOK(bool flg)
{
	m_isBack_Category = flg; //セット
}

void IRace_Player::SetBackCount(int num)
{
	//１回だけ引く
	if (!m_isBack_Cnt_Pull)
	{
		m_Back_Count -= num;
		m_isBack_Cnt_Pull = true;
	}
}


//今自分が何升目にいるか入れる関数
void IRace_Player::SetNowNumMap(int num)
{
	m_Now_Num_Map = num; //瞬間的なマップ情報
}

void IRace_Player::SetSpeed(float speed)
{
	m_Velocity.x = speed;
}




