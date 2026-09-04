/* キャラクター説明 接続
	プレイヤーの表示
*/
#include"option.h"
#include"..\..\scene_manager.h"
#include"vivid.h"

//インスタンス取得
COption& COption::GetInstance()
{
	static COption instance;
	return instance;
}

COption::COption(void)
{
	
}

//初期化
void COption::Initialize(void)
{
	vivid::LoadSound("data\\sound\\click.mp3");
	vivid::PlaySound("data\\sound\\title_bgm.mp3",true);

	COption::m_player1_ok = false;
	COption::m_player2_ok = false;

}

//更新
void COption::Update(void)
{
	SetCharacter();//準備完了処理
	
}

//描画
void COption::Draw(void)
{

	vivid::DrawTexture("data\\debug\\option_bg.png", { 0.0f,0.0f });
	vivid::DrawText(48, "キャラクターを選択してね", { 0.0f,0.0f });
	vivid::DrawTexture("data\\debug\\cha1.png", { 100.0f,100.0f });
	vivid::DrawTexture("data\\debug\\cha2.png", { 400.0f,140.0f });
	vivid::DrawTexture("data\\debug\\cha3.png", { 700.0f,100.0f });
	vivid::DrawTexture("data\\debug\\cha4.png", { 1000.0f,100.0f });
}

//解放
void COption::Finalize(void)
{
}

//準備完了後シーン切り替え処理
void COption::SetCharacter(void)
{
	//二人ともが準備Ｏｋになったら
	if (m_player1_ok == true)
	{
		if (m_player2_ok == true)
		{
			/* シーンチェンジ処理 */
	//キーボード用
			if (vivid::keyboard::Trigger(vivid::keyboard::KEY_ID::SPACE))
			{
				vivid::PlaySound("data\\sound\\click.mp3", false);
				vivid::StopSound("data\\sound\\title_bgm.mp3");
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}
			//コントローラー用
			if (vivid::controller::Trigger(vivid::controller::DEVICE_ID::PLAYER1, vivid::controller::BUTTON_ID::B))
			{
				vivid::PlaySound("data\\sound\\click.mp3", false);
				vivid::StopSound("data\\sound\\title_bgm.mp3");
				CSceneManager::GetInstance().Change(SCENE_ID::STAGE_SELECT);
			}
		}
	}
}