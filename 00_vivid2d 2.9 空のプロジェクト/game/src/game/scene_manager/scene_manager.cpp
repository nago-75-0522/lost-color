#include "scene_manager.h"
#include"scene/title/title.h"
#include"scene/option_character/option.h"
#include"scene/gamemain/gamemain.h"
#include"scene/stage/stage1/stage1.h"
#include"scene/stage/stage2/stage2.h"
#include"scene/stage/stage3/stage3.h"
#include"scene/result/result.h"


CSceneManager::CSceneManager()
	:m_Scene(nullptr)
	,m_StageCount(0)
{
}

CSceneManager& CSceneManager::GetInstance()
{
	static CSceneManager instance;//CSceneManager型のインスタンスの作成
	return instance;//インスタンスを返す
}

void CSceneManager::Initialize()
{
	m_NextID =(SCENE_ID::TITLE);//最初の画面の設定

	_ChangeScene();
	if (m_Scene)
	{
		m_Scene->Initialize();
		m_CurrentID = m_NextID;
	}
	

}

void CSceneManager::Update()
{
	if (m_CurrentID != m_NextID)
	{
		_ChangeScene();
		if (m_Scene)
			m_Scene->Initialize();
	}

	if (!m_Scene)
		return;

	m_Scene->Update();

}

void CSceneManager::Draw()
{
	if (m_Scene)
		m_Scene->Draw();
}

void CSceneManager::Finalize()
{

}

void CSceneManager::Change(SCENE_ID id)
{

	//呼び出されたシーンをいれる
	m_NextID = id;//id次のやつ

}

void CSceneManager::_ChangeScene()
{
	if (m_Scene)
	{
		m_Scene->Finalize();

		delete m_Scene;
		m_Scene = nullptr;
	}

	switch (m_NextID)
	{
	case SCENE_ID::TITLE:
		m_Scene = new CTitle();
		break;

	case SCENE_ID::OPTION:
		m_Scene = new COption();
		break;

	case SCENE_ID::GAMEMAIN:
		m_Scene = new CGamemain();
		break;

	case SCENE_ID::STAGE1:
		m_Scene = new CStage1();
		break;

	case SCENE_ID::STAGE2:
		m_Scene = new CStage2();
		break;

	case SCENE_ID::STAGE3:
		m_Scene = new CStage3();
		break;

	case SCENE_ID::RESULT:
		m_Scene = new CResult();
		break;


	default:
		break;
	}

	if (m_Scene)
		m_Scene->Initialize();

	m_CurrentID = m_NextID;
}

//ステージ回数加算
void CSceneManager::AddStageCount(void)
{
	m_StageCount++;//回数加算
}

//終了するかの値を返す
int CSceneManager::FinishStage()
{
	return m_StageCount;//ステージ回数値を返す
}

//回数リセット
void CSceneManager::ResetStageCount()
{
	m_StageCount = 0;
}

