#include"ball_score.h"

const int   CBallScore::m_max_score = 999999999;
const int   CBallScore::m_max_score_digit = 9;
const float CBallScore::m_scale = 0.6f;

//シングルトン
CBallScore& CBallScore::GetInstance()
{
	static CBallScore instance;
	return instance;
}

//コンストラクタ
CBallScore::CBallScore(void)
	: m_Player1Score(0)
	, m_Player2Score(0)
	, m_Player1Magenta(0)
	, m_Player1Cyan(0)
	, m_Player1Yellow(0)
	, m_Player2Magenta(0)
	, m_Player2Cyan(0)
	, m_Player2Yellow(0)
{
}

//初期化
void CBallScore::Initialize(void)
{
	//画像の読み込み
	vivid::LoadTexture("data\\logo\\number(白大).png");

	//スコア初期化
	m_Player1Score = 0;
	m_Player2Score = 0;
	//取得個数初期化
	m_Player1Magenta = 0;
	m_Player1Cyan = 0;
	m_Player1Yellow = 0;

	m_Player2Magenta = 0;
	m_Player2Cyan = 0;
	m_Player2Yellow = 0;
}

//描画
void CBallScore::Draw(const vivid::Vector2& position, int m_score)
{
	int s = m_score;

	// 桁数を数える
	int digit_num = 1;
	int temp = s;

	while (temp >= 10)
	{
		temp /= 10;
		++digit_num;
	}

	int digit_count = 1;

	do
	{
		int d = s % 10;
		vivid::Rect rect;

		rect.left = d * NumberImage2::WIDTH;
		rect.right = rect.left + NumberImage2::WIDTH;
		rect.top = 0;
		rect.bottom = NumberImage2::HEIGHT;

		vivid::Vector2 anchor(NumberImage2::WIDTH / 2.0f, NumberImage2::HEIGHT / 2.0f);

		vivid::Vector2 scale(m_scale, m_scale);

		vivid::Vector2 m_pos;

		// 右から左へ配置
		m_pos.x = position.x + (NumberImage2::WIDTH * m_scale) * (digit_num - digit_count);
		m_pos.y = position.y;

		vivid::DrawTexture("data\\logo\\number(白大).png", m_pos, 0xffffffff, rect, anchor, scale);

		s /= 10;
		++digit_count;

	} while (s > 0);
}

//解放
void CBallScore::Finalize(void)
{
}
