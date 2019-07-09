#include "pch.h"
#include "bar.h"

BAR::BAR()
{
	gh = LoadGraph("bar.bmp");


	GetGraphSize(gh, &width, &height);

	//y座標は固定なのでここで設定
	y = 460;

	//最初は真ん中
	x = WIDTH / 2;


	//終了フラグは偽にしとく
	endflag = false;

}

void BAR::Draw() {

	DrawGraph(x - width / 2, y - height / 2, gh, TRUE);

}

void BAR::KeyGet()
{

	if (key[KEY_INPUT_LEFT] == 1) {
		//左に移動。
		x -= SPEED;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		//右に移動
		x += SPEED;
	}
	if (key[KEY_INPUT_ESCAPE] == 1) {
		//エスケープキーが押されていれば終了フラグをtrueにする
		endflag = true;
	}

	//画面のはみ出し処理
	if (x<width / 2)
		x = width / 2;

	if (x>WIDTH - width / 2)
		x = WIDTH - width / 2;


}

int BAR::GetX()
{
	return x;
}

int BAR::GetY()
{
	return y;
}

int BAR::GetWidth()
{
	return width;

}

int BAR::GetHeight()
{
	return height;
}



bool BAR::All()
{

	//キー処理
	KeyGet();

	//描画処理
	Draw();

	//終了フラグを返す。
	return endflag;

}


void BAR::Destroy() {


}


BAR::~BAR()
{
	Destroy();

}












