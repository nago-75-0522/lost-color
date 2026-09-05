#pragma once

enum class SCENE_ID
{
	DUMMY,				//ダミー
	TITLE,				//タイトル
	OPTION,				//コントローラ接続 設定 キャラクター紹介

	STAGE_SELECT,		//ステージ選択
	STAGE_EXPLANATION,	//ステージ説明
	ITEM_EXPLANATION,	//アイテム説明
	COLOR_SELECT,		//消す色を選択

	STAGE_MANAGER,		//実際にプレイするステージ
	GAMERISULT,			//ゲームリザルト
	RESULT,				//リザルト
};