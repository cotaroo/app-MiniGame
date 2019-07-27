#pragma once
#include "pch.h"

class BALL {

private:
	// x���W�Ay���W
	int x, y;

	// x��y�̈ړ���
	int dx, dy;

	// �摜�̉��A�c��
	int width, height;

	// �Q�[���[�I�[�o�[�t���O
	bool endflag;

	// �O���t�B�b�N�n���h��
	int gh;

private:

	void Draw();
	void Destroy();
	void Move(int);

public:

	BALL(int);
	~BALL();
	bool All(int);
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
	void SetDX(int);
	void SetDY(int);
	int GetDX();
	int GetDY();

};
