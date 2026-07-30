#include "ball_manager.h"
#include "ball_score/ball_score.h"

CBallManager& CBallManager::GetInstance()
{
	static CBallManager instance;
	return instance;
}

CBallManager::CBallManager(void)
{
}

void CBallManager::Initialize(void)
{
	CBallScore::GetInstance().Initialize();
	CBall::GetInstance().Initialize();
	m_ball_player1.Initialize();
	m_ball_player2.Initialize();
}

void CBallManager::Update(void)
{
	CBall::GetInstance().Update();
	m_ball_player1.Update();
	m_ball_player2.Update();
	CBall::GetInstance().CheckHit(m_ball_player1.GetBasket(), m_ball_player2.GetBasket());
}

void CBallManager::Draw(void)
{
	CBall::GetInstance().Draw();
	m_ball_player2.Draw();
	m_ball_player1.Draw();
}

void CBallManager::Finalize(void)
{
	m_ball_player2.Finalize();
	m_ball_player1.Finalize();
}

