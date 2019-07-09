#include "pch.h"
#include "control.h"

void CONTROL::HitCheckBallAndBar()
{

	//最初はフラグをfalseにしとく。
	boundflag = false;

	//ボールクラス内での音フラグをセット
	boundflag = ball->GetSoundflag();


	//バーの座標取得
	bdx = bar->GetX();
	bdy = bar->GetY();

	//ボールの座標取得
	blx = ball->GetX();
	bly = ball->GetY();


	//ボールとバーの高さの半分を足したものよりも
	//バーの中心とボールの中心の距離の絶対値の方が小さかったら当たり
	//その距離より大きいやつは除外
	if (abs(bdy - bly)<blheight / 2 + bdheight / 2) {
		//且つ、ボールがバー内にあれば当たり
		if (bdx + bdwidth / 2>blx &&
			bdx - bdwidth / 2<blx) {
			//バーの左端に当たっていれば、逆方向に飛ばす。
			if (blx<bdx - bdwidth / 2 * 2 / 3) {
				//ボールを反転
				ball->SetDX(-1 * ball->GetDX());
				//Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);
				//バウンド音フラグを立てる。
				boundflag = true;

				//右端
			}
			else if (blx>bdx + bdwidth / 2 * 2 / 3) {
				//ボールを反転
				ball->SetDX(-1 * ball->GetDX());
				//Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);
				//バウンド音フラグを立てる。
				boundflag = true;

				//それ以外はただ反射
			}
			else {
				//xは何もなし
				//Yは跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);
				//バウンド音フラグを立てる。
				boundflag = true;
			}
		}
	}

}

void CONTROL::HitCheckBallAndBlock()
{

	//破壊音フラグ
	demolishflag = false;

	//ボールの座標取得
	blx = ball->GetX();
	bly = ball->GetY();

	//ブロック全てをループ
	for (int i = 0; i<12; ++i) {
		//壊れてない奴だけ対象
		if (!block[i]->GetFlag()) {
			bkx = block[i]->GetX();
			bky = block[i]->GetY();

			//ブロックの上との当たり判定
			if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly + blheight / 2>bky - bkheight / 2 && bly + blheight / 2<bky + bkheight / 2) {
				//フラグをオフに
				block[i]->SetFlag(true);
				//破壊音フラグを立てる
				demolishflag = true;
				//ボールはただ跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);

				//ブロックの下との当たり判定
			}
			else if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly - blheight / 2>bky - bkheight / 2 && bly - blheight / 2<bky + bkheight / 2) {

				//フラグをオフに
				block[i]->SetFlag(true);
				//破壊音フラグを立てる
				demolishflag = true;
				//ボールはただ跳ね返すだけ
				ball->SetDY(ball->GetDY()*-1);

				//ブロックの左との当たり判定
			}
			else if (blx + blwidth / 2<bkx - bkwidth / 2 + blwidth && blx + blwidth / 2>bkx - bkwidth / 2 &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				//フラグをオフに
				block[i]->SetFlag(true);
				//破壊音フラグを立てる
				demolishflag = true;
				//ボールはただ跳ね返すだけ
				ball->SetDX(ball->GetDX()*-1);

				//ブロックの右との当たり判定
			}
			else if (blx - blwidth / 2<bkx + bkwidth / 2 && blx - blwidth / 2>bkx + bkwidth / 2 - blwidth &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				//フラグをオフに
				block[i]->SetFlag(true);
				//破壊音フラグを立てる
				demolishflag = true;
				//ボールはただ跳ね返すだけ
				ball->SetDX(ball->GetDX()*-1);

			}
		}
	}
}



void CONTROL::SoundPlay()
{
	if (boundflag) {

		PlaySoundMem(bh, DX_PLAYTYPE_BACK);
	}

	if (demolishflag) {
		PlaySoundMem(dh, DX_PLAYTYPE_BACK);
	}

}


bool CONTROL::All()
{
	bool back;

	for (int i = 0; i<12; ++i) {
		block[i]->All();
	}


	//バーの処理
	bar->All();

	//ボールの動き
	back = ball->All();

	//ボールとバーの当たり判定
	HitCheckBallAndBar();

	//ボールとブロックの当たり判定
	HitCheckBallAndBlock();

	///音再生
	SoundPlay();

	return back;
}


CONTROL::CONTROL()
{
	//バーとボールのインスタンスを生成
	bar = new BAR;
	ball = new BALL;

	boundflag = false;
	demolishflag = false;

	//バーの幅と高さ
	bdwidth = bar->GetWidth();
	bdheight = bar->GetHeight();

	//ボールの幅と高さ
	blwidth = ball->GetWidth();
	blheight = ball->GetHeight();

	//音声ファイル読み込み。
	bh = LoadSoundMem("bound.wav");
	dh = LoadSoundMem("demolish.wav");

	//ブロックの間を50ピクセルあけて、横4列、縦3行で配置
	//左端が45ピクセルの位置になる。それに画像の横幅の半分を足す
	for (int i = 0; i<12; ++i) {
		if (i<4)
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*i, 50 * 1);
		else if (i>3 && i<8)
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*(i - 4), 50 * 2);
		else
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*(i - 8), 50 * 3);
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
