#include "pch.h"
#include "control.h"
#include <Windows.h>
#include <fstream>

char key[256];
int Key[256]; // キーが押されているフレーム数を格納する
int PlayGameCounter = 0; // ゲームをプレイした回数を格納する
int WinCounter = 0; // 勝利した回数を格納する
double winRate; // 勝率を格納する

// 現在のディレクトリの階層を取得する
void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}


// キーの入力状態を更新する
int gpUpdateKey() {
	char tmpKey[256]; // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey); // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++) {
		if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
			Key[i]++;     // 加算
		}
		else {              // 押されていなければ
			Key[i] = 0;   // 0にする
		}
	}
	return 0;
}

void DrawEnemy(int gh, int enemeNumber) {
	DrawExtendGraph(30 + 100 * enemeNumber, 30, 150 + 100 * enemeNumber, 150 + 100 * enemeNumber, gh, true);
}

// 残りライフに応じて画像の描画数を変更する
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

	// iniファイルの読み込みに関する操作を行う
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section");
	char unit[CHARBUFF];
	sprintf_s(unit, "unit");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	
	int life = GetPrivateProfileInt(section, unit, -1, settingFile);

	// 結果ファイルへの入出力を行う
	FILE *fp;
	char line[BUFFSIZE];

	errno_t error;

	// ファイルをオープンしている
	error = fopen_s(&fp, "result.txt", "r");

	// ファイルオープンが失敗すると、エラーを出すようにしている
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

	// 以下からはファイルへの書き込みを行う
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
		snprintf(buf000, 100, "あなたの勝率は%dパーセントです\n", (100 * WinCounter / PlayGameCounter));
		fputs(buf000, fp);

		fclose(fp);
	}



	// DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// GameOverに関するフラグ
	bool isGameOver = false;

	// hasBlockはブロックを持っているか
	bool hasBlock = true;

	// 裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	// スタート画面の描画を行います
	int font1;
	int font2;
	font1 = CreateFontToHandle("メイリオ", 50, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	font2 = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	// 音楽の番号を入れる
	int musicNumber;
	char music[3][100] = { "still.mp3", "begarosuto.mp3", "12345.mp3" };

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
		DrawStringToHandle(150, 200, "Game Start??", GetColor(255, 255, 255), font1);

		if (Key[KEY_INPUT_SPACE] >= 1) {
			break;
		}
	}

	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
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
									////////////////////第一ステージ//////////////////////
	*/


	// キーボードの状態を取得
	char firstStageImages[3][100] = { "kandai.png","kangaku.png","ritsumei.png" };

	// 第二引数はステージナンバー
	CONTROL *control = new CONTROL(firstStageImages, 1);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {
		
		// blockのチェックを行い、0の場合は処理を中断する
		hasBlock = control->CheckBlock();
		if (hasBlock == false) {
			break;
		}
		
		// ゲームオーバーでtrueを返す
		if (control->All(life)) {
			// lifeが0でなければゲームは続行する
			life = life - 1;
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}
		}

		// 以下から隠しコマンド
		// 現在のステージをスキップする
		if (Key[KEY_INPUT_A] >= 1) {
			hasBlock = false;
			break;
		}

		// 画面右下にライフを設定する
		int gh = LoadGraph("image/unit.png");
		DrawLife(life, gh);
		
	}

	// GameOverになった場合の処理を行う
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DXライブラリを終了させる
		DxLib_End();
	}

	// 全てのブロックを崩すと、次のステージに進む
	if (hasBlock == false) {
		// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	
											////////////////////第二ステージ//////////////////////
	

	hasBlock = true;
	char secondeStageImages[3][100] = { "keio.png", "waseda.png", "jochi.png" };

	// 第二引数はステージナンバー
	CONTROL *control2 = new CONTROL(secondeStageImages, 2);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {

		// blockのチェックを行い、0の場合は処理を中断する
		hasBlock = control2->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		// ゲームオーバーでtrueを返す
		if (control2->All(life)) {
			// lifeが0でなければゲームは続行する
			life = life - 1;
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}
		}

		// 以下から隠しコマンド
		// 現在のステージをスキップする
		if (Key[KEY_INPUT_A] >= 1) {
			hasBlock = false;
			break;
		}

		// 画面右下にライフを設定する
		int gh = LoadGraph("image/unit.png");
		DrawLife(life, gh);
	}

	// GameOverになった場合の処理を行う
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DXライブラリを終了させる
		DxLib_End();
	}


	if (hasBlock == false) {
		// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	/*
													////////////////////第三ステージ//////////////////////
	*/


	hasBlock = true;

	// オプションの敵を付けるかどうかのフラグである
	bool enemyFlag[5] = { false, false, false, false, false };

	char thirdStageImages[3][100] = { "kyodai.png", "todai.png", "oxford.png" };

	// 第二引数はステージナンバー
	CONTROL *control3 = new CONTROL(thirdStageImages, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {

		// blockのチェックを行い、0の場合は処理を中断する
		hasBlock = control3->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		// ゲームオーバーでtrueを返す
		if (control3->All(life)) {
				life = life - 1;
			// lifeが0でなければゲームは続行する
			if (life != 0) {}
			else {
				isGameOver = true;
				break;
			}

		}

		// 以下から隠しコマンド
		// 現在のステージをスキップする
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

		// 画面右下にライフを設定する

		DrawLife(life, gh);
	}

	// GameOverになった場合の処理を行う
	if (isGameOver == true) {
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "You are loser", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
		// DXライブラリを終了させる
		DxLib_End();
	}


	if (hasBlock == false) {
		// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
		WinCounter += 1;
		while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
			DrawStringToHandle(150, 200, "All Finish", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}

	// 以下からはファイルへの書き込みを行う
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
		snprintf(buf3, 100, "あなたの勝率は%dパーセントです\n", (100 * WinCounter / PlayGameCounter));
		fputs(buf3, fp);
		fclose(fp);

		fclose(fp);
	}


	//DXライブラリ終了
	DxLib_End();

	delete control;

	return 0;
}
