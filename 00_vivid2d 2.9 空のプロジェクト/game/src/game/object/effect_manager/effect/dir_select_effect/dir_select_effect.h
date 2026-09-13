#pragma once
#include"../effect.h"

class CDirSelectEffect : public IEffect
{
public:
	CDirSelectEffect(void);
	~CDirSelectEffect(void) = default;

	void Initialize(const vivid::Vector2& pos, unsigned int color, float rotation) override;
	void Update(void)override;
	void Draw(void)override;

private:
	static const int   m_width; //幅
	static const int   m_height;//高さ
	static const int   m_fade_speed;

};
