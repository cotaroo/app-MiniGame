#pragma once
#include "pch.h"


#define SPEED 4

class BAR {
private:
	// x座標、y座標
	int x, y;

	// 画像の横、縦幅
	int width, height;

	// 終了フラグ。終了ならtrue
	bool endflag;

	//グラフィックハンドル
	int gh;


private:
	void Draw();
	void KeyGet();
	void Destroy();

public:
	BAR();
	~BAR();
	bool All();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
};
