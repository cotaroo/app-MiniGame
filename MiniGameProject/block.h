#pragma once
#include "pch.h"


class BLOCK {
private:
	// ���W
	int x, y;

	// �������W
	int inix, iniy;

	// �u���b�N�ԍ�
	int num;

	// �c�A����
	int width, height;

	// �u���b�N�����Ă邩���ĂȂ����̃t���O�B
	bool endflag;

	// �O���t�B�b�N�n���h���B
	// (�S�������摜�Ȃ̂ŐÓI�ϐ��ɂ��ċ��L�B)�ύX�B�摜��ς���B

	int gh[12];

	// �t�F�[�h�`��p�J�E���g
	int count;

	// �摜
	char *imageName;

	// CountRepeatNumber�͌J��Ԃ��񐔂�\�����Ă���
	int CountRepeatNumber = 0;

	int MovableWidth = 0;

	bool FlagForStage1 = false;
	bool FlagForStage2 = false;
	bool FlagForStage3 = false;

private:
	void Draw(int);
public:
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetFlag(bool);
	bool GetFlag();
	BLOCK(char *, char *, int, int, int);
	void All(int);
	int BLOCK::Rand(int);

};
