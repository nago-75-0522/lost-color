#include "race_player.h"
#include"../../../minigame_manager/race/race_manager/camera/camera.h"
#include"../../../minigame_manager/race/race_manager/map/map.h"

const vivid::Vector2 IPlayer::m_speed = { 8.0f,8.0f };
const int IPlayer::m_size = 64;
const float IPlayer::m_move_time = 120.f / m_speed.y; 
const int IPlayer::m_back_time = 1 * 60; //1秒

IPlayer::IPlayer(PLAYER_CATEGORY category)
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
	, m_Category(category)
{
}

void IPlayer::Initialize()
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
}

void IPlayer::Update(void)
{
	CMap& map = CMap::GetInstance();
	//左へ行く
	m_Player_Pos.x -= m_Velocity.x;

	if (m_Now_Num_Map == 2)
	{
		//2番のところまで上も下も押されなかった時の処理
		if (!m_isUp_Move && !m_isDown_Move)
		{
			//どっちが加速レーンにつながるか判断する
			if (map.isUpNum() == 3)
				m_isDown_Move = true;
			else if (map.isUpNum() == 4)
				m_isUp_Move = true;

		}
	}
	else if (m_Now_Num_Map == 3)
	{
		m_Keep_Num = 3; //保存
	}
	else if (m_Now_Num_Map == 4)
	{
		m_Keep_Num = 4; //保存
	}
	else if (m_Now_Num_Map == 7) //加速レーン
	{
		m_isAccele = true;
	}

	//** 上や下に移動する処理 **//
	if (m_Now_Num_Map == 2 || m_Now_Num_Map == 5 || m_Now_Num_Map == 6)
	{
		m_Velocity.y = m_speed.y;
		m_Keep_Num = m_Now_Num_Map;

		if (m_isUp_Move)
		{
			//上に移動
			if (--m_Move_Timer > 0)
			{
				m_Move_Pos.y -= m_Velocity.y;
			}
		}
		else if (m_isDown_Move)
		{
			//下に移動
			if (--m_Move_Timer > 0)
			{
				m_Move_Pos.y += m_Velocity.y;
			}
		}

		//** 代入 **//
		m_isUp_Lane = m_isUp_Move;
		m_isDown_Lane = m_isDown_Move;
	}

	//** 真ん中に戻り始める場所 **//
	if (m_Now_Num_Map == 5)
	{
		m_isDown_Move = true;
		m_isPush = false;
		m_Back_Timer = m_back_time;
	}
	else if (m_Now_Num_Map == 6)
	{
		m_isUp_Move = true;
		m_isPush = false;
		m_Back_Timer = m_back_time;
	}
	else if (m_Now_Num_Map == 0)
	{
		if (!m_isPush)
		{
			m_isUp_Move = false;
			m_isDown_Move = false;
		}

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

void IPlayer::Finalize()
{
}

//後ろに下がるときに入れる用、もしくは元の場所に戻す用
void IPlayer::SetMovePosX(float x)
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

void IPlayer::SetIsAccele(bool flg)
{
	m_isAccele = flg; //セット
}

void IPlayer::SetBackOK(bool flg)
{
	m_isBack_Category = flg; //セット
}

void IPlayer::SetBackCount(int num)
{
	//１回だけ引く
	if (!m_isBack_Cnt_Pull)
	{
		m_Back_Count -= num;
		m_isBack_Cnt_Pull = true;
	}
}

//今自分が何升目にいるか入れる関数
void IPlayer::SetNowNumMap(int num)
{
	m_Now_Num_Map = num; //瞬間的なマップ情報
}

void IPlayer::SetSpeed(float speed)
{
	m_Velocity.x = speed;
}




