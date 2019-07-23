#pragma once
#include "pch.h"


class BLOCK {
private:
	// 座標
	int x, y;

	// 初期座標
	int inix, iniy;

	// ブロック番号
	int num;

	// 縦、横幅
	int width, height;

	// ブロックが壊れてるか壊れてないかのフラグ。
	bool endflag;

	// グラフィックハンドル。
	// (全部同じ画像なので静的変数にして共有。)変更。画像を変える。

	int gh[12];

	// フェード描画用カウント
	int count;

	// 画像
	char *imageName;

	// CountRepeatNumberは繰り返し回数を表現している
	int CountRepeatNumber = 0;

	int MovableWidth = 0;

	bool FlagForStage1 = false;
	bool FlagForStage2 = false;
	bool FlagForStage3 = false;

private:
	void Draw(int);
public:
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetFlag(bool);
	bool GetFlag();
	BLOCK(char *, char *, int, int, int);
	void All(int);
	int BLOCK::Rand(int);

};
