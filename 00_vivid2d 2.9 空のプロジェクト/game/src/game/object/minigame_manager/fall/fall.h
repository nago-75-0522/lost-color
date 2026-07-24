#pragma once
#include"vivid.h"
#include"fall_chip.h"
#include<vector>
class CFall
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	int GetMapChipSize(void);
	bool CheckEmpty(int x, int y);
	bool CheckWall(int x, int y);
	static CFall& GetInstance();

	MAP_CHIP_ID GetMapChipID();

private:
	CFall(void);
	//コピーコンストラクタ
	CFall(const CFall& rhp) = delete;

	CFall& operator=(const CFall& rhp) = delete;

	~CFall(void) = default;



	//定数
	static const int m_map_chip_size;////１マスの大きさ
	static const int m_map_chip_count_width;//マス（横）の数
	static const int m_map_chip_count_height;//マス（縦）高さ
	static const int m_floor_time;//同じマスにずっと乗ってたら床の色が変わる
	static const char* m_map_path;//マップのパス
	static const std::string m_fall_chip_path;//床の画像のパス
	static const int m_chara_center;//キャラの中心
	static const int m_map_width;//横のマスの数
	static const int m_map_height;//縦のマスの数
	static const int m_max_player;


	//変数
	std::vector<std::vector<unsigned char>>m_Map;//二次元配列 : 見た目
	std::vector<std::vector<unsigned char>>m_Now_Map;//二次元配列　：　データ上
	int m_Floor_Timer[2];
	int m_Old_X[2];
	int m_Old_Y[2];
	MAP_CHIP_ID m_Map_Chip_ID;



};