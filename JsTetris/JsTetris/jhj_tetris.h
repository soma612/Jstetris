#pragma once
#define SKOUT_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#ifndef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <windows.h>
#endif
#include <process.h>

#define RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define PINK (RED | BLUE)
#define WHITE (RED | GREEN | BLUE)
#define GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define YELLOW (RED | GREEN)
#define SKYBLUE (GREEN | BLUE)
#define ORIGINAL 0x0007
#define GRAY 0x0008
#define BROWN 0x04

#define RED_BG (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BLUE_BG (BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define PINK_BG (RED_BG | BLUE_BG)
#define WHITE_BG (RED_BG | GREEN_BG | BLUE_BG)
#define GREEN_BG (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define YELLOW_BG (RED_BG | GREEN_BG)
#define SKYBLUE_BG (GREEN_BG | BLUE_BG)
/*
enum {
BLACK,
DARK_BLUE,
DARK_GREEN,
DARK_SKYBLUE,
DARK_RED,
DARK_VIOLET,
DARK_YELLO,
GRAY,
DARK_GRAY,
BLUE,
GREEN,
SKYBLUE,
RED,
VIOLET,
YELLOW,
WHITE
};
*/
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);
void resz(int w, int h);
void setColor(WORD Attribute);

void printGameOver();
void printGameStart();
void printGamePause();

void putixy(int x, int y, int d) { gotoxy(x, y); printf("%d", d); }
void putsxy(int x, int y, char* c) { gotoxy(x, y); puts(c); }
void putchxy(int x, int y, char c) { gotoxy(x, y); _putch(c); }
void printB(int x, int y) { gotoxy(x, y); printf("��"); }
void selectColor(int block);

#define delay(n) Sleep(n)                              // n/1000�ʸ�ŭ �ð� ����
#define randomize() srand((unsigned)time(NULL))         // ���� �߻��� �ʱ�ȭ
#define random(n) (rand() % (n))                        //0~n������ ���� �߻�

HANDLE hd;

// �� ��ũ�ΰ� ���ǵǾ� ������ �Լ��� ������ �����ϰ� ���Ǵ� ���� �ʴ´�.
#ifndef SKOUT_PROTOTYPE_ONLY

#define SKOUT_PROTOTYPE_ONLY
// ȭ���� ��� �����.
void clrscr()
{
	system("cls");
}

// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

// Ŀ���� x ��ǥ�� �����Ѵ�.
int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO BufInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &BufInfo);
	return BufInfo.dwCursorPosition.Y;
}

// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;

	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
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

void setColor(WORD Attribute) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Attribute);
}
void selectColor(int block) {
	switch (block) {
	case 0: setColor(RED); break;
	case 1: setColor(BLUE); break;
	case 2: setColor(BROWN); break;
	case 3: setColor(GREEN); break;
	case 4: setColor(PINK); break;
	case 5: setColor(YELLOW); break;
	case 6: setColor(SKYBLUE); break;
	case 7: setColor(WHITE); break;
	}
}














#endif  