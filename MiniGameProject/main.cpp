#include "pch.h"
#include "control.h"

char key[256];
int Key[256]; // �L�[��������Ă���t���[�������i�[����

// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey() {
	char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey); // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			Key[i]++;     // ���Z
		}
		else {              // ������Ă��Ȃ����
			Key[i] = 0;   // 0�ɂ���
		}
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 70 )
#endif

	ChangeWindowMode(TRUE);


	//DX���C�u����������
	if (DxLib_Init() == -1) {
		return -1;
	}

	// GameOver�Ɋւ���t���O
	bool isGameOver = false;

	// hasBlock�̓u���b�N�������Ă��邩
	bool hasBlock = true;

	//����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	// �X�^�[�g��ʂ̕`����s���܂�
	int font1;
	font1 = CreateFontToHandle("���C���I", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	
	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
		DrawStringToHandle(100, 100, "Game Start!?", GetColor(255, 255, 255), font1);

		if (Key[KEY_INPUT_SPACE] >= 1) {
			break;
		}
	}

	
	/* 
									////////////////////���X�e�[�W//////////////////////
	*/


	//�L�[�{�[�h�̏�Ԃ��擾
	char firstStageImages[3][100] = { "kandai.png","kangaku.png","ritsumei.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control = new CONTROL(firstStageImages, 1);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		
		hasBlock = control->CheckBlock();
		if (hasBlock == false) {
			break;
		}
		
		//�Q�[���I�[�o�[��true��Ԃ�
		if (control->All()) {
			isGameOver = true;
			break;
		}
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DX���C�u�������I��������
		DxLib_End();
	}

	if (hasBlock == false) {
		// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}



	/*
											////////////////////���X�e�[�W//////////////////////
	*/


	hasBlock = true;
	char secondeStageImages[3][100] = { "keio.png", "waseda.png", "jochi.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control2 = new CONTROL(secondeStageImages, 2);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		hasBlock = control2->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//�Q�[���I�[�o�[��true��Ԃ�
		if (control2->All()) {
			isGameOver = true;
			break;
		}
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DX���C�u�������I��������
		DxLib_End();
	}


	if (hasBlock == false) {
		// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	/*
													////////////////////��O�X�e�[�W//////////////////////
	*/


	hasBlock = true;
	char thirdStageImages[3][100] = { "kyodai.png", "todai.png", "oxford.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control3 = new CONTROL(thirdStageImages, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		hasBlock = control3->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//�Q�[���I�[�o�[��true��Ԃ�
		if (control3->All()) {
			isGameOver = true;
			break;
		}
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DX���C�u�������I��������
		DxLib_End();
	}


	if (hasBlock == false) {
		// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(100, 100, "All Finish", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	//DX���C�u�����I��
	DxLib_End();

	delete control;

	return 0;
}

