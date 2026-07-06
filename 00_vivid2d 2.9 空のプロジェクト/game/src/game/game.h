#pragma once
class CGame
{
public:

	//インスタンスの呼び出し
	static CGame& GetInstance();

	//初期化
	void Initialize(void);
	
	//更新	
	void Update(void);
	
	//描画	
	void Draw(void);
	
	//解放	
	void Finalize(void);


private:
	CGame(void) = default;
	~CGame(void) = default;

	//どこからでも呼び出せるようにする
	CGame(const CGame& rhs) = delete;//コピーの禁止
	CGame& operator =(const CGame& rhs) = delete;//代入の禁止


};