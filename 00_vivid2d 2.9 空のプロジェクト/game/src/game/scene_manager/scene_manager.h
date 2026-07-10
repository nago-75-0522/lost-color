#pragma once
#include"scene/scene_id.h"
#include"scene\scene.h"

enum class FADE
{
	FADE_NOME,	//通常時
	FADE_IN,	//フェードイン
	FADE_OUT,	//フェードアウト
};

class CSceneManager
{

public:
	//インスタンス呼び出す
	static CSceneManager& GetInstance();


	//初期化
	void Initialize();

	//更新
	void Update();

	//描画
	void Draw();

	//解放
	void Finalize();

	/* シーンの切り替え */
	void Change(SCENE_ID id);

	void _ChangeScene();

	/* ステージ回数系 */
	void AddStageCount(void);//加算
	
	int FinishStage();//終了時

	void ResetStageCount();//タイトルに行ったらリセットをかける


private:
	//コンストラクタ
	CSceneManager(); //なにもしない

	//デストラクタ
	~CSceneManager() = default;

	//どこからでも呼び出せるようにする
	CSceneManager(const CSceneManager& rhs) = delete;//コピーの禁止
	CSceneManager& operator =(const CSceneManager& rhs) = delete;//代入の禁止

	/* シーン */
	IScene* m_Scene;		//シーンの保存本体
	SCENE_ID m_CurrentID;	//現在のシーンID
	SCENE_ID m_NextID;		//次のシーン

	/* フェード */
	static const float m_fade_speed;//フェード速度
	FADE	m_FadeState;			//フェード状態
	float	m_FadeAlpha;			//フェード透明度




	int m_StageCount;//ステージ回数

};

