#pragma once
#include"vivid.h"
#include"../../../item_manager/item_manager.h"


class CFall_Player1
{
public:

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void Wait_Character();
	void Move_Character();
	bool Hit_Item_Box();
	bool Get_Item();
	void Item_Lottery();
	vivid::Vector2 GetScale();
	static CFall_Player1& GetInstance();
	ITEM_ID& GetItemID() { return m_Item_ID; }
	vivid::Vector2& GetCharaPos() { return m_Player1_Chara_Pos; }

	enum class CHARA_DIRECTION
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
	};//キャラの向き
	CHARA_DIRECTION GetCharaDirection() { return m_Player1_Chara_Dir; }
private:
	CFall_Player1(void);
	//コピーコンストラクタ
	CFall_Player1(const CFall_Player1& rhp) = delete;

	CFall_Player1& operator=(const CFall_Player1& rhp) = delete;

	~CFall_Player1(void) = default;

	enum class CHARA_STATE
	{
		WAIT,
		MOVE,
	};//キャラの状態

	//定数
	static const int m_player1_chara_width;
	static const int m_player1_chara_height;
	static const int m_player1_chara_move_time;
	static const float m_player1_chara_move_speed;
	static const vivid::Vector2 m_player1_tree_size;
	static const std::string m_player1_boy_path;
	static const int m_player1_chara_center;
	static const std::string m_player1_marker_path;
	static const vivid::Vector2 m_player1_marker_size;
	static const int m_item_box_size;
	//変数
	CHARA_DIRECTION m_Player1_Chara_Dir;
	CHARA_STATE m_Player1_Chara_State;
	vivid::Vector2 m_Player1_Chara_Pos;
	vivid::Vector2 m_Player1_Chara_Speed;
	int m_Player1_Chara_Anime_Frame;
	int m_Player1_Chara_Anime_Timer;
	int m_Player1_Chara_Move_Timer;
	int m_Player1_Chara_Angle;
	vivid::Vector2 m_Player1_Chara_Anchor;
	vivid::Vector2 m_Player1_Chara_Scale;
	vivid::Rect m_Player1_Chara_Rect;
	vivid::Vector2 m_Player1_Marker_Pos;
	bool m_Player1_Fall_Sound;
	bool m_Player1_Get_Item;
	ITEM_ID m_Item_ID;
};