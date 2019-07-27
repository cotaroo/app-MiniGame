#pragma once
#include "pch.h"
#include "bar.h"
#include "ball.h"
#include "block.h"

class CONTROL {
private:
	// �o�[�N���X�̃|�C���^
	BAR * bar;
	// �{�[���N���X�̃|�C���^
	BALL *ball;
	// �u���b�N�N���X�̃|�C���^
	BLOCK *block[12];

	// �{�[���ƃo�[�ƃu���b�N�̍��W
	int bdx, bdy, blx, bly, bkx, bky;

	// �{�[���ƃo�[�ƃu���b�N�̉摜�̕��ƍ���
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


