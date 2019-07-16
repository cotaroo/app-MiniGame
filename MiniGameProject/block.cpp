#include "pch.h"
#include "block.h"

BLOCK::BLOCK(char *filename, int x, int y, int num)
{
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

void BLOCK::Draw(int num)
{
	//ブロックが壊れてないときだけ描画
	if (!endflag) {
		DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
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
