#include "pch.h"
#include "bar.h"

BAR::BAR()
{
	gh = LoadGraph("bar.bmp");


	GetGraphSize(gh, &width, &height);

	//y���W�͌Œ�Ȃ̂ł����Őݒ�
	y = 460;

	//�ŏ��͐^��
	x = WIDTH / 2;


	//�I���t���O�͋U�ɂ��Ƃ�
	endflag = false;

}

void BAR::Draw() {

	DrawGraph(x - width / 2, y - height / 2, gh, TRUE);

}

void BAR::KeyGet()
{

	if (key[KEY_INPUT_LEFT] == 1) {
		//���Ɉړ��B
		x -= SPEED;
	}
	if (key[KEY_INPUT_RIGHT] == 1) {
		//�E�Ɉړ�
		x += SPEED;
	}
	if (key[KEY_INPUT_ESCAPE] == 1) {
		//�G�X�P�[�v�L�[��������Ă���ΏI���t���O��true�ɂ���
		endflag = true;
	}

	//��ʂ̂͂ݏo������
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

	//�L�[����
	KeyGet();

	//�`�揈��
	Draw();

	//�I���t���O��Ԃ��B
	return endflag;

}


void BAR::Destroy() {


}


BAR::~BAR()
{
	Destroy();

}












