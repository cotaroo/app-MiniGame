#pragma once
#include "pch.h"


class BLOCK {
private:
	//���W
	int x, y;

	//�c�A����
	int width, height;

	//�u���b�N�����Ă邩���ĂȂ����̃t���O�B
	bool endflag;

	//�O���t�B�b�N�n���h���B
	//�S�������摜�Ȃ̂ŐÓI�ϐ��ɂ��ċ��L�B
	static	int gh;


	//�t�F�[�h�`��p�J�E���g
	int count;

private:
	void Draw();
public:
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetFlag(bool);
	bool GetFlag();
	BLOCK(char *, int, int);
	void All();

};
