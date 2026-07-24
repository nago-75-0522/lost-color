#pragma once
#include"vivid.h"
#include"../number_def.h"
#include<string>

class CBallTimer
{
public:
	CBallTimer(void);
	~CBallTimer(void) = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);

	bool IsTimeUp(void);//ゲーム終了判定

private:
	void DrawNumber(int number, int offset);//数字描画

	static const int play_time;//制限時間(秒)

	//変数
	vivid::Vector2 m_TimerPos;//表示位置
	int m_PlayTime;			  //残り秒数
	int m_Timer;			  //フレーム数

};
