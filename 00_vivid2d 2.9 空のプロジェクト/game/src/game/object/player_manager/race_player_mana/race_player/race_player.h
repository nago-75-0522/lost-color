#pragma once
#include"vivid.h"
#include"race_player_id.h"
#include"../../../minigame_manager/race/race_manager/map/map.h"

class IPlayer
{
public:
	IPlayer(PLAYER_CATEGORY categoty);
	virtual ~IPlayer(void) = default;

	void Initialize(void);

	virtual void Update(void);

	virtual void Draw(void) = 0;//純粋仮想関数

	void Finalize(void);

	virtual vivid::Vector2 GetPosition(void) = 0;

	virtual vivid::Vector2 GetDrawPosition(void) = 0;

	bool GetFlag() { return m_Active_Flag; }

	bool GetAccele(void) { return m_isAccele; } //自分が加速したかどうかを返す関数

	bool GetUpLane(void) { return m_isUp_Lane; } //自分が上のレーンにいるかどうかを返す関数
	bool GetDownLane(void) { return m_isDown_Lane; } //自分が下のレーンにいるかどうかを返す関数

	void SetMovePosX(float x); //自分だけ加速できなかったときに、moveposに入れる関数（後ろに下がるときに使う）

	void SetNowNumMap(int num); //今自分が度のマス目にいるかセットする関数

	void SetSpeed(float speed); //

	void SetIsAccele(bool flg); //加速フラグをfalseにする（リセット）ための関数

	void SetBackOK(bool flg); //自分が下がる対象者なのか判別する変数をセットするための関数

	int GetBackTimer(void) { return m_Back_Timer; } //後ろに下がる時間を外部に渡すための関数

	int GetBackCount(void) { return m_Back_Count; } //後ろに下がった回数を返す変数

	void SetBackCount(int num);

	bool GetIsGoal(void) { return m_isGoal; } //ゴールしたかどうかを返す関数

	bool isOffscreen(void); //画面外に出たかどうかを返す関数

	PLAYER_CATEGORY GetPlayerCategory(void) { return m_Category; } //自分が1pか2pか返す関数

protected:
	static const vivid::Vector2 m_speed;
	static const int m_size;
	static const float m_move_time;//上か下か移動するときに使うタイム
	static const int m_back_time; //後ろに下がっている時間

	vivid::Vector2 m_Player_Pos; //カメラで使う場所
	vivid::Vector2 m_Draw_Pos; //描画するために使う場所
	vivid::Vector2 m_Move_Pos;
	vivid::Vector2 m_Camera_Copy_Pos;
	vivid::Vector2 m_Velocity; //速さ
	bool m_Active_Flag;
	bool m_isAccele; //加速したかどうか
	bool m_isPush; //ボタンを押したかどうか

	bool m_isUp_Move; //上に上がっているかどうか
	bool m_isDown_Move; //下に下がっているかどうか
	bool m_isUp_Lane; //上のレーンにいるかどうか
	bool m_isDown_Lane; //下のレーンにいるかどうか

	float m_Move_Timer; //上と下に下がっている時間
	int m_Back_Timer; //後ろに下がっている時間

	int m_Now_Num_Map; //今自分が何番のマップにいるか
	int m_Keep_Num; //保存用変数

	int m_Back_Count; //何回後ろに下がったか
	bool m_isBack_Category; //そもそも下がる対象者かどうか
	bool m_isBack; //後ろに下がったかどうか
	bool m_isBack_Cnt_Pull; //後ろに下がった回数を減らしたかどうか

	bool m_isGoal; //ゴールしたかどうか

	PLAYER_CATEGORY m_Category; //1Pか2Pか
};

