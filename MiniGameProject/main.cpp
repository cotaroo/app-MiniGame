#include "pch.h"
#include "control.h"

char key[256];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)

{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 70 );
#endif

	ChangeWindowMode(TRUE);


	//DX���C�u����������
	if (DxLib_Init() == -1) {
		return -1;
	}

	//����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	//�L�[�{�[�h�̏�Ԃ��擾


	CONTROL *control = new CONTROL;

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {


		//�Q�[���I�[�o�[��true��Ԃ�
		if (control->All()) {
			break;
		}

	}


	//DX���C�u�����I��
	DxLib_End();

	delete control;

	return 0;
}

