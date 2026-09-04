#pragma once
#include <list>
#include"vivid.h"
#include"effect\\effect_id.h"

class IEffect;

class CEffectManager
{
public:
	static CEffectManager& GetInstance(void);

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	//エフェクトの生成
	void Create(EFFECT_ID id, const vivid::Vector2& pos, unsigned int color, float rotation);

private:
	CEffectManager(void);
	CEffectManager(const CEffectManager& rhs);
	~CEffectManager(void);
	CEffectManager& operator = (const CEffectManager& rhs);

	//エフェクトリスト型の定義
	using EFFECT_LIST = std::list<IEffect*>;
	EFFECT_LIST m_EffectList;//エフェクトリスト
};