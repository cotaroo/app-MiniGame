#pragma once
#include "pch.h"
#include "bar.h"
#include "ball.h"
#include "block.h"

class CONTROL {
private:
	// バークラスのポインタ
	BAR * bar;
	// ボールクラスのポインタ
	BALL *ball;
	// ブロッククラスのポインタ
	BLOCK *block[12];

	// ボールとバーとブロックの座標
	int bdx, bdy, blx, bly, bkx, bky;

	// ボールとバーとブロックの画像の幅と高さ
	int bdwidth, bdheight, blwidth, blheight, bkwidth, bkheight;

private:

	void HitCheckBallAndBar();
	void HitCheckBallAndBlock();

public:

	bool All(int);
	bool CheckBlock();
	CONTROL(char [3][100], int);
	~CONTROL();

};


