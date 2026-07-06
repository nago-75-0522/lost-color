#pragma once
#include"vivid.h"

//基底クラス
class IScene
{
public:
	//コンストラクタ
	IScene() = default;

	//デストラクタ
	virtual ~IScene() = default;

	//初期化
	virtual void Initialize();
	
	//更新
	virtual void Update();

	//描画
	virtual void Draw();

	//解放
	virtual void Finalize();


};