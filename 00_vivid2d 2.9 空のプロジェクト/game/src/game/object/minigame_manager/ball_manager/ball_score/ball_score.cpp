#include"ball_score.h"

const int CBallScore::m_max_score = 999999999;
const int CBallScore::m_max_score_digit = 9;

//シングルトン
CBallScore& CBallScore::GetInstance()
{
	static CBallScore instance;
	return instance;
}

//コンストラクタ
CBallScore::CBallScore(void)
	:m_Player1Score(0)
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
	vivid::LoadTexture("data\\number.png");

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
	int digit_count = 1;//桁のカウント

	do
	{
		//一桁取り出す
		int d = s % 10;

		//読み込み範囲を計算
		vivid::Rect rect;

		rect.left = d * NumberImage::WIDTH;			//左
		rect.right = rect.left + NumberImage::WIDTH;//右
		rect.top = 0;								//上
		rect.bottom = NumberImage::HEIGHT;			//下

		//表示位置の計算
		vivid::Vector2 m_pos;

		m_pos.x = position.x + NumberImage::WIDTH * (m_max_score_digit - digit_count);
		m_pos.y = position.y;

		vivid::DrawTexture("data\\number.png", m_pos, 0xffffffff, rect);

		//桁をずらす
		s /= 10;//10で割る

		//桁数加算
		++digit_count;

	} while (s > 0 && digit_count < m_max_score_digit);
}

//解放
void CBallScore::Finalize(void)
{
}
