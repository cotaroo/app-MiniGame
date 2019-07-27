#pragma once
#include "pch.h"

class BALL {

private:
	// x座標、y座標
	int x, y;

	// xとyの移動量
	int dx, dy;

	// 画像の横、縦幅
	int width, height;

	// ゲームーオーバーフラグ
	bool endflag;

	// グラフィックハンドル
	int gh;

private:

	void Draw();
	void Destroy();
	void Move(int);

public:

	BALL(int);
	~BALL();
	bool All(int);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetDX(int);
	void SetDY(int);
	int GetDX();
	int GetDY();

};
