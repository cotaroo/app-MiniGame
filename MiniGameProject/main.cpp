#include "pch.h"
#include "control.h"

char key[256];
int Key[256]; // キーが押されているフレーム数を格納する

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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc( 70 )
#endif

	ChangeWindowMode(TRUE);


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
		DrawStringToHandle(100, 100, "Game Start!?", GetColor(255, 255, 255), font1);

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
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {
		
		hasBlock = control->CheckBlock();
		if (hasBlock == false) {
			break;
		}
		
		//ゲームオーバーでtrueを返す
		if (control->All()) {
			isGameOver = true;
			break;
		}
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
											////////////////////第二ステージ//////////////////////
	*/


	hasBlock = true;
	char secondeStageImages[3][100] = { "keio.png", "waseda.png", "jochi.png" };

	// 第二引数はステージナンバー
	CONTROL *control2 = new CONTROL(secondeStageImages, 2);
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		hasBlock = control2->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//ゲームオーバーでtrueを返す
		if (control2->All()) {
			isGameOver = true;
			break;
		}
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
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && GetHitKeyStateAll(key) == 0) {

		hasBlock = control3->CheckBlock();
		if (hasBlock == false) {
			break;
		}

		//ゲームオーバーでtrueを返す
		if (control3->All()) {
			isGameOver = true;
			break;
		}
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

