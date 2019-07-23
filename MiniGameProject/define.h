#pragma once
#include <windows.h>

#define MSG(m) {\
	MessageBox(NULL,m,"メッセージ",MB_OK);}


#define MSGPLUS(m,...) {\
	char buf[100];\
	sprintf(buf,m,__VA_ARGS__);\
	MessageBox(NULL,buf,"メッセージ",MB_OK);}


#define WIDTH 640
#define HEIGHT 480

#define CHARBUFF 124
#define BUFFSIZE 1024

// キー押下状態格納変数
extern char key[256];