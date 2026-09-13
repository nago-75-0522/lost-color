#pragma once
//エフェクトID
enum class EFFECT_ID
{
	CATCH, //ボールキャッチ
	DROP,  //ボールを落とす
	HIT,   //被弾(爆発)
	DIR_SELECT, //車が上下選び完了
};