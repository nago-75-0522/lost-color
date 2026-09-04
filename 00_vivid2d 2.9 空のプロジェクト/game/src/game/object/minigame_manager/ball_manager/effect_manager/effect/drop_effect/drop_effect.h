#pragma once
#include"vivid.h"
#include"../effect.h"
#include"../../../ball_stageset/ball_stageset.h"

class CDropEffect :public IEffect
{
public:
	CDropEffect(void);
	~CDropEffect(void);

	void Initialize(const vivid::Vector2& pos, unsigned int color, float rotation);
	void Update(void);
	void Draw(void);

private:
	CBallStageSet m_ball_stageset;

	static const int   m_width; //幅
	static const int   m_height;//高さ
	static const float m_scale; //拡大率

	vivid::Vector2	m_Velocity;
	bool			m_IsBound;
};