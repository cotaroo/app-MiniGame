#include "pch.h"
#include "block.h"
#include <time.h> 


BLOCK::BLOCK(char *filename, char *image, int x, int y, int num)
{
	this->imageName = image;

	gh[num] = LoadGraph(filename);

	GetGraphSize(gh[num], &width, &height);

	endflag = false;

	this->x = x;
	this->y = y;

	count = 0;

}

int BLOCK::GetX()
{
	return x;
}
int BLOCK::GetY()
{
	return y;
}
int BLOCK::GetWidth()
{
	return width;
}
int BLOCK::GetHeight()
{
	return height;
}

void BLOCK::SetFlag(bool flag)
{
	endflag = flag;
}
bool BLOCK::GetFlag()
{
	return endflag;
}

// CountRepeatNumberは繰り返し回数を表現している
int CountRepeatNumber = 0;
int MovableWidth = 0;
bool FlagForKandai = false;
bool FlagForKangaku = false;
bool FlagForRitsumei = false;
bool FlagForKeio = false;
bool FlagForWaseda = false;
bool FlagForJochi = false;
bool FlagForTodai = false;
bool FlagForKyodai = false;
bool FlagForOxford = false;

void BLOCK::Draw(int num)
{
	CountRepeatNumber++;
	if (CountRepeatNumber % 40 == 0) {
		MovableWidth++;
	}

	//ブロックが壊れてないときだけ描画
	if (!endflag) {
		
		const char *image = imageName;

		char images[9][100] = { "kandai.png" , "kangaku.png", "ritsumei.png", "keio.png", "waseda.png", "jochi.png", "todai.png"," kyodai.png", "oxford.png" };

		// 以下で画像による動きの分類を行う
		if (*imageName == images[0][100]) {
			if (MovableWidth == 30) {
				if (FlagForKandai == false) {
					FlagForKandai = true;
				} else {
					FlagForKandai = false;
				}
				MovableWidth = 0;
			}
			if (FlagForKandai == false) {
				DrawGraph(x - width / 2 + (MovableWidth)*2, y - height / 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth)*2), y - height / 2, gh[num], FALSE);
			}
		}
		else if(*imageName == images[1][100]) {
			if (MovableWidth == 30) {
				if (FlagForKangaku == false) {
					FlagForKangaku = true;
				}
				else {
					FlagForKangaku = false;
				}
				MovableWidth = 0;
			}
			if (FlagForKangaku == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * 2, y - height / 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth) * 2), y - height / 2, gh[num], FALSE);
			}
		}
		else if (*imageName == images[2][100]) {
			if (MovableWidth == 30) {
				if (FlagForRitsumei == false) {
					FlagForRitsumei = true;
				}
				else {
					FlagForRitsumei = false;
				}
				MovableWidth = 0;
			}
			if (FlagForRitsumei == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * 2, y - height / 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth) * 2), y - height / 2, gh[num], FALSE);
			}
		}
		else if (*imageName == images[3][100]) {
			if (MovableWidth == 30) {
				if (FlagForKeio == false) {
					FlagForKeio = true;
				}
				else {
					FlagForKeio = false;
				}
				MovableWidth = 0;
			}
			if (FlagForKeio == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * 2, y - height / 2 + (MovableWidth) * 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth) * 2), y - height / 2 + (59 - (MovableWidth) * 2), gh[num], FALSE);
			}

		}
		else if (*imageName == images[4][100]) {
			if (MovableWidth == 30) {
				if (FlagForWaseda == false) {
					FlagForWaseda = true;
				}
				else {
					FlagForWaseda = false;
				}
				MovableWidth = 0;
			}
			if (FlagForWaseda == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * 2, y - height / 2 + (MovableWidth) * 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth) * 2), y - height / 2 + (59 - (MovableWidth) * 2), gh[num], FALSE);
			}

		}
		else if (*imageName == images[5][100]) {
			if (MovableWidth == 30) {
				if (FlagForJochi == false) {
					FlagForJochi = true;
				}
				else {
					FlagForJochi = false;
				}
				MovableWidth = 0;
			}
			if (FlagForJochi == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * 2, y - height / 2 + (MovableWidth) * 2, gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (59 - (MovableWidth) * 2), y - height / 2 +(59 - (MovableWidth) * 2), gh[num], FALSE);
			}

		}
		else if (*imageName == images[6][100]) {
			if (MovableWidth == 30) {
				if (FlagForTodai == false) {
					FlagForTodai = true;
				}
				else {
					FlagForTodai = false;
				}
				MovableWidth = 0;
			}
			if (FlagForTodai == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}

		}
		else if (*imageName == images[7][100]) {
			if (MovableWidth == 30) {
				if (FlagForKyodai == false) {
					FlagForKyodai = true;
				}
				else {
					FlagForKyodai = false;
				}
				MovableWidth = 0;
			}
			if (FlagForKyodai == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 +  (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}

		}
		else if (*imageName == images[8][100]) {
			if (MovableWidth == 30) {
				if (FlagForOxford == false) {
					FlagForOxford = true;
				}
				else {
					FlagForOxford = false;
				}
				MovableWidth = 0;
			}
			if (FlagForOxford == false) {
				DrawGraph(x - width / 2 + (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}
			else {
				DrawGraph(x - width / 2 + (MovableWidth) * BLOCK::Rand(), y - height / 2 + (MovableWidth) * BLOCK::Rand(), gh[num], FALSE);
			}

		}

	}
	else {
		if (count<40) {
			//透過度を指定
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 / 40)*(40 - count));
			//描画
			DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			//設定を戻す
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			++count;
		}
	}

}

void BLOCK::All(int num)
{
	Draw(num);
}

int BLOCK::Rand()
{

	// srand関数で、乱数パターンを初期化する
	// 乱数パターンの初期値は、現在時刻にしてやると、
	// プログラム実行ごとに異なるパターンが使える
	unsigned int    now = (unsigned int)time(0);
	srand(now * rand());

	// 毎回異なる乱数が取得できる
	return rand();
}