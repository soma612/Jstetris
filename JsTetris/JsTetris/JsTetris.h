#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <process.h>
#include "tools.h"



#define ESC 27
#define SPACEBAR 32
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ENTER 13
#define HOLD 122
#define TURNLEFT 99
#define RESTART 114
#define PAUSE 112
#define LEVELUP 61
#define LEVELDOWN 45
#define STARTX 24
#define STARTY 1
#define MSG_X 42
#define MSG_Y 16

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


CRITICAL_SECTION cs;
HANDLE thread1;
HANDLE thread2;



int stage[22][12];
int holdBlock = -1;
int holdMotion = 0;
int save_x = STARTX;
int save_y = STARTY;
int save_block = 0;
int save_motion = 0;
int save_pv_y = 0;
int save_pv_x = 0;
int score = 0;
int combo = 0;
int nextBlock[2] = { 0,0 };
int leveltime = 1000;
WORD saveColor = 0;
boolean isTurnMode = TRUE;
boolean isSpeedMode = FALSE;
boolean isPreViewMode = FALSE;
boolean msgState = FALSE;
boolean isBlockCreated = FALSE;
boolean ishold = TRUE;
boolean isConnected = TRUE;
HANDLE hd;

void putixy(int x, int y, int d) { gotoxy(x, y); printf("%d", d); }
void putsxy(int x, int y,char* c) {gotoxy(x,y); puts(c);}
void putchxy(int x, int y,char c) {gotoxy(x,y); _putch(c);}
void printB(int x, int y) { gotoxy(x, y); printf("■"); }
void color(WORD Attribute) { setColor(hd, Attribute); saveColor = Attribute; }

int PlayerMoveAction();
int autoDownBlock();
void playGame();
void playing();
void listenMsg();

void startPage();
int pausePage();
void configPage();
void checkScore();
void loadStage();
void createNewBlock();
void moveBlock(int dx, int dy);
void turnBlock(boolean isRight);
void createPreViewBlock(int x,int y, int block, int motion);
void removePreViewBlock();
void removeBlock();
boolean checkWalls(int block, int motion, int dx, int dy);
boolean checkPreViewWalls(int block, int motion,int y, int dx, int dy);
void changeBlockToWalll();
void checkAllLine();
void clearLine(int line);
void createBlock(int x, int y, int block, int motion);
void saveBlock(int x, int y, int block, int motion);
void initBlock();
void holdingBlock();
void printInfo();
void printNextBlock();
void printHoldBlock();
void printGameOver();
void selectColor(int block);
void printGameStart();
void printGamePause();

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