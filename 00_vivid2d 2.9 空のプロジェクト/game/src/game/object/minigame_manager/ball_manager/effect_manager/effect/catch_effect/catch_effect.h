#pragma once
#include"vivid.h"
#include"../effect.h"

class CCatchEffect :public IEffect
{
public:
	CCatchEffect(void);
	~CCatchEffect(void);

	void Initialize(const vivid::Vector2& pos, unsigned int color, float rotation);
	void Update(void);
	void Draw(void);


private:
	struct CATCH_EFFECT_DATA
	{
		vivid::Vector2	pos;//位置
		vivid::Vector2	velocity;//速さ
		float			rotation;//回転
		float			rotation_speed;//回転速度
	};

	static const int   m_width; //幅
	static const int   m_height;//高さ
	static const int   m_max_effect_count = 5;//最大数

	CATCH_EFFECT_DATA m_catch[m_max_effect_count];//生成数
	int m_Life;//エフェクト生存時間

};