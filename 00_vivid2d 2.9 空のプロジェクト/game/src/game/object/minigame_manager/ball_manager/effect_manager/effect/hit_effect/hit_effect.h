#pragma once
#include"vivid.h"
#include"../effect.h"

class CHitEffect :public IEffect
{
public:
	CHitEffect(void);
	~CHitEffect(void);

	void Initialize(const vivid::Vector2& pos, unsigned int color, float rotation);
	void Update(void);
	void Draw(void);


private:
	static const int   m_width; //幅
	static const int   m_height;//高さ
	static const int   m_max_alpha;//最大透明度
	static const float m_start_scale;//初期拡大率
	static const float m_max_scale;//最大拡大率
	static const float m_scale_speed;//拡大速度

	int	  m_Alpha;//透明度
	bool  m_IsShrink;//サイズフラグ
};