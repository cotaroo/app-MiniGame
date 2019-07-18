#pragma once
#include "pch.h"
#include "bar.h"
#include "ball.h"
#include "block.h"

class CONTROL {
private:
	//バークラスのポインタ
	BAR * bar;
	//ボールクラスのポインタ
	BALL *ball;
	//ブロッククラスのポインタ
	BLOCK *block[12];

	//ボールとバーとブロックの座標
	int bdx, bdy, blx, bly, bkx, bky;


	//ボールとバーとブロックの画像の幅と高さ
	int bdwidth, bdheight, blwidth, blheight, bkwidth, bkheight;


	//バウンド音とぶつかり音のフラグ
	bool boundflag, demolishflag;

	//バウンド音とぶつかり音のサウンドハンドル
	int bh, dh;





private:
	void HitCheckBallAndBar();
	void HitCheckBallAndBlock();
	void SoundPlay();
public:
	bool All();
	bool CheckBlock();
	CONTROL(char [3][100], int);
	~CONTROL();
};


