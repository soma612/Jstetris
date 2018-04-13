#pragma once
#define SKOUT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "SingleMode.h"
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <windows.h>
#endif
#include <process.h>

//위치값
#define STARTX 24
#define STARTY 1
#define MSG_X 42
#define MSG_Y 16

//게임모드
#define MOD_WAIT 0
#define MOD_GAME 1

// 키보드 입력
#define ESC 27
#define SPACEBAR 32
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define HOLD 122
#define SHAKE 9
#define TURNLEFT 99
#define RESTART 114
#define PAUSE 112
#define LEVELUP 61
#define LEVELDOWN 45

// 색 정의
#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK (RED | BLUE)
#define GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define WHITE (RED | GREEN | BLUE)
#define YELLOW (RED | GREEN)
#define SKYBLUE (GREEN | BLUE)
#define ORIGINAL 0x0007
#define GRAY 0x0008
#define BROWN 0x04

HANDLE hd;
WORD saveColor = 0;

int stageData[22][12] = {
	{ 7,7,7,7,7,7,7,7,7,7,7,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,8,8,8,8,8,8,8,8,8,8,7 },
	{ 7,7,7,7,7,7,7,7,7,7,7,7 }
};

//배열 순서대로 block, motion, block한개위치값, , xy값
int blocks[7][4][4][2] = {
	{
		// ㄱ자 블록 시계방향 순으로 회전
		{ { 0,0 },{ 1,0 },{ 2,0 },{ 2,1 } },
		{ { 1,0 },{ 1,1 },{ 0,2 },{ 1,2 } },
		{ { 0,0 },{ 0,1 },{ 1,1 },{ 2,1 } },
		{ { 0,0 },{ 1,0 },{ 0,1 },{ 0,2 } }
	},
	{
		// 역 ㄱ 자 블록
		{ { 0,0 },{ 1,0 },{ 2,0 },{ 0,1 } },
		{ { 0,0 },{ 1,0 },{ 1,1 },{ 1,2 } },
		{ { 0,1 },{ 1,1 },{ 2,0 },{ 2,1 } },
		{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,2 } }
	},
	{
		//  ㄹ 자 블록
		{ { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },
		{ { 1,0 },{ 0,1 },{ 1,1 },{ 0,2 } },
		{ { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },
		{ { 1,0 },{ 0,1 },{ 1,1 },{ 0,2 } }
	},
	{
		//  역 ㄹ 자 블록
		{ { 1,0 },{ 2,0 },{ 0,1 },{ 1,1 } },
		{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } },
		{ { 1,0 },{ 2,0 },{ 0,1 },{ 1,1 } },
		{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } }
	},
	{
		//  ㅗ 자 블록
		{ { 1,0 },{ 0,1 },{ 1,1 },{ 2,1 } },
		{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,1 } },
		{ { 0,0 },{ 1,0 },{ 2,0 },{ 1,1 } },
		{ { 0,1 },{ 1,1 },{ 1,0 },{ 1,2 } }
	},
	{
		//  ㅁ 자 블록
		{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
		{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
		{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
		{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } }
	},
	{
		//  l 자 블록
		{ { 1,0 },{ 1,1 },{ 1,2 },{ 1,3 } },
		{ { 0,1 },{ 1,1 },{ 2,1 },{ 3,1 } },
		{ { 1,0 },{ 1,1 },{ 1,2 },{ 1,3 } },
		{ { 0,1 },{ 1,1 },{ 2,1 },{ 3,1 } }
	}
};

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);
void resz(int w, int h);
void setColor(HANDLE hStdOut, WORD Attribute);
void putixy(int x, int y, int d) { gotoxy(x, y); printf("%d", d); }
void putsxy(int x, int y, char* c) { gotoxy(x, y); puts(c); }
void putchxy(int x, int y, char c) { gotoxy(x, y); _putch(c); }
void printB(int x, int y) { gotoxy(x, y); printf("■"); }
void color(WORD Attribute) { setColor(hd, Attribute); saveColor = Attribute; }

#define delay(n) Sleep(n)                              // n/1000초만큼 시간 지연
#define randomize() srand((unsigned)time(NULL))         // 난수 발생기 초기화
#define random(n) (rand() % (n))                        //0~n까지의 난수 발생

// 이 매크로가 정의되어 있으면 함수의 원형만 선언하고 정의는 하지 않는다.
#ifndef SKOUT_PROTOTYPE_ONLY

#define SKOUT_PROTOTYPE_ONLY
// 화면을 모두 지운다.
void clrscr()
{
	system("cls");
}

// 커서를 x,y좌표로 이동시킨다.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X=x;
	Cur.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

// 커서의 x 좌표를 조사한다.
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.X;
}

// 커서의 y좌표를 조사한다.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

// 커서를 숨기거나 다시 표시한다.
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize=1;
		CurInfo.bVisible=FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize=100;
		CurInfo.bVisible=TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize=20;
		CurInfo.bVisible=TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}
void resz(int w, int h) {
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD temp = { 999, 999 };
	COORD size = { w,h };
	SMALL_RECT sr;

	sr.Left = 0;
	sr.Top = 0;
	sr.Right = w - 1;
	sr.Bottom = h - 1;

	SetConsoleScreenBufferSize(hout, temp);
	SetConsoleWindowInfo(hout, TRUE, &sr);
	SetConsoleScreenBufferSize(hout, size);
}

void setColor(HANDLE hStdOut, WORD Attribute) {
	SetConsoleTextAttribute(hStdOut, Attribute);
}

#endif  