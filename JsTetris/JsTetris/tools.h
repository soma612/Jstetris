//#pragma once
#define SKOUT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK (RED | BLUE)
#define WHITE (RED | GREEN | BLUE)
#define YELLOW (RED | GREEN)
#define SKYBLUE (GREEN | BLUE)

#define RED_BG (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BLUE_BG (BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define PINK_BG (RED_BG | BLUE_BG)
#define WHITE_BG (RED_BG | GREEN_BG | BLUE_BG)
#define GREEN_BG (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define YELLOW_BG (RED_BG | GREEN_BG)
#define SKYBLUE_BG (GREEN_BG | BLUE_BG)

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);
void resz(int w, int h);
void setColor(HANDLE hStdOut, WORD Attribute);

#define delay(n) Sleep(n)                              // n/1000초만큼 시간 지연
#define randomize() srand((unsigned)time(NULL))         // 난수 발생기 초기화
#define random(n) (rand() % (n))                        //0~n까지의 난수 발생

// 이 매크로가 정의되어 있으면 함수의 원형만 선언하고 정의는 하지 않는다.
//#ifndef SKOUT_PROTOTYPE_ONLY

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

//#endif  