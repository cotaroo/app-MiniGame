#pragma once
#include "pch.h"


#define SPEED 4

class BAR {
private:
	// x���W�Ay���W
	int x, y;

	// �摜�̉��A�c��
	int width, height;

	// �I���t���O�B�I���Ȃ�true
	bool endflag;

	//�O���t�B�b�N�n���h��
	int gh;


private:
	void Draw();
	void KeyGet();
	void Destroy();

public:
	BAR();
	~BAR();
	bool All();
	int GetX();
	int GetY();
	int GetWidth();
	int GetHeight();
};
