#pragma once
#include"vivid.h"
#include<vector>
#include"../../../../player_manager/race_player_mana/race_player/race_player_id.h"

class CMap
{
public:
	void Inisitalize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	int isUpNum(void); //どっちが加速レーンなのか確かめる

	void SetNum(int num, PLAYER_CATEGORY category); //仮

	//あたりかはずれのレーンの色を表すための数を入れるための関数
	void SetColorRectNum(int win, int lose);

	static CMap& GetInstance();
private:
	CMap();
	~CMap() = default;
	CMap(const CMap& rhs);
	CMap& operator =(const CMap& rhs);

	void isCharaNumNow(vivid::Vector2& pos, float x, float y, float camera_posX); //該当する升目の値を返すために計算する関数

	static const int m_map_width;
	static const int m_map_height;
	static const int m_size;
	static const vivid::Vector2 m_distance;

	std::vector<std::vector<unsigned char>> m_Map; //二次元配列

	int m_Chara_Num; //キャラが何番の升目にいるか返すための変数
	int m_Up_Num; //3か4が出てきたときに上にいるほうの数
	int m_Player1_Num; //仮 判定するときに使うやつ1p用
	int m_Player2_Num; //仮 判定するときに使うやつ2p用

	int m_Color_Win_Num; //当たりレーンの色の数 1or2or3（C,Y,M）
	int m_Color_Lose_Num; //外れレーンの色の数 1or2or3（C,Y,M）
};