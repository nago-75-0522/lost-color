#include "ball_manager.h"
#include "ball_score/ball_score.h"
#include"../../player_manager/ball_player_mana/ball_player_mana.h"

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
	CBall_Player_Manager::GetInstance().Initialize();
}

void CBallManager::Update(void)
{
	CBall::GetInstance().Update();
	CBall_Player_Manager::GetInstance().Update();
}

void CBallManager::Draw(void)
{
	CBall::GetInstance().Draw();
	CBall_Player_Manager::GetInstance().Draw();
}

void CBallManager::Finalize(void)
{
	CBall_Player_Manager::GetInstance().Finalize();
}

