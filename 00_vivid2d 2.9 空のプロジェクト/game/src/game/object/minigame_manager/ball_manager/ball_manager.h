#pragma once
#pragma once
#include"ball/ball.h"

class CBallManager
{
public:
	//初期化
	void Initialize(void);
	//更新
	void Update(void);
	//描画
	void Draw(void);
	//解放
	void Finalize(void);
	//インスタンス呼び出す
	static CBallManager& GetInstance();
private:
	CBallManager(void);
	//コピーコンストラクタ
	CBallManager(const CBallManager& rhp) = delete;

	CBallManager& operator=(const CBallManager& rhp) = delete;

	~CBallManager(void) = default;
};