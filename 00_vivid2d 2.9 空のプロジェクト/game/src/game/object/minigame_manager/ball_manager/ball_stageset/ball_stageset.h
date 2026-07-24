#pragma once

class CBallStageSet
{
public:
	CBallStageSet(void) = default;
	~CBallStageSet(void) = default;

	void Draw(void);

	float GroundLine(void);// 地面の高さ
	float Gravity(void);   //重力の値の取得

private:
	static const float m_goundline;// 地面
	static const float m_gravity;  //重力
};