#include "DxLib.h"
#include <math.h>
#include <float.h>
#include <time.h>
const double M_PI = 3.1415926535897932384626433832795;
const double D_FORWARD = M_PI / 2.0;
const double D_FORWARD0 = 0.0;
//オブジェクトの構造体
typedef struct {
	double x;
	double y;
}Vector2;

typedef struct {
	int s;
	int e;
}Line2;

typedef struct Object {
	int pointLength;
	int lineLength;
	Vector2 pointL[100];
	Vector2 pointW[100];
	Line2 line[100];
	double positionX;
	double positionY;
	double rotationZ;
	double speed;	//速度（スカラー）
	double angularSpeed;	//角速度（スカラー）
	unsigned int color;		//カラー
	double direction;		//前方方向
}Object;

void placeLocalToWorld(Object* object) {
	//オブジェクトのローカル座標からワールド座標変換　（配置）
	for (int iii = 0; iii < object->pointLength; iii++) {		//ポイント数
		double px = object->pointL[iii].x;
		double py = object->pointL[iii].y;
		//回転処理
		double xy = sqrt(pow(px, 2.0) + pow(py, 2.0));
		double k0 = atan2(py, px);
		double k1 = (2.0f * M_PI) / 360.0 * object->rotationZ;
		k0 = k0 + k1;
		px = xy * cos(k0);
		py = xy * sin(k0);
		//移動処理
		px = px + object->positionX;
		py = py + object->positionY;

		//変換後頂点ワーク格納
		object->pointW[iii].x = px;
		object->pointW[iii].y = py;
	}

}

void placeWorldToScreen(Object* object) {
	int k = 1000;		//分割数
	double j = 1 / (double)k;	//分割係数

	int nline = object->lineLength;

	for (int iii = 0; iii < nline; iii++) {		//ライン数
		for (int i = 0; i < k + 1; i++) {		//分割数
			int xp = (int)(object->pointW[object->line[iii].s].x
				+ (object->pointW[object->line[iii].e].x
					- object->pointW[object->line[iii].s].x) * (j * i));
			int yp = (int)(object->pointW[object->line[iii].s].y
				+ (object->pointW[object->line[iii].e].y
					- object->pointW[object->line[iii].s].y) * (j * i));

			//座標変換
			xp = 320 + xp;
			yp = 240 - yp;
			//点描画
			DrawPixel(xp, yp, object->color);
		}
	}

}

//正多角形生成
void createPolygon(Object* object, int corners, double r) {
	for (int i = 0; i < corners; i++) {
		object->pointL[i + 1].x = r * cos(((M_PI * 2.0) / corners) * i);
		object->pointL[i + 1].y = r * sin(((M_PI * 2.0) / corners) * i);
	}

	for (int i = 0; i < corners; i++) {
		object->line[i].s = i + 1;
		object->line[i].e = i + 2;
	}
	object->line[corners - 1].e = 1;

	object->pointLength = corners + 1;
	object->lineLength = corners;
}

//浮動小数点多角形生成（外角明記）
void createPolygonf(Object* object, double polygon, double r) {

	double externalAngle = ((2.0 * M_PI) / polygon);	//外角
	int npoint = sizeof object->pointL / sizeof object->pointL[0];	//全点数

	int pointSuu;
	for (int i = 1; i < npoint; i++) {
		object->pointL[i].x = r * cos(externalAngle * i);
		object->pointL[i].y = r * sin(externalAngle * i);

		//終了条件判定（誤差を切り捨て）
		int pointX0 = (int)(r);
		int pointY0 = (int)0.0;
		int pointXi = (int)object->pointL[i].x;
		int pointYi = (int)object->pointL[i].y;

		if ((pointX0 == pointXi) && (pointY0 == pointYi))
		{
			pointSuu = i;
			break;
		}
		pointSuu = i;
	}
	for (int i = 0; i < pointSuu; i++) {
		object->line[i].s = i + 1;
		object->line[i].e = i + 2;
	}
	object->line[pointSuu - 1].e = 1;

	object->pointLength = pointSuu + 1;
	object->lineLength = pointSuu;
}

//円同士の衝突判定
bool collisionCheckOfCircle(Object* object1, Object* object2) {
	double r1 = fabs(object1->pointL[1].x);
	double r2 = fabs(object2->pointL[1].x);
	double m1 = r1 + r2;

	double m2 =
		sqrt(pow((object1->positionX - object2->positionX), 2.0) +
			(pow((object1->positionY - object2->positionY), 2.0)));

	DrawFormatString(100, 100, GetColor(255, 32, 32),
		"r1 = %f  r2 = %f m1 = %f  m2 = %f\n", r1, r2, m1, m2);

	if (m1 >= m2)
		return true;
	else
		return false;
}

//矩形（回転なし）同士の衝突判定
bool collisionCheckOfRectangle(Object* object1, Object* object2) {

	double x1Max = fmax(object1->pointW[1].x, object1->pointW[2].x);
	x1Max = fmax(x1Max, object1->pointW[3].x);
	double x1Min = fmin(object1->pointW[1].x, object1->pointW[2].x);
	x1Min = fmin(x1Min, object1->pointW[3].x);

	double y1Max = fmax(object1->pointW[1].y, object1->pointW[2].y);
	y1Max = fmax(y1Max, object1->pointW[3].y);
	double y1Min = fmin(object1->pointW[1].y, object1->pointW[2].y);
	y1Min = fmin(y1Min, object1->pointW[3].y);

	double x2Max = fmax(object2->pointW[1].x, object2->pointW[2].x);
	x2Max = fmax(x2Max, object2->pointW[3].x);
	double x2Min = fmin(object2->pointW[1].x, object2->pointW[2].x);
	x2Min = fmin(x2Min, object2->pointW[3].x);

	double y2Max = fmax(object2->pointW[1].y, object2->pointW[2].y);
	y2Max = fmax(y2Max, object2->pointW[3].y);
	double y2Min = fmin(object2->pointW[1].y, object2->pointW[2].y);
	y2Min = fmin(y2Min, object2->pointW[3].y);

	if ((x1Max >= x2Min) && (x1Min <= x2Max) && (y1Max >= y2Min) && (y1Min <= y2Max))
		return true;
	else
		return false;

}

//円と矩形（回転なし）との衝突判定
bool collisionCheckOfCircleAndRectangle(Object* object1, Object* object2) {
	//衝突判定（円と矩形のチェック方式）回転なし
	bool hit = false;

	//円の	半径計算	
	double rA = fabs(object1->pointL[1].x);

	// object2の境界ボックスの座標を計算
	double x2Max = fmax(object2->pointW[1].x, object2->pointW[2].x);
	x2Max = fmax(x2Max, object2->pointW[3].x);
	double x2Min = fmin(object2->pointW[1].x, object2->pointW[2].x);
	x2Min = fmin(x2Min, object2->pointW[3].x);

	double y2Max = fmax(object2->pointW[1].y, object2->pointW[2].y);
	y2Max = fmax(y2Max, object2->pointW[3].y);
	double y2Min = fmin(object2->pointW[1].y, object2->pointW[2].y);
	y2Min = fmin(y2Min, object2->pointW[3].y);

	//円の中心点座標（ｘ、ｙ）と矩形の（ｘ、ｙ）の最短距離座標を算出
	double shortestX = object1->positionX;
	double shortestY = object1->positionY;
	if (object1->positionX < x2Min)
		shortestX = x2Min;
	else
		if (object1->positionX > x2Max)
			shortestX = x2Max;
	if (object1->positionY < y2Min)
		shortestY = y2Min;
	else
		if (object1->positionY > y2Max)
			shortestY = y2Max;

	//円と矩形の最短距離算出
	double difference = sqrt(
		pow((shortestX - object1->positionX), 2.0)
		+ pow((shortestY - object1->positionY), 2.0));

	//比較
	if (rA >= difference)
		hit = true;

	//最短線表示
	DrawLine(320 + object1->positionX, 240 - object1->positionY,
		320 + shortestX, 240 - shortestY, GetColor(255, 255, 55));


	return hit;
}

//円と矩形（回転あり）との衝突判定
bool collisionCheckOfCircleAndRectangle2(Object* object1, Object* object2) {
	//衝突判定（円と矩形のチェック方式）回転あり
	bool hit = false;

	//円の	半径計算	
	double rA = fabs(object1->pointL[1].x);

	//４座標を回転させる
	Vector2 point[4 + 1];

	//元々円の中心とのなす角を何度戻したいか＝矩形の回転角
	//戻す度数は、全ての頂点に対して、矩形の回転角
	//従って、現在各頂点が円の中心となす角から、矩形の回転角を減算すればよい
	//これにより、円を中心として矩形が回転することになる。
	//座標計算では円と矩形の各頂点の相対距離により計算されるので、
	//実際のワールド座標は、その座標に中心点となる円の位置を加算したものになる
	//従って、ワールド座標の原点を中心としての回転と考えれば、
	//そのまま原点が円の中心まで平行移動した形になるので加算が必要となる
	for (int i = 1; i < 4 + 1; i++) {
		//回転処理
		double px = object2->pointW[i].x - object1->positionX;
		double py = object2->pointW[i].y - object1->positionY;
		double xy = sqrt(pow(px, 2.0) + pow(py, 2.0));
		double k0 = atan2(py, px);
		double k1 = (2.0f * M_PI) / 360.0 * object2->rotationZ;
		k0 = k0 - k1;
		px = xy * cos(k0);
		py = xy * sin(k0);
		//円を中心とした回転の為、円の座標が加算されている
		point[i].x = px + object1->positionX;
		point[i].y = py + object1->positionY;
	}

	// object2の境界ボックスの座標を計算
	double x2Max = fmax(point[1].x, point[2].x);
	x2Max = fmax(x2Max, point[3].x);
	double x2Min = fmin(point[1].x, point[2].x);
	x2Min = fmin(x2Min, point[3].x);

	double y2Max = fmax(point[1].y, point[2].y);
	y2Max = fmax(y2Max, point[3].y);
	double y2Min = fmin(point[1].y, point[2].y);
	y2Min = fmin(y2Min, point[3].y);

	//円の中心点座標（ｘ、ｙ）と矩形の（ｘ、ｙ）の最短距離座標を算出
	double shortestX = object1->positionX;
	double shortestY = object1->positionY;
	if (object1->positionX < x2Min)
		shortestX = x2Min;
	else
		if (object1->positionX > x2Max)
			shortestX = x2Max;
	if (object1->positionY < y2Min)
		shortestY = y2Min;
	else
		if (object1->positionY > y2Max)
			shortestY = y2Max;

	//円と矩形の最短距離算出
	double difference = sqrt(
		pow((shortestX - object1->positionX), 2.0)
		+ pow((shortestY - object1->positionY), 2.0));

	//比較
	if (rA >= difference)
		hit = true;

#if FUNC0130 == 1
	//最短線表示
	DrawLine(320 + object1->positionX, 240 - object1->positionY,
		320 + shortestX, 240 - shortestY, GetColor(255, 255, 55));

	DrawBox(320 + point[1].x, 240 - point[1].y,
		320 + point[3].x, 240 - point[3].y,
		GetColor(255, 255, 32), FALSE);
#endif

	return hit;
}


// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	ChangeWindowMode(TRUE);

	if (DxLib_Init() == -1)// ＤＸライブラリ初期化処理
	{
		return -1;// エラーが起きたら直ちに終了
	}

	SetDrawScreen(DX_SCREEN_BACK);	//書込みバッファ指定
	//時間関連
	clock_t time_Start = clock();
	clock_t time_End = time_Start;
	double timeDelta;
	double timeCount = 0.0;
	bool timeSw = false;
	double timeMinute = 0.0;

	Object object1 = {
		//構造体変数の初期化
		4,				//頂点数
		3,				//稜線数
		{				//頂点座標（ローカル座標）
			{ 0,0 },	//要素０は原点として活用
			{ 0,50 },	//
			{ -50,-50 },
			{ 50,-50 }
		},
		{				//頂点座標（ワールド座標）
		},
		{				//稜線データ
			{1,2},
			{2,3},
			{3,1}
		},
		0.0,			//位置X
		0.0,			//位置Y
		0.0,			//角度
		100.0,			//速度（スカラー）
		90.0,			//角速度（スカラー）
		GetColor(155,155,255),		//色
		D_FORWARD0	//方向
	};

	createPolygon(&object1, 32, 50.0);

	Object object2 = {
		//構造体変数の初期化
		//構造体変数の初期化
		5,				//頂点数
		4,				//稜線数
		{				//頂点座標（ローカル座標）
			{ 0,0 },	//p1～の表記の為　要素０に空を入れている
			{ -50,-50 },	//
			{ -50,50 },
			{ 50,50 },
			{ 50,-50 }
		},
		{				//頂点座標（ワールド座標）
			{ 0,0 },	//p1～の表記の為　要素０に空を入れている
			{ -50,-50 },	//
			{ -50,50 },
			{ 50,50 },
			{ 50,-50 }
		},
		{				//稜線データ
			{1,2},
			{2,3},
			{3,4},
			{4,1}
		},
		-100.0,			//位置X
		0.0,			//位置Y
		0.0,			//角度
		2.0,			//速度（スカラー）
		2.0,			//角速度（スカラー）
		GetColor(55,55,255),		//色
		D_FORWARD	//方向
	};


	//---- ゲームループ
	while (true) {
		ClearDrawScreen();				//書込みバッファクリア

		//TimeDeltaTime 算出--------
		time_Start = clock();
		timeDelta = double(time_Start - time_End) / CLOCKS_PER_SEC;
		time_End = time_Start;
		timeMinute += timeDelta;
		DrawFormatString(40, 20, GetColor(255, 232, 232), "Tomoshige Hashishita\n");

		DrawFormatString(40, 40, GetColor(255, 232, 232), "timeCount = %5f\ttimeDelta =% 5f  \tCLOCKS_PER_SEC = %ld\n", timeCount, timeDelta, CLOCKS_PER_SEC);
		DrawFormatString(40, 60, GetColor(255, 232, 232), "Minute = %.2f\n", timeMinute);

		DrawFormatString(40, 320, GetColor(55, 232, 32), "nline =  %d  npoint = %d\n", object1.lineLength, object1.pointLength);
		DrawFormatString(40, 340, GetColor(55, 232, 32), "positionX =  %f  positionY = %f\n", object1.positionX, object1.positionY);
		DrawFormatString(40, 360, GetColor(55, 232, 32), "angle = %f\n", object1.rotationZ);

		//各操作
		if (CheckHitKey(KEY_INPUT_UP)) {
			object1.positionY =
				object1.positionY + object1.speed * timeDelta;
		};
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			object1.positionY =
				object1.positionY - object1.speed * timeDelta;
		};
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			object1.positionX =
				object1.positionX + object1.speed * timeDelta;
		};
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			object1.positionX =
				object1.positionX - object1.speed * timeDelta;
		};

		//object2
		if (CheckHitKey(KEY_INPUT_W)) {
			object2.positionY =
				object2.positionY + object2.speed;
		};
		if (CheckHitKey(KEY_INPUT_S)) {
			object2.positionY =
				object2.positionY - object2.speed;
		};
		if (CheckHitKey(KEY_INPUT_D)) {
			object2.rotationZ =
				object2.rotationZ + object2.angularSpeed;
		};
		if (CheckHitKey(KEY_INPUT_A)) {
			object2.rotationZ =
				object2.rotationZ - object2.angularSpeed;
		};



		//ローカル座標からワールド座標へ変換（配置）
		placeLocalToWorld(&object1);
		placeLocalToWorld(&object2);

		//当たり判定
		if (collisionCheckOfCircleAndRectangle2(&object1, &object2)) {
			DrawFormatString(400, 200, GetColor(255, 32, 32), "**** HIT !! ****\n");
			object1.color = GetColor(155, 255, 155);
			object2.color = GetColor(155, 255, 155);
		}
		else {
			object1.color = GetColor(155, 155, 255);
			object2.color = GetColor(255, 155, 155);
		}


		//ワールド座標からスクリーン座標へ変換（表示）
		placeWorldToScreen(&object1);
		placeWorldToScreen(&object2);


		ScreenFlip();//表裏画面切替（書込みバッファを表示バッファへ切替）

		if (CheckHitKey(KEY_INPUT_R))
			break;
	}


	WaitKey();// キー入力待ち

	DxLib_End();// ＤＸライブラリ使用の終了処理


	return 0;// ソフトの終了 
}