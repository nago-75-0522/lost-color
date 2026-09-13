#include "catch_effect.h"

const int CCatchEffect::m_width = 16;
const int  CCatchEffect::m_height = 16;

CCatchEffect::CCatchEffect(void)
	:IEffect(m_width, m_height)
	, m_Life(30)
{
}

CCatchEffect::~CCatchEffect(void)
{
}

void CCatchEffect::Initialize(const vivid::Vector2& pos, unsigned int color, float rotation)
{
	IEffect::Initialize(pos, color, rotation);
	m_Life = 30;
	for (int i = 0; i < m_max_effect_count; i++)
	{
		//エフェクトの初期位置の設定
		m_catch[i].pos = pos;
		//ランダムな方向へ飛び出す(０～359度)
		float angle = (float)(rand() % 360) * 3.14f / 180.0f;
		//飛び出す速さをランダムで決める
		//今は２～４の間の値になる
		float speed = (float)(rand() % 3 + 2);

		// X方向の移動速度を計算
		// cosfによって左右への移動量を求める
		m_catch[i].velocity.x = cosf(angle) * speed;
		// Y方向の移動速度を計算
		// sinfによって上下への移動量を求める
		m_catch[i].velocity.y = sinf(angle) * speed;
		// 星の初期回転角度をランダムに設定
		m_catch[i].rotation = (float)(rand() % 360);
		// 回転速度をランダムに設定
		// -5～4の範囲で左回転・右回転が発生
		m_catch[i].rotation_speed = (float)(rand() % 10 - 5);
	}
}

void CCatchEffect::Update(void)
{
	for (int i = 0; i < m_max_effect_count; i++)
	{
		//移動
		m_catch[i].pos += m_catch[i].velocity;
		//重力
		m_catch[i].velocity.y += 0.15f;
		//回転
		m_catch[i].rotation += m_catch[i].rotation_speed;
	}
	m_Life--;
	if (m_Life <= 0)
		SetActive(false);
}

void CCatchEffect::Draw(void)
{
	for (int i = 0; i < m_max_effect_count; i++)
	{
		vivid::DrawTexture("data\\ball\\catch_effect.png", m_catch[i].pos, m_Color, m_Rect, m_Anchor, m_Scale, m_catch[i].rotation);
	}
}
