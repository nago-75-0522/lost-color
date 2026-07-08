#pragma once
#include"vivid.h"
class CPlayer2_Character
{
public:
	void Initialize();
	void Update();
	void Draw();
	void Finalize();
	void WaitCharacter();
	void MoveCharacter();
	vivid::Vector2 GetScale();
	static CPlayer2_Character& GetInstance();

	vivid::Vector2 GetCharaPos() { return m_Player2_Chara_Pos; }
private:
	CPlayer2_Character(void);
	//コピーコンストラクタ
	CPlayer2_Character(const CPlayer2_Character& rhp) = delete;

	CPlayer2_Character& operator=(const CPlayer2_Character& rhp) = delete;

	~CPlayer2_Character(void) = default;
	enum class CHARA_DIRECTION
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
	};//キャラの向き
	enum class CHARA_STATE
	{
		WAIT,
		MOVE,
	};//キャラの状態

	//定数
	static const int m_player2_chara_width;
	static const int m_player2_chara_height;
	static const int m_player2_chara_move_time;
	static const float m_player2_chara_move_speed;
	static const vivid::Vector2 m_player2_tree_size;
	static const std::string m_player2_boy_path;
	static const int m_player2_chara_center;
	//変数
	CHARA_DIRECTION m_Player2_Chara_Dir;
	CHARA_STATE m_Player2_Chara_State;
	vivid::Vector2 m_Player2_Chara_Pos;
	vivid::Vector2 m_Player2_Chara_Speed;
	int m_Player2_Chara_Anime_Frame;
	int m_Player2_Chara_Anime_Timer;
	int m_Player2_Chara_Move_Timer;

	int m_Player2_Chara_Angle;
	vivid::Vector2 m_Player2_Chara_Anchor;
	vivid::Vector2 m_Player2_Chara_Scale;
	vivid::Rect m_Player2_Chara_Rect;

};