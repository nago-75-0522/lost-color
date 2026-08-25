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
}

void CBallManager::Update(void)
{
	CBall::GetInstance().Update();
}

void CBallManager::Draw(void)
{
	CBall::GetInstance().Draw();
}

void CBallManager::Finalize(void)
{
}

