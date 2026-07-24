#pragma once
#include"..\..\scene\scene.h"



class CTitle :public IScene
{
public:
	//初期化
	void Initialize(void)override;//多重定義
	//更新
	void Update(void)override;
	//描画
	void Draw(void)override;
	//解放
	void Finalize(void)override;

	static CTitle& GetInstance();
private:
	CTitle(void);
	//コピーコンストラクタ
	CTitle(const CTitle& rhp) = delete;

	CTitle& operator=(const CTitle& rhp) = delete;

	~CTitle(void) = default;

	const std::string m_title_logo_file;		//ロゴ画像
	const int		  m_title_logo_width;		//幅
	const int		  m_title_logo_height;		//高さ

	//vivid::Vector2		  m_title_logo_anchor;		//中心点
	vivid::Vector2			  m_TitlePos;			//タイトル画像表示位置


	int m_Logo_Time;						//ロゴの表示時間
	
	vivid::Vector2 m_start_logo;			//ロゴスタートの位置

	

};