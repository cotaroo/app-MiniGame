#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "control.h"
#include <time.h>   // time関数

void CONTROL::HitCheckBallAndBar()
{

	// バーの座標取得する
	bdx = bar->GetX();
	bdy = bar->GetY();

	// ボールの座標取得する
	blx = ball->GetX();
	bly = ball->GetY();


	// ボールとバーの高さの半分を足したものよりも
	// バーの中心とボールの中心の距離の絶対値の方が小さかったら当たり
	// その距離より大きいやつは除外
	if (abs(bdy - bly)<blheight / 2 + bdheight / 2) {

		// 且つ、ボールがバー内にあれば当たり
		if (bdx + bdwidth / 2>blx &&
			bdx - bdwidth / 2<blx) {

			// バーの左端に当たっていれば、逆方向に飛ばす
			if (blx<bdx - bdwidth / 2 * 2 / 3) {

				// ボールを反転
				ball->SetDX(-1 * ball->GetDX());

				// Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);
		
			}

			else if (blx>bdx + bdwidth / 2 * 2 / 3) {

				// ボールを反転
				ball->SetDX(-1 * ball->GetDX());

				// Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);
	
			}

			else {

				// xは何もなし
				// Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);

			}

		}

	}

}

bool CONTROL::CheckBlock() 
{
	// 
	for (int i = 0; i < 12; i++) {
		if (!block[i]->GetFlag()) {
			return true;
		}
	}
	return false;
}

void CONTROL::HitCheckBallAndBlock()
{

	// ボールの座標取得
	blx = ball->GetX();
	bly = ball->GetY();

	// ブロック全てをループ
	for (int i = 0; i<12; ++i) {

		// 壊れてない奴だけ対象
		if (!block[i]->GetFlag()) {
			bkx = block[i]->GetX();
			bky = block[i]->GetY();

			// ブロックの上との当たり判定
			if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly + blheight / 2>bky - bkheight / 2 && bly + blheight / 2<bky + bkheight / 2) {

				// フラグをオフに
				block[i]->SetFlag(true);

				// ボールはただ跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);

			}

			else if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly - blheight / 2>bky - bkheight / 2 && bly - blheight / 2<bky + bkheight / 2) {

				// フラグをオフに
				block[i]->SetFlag(true);
				
				// ボールはただ跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);

			}
			else if (blx + blwidth / 2<bkx - bkwidth / 2 + blwidth && blx + blwidth / 2>bkx - bkwidth / 2 &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				// フラグをオフに
				block[i]->SetFlag(true);
				
				// ボールはただ跳ね返すだけ
				ball->SetDX(ball->GetDX()*-1);

			}
			else if (blx - blwidth / 2<bkx + bkwidth / 2 && blx - blwidth / 2>bkx + bkwidth / 2 - blwidth &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				// フラグをオフに
				block[i]->SetFlag(true);
				
				// ボールはただ跳ね返すだけ
				ball->SetDX(ball->GetDX()*-1);

			}

		}

	}

}

bool CONTROL::All(int life)
{

	bool back;

	for (int i = 0; i<12; ++i) {

		block[i]->All(i);

	}

	// バーの処理
	bar->All();

	// ボールの動き
	back = ball->All(life);

	// ボールとバーの当たり判定
	HitCheckBallAndBar();

	// ボールとブロックの当たり判定
	HitCheckBallAndBlock();


	return back;
}

CONTROL::CONTROL(char images[3][100], int stageNumber)
{

	// バーとボールのインスタンスを生成
	bar = new BAR;
	ball = new BALL(stageNumber);

	// バーの幅と高さ
	bdwidth = bar->GetWidth();
	bdheight = bar->GetHeight();

	// ボールの幅と高さ
	blwidth = ball->GetWidth();
	blheight = ball->GetHeight();

	// ブロックの間ルを50ピクセルあけて、横4列、縦3行で配置
	// 左端が45ピクセの位置になる。それに画像の横幅の半分を足す
	for (int i = 0; i<12; ++i) {

		char imageFolder[100] = "image/";

		// 乱数の種を設定（srand関数）
		int     val2;

		// srand関数で、乱数パターンを初期化する
		// 乱数パターンの初期値は、現在時刻にしてやると、
		// プログラム実行ごとに異なるパターンが使える
		unsigned int    now = (unsigned int)time(0);
		srand(now * i * rand());

		// 毎回異なる乱数が取得できる
		val2 = rand();

		char* image = images[val2 % 3];

		if (i < 4) {

			block[i] = new BLOCK(strcat(imageFolder, image), image, 95 + (50 + 100)*i, 50 * 1, i);

		}

		else if (i > 3 && i < 8) {

			block[i] = new BLOCK(strcat(imageFolder, image), image, 95 + (50 + 100)*(i - 4), 50 * 2, i);

		}

		else {

			block[i] = new BLOCK(strcat(imageFolder, image), image, 95 + (50 + 100)*(i - 8), 50 * 3, i);

		}

	}

	bkwidth = block[0]->GetWidth();
	bkheight = block[0]->GetHeight();
}

CONTROL::~CONTROL()
{

	delete bar;
	delete ball;

	for (int i = 0; i<12; ++i) {

		delete block[i];

	}

}
