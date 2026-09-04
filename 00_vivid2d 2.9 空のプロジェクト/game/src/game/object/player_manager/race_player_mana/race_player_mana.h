#pragma once
#include"race_player/race_player.h"
#include"race_player/race_player_id.h"

class CRace_Player_Manager
{
public:
	static CRace_Player_Manager& GetInstance(void);

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	vivid::Vector2 GetPosition(void);

	vivid::Vector2 GetDrawPosition(PLAYER_CATEGORY category); //プレイヤーがいる場所を返す関数

	void SetNowNumMap(PLAYER_CATEGORY category, int num); //1p、2pそれぞれ今何マス目にいるかセットする関数

	void SetSpeed(float speed);

	int isRaceWinner(void); //誰が勝ったのか、もしくは引分けだったのかを返す関数

	bool isFinish(void) { return m_isFinish; } //どちらかがゴールしたか返す

private:

	CRace_Player_Manager(void);
	~CRace_Player_Manager(void) = default;
	CRace_Player_Manager(const CRace_Player_Manager& rhs) = delete;
	CRace_Player_Manager& operator =(const CRace_Player_Manager& rhs) = delete;

	void isWhichAccele(void); //どっちが加速したか判定する用の関数

	int m_Distance_Num; //プレイヤーとマップの位置を判定するときの、差を埋めるための変数
	bool m_isAdd_Num; //m_Distance_Numを足したかどうか

	int m_isWinnerNum; //誰が勝ったかを記録する変数（1or2or3）（3は引分け)
	bool m_isFinish;
};
