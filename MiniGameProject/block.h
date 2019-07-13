#pragma once
#include "pch.h"


class BLOCK {
private:
	//座標
	int x, y;

	//ブロック番号
	int num;

	//縦、横幅
	int width, height;

	//ブロックが壊れてるか壊れてないかのフラグ。
	bool endflag;

	//グラフィックハンドル。
	//(全部同じ画像なので静的変数にして共有。)変更。画像を変える。

	int gh[12];

	//フェード描画用カウント
	int count;

private:
	void Draw(int);
public:
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetFlag(bool);
	bool GetFlag();
	BLOCK(char *, int, int, int);
	void All(int);

};
