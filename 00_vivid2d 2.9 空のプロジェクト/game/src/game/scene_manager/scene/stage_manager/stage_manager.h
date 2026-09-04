#pragma once
#include"..\stage_select\stage_id.h"
#include"..\..\scene\scene.h"

class CStageManager :public IScene
{

public:
	//インスタンス呼び出す
	static CStageManager& GetInstance();

	//初期化
	void Initialize()override;

	//更新
	void Update()override;

	//描画
	void Draw()override;

	//解放
	void Finalize()override;

private:

	//コンストラクタ
	CStageManager(); //なにもしない

	//デストラクタ
	~CStageManager() = default;

	//どこからでも呼び出せるようにする
	CStageManager(const CStageManager& rhs) = delete;//コピーの禁止
	CStageManager& operator =(const CStageManager& rhs) = delete;//代入の禁止

	//現在のステージ
	STAGE_ID m_Stage_id;
};

