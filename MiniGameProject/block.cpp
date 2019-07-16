#include "pch.h"
#include "block.h"

int BLOCK::gh = -1;

BLOCK::BLOCK(char *filename, int x, int y)
{
	//�ŏ������ǂݍ��܂Ȃ��B
	if (gh == -1)
		// ���u�Ђɉ摜��ύX����
		gh = LoadGraph("block.bmp");

	GetGraphSize(gh, &width, &height);

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

void BLOCK::Draw()
{
	//�u���b�N�����ĂȂ��Ƃ������`��
	if (!endflag) {
		DrawGraph(x - width / 2, y - height / 2, gh, FALSE);
	}
	else {
		if (count<40) {
			//���ߓx���w��
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, (255 / 40)*(40 - count));
			//�`��
			DrawGraph(x - width / 2, y - height / 2, gh, FALSE);
			//�ݒ��߂�
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			++count;
		}
	}

}

void BLOCK::All()
{
	Draw();
}
