#include"race_player_mana.h"
#include"race_player/race_player1/race_player1.h"
#include"race_player/race_player2/race_player2.h"

void CRace_Player_Manager::Initialize(void)
{
	CPlayer1::GetInstance().Initialize();
	CPlayer2::GetInstance().Initialize();

	m_Distance_Num = 0;
	m_isAdd_Num = false;
}

void CRace_Player_Manager::Update(void)
{
	CPlayer1::GetInstance().Update();
	CPlayer2::GetInstance().Update();

	isWhichAccele(); //どっちが加速したか判定し、該当プレイヤーを動かす
}

void CRace_Player_Manager::Draw()
{
	CPlayer1::GetInstance().Draw();
	CPlayer2::GetInstance().Draw();

#if 0
	vivid::DrawText(40, "DistanceNum:" + std::to_string(m_Distance_Num), { 0.0f,120.f }, 0xff000000);
#endif
}

void CRace_Player_Manager::Finalize()
{
	CPlayer1::GetInstance().Finalize();
	CPlayer2::GetInstance().Finalize();
}

vivid::Vector2 CRace_Player_Manager::GetPosition()
{
	return CPlayer1::GetInstance().GetPosition();
	//CPlayer2::GetInstance().GetPosition();
}

//プレイヤーがいる場所を返す関数
vivid::Vector2 CRace_Player_Manager::GetDrawPosition(PLAYER_CATEGORY category)
{
	switch (category)
	{
	case PLAYER_CATEGORY::PLAYER1:
		return CPlayer1::GetInstance().GetDrawPosition();
		break;
	case PLAYER_CATEGORY::PLAYER2:
		return CPlayer2::GetInstance().GetDrawPosition();
		break;
	}
}

//今プレイヤーが何番目のマスにいるかをセットする用の関数
void CRace_Player_Manager::SetNowNumMap(PLAYER_CATEGORY category,int num)
{
	switch (category)
	{
	case PLAYER_CATEGORY::PLAYER1:
		CPlayer1::GetInstance().SetNowNumMap(num);
		break;
	case PLAYER_CATEGORY::PLAYER2:
		CPlayer2::GetInstance().SetNowNumMap(num);
		break;
	}
}

//外部から受け取った速さをセット（上下に動くときだけかな）
void CRace_Player_Manager::SetSpeed(float speed)
{
	CPlayer1::GetInstance().SetSpeed(speed);
	CPlayer2::GetInstance().SetSpeed(speed);
}

//*************************************
// どっちが加速したか判定する用の関数
//*************************************
void CRace_Player_Manager::isWhichAccele(void)
{
	CPlayer1& p1 = CPlayer1::GetInstance();
	CPlayer2& p2 = CPlayer2::GetInstance();

	//** 変数代入 **//
	// 1p
	bool is_player1_accele = p1.GetAccele(); //加速したかどうか
	bool is_player1_up = p1.GetUpLane(); //上のレーンにいるかどうか
	bool is_player1_down = p1.GetDownLane(); //下のレーンにいるかどうか
	// 2p
	bool is_player2_accele = p2.GetAccele(); //加速したかどうか
	bool is_player2_up = p2.GetUpLane(); //上のレーンにいるかどうか
	bool is_player2_down = p2.GetDownLane(); //下のレーンにいるかどうか

	PLAYER_CATEGORY judge_category = PLAYER_CATEGORY::DUMMY; //地面判定の誤差を埋めるために使うプレイヤーの種類

	//** 両方加速してたら関数を抜ける **//
	if (is_player1_accele && is_player2_accele)
	{
		//加速フラグをfalseにする（リセット)
		p1.SetIsAccele(false); 
		p2.SetIsAccele(false); 
		return;		
	}

	//** 両方加速していなかったら関数を抜ける **//
	if (!is_player1_accele && !is_player2_accele)
		return;

	//** 1pと2pが同じレーンにいた場合、関数を抜ける **//
	if(is_player1_up == is_player2_up || is_player1_down == is_player2_down)
	{
		//加速フラグをfalseにする（リセット)
		p1.SetIsAccele(false); 
		p2.SetIsAccele(false); 
		return;
	}

	int back_pos = 4; //後ろに下がるときの移動スピード

	//もし1pだけ加速していたら
	if (is_player1_accele)
	{
		//もし、1pが一回以上後ろに下がっていたら
		if (p1.GetBackCount() >= 1)
		{
			//** 該当プレイヤーは1p **//
			
			//前に進むようにする
			back_pos *= -1; //プラス→マイナス
			judge_category = p1.GetPlayerCategory(); //1p
			//元の位置に戻る用のスピードと該当のプレイヤーセット
			p1.SetMovePosX((float)back_pos); //1p

			//プレイヤーが元の位置に戻ったら
			if (p1.GetBackTimer() < 0)
			{
				p1.SetBackCount(1);	//回数を1回減らす
					
				m_isAdd_Num = false;

				p1.SetIsAccele(false); //1pの加速フラグをfalseにする（リセット）
			}

			//お互いに下がる対象じゃないことをセットする
			p1.SetBackOK(false);
			p2.SetBackOK(false);			
		}
		//1pが一回も下がっていなかったら
		else if (p1.GetBackCount() == 0)
		{
			//** 該当プレイヤーは2p **//
			
			p2.SetBackOK(true); //該当のものを下がらせる対象に
			judge_category = p2.GetPlayerCategory(); //2p

			//後ろに下がる用のスピードと該当のプレイヤーセット
			p2.SetMovePosX((float)back_pos);

			//後ろに下がったプレイヤーのタイマーが 0 になったら
			if (p2.GetBackTimer() < 0)
			{
				m_isAdd_Num = false;

				p1.SetIsAccele(false); //加速フラグをfalseにする（リセット）
			}
		}
	}
	//もし2pだけ加速していたら
	else if (is_player2_accele)
	{
		//もし、2pが一回以上後ろに下がっていたら
		if (p2.GetBackCount() >= 1)
		{
			//** 該当プレイヤーは2p **//
			
			//前に進むようにする
			back_pos *= -1; //プラス→マイナス
			judge_category = p2.GetPlayerCategory(); //2p
			//元の位置に戻る用のスピードセット
			p2.SetMovePosX((float)back_pos);

			//プレイヤーが元の位置に戻ったら
			if (p2.GetBackTimer() < 0)
			{
				p2.SetBackCount(1);	//回数を1回減らす
	
				m_isAdd_Num = false;
				p2.SetIsAccele(false); //2pの加速フラグをfalseにする（リセット）
			}

			//お互いに下がる対象じゃないことをセットする
			p1.SetBackOK(false);
			p2.SetBackOK(false);	
		}
		//2pが一回も下がっていなかったら
		else if (p2.GetBackCount() == 0)
		{
			//** 該当プレイヤーは1p **//

			p1.SetBackOK(true); //該当のものを下がらせる対象に
			judge_category = p1.GetPlayerCategory(); //1p

			//後ろに下がる用のスピードセット
			p1.SetMovePosX((float)back_pos);

			//後ろに下がったプレイヤー（1p）のタイマーが 0 になったら
			if (p1.GetBackTimer() < 0)
			{
				m_isAdd_Num = false;
				p2.SetIsAccele(false); //2pの加速フラグをfalseにする（リセット）
			}
		}
	}

	CMap& map = CMap::GetInstance();

	//最初の一回だけ足したい
	if (!m_isAdd_Num)
	{
		m_Distance_Num += back_pos;
		m_isAdd_Num = true;
	}

	//判定の位置調整用の数字セット（後ろに行くとき、前に行くとき両方使う）
	map.SetNum(m_Distance_Num, judge_category);

}


CRace_Player_Manager& CRace_Player_Manager::GetInstance()
{
	static CRace_Player_Manager instance;

	return instance;
}

CRace_Player_Manager::CRace_Player_Manager()
	:m_Distance_Num(0)
	,m_isAdd_Num(false)
{
}



