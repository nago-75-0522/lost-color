#pragma once
#include"vivid.h"
#include"effect_id.h"

class IEffect
{
public:
	IEffect(void);
	IEffect(int width, int height);
	virtual ~IEffect(void);
	virtual void Initialize(const vivid::Vector2& pos, unsigned int color, float rotation);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Finalize(void);

	//位置の取得
	vivid::Vector2 GetPosition(void);
	//位置の特定
	void SetPosition(const vivid::Vector2& pos);
	//アクティブフラグの取得
	bool GetActive(void);
	//アクティブフラグの設定
	void SetActive(bool active);

protected:

	int				m_Width;//幅
	int				m_Height;//高さ
	vivid::Vector2	m_Pos;//位置
	unsigned int	m_Color;//色
	vivid::Vector2	m_Anchor;//基準点
	vivid::Rect		m_Rect;//読み込み範囲
	vivid::Vector2	m_Scale;//拡大率
	float			m_Rotation;//回転率
	bool			m_ActiveFlage;//アクティブフラグ
};