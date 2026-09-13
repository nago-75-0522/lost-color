#include"game.h"
#include"../game/scene_manager/scene_manager.h"
#include"object/effect_manager/effect_manager.h"

CGame& CGame::GetInstance()
{
	static CGame instance;
	return instance;
}

void CGame::Initialize(void)
{
	CSceneManager::GetInstance().Initialize();//初期化の呼び出し

	CEffectManager::GetInstance().Initialize();
}

void CGame::Update(void)
{
	CSceneManager::GetInstance().Update();//アップデートの呼び出し

	CEffectManager::GetInstance().Update();
}

void CGame::Draw(void)
{
	CSceneManager::GetInstance().Draw();//描画の呼び出し

	CEffectManager::GetInstance().Draw();
}

void CGame::Finalize(void)
{
	CEffectManager::GetInstance().Finalize();

	CSceneManager::GetInstance().Finalize();//解放の呼び出し
}
