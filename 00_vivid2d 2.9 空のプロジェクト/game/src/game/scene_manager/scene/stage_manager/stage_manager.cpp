#include"stage_manager.h"
#include"stage1/stage1.h"
#include"stage2/stage2.h"
#include"stage3/stage3.h"
#include"vivid.h"
#include"..\stage_select\stage_select.h"

/*ステージの切り替えるだけのマネージャー */


//インスタンスの取得
CStageManager& CStageManager::GetInstance()
{
	static CStageManager instance;
	return instance;

}

CStageManager::CStageManager(void)
{

}

void CStageManager::Initialize()
{

	//保存したIDの取得
	m_Stage_id = CStage_Select::GetInstance().GetStageID();

	switch (m_Stage_id)
	{
	case STAGE_ID::STAGE1:
		CStage1::GetInstance().Initialize();
		break;


	case STAGE_ID::STAGE2:
		CStage2::GetInstance().Initialize();
		break;


	case STAGE_ID::STAGE3:
		CStage3::GetInstance().Initialize();
		break;

	default:
		break;
	}
}

void CStageManager::Update()
{
	switch (m_Stage_id)
	{
	case STAGE_ID::STAGE1:
		CStage1::GetInstance().Update();
		break;


	case STAGE_ID::STAGE2:
		CStage2::GetInstance().Update();
		break;


	case STAGE_ID::STAGE3:
		CStage3::GetInstance().Update();
		break;

	default:
		break;
	}
}

void CStageManager::Draw()
{
	switch (m_Stage_id)
	{
	case STAGE_ID::STAGE1:
		CStage1::GetInstance().Draw();
		break;


	case STAGE_ID::STAGE2:
		CStage2::GetInstance().Draw();
		break;


	case STAGE_ID::STAGE3:
		CStage3::GetInstance().Draw();
		break;

	default:
		break;
	}
}

void CStageManager::Finalize()
{
	switch (m_Stage_id)
	{
	case STAGE_ID::STAGE1:
		CStage1::GetInstance().Finalize();
		break;


	case STAGE_ID::STAGE2:
		CStage2::GetInstance().Finalize();
		break;


	case STAGE_ID::STAGE3:
		CStage3::GetInstance().Finalize();
		break;

	default:
		break;
	}
}
