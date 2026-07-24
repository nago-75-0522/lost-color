#include"ball_stageset.h"

const float CBallStageSet::m_goundline = 650.0f;
const float CBallStageSet::m_gravity = 0.5f;

void CBallStageSet::Draw(void)
{
}

//地面の高さの取得
float CBallStageSet::GroundLine(void)
{
	return m_goundline;
}

//重力の値の取得
float CBallStageSet::Gravity(void)
{
	return m_gravity;
}
