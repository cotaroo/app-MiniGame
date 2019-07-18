#pragma once
#include "pch.h"
#include "bar.h"
#include "ball.h"
#include "block.h"

class CONTROL {
private:
	//�o�[�N���X�̃|�C���^
	BAR * bar;
	//�{�[���N���X�̃|�C���^
	BALL *ball;
	//�u���b�N�N���X�̃|�C���^
	BLOCK *block[12];

	//�{�[���ƃo�[�ƃu���b�N�̍��W
	int bdx, bdy, blx, bly, bkx, bky;


	//�{�[���ƃo�[�ƃu���b�N�̉摜�̕��ƍ���
	int bdwidth, bdheight, blwidth, blheight, bkwidth, bkheight;


	//�o�E���h���ƂԂ��艹�̃t���O
	bool boundflag, demolishflag;

	//�o�E���h���ƂԂ��艹�̃T�E���h�n���h��
	int bh, dh;





private:
	void HitCheckBallAndBar();
	void HitCheckBallAndBlock();
	void SoundPlay();
public:
	bool All();
	bool CheckBlock();
	CONTROL(char [3][100], int);
	~CONTROL();
};


