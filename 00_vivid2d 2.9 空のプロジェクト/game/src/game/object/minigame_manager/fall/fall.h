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
	void ChangeFloor(int x,int y);
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
	static const int m_map_chip_size;
	static const int m_map_chip_count_width;
	static const int m_map_chip_count_height;
	static const int m_floor_time;
	static const char* m_map_path;
	static const std::string m_fall_chip_path;
	static const int m_chara_center;
	static const int m_map_width;
	static const int m_map_height;
	
	
	//変数
	bool m_Empty;

	std::vector<std::vector<unsigned char>>m_Map;//二次元配列
	MAP_CHIP_ID m_Map_Chip_ID;

	

};