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

	inix = x;
	iniy = y;

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
	CountRepeatNumber++;
	if (CountRepeatNumber % 3 == 0) {
		MovableWidth++;
	}

	//�u���b�N�����ĂȂ��Ƃ������`��
	if (!endflag) {
		
		const char *image = imageName;

		char images[9][101] = { "kandai.png" , "kangaku.png", "ritsumei.png", "keio.png", "waseda.png", "jochi.png", "todai.png"," kyodai.png", "oxford.png" };

		// �ȉ��ŉ摜�ɂ�铮���̕��ނ��s��
		if (*imageName == images[0][101] || *imageName == images[1][101] || *imageName == images[2][101]) {
			if (MovableWidth == 30) {
				if (FlagForStage1 == false) {
					FlagForStage1 = true;
				} else {
					FlagForStage1 = false;
				}
				MovableWidth = 0;
			}
			if (FlagForStage1 == false) {

				this->x = inix + (MovableWidth) * 2;

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}
			else {

				this->x = inix + (59 - (MovableWidth) * 2);

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}
		}
		
		else if (*imageName == images[3][101] || *imageName == images[4][101] || *imageName == images[5][101]) {
			if (MovableWidth == 30) {
				if (FlagForStage2 == false) {
					FlagForStage2 = true;
				}
				else {
					FlagForStage2 = false;
				}
				MovableWidth = 0;
			}
			if (FlagForStage2 == false) {
				this->x = inix + (MovableWidth) * 2;
				this->y = iniy + (MovableWidth) * 2;

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}
			else {

				this->x = inix + (59 - (MovableWidth) * 2);
				this->y = iniy + (59 - (MovableWidth) * 2);

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}

		}

		else if (*imageName == images[6][101] || *imageName == images[7][101] || *imageName == images[8][101]) {
			if (MovableWidth == 30) {
				if (FlagForStage3 == false) {
					FlagForStage3 = true;
				}
				else {
					FlagForStage3 = false;
				}
				MovableWidth = 0;
			}
			if (FlagForStage3 == false) {
				this->x = inix + (MovableWidth) * BLOCK::Rand(x) % 3;
				this->y = iniy + (MovableWidth) * BLOCK::Rand(y) % 3;

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}
			else {

				this->x = inix + (59 - (MovableWidth) * BLOCK::Rand(x) % 3);
				this->y = iniy + (59 - (MovableWidth) * BLOCK::Rand(y) % 3);

				DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			}

		}
		

	}
	else {
		if (count<40) {
			//���ߓx���w��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 / 40)*(40 - count));
			//�`��
			DrawGraph(x - width / 2, y - height / 2, gh[num], FALSE);
			//�ݒ��߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			++count;
		}
	}

}

void BLOCK::All(int num)
{
	Draw(num);
}

int BLOCK::Rand(int num)
{
	int     val2;
	// srand�֐��ŁA�����p�^�[��������������
	// �����p�^�[���̏����l�́A���ݎ����ɂ��Ă��ƁA
	// �v���O�������s���ƂɈقȂ�p�^�[�����g����
	unsigned int    now = (unsigned int)time(0);
	srand(now * rand() * num);

	// ����قȂ闐�����擾�ł���
	val2 = rand();

	return val2;
}