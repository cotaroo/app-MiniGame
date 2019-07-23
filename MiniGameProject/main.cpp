#include "pch.h"
#include "control.h"
#include <Windows.h>
#include <fstream>

char key[256];
int Key[256]; // �L�[��������Ă���t���[�������i�[����
int PlayGameCounter = 0; // �Q�[�����v���C�����񐔂��i�[����
int WinCounter = 0; // ���������񐔂��i�[����
double winRate; // �������i�[����

// ���݂̃f�B���N�g���̊K�w���擾����
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}


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

void DrawEnemy(int gh, int enemeNumber) {
	DrawExtendGraph(30 + 100 * enemeNumber, 30, 150 + 100 * enemeNumber, 150 + 100 * enemeNumber, gh, true);
}

// �c�胉�C�t�ɉ����ĉ摜�̕`�搔��ύX����
void DrawLife(int life, int gh) {
	int lifeCount = 0;
	for (lifeCount; lifeCount < life; lifeCount++) {
		DrawExtendGraph(500 + lifeCount * 50, 400, 550 + lifeCount * 50, 450, gh, true);
	}
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 70 )
#endif

	ChangeWindowMode(TRUE);

	// ini�t�@�C���̓ǂݍ��݂Ɋւ��鑀����s��
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section");
	char unit[CHARBUFF];
	sprintf_s(unit, "unit");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	
	int life = GetPrivateProfileInt(section, unit, -1, settingFile);

	// ���ʃt�@�C���ւ̓��o�͂��s��
	FILE *fp;
	char line[BUFFSIZE];

	errno_t error;

	// �t�@�C�����I�[�v�����Ă���
	error = fopen_s(&fp, "result.txt", "r");

	// �t�@�C���I�[�v�������s����ƁA�G���[���o���悤�ɂ��Ă���
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		int lineCounter = 0;
		while (fgets(line, BUFFSIZE, fp) != NULL) {
			lineCounter++;
			if (lineCounter == 1) {
				PlayGameCounter = (int)(*line) -48;
			}
			else if (lineCounter == 2) {
				WinCounter = (int)(*line) -48;
			}
		}
		fclose(fp);
	}

	// �ȉ�����̓t�@�C���ւ̏������݂��s��
	error = fopen_s(&fp, "result.txt", "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		char buf0[12];
		PlayGameCounter += 1; 
		snprintf(buf0, 12, "%d", PlayGameCounter);
		fputs(buf0, fp);

		char buf00[12];
		snprintf(buf00, 12, "%d\n", WinCounter);
		fputs(buf00, fp);

		char buf000[100];
		snprintf(buf000, 100, "���Ȃ��̏�����%d�p�[�Z���g�ł�\n", (100 * WinCounter / PlayGameCounter));
		fputs(buf000, fp);

		fclose(fp);
	}



	// DX���C�u����������
	if (DxLib_Init() == -1) {
		return -1;
	}

	// GameOver�Ɋւ���t���O
	bool isGameOver = false;

	// hasBlock�̓u���b�N�������Ă��邩
	bool hasBlock = true;

	// ����ʂɕ`��
	SetDrawScreen(DX_SCREEN_BACK);

	// �X�^�[�g��ʂ̕`����s���܂�
	int font1;
	int font2;
	font1 = CreateFontToHandle("���C���I", 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	font2 = CreateFontToHandle("���C���I", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	// ���y�̔ԍ�������
	int musicNumber;
	char music[3][100] = { "still.mp3", "begarosuto.mp3", "12345.mp3" };

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
		DrawStringToHandle(150, 200, "Game Start??", GetColor(255, 255, 255), font1);

		if (Key[KEY_INPUT_SPACE] >= 1) {
			break;
		}
	}

	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
		DrawStringToHandle(150, 200, "Select Music ", GetColor(255, 255, 255), font1);
		DrawStringToHandle(150, 400, "Please Enter A or B or C ", GetColor(255, 255, 255), font2);

		if (Key[KEY_INPUT_A] >= 1) {
			musicNumber = 0;
			break;
		}else if (Key[KEY_INPUT_B] >= 1) {
			musicNumber = 1;
			break;
		}else if (Key[KEY_INPUT_C] >= 1) {
			musicNumber = 2;
			break;
		}
	}
	char buffer[30];
	strcpy_s(buffer, "sound/");
	strcat_s(buffer, music[musicNumber]);

	PlaySound(buffer, DX_PLAYTYPE_LOOP);
	
	/* 
									////////////////////���X�e�[�W//////////////////////
	*/


	// �L�[�{�[�h�̏�Ԃ��擾
	char firstStageImages[3][100] = { "kandai.png","kangaku.png","ritsumei.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control = new CONTROL(firstStageImages, 1);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {
		
		// block�̃`�F�b�N���s���A0�̏ꍇ�͏����𒆒f����
		hasBlock = control->CheckBlock();
		if (hasBlock == false) {
			break;
		}
		
		// �Q�[���I�[�o�[��true��Ԃ�
		if (control->All(life)) {
			// life��0�łȂ���΃Q�[���͑��s����
			life = life - 1;
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}
		}

		// �ȉ�����B���R�}���h
		// ���݂̃X�e�[�W���X�L�b�v����
		if (Key[KEY_INPUT_A] >= 1) {
			hasBlock = false;
			break;
		}

		// ��ʉE���Ƀ��C�t��ݒ肷��
		int gh = LoadGraph("image/unit.png");
		DrawLife(life, gh);
		
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DX���C�u�������I��������
		DxLib_End();
	}

	// �S�Ẵu���b�N������ƁA���̃X�e�[�W�ɐi��
	if (hasBlock == false) {
		// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	
											////////////////////���X�e�[�W//////////////////////
	

	hasBlock = true;
	char secondeStageImages[3][100] = { "keio.png", "waseda.png", "jochi.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control2 = new CONTROL(secondeStageImages, 2);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {

		// block�̃`�F�b�N���s���A0�̏ꍇ�͏����𒆒f����
		hasBlock = control2->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		// �Q�[���I�[�o�[��true��Ԃ�
		if (control2->All(life)) {
			// life��0�łȂ���΃Q�[���͑��s����
			life = life - 1;
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}
		}

		// �ȉ�����B���R�}���h
		// ���݂̃X�e�[�W���X�L�b�v����
		if (Key[KEY_INPUT_A] >= 1) {
			hasBlock = false;
			break;
		}

		// ��ʉE���Ƀ��C�t��ݒ肷��
		int gh = LoadGraph("image/unit.png");
		DrawLife(life, gh);
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

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
			DrawStringToHandle(150, 200, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	/*
													////////////////////��O�X�e�[�W//////////////////////
	*/


	hasBlock = true;

	// �I�v�V�����̓G��t���邩�ǂ����̃t���O�ł���
	bool enemyFlag[5] = { false, false, false, false, false };

	char thirdStageImages[3][100] = { "kyodai.png", "todai.png", "oxford.png" };

	// �������̓X�e�[�W�i���o�[
	CONTROL *control3 = new CONTROL(thirdStageImages, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {

		// block�̃`�F�b�N���s���A0�̏ꍇ�͏����𒆒f����
		hasBlock = control3->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		// �Q�[���I�[�o�[��true��Ԃ�
		if (control3->All(life)) {
				life = life - 1;
			// life��0�łȂ���΃Q�[���͑��s����
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}

		}

		// �ȉ�����B���R�}���h
		// ���݂̃X�e�[�W���X�L�b�v����
		if (Key[KEY_INPUT_A] >= 1) {
			hasBlock = false;
			break;
		}

		int gh = LoadGraph("image/unit.png");

		if (Key[KEY_INPUT_0] >= 1) {
			enemyFlag[0] = true;
		}
		if (enemyFlag[0] == true) {
			DrawEnemy(gh, 0);
		}

		if (Key[KEY_INPUT_1] >= 1) {
			enemyFlag[1] = true;
		}
		if (enemyFlag[1] == true) {
			DrawEnemy(gh, 1);
		}
		
		if (Key[KEY_INPUT_2] >= 1) {
			enemyFlag[2] = true;
		}
		if (enemyFlag[2] == true) {
			DrawEnemy(gh, 2);
		}

		if (Key[KEY_INPUT_3] >= 1) {
			enemyFlag[3] = true;
		}
		if (enemyFlag[3] == true) {
			DrawEnemy(gh, 3);
		}
		
		if (Key[KEY_INPUT_4] >= 1) {
			enemyFlag[4] = true;
		}
		if (enemyFlag[4] == true) {
			DrawEnemy(gh, 4);
		}

		// ��ʉE���Ƀ��C�t��ݒ肷��

		DrawLife(life, gh);
	}

	// GameOver�ɂȂ����ꍇ�̏������s��
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DX���C�u�������I��������
		DxLib_End();
	}


	if (hasBlock == false) {
		// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A )
		WinCounter += 1;
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "All Finish", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}

	// �ȉ�����̓t�@�C���ւ̏������݂��s��
	error = fopen_s(&fp, "result.txt", "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	else {
		char buf[12];
		snprintf(buf, 12, "%d\n", PlayGameCounter);
		fputs(buf, fp);

		char buf2[12];
		snprintf(buf2, 12, "%d\n", WinCounter);
		fputs(buf2, fp);

		char buf3[100];
		snprintf(buf3, 100, "���Ȃ��̏�����%d�p�[�Z���g�ł�\n", (100 * WinCounter / PlayGameCounter));
		fputs(buf3, fp);
		fclose(fp);

		fclose(fp);
	}


	//DX���C�u�����I��
	DxLib_End();

	delete control;

	return 0;
}
