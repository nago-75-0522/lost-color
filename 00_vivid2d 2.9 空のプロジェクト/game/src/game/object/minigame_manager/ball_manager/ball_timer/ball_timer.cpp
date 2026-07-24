#include"ball_timer.h"

const int CBallTimer::play_time = 15;

CBallTimer::CBallTimer(void)
	: m_TimerPos(vivid::Vector2(0.0f, 0.0f))
	, m_PlayTime(0)
	, m_Timer(0)
{
}

void CBallTimer::Initialize(void)
{
	vivid::LoadTexture("data\\number.png");//読み込み

	m_TimerPos = { 560.0f,50.0f };
	m_PlayTime = play_time;
	m_Timer = 0;
}

void CBallTimer::Update(void)
{
	++m_Timer;//フレーム数加算
	//60フレームで1秒として残り時間を計算
	m_PlayTime = play_time - (m_Timer / 60);

	if (m_PlayTime < 0)
		m_PlayTime = 0;
}

void CBallTimer::Draw(void)
{
	//残り秒数を「分」と「秒」に変換
	int minute = m_PlayTime / 60;//分
	int second = m_PlayTime % 60;//秒

	DrawNumber(minute / 10, 0);//分(10の位）
	DrawNumber(minute % 10, 1);//分(1の位）

	// コロン
	vivid::DrawText(40, ":", { m_TimerPos.x + 72.0f, m_TimerPos.y });

	DrawNumber(second / 10, 3);//秒(10の位）
	DrawNumber(second % 10, 4);//秒(1の位）
}

bool CBallTimer::IsTimeUp(void)
{
	return m_PlayTime <= 0;
}

void CBallTimer::DrawNumber(int number, int offset)
{
	vivid::Rect rect;

	rect.left = number * NumberImage::WIDTH;
	rect.right = rect.left + NumberImage::WIDTH;
	rect.top = 0;
	rect.bottom = NumberImage::HEIGHT;

	vivid::Vector2 m_pos;

	m_pos.x = m_TimerPos.x + offset * NumberImage::WIDTH;
	m_pos.y = m_TimerPos.y;

	vivid::DrawTexture("data\\number.png", m_pos, 0xffffffff, rect);
}
