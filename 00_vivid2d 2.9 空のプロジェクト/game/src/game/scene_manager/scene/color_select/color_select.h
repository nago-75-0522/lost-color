#pragma once
#include"../scene.h"
#include"vivid.h"
class CColor_Select :public IScene
{
public:
	void Initialize()override;
	void Update()override;
	void Draw()override;
	void Finalize()override;
	void IniColor();
	bool GetBlue() { return m_Blue; }
	bool GetRed() { return m_Red; }
	bool GetYellow() { return m_Yellow; }
	static CColor_Select& GetInstance();

private:
	CColor_Select(void);
	//コピーコンストラクタ
	CColor_Select(const CColor_Select& rhp) = delete;

	CColor_Select& operator=(const CColor_Select& rhp) = delete;

	~CColor_Select(void) = default;

	//定数
	vivid::Vector2 m_color_pos;

	//変数
	bool m_Blue;
	bool m_Yellow;
	bool m_Red;
};