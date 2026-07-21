#include "color_select.h"
#include"../gamemain/gamemain.h"
#include"../../scene_manager.h"
CColor_Select::CColor_Select()

	:m_color_pos{ 0.0f,100.0f }
{
}

void CColor_Select::Initialize()
{
}

void CColor_Select::Update()
{

#if 0
	//デバック用 全色表示
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
	{
		if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);
	}

#endif 0

	//ステージから青色を消し、選ばれたステージにする
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
	{
		m_Blue = false;
		if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);

	}
	//ステージから黄色を消し、選ばれたステージにする
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))
	{
		m_Yellow = false;
		if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);
	}
	//ステージから赤色を消し、選ばれたステージにする
	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
	{
		m_Red = false;
		if (CGamemain::GetInstance().GetStageSelect() == STAGE_SELECT::STAGE1)
			CSceneManager::GetInstance().Change(SCENE_ID::STAGE1);
	}

}

//描画
void CColor_Select::Draw()
{

	vivid::DrawText(40, "Color_Select", { 0.0f,0.0f });

	if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::A))
		vivid::DrawText(40, "BLUE", m_color_pos);

	else if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::W))
		vivid::DrawText(40, "YELLOW", m_color_pos);

	else if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::D))
		vivid::DrawText(40, "RED", m_color_pos);


}

//解放
void CColor_Select::Finalize()
{
}

//色の初期化
void CColor_Select::IniColor()
{
	m_Blue = true;
	m_Yellow = true;
	m_Red = true;
}

CColor_Select& CColor_Select::GetInstance()
{
	static CColor_Select instance;
	return instance;
}
