#include "pch.h"
#include "control.h"

void CONTROL::HitCheckBallAndBar()
{

	//�ŏ��̓t���O��false�ɂ��Ƃ��B
	boundflag = false;

	//�{�[���N���X���ł̉��t���O���Z�b�g
	boundflag = ball->GetSoundflag();


	//�o�[�̍��W�擾
	bdx = bar->GetX();
	bdy = bar->GetY();

	//�{�[���̍��W�擾
	blx = ball->GetX();
	bly = ball->GetY();


	//�{�[���ƃo�[�̍����̔����𑫂������̂���
	//�o�[�̒��S�ƃ{�[���̒��S�̋����̐�Βl�̕��������������瓖����
	//���̋������傫����͏��O
	if (abs(bdy - bly)<blheight / 2 + bdheight / 2) {
		//���A�{�[�����o�[���ɂ���Γ�����
		if (bdx + bdwidth / 2>blx &&
			bdx - bdwidth / 2<blx) {
			//�o�[�̍��[�ɓ������Ă���΁A�t�����ɔ�΂��B
			if (blx<bdx - bdwidth / 2 * 2 / 3) {
				//�{�[���𔽓]
				ball->SetDX(-1 * ball->GetDX());
				//Y�͒��˕Ԃ�����
				ball->SetDY(ball->GetDY()*-1);
				//�o�E���h���t���O�𗧂Ă�B
				boundflag = true;

				//�E�[
			}
			else if (blx>bdx + bdwidth / 2 * 2 / 3) {
				//�{�[���𔽓]
				ball->SetDX(-1 * ball->GetDX());
				//Y�͒��˕Ԃ�����
				ball->SetDY(ball->GetDY()*-1);
				//�o�E���h���t���O�𗧂Ă�B
				boundflag = true;

				//����ȊO�͂�������
			}
			else {
				//x�͉����Ȃ�
				//Y�͒��˕Ԃ�����
				ball->SetDY(ball->GetDY()*-1);
				//�o�E���h���t���O�𗧂Ă�B
				boundflag = true;
			}
		}
	}

}

void CONTROL::HitCheckBallAndBlock()
{

	//�j�󉹃t���O
	demolishflag = false;

	//�{�[���̍��W�擾
	blx = ball->GetX();
	bly = ball->GetY();

	//�u���b�N�S�Ă����[�v
	for (int i = 0; i<12; ++i) {
		//���ĂȂ��z�����Ώ�
		if (!block[i]->GetFlag()) {
			bkx = block[i]->GetX();
			bky = block[i]->GetY();

			//�u���b�N�̏�Ƃ̓����蔻��
			if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly + blheight / 2>bky - bkheight / 2 && bly + blheight / 2<bky + bkheight / 2) {
				//�t���O���I�t��
				block[i]->SetFlag(true);
				//�j�󉹃t���O�𗧂Ă�
				demolishflag = true;
				//�{�[���͂������˕Ԃ�����
				ball->SetDY(ball->GetDY()*-1);

				//�u���b�N�̉��Ƃ̓����蔻��
			}
			else if (blx<bkx + bkwidth / 2 && blx>bkx - bkwidth / 2 &&
				bly - blheight / 2>bky - bkheight / 2 && bly - blheight / 2<bky + bkheight / 2) {

				//�t���O���I�t��
				block[i]->SetFlag(true);
				//�j�󉹃t���O�𗧂Ă�
				demolishflag = true;
				//�{�[���͂������˕Ԃ�����
				ball->SetDY(ball->GetDY()*-1);

				//�u���b�N�̍��Ƃ̓����蔻��
			}
			else if (blx + blwidth / 2<bkx - bkwidth / 2 + blwidth && blx + blwidth / 2>bkx - bkwidth / 2 &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				//�t���O���I�t��
				block[i]->SetFlag(true);
				//�j�󉹃t���O�𗧂Ă�
				demolishflag = true;
				//�{�[���͂������˕Ԃ�����
				ball->SetDX(ball->GetDX()*-1);

				//�u���b�N�̉E�Ƃ̓����蔻��
			}
			else if (blx - blwidth / 2<bkx + bkwidth / 2 && blx - blwidth / 2>bkx + bkwidth / 2 - blwidth &&
				bly>bky - bkheight / 2 && bly<bky + bkheight / 2) {

				//�t���O���I�t��
				block[i]->SetFlag(true);
				//�j�󉹃t���O�𗧂Ă�
				demolishflag = true;
				//�{�[���͂������˕Ԃ�����
				ball->SetDX(ball->GetDX()*-1);

			}
		}
	}
}



void CONTROL::SoundPlay()
{
	if (boundflag) {

		PlaySoundMem(bh, DX_PLAYTYPE_BACK);
	}

	if (demolishflag) {
		PlaySoundMem(dh, DX_PLAYTYPE_BACK);
	}

}


bool CONTROL::All()
{
	bool back;

	for (int i = 0; i<12; ++i) {
		block[i]->All();
	}


	//�o�[�̏���
	bar->All();

	//�{�[���̓���
	back = ball->All();

	//�{�[���ƃo�[�̓����蔻��
	HitCheckBallAndBar();

	//�{�[���ƃu���b�N�̓����蔻��
	HitCheckBallAndBlock();

	///���Đ�
	SoundPlay();

	return back;
}


CONTROL::CONTROL()
{
	//�o�[�ƃ{�[���̃C���X�^���X�𐶐�
	bar = new BAR;
	ball = new BALL;

	boundflag = false;
	demolishflag = false;

	//�o�[�̕��ƍ���
	bdwidth = bar->GetWidth();
	bdheight = bar->GetHeight();

	//�{�[���̕��ƍ���
	blwidth = ball->GetWidth();
	blheight = ball->GetHeight();

	//�����t�@�C���ǂݍ��݁B
	bh = LoadSoundMem("bound.wav");
	dh = LoadSoundMem("demolish.wav");

	//�u���b�N�̊Ԃ�50�s�N�Z�������āA��4��A�c3�s�Ŕz�u
	//���[��45�s�N�Z���̈ʒu�ɂȂ�B����ɉ摜�̉����̔����𑫂�
	for (int i = 0; i<12; ++i) {
		if (i<4)
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*i, 50 * 1);
		else if (i>3 && i<8)
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*(i - 4), 50 * 2);
		else
			block[i] = new BLOCK("block.bmp", 95 + (50 + 100)*(i - 8), 50 * 3);
	}

	bkwidth = block[0]->GetWidth();
	bkheight = block[0]->GetHeight();
}

CONTROL::~CONTROL()
{

	delete bar;
	delete ball;

	for (int i = 0; i<12; ++i) {
		delete block[i];
	}
}
