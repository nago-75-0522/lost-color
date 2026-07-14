#include "scene_manager.h"
#include"scene/title/title.h"
#include"scene/option_character/option.h"
#include"../scene_manager/scene/color_select/color_select.h"
#include"scene/gamemain/gamemain.h"
#include"scene/stage/stage1/stage1.h"
#include"scene/stage/stage2/stage2.h"
#include"scene/stage/stage3/stage3.h"
#include"scene/result/result.h"

const float CSceneManager::m_fade_speed = 1.0f;

CSceneManager::CSceneManager()
	:m_Scene(nullptr)
	, m_StageCount(0)
{
}

CSceneManager& CSceneManager::GetInstance()
{
	static CSceneManager instance;//CSceneManager型のインスタンスの作成
	return instance;//インスタンスを返す
}

//初期化
void CSceneManager::Initialize()
{
	//フェードインから開始
	m_FadeState = FADE::FADE_IN;
	m_FadeAlpha = 1.0f;

	m_NextID = (SCENE_ID::TITLE);//最初の画面の設定

	_ChangeScene();
	if (m_Scene)
	{
		m_Scene->Initialize();
		m_CurrentID = m_NextID;
	}

}

void CSceneManager::Update()
{
	switch (m_FadeState)
	{
	case FADE::FADE_NOME:

		if (!m_Scene)
			return;
		m_Scene->Update();


		break;

	case FADE::FADE_IN:
		//画面を明るくする
		m_FadeAlpha -= m_fade_speed * vivid::GetDeltaTime();

		if (m_FadeAlpha <= 0.0f)
		{
			m_FadeAlpha = 0.0f;

			//フェード完了　通常にする
			m_FadeState = FADE::FADE_NOME;

		}

		break;

	case FADE::FADE_OUT:
		//画面を暗くする
		m_FadeAlpha += m_fade_speed * vivid::GetDeltaTime();

		if (m_FadeAlpha >= 1.0f)
		{
			m_FadeAlpha = 1.0f;


			//シーン変更
			_ChangeScene();

			//明るくする
			m_FadeState = FADE::FADE_IN;
#if 0
			if (m_CurrentID != m_NextID)
			{
				_ChangeScene();
				if (m_Scene)
					m_Scene->Initialize();
			}

#endif 0
		}
		break;

	default:
		break;


	}

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

	// フェード中なら黒画像を重ねる
	if (m_FadeState != FADE::FADE_NOME)
	{
		//0.0～1.0を0～255に変換
		unsigned int alpha = static_cast<unsigned int>(m_FadeAlpha * 255.0f);

		//ARGB形式のアルファ値を作成
		unsigned int color = (alpha << 24);

		vivid::DrawTexture("data\\fade.png", vivid::Vector2::ZERO, color);
	}
}

void CSceneManager::Finalize()
{

}

void CSceneManager::Change(SCENE_ID id)
{

	// 同じシーンなら何もしない
	if (m_CurrentID == id)
		return;

	//呼び出されたシーンをいれる
	m_NextID = id;//id次のやつ

	// フェードアウト開始
	m_FadeState = FADE::FADE_OUT;
}

void CSceneManager::_ChangeScene()
{
	if (m_Scene)
	{
		m_Scene->Finalize();

		//delete m_Scene;
		//m_Scene = nullptr;
	}

	switch (m_NextID)
	{
	case SCENE_ID::TITLE:
		m_Scene = &CTitle::GetInstance();
		break;

	case SCENE_ID::OPTION:
		m_Scene = &COption::GetInstance();
		break;

	case SCENE_ID::GAMEMAIN:
		m_Scene = &CGamemain::GetInstance();
		break;

	case SCENE_ID::COLOR_SELECT:
		m_Scene = &CColor_Select::GetInstance();
		break;

	case SCENE_ID::STAGE1:
		m_Scene = &CStage1::GetInstance();
		break;

	case SCENE_ID::STAGE2:
		m_Scene = &CStage2::GetInstance();
		break;

	case SCENE_ID::STAGE3:
		m_Scene = &CStage3::GetInstance();
		break;

	case SCENE_ID::RESULT:
		m_Scene = &CResult::GetInstance();
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

