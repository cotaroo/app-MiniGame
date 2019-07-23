#include "pch.h"
#include "control.h"
#include <Windows.h>

char key[256];
int Key[256]; // キーが押されているフレーム数を格納する


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

// 
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


	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	sprintf_s(section, "section");
	char unit[CHARBUFF];
	sprintf_s(unit, "unit");
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);
	
	int life = GetPrivateProfileInt(section, unit, -1, settingFile);


	//DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	// GameOverに関するフラグ
	bool isGameOver = false;

	// hasBlockはブロックを持っているか
	bool hasBlock = true;

	//裏画面に描画
	SetDrawScreen(DX_SCREEN_BACK);

	// スタート画面の描画を行います
	int font1;
	font1 = CreateFontToHandle("メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);
	
	
	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア )
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && gpUpdateKey() == 0) {
		DrawStringToHandle(100, 100, "Game Start??", GetColor(255, 255, 255), font1);

		if (Key[KEY_INPUT_SPACE] >= 1) {
			break;
		}
	}


	
	/* 
									////////////////////第一ステージ//////////////////////
	*/


	//キーボードの状態を取得
	char firstStageImages[3][100] = { "kandai.png","kangaku.png","ritsumei.png" };

	// 第二引数はステージナンバー
	CONTROL *control = new CONTROL(firstStageImages, 1);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {
		
		hasBlock = control->CheckBlock();
		if (hasBlock == false) {
			break;
		}
		
		//ゲームオーバーでtrueを返す
		if (control->All(life)) {
			// lifeが0でなければゲームは続行する
			life = life - 1;
			if (life != 0) {
			}
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
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

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
			DrawStringToHandle(100, 100, "Next Stage!?", GetColor(255, 255, 255), font1);

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

		hasBlock = control2->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//ゲームオーバーでtrueを返す
		if (control2->All(life)) {
			// lifeが0でなければゲームは続行する
			life = life - 1;
			if (life != 0) {
			}
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
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

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
			DrawStringToHandle(100, 100, "Next Stage!?", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	/*
													////////////////////第三ステージ//////////////////////
	*/


	hasBlock = true;
	char thirdStageImages[3][100] = { "kyodai.png", "todai.png", "oxford.png" };

	// 第二引数はステージナンバー
	CONTROL *control3 = new CONTROL(thirdStageImages, 3);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0 && gpUpdateKey() == 0) {

		hasBlock = control3->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//ゲームオーバーでtrueを返す
		if (control3->All(life)) {
				life = life - 1;
			// lifeが0でなければゲームは続行する
			if (life != 0) {
			}
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
			DrawStringToHandle(100, 100, "You are loser", GetColor(255, 255, 255), font1);

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
			DrawStringToHandle(100, 100, "All Finish", GetColor(255, 255, 255), font1);

			if (Key[KEY_INPUT_SPACE] >= 1) {
				break;
			}
		}
	}


	//DXライブラリ終了
	DxLib_End();

	delete control;

	return 0;
}
