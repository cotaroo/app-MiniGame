#include "pch.h"
#include "ball.h"

BALL::BALL(int stageNumber)
{

	gh = LoadGraph("ball.bmp");


	GetGraphSize(gh, &width, &height);

	// y���W�͌Œ�Ȃ̂ł����Őݒ�
	y = 410 - height / 2;

	// �ŏ��͐^��
	x = WIDTH / 2;

	switch(stageNumber) {

	case 1:
		// �ŏ��̌W��
		dx = 3;
		dy = -3;
		break;

	case 2:
		dx = 4;
		dy = -4;
		break;

	case 3:
		dx = 4;
		dy = -4;
		break;
	}

	endflag = false;

	soundflag = false;

}

void BALL::Draw() {

	DrawGraph(x - width / 2, y - height / 2, gh, TRUE);

}

void BALL::Move(int life) {
	// endflag �������I��false�ɂ��Ă���
	endflag = false;

	// �܂�����OFF�ɂ��Ƃ�
	soundflag = false;

	// �ړ��ʂ����Z
	x += (dx);
	y += (dy);


	// ��ʂ͂ݏo������
	if (x<width / 2) {
		x = width / 2;
		dx *= -1;
		// ���������̂ŃT�E���h�t���O�𗧂Ă�
		soundflag = true;
	}
	if (x>WIDTH - width / 2) {
		x = WIDTH - width / 2;
		dx *= -1;
		// ���������̂ŃT�E���h�t���O�𗧂Ă�
		soundflag = true;
	}

	if (y<height / 2) {
		y = height / 2;
		dy *= -1;
		// ���������̂ŃT�E���h�t���O�𗧂Ă�
		soundflag = true;
	}

	// ���ɂ͂ݏo����Q�[���I�[�o�[
	if (y>HEIGHT) {
		if (life == 0) {
		}
		else {
			y = HEIGHT - height / 2;
			dy *= -1;
			soundflag = true;
		}
		endflag = true;

	}

}

int BALL::GetX()
{
	return x;
}

int BALL::GetY()
{
	return y;
}

void BALL::SetDX(int x)
{
	dx = x;
}

void BALL::SetDY(int y)
{
	dy = y;
}

int BALL::GetDX()
{
	return dx;
}


int BALL::GetDY()
{
	return dy;
}


int BALL::GetWidth()
{
	return width;
}

int BALL::GetHeight()
{
	return height;
}

bool BALL::GetSoundflag()
{
	return soundflag;
}




bool BALL::All(int life)
{

	Move(life);

	// �`�揈��
	Draw();

	return endflag;

}


void BALL::Destroy() {


}


BALL::~BALL()
{
	Destroy();

}
