#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <process.h>
#include "jhj_tetris.h"

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
//==========================================================================//
void initMain();
void showMainPage();
void playGame();
void printInfo();
void initStartGame();
void printStage();
void printNextBlock();
void printHoldBlock();
void createBlock(int x, int y, int block, int motion);
void removeBlock();
void autoDownBlock();
void listenMsg();
void playing();
void moveBlock(int dx, int dy);

//==========================================================================//
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
int stage[22][12];
char menus[4][30] = {
	{ "G A M E  S T A R T" },
{ "S E T T I N G" },
{ "E X I T" }
};
int tetris[6][5][3] = {
	{ { 1,1,1 },
{ 0,1,0 },
{ 0,1,0 },
{ 0,1,0 },
{ 0,1,0 }
	},
{ { 1,1,1 },
{ 1,0,0 },
{ 1,1,1 },
{ 1,0,0 },
{ 1,1,1 }
},
{ { 1,1,1 },
{ 0,1,0 },
{ 0,1,0 },
{ 0,1,0 },
{ 0,1,0 }
},
{ { 1,1,0 },
{ 1,0,1 },
{ 1,1,1 },
{ 1,0,1 },
{ 1,0,1 }
},
{ { 1,1,1 },
{ 0,1,0 },
{ 0,1,0 },
{ 0,1,0 },
{ 1,1,1 }
},
{ { 1,1,1 },
{ 1,0,0 },
{ 1,1,1 },
{ 0,0,1 },
{ 1,1,1 } }
};
//배열 순서대로 block, motion, block한개위치값, , xy값
int blocks[7][4][4][2] = {
	{	// ㄱ자 블록 시계방향 순으로 회전
		{ { 0,0 },{ 1,0 },{ 2,0 },{ 2,1 } },
{ { 1,0 },{ 1,1 },{ 0,2 },{ 1,2 } },
{ { 0,0 },{ 0,1 },{ 1,1 },{ 2,1 } },
{ { 0,0 },{ 1,0 },{ 0,1 },{ 0,2 } }
	},
	{	// 역 ㄱ 자 블록
		{ { 0,0 },{ 1,0 },{ 2,0 },{ 0,1 } },
{ { 0,0 },{ 1,0 },{ 1,1 },{ 1,2 } },
{ { 0,1 },{ 1,1 },{ 2,0 },{ 2,1 } },
{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,2 } }
	},
	{	//  ㄹ 자 블록
		{ { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },
{ { 1,0 },{ 0,1 },{ 1,1 },{ 0,2 } },
{ { 0,0 },{ 1,0 },{ 1,1 },{ 2,1 } },
{ { 1,0 },{ 0,1 },{ 1,1 },{ 0,2 } }
	},
	{	//  역 ㄹ 자 블록
		{ { 1,0 },{ 2,0 },{ 0,1 },{ 1,1 } },
{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } },
{ { 1,0 },{ 2,0 },{ 0,1 },{ 1,1 } },
{ { 0,0 },{ 0,1 },{ 1,1 },{ 1,2 } }
	},
	{	//  ㅗ 자 블록
		{ { 1,0 },{ 0,1 },{ 1,1 },{ 2,1 } },
{ { 0,0 },{ 0,1 },{ 0,2 },{ 1,1 } },
{ { 0,0 },{ 1,0 },{ 2,0 },{ 1,1 } },
{ { 0,1 },{ 1,1 },{ 1,0 },{ 1,2 } }
	},
	{	//  ㅁ 자 블록
		{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } },
{ { 0,0 },{ 0,1 },{ 1,0 },{ 1,1 } }
	},
	{	//  l 자 블록
		{ { 1,0 },{ 1,1 },{ 1,2 },{ 1,3 } },
{ { 0,1 },{ 1,1 },{ 2,1 },{ 3,1 } },
{ { 1,0 },{ 1,1 },{ 1,2 },{ 1,3 } },
{ { 0,1 },{ 1,1 },{ 2,1 },{ 3,1 } }
	}
};

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

boolean isBlockCreated = FALSE;
HANDLE thread1;
HANDLE thread2;
CRITICAL_SECTION cs;
boolean isPreViewMode = FALSE;


//==========================================================================//
int main(void) {
	initMain();
	showMainPage();



	return 0;
}

void initMain() {
	srand((unsigned)time(NULL)); // 시간으로 랜덤 설정
	setcursortype(NOCURSOR); //커서 깜박임 제거
	resz(80, 22);
}

void showMainPage() {

	clrscr();

	int i, j, k;
	setColor(WHITE);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy(16 + i * 8, 4 + j);
			for (k = 0; k < 3; k++) {
				selectColor(i);
				if (tetris[i][j][k] == 1) printf("■");
				else printf("  ");
			}
		}
	}
	setColor(WHITE); putsxy(26, 12, menus[0]);
	putsxy(26, 14, menus[1]);
	putsxy(26, 16, menus[2]);
	setColor(WHITE);
	putsxy(65, 20, "made by SOMA");

	int menu_Y = 12;
	int priorMenu = 0;
	int selectedMenu = 0;

	for (i = 0; i < 3; i++) {
		if (selectedMenu == i)
			setColor(GREEN);
		else
			setColor(WHITE);
		putsxy(26, menu_Y + (i * 2), menus[i]);
	}
	int flag = 1;
	while (flag) {
		char ch = _getch();
		switch (ch) {
		case DOWN:
			priorMenu = selectedMenu;
			selectedMenu = selectedMenu >= 2 ? 2 : selectedMenu + 1;
			setColor(WHITE);	putsxy(26, menu_Y + (priorMenu * 2), menus[priorMenu]);
			setColor(GREEN);	putsxy(26, menu_Y + (selectedMenu * 2), menus[selectedMenu]);
			break;
		case UP:
			priorMenu = selectedMenu;
			selectedMenu = selectedMenu <= 0 ? 0 : selectedMenu - 1;
			setColor(WHITE);	putsxy(26, menu_Y + (priorMenu * 2), menus[priorMenu]);
			setColor(GREEN);	putsxy(26, menu_Y + (selectedMenu * 2), menus[selectedMenu]);
			break;
		case ENTER:
			if (selectedMenu == 0) { playGame();	flag = 0; }
			else if (selectedMenu == 1) { printf("not yet\n"); /*configPage(); printTetris();*/ }
			else if (selectedMenu == 2) exit(1);

			break;
		}
	}
}

void playGame() {
	clrscr();
	initStartGame();
	InitializeCriticalSection(&cs);
	thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)autoDownBlock, NULL, 0, NULL);
	thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)listenMsg, NULL, 0, NULL);
	playing();
	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	DeleteCriticalSection(&cs);
}
void playing() {
	int i = 0;
	while (1) {
		delay(500);
		EnterCriticalSection(&cs);
		putixy(10, 5, i++);
		LeaveCriticalSection(&cs);
	}
}
void autoDownBlock() {
	int i = 0;
	while (1) {
		/*		delay(leveltime);
		EnterCriticalSection(&cs);
		if (isBlockCreated) moveBlock(0, 1);
		else createNewBlock();
		LeaveCriticalSection(&cs);
		*/
	}
}

void moveBlock(int dx, int dy) {
	/*
	if (checkWalls(save_block, save_motion, dx, dy)) {
	if (dy == 1) changeBlockToWalll();
	return;
	}
	else {
	removeBlock();
	if (isPreViewMode || score < 15000) {
	removePreViewBlock();
	createPreViewBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);
	}
	createBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);
	saveBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);

	}
	*/
}
void listenMsg() {
	int i = 0;
	while (1) {
		delay(300);
		EnterCriticalSection(&cs);
		putixy(10, 13, i++); LeaveCriticalSection(&cs);
		/*
		if (msgState) {
		msgState = FALSE;
		int count = 0;
		while (count != 1000) {
		delay(1);
		count++;
		if (msgState) count = 0;
		}
		//delay(3000);
		EnterCriticalSection(&cs);
		gotoxy(MSG_X, MSG_Y); printf("              ");
		gotoxy(MSG_X, MSG_Y + 1); printf("              ");
		gotoxy(MSG_X, MSG_Y + 2); printf("              ");
		gotoxy(MSG_X, MSG_Y + 3); printf("              ");
		LeaveCriticalSection(&cs);
		//msgState = FALSE;
		}
		*/
	}
}//////////////////////////////////////////////


void initStartGame() {
	memcpy(stage, stageData, sizeof(stage));
	save_x = STARTX;
	save_y = STARTY;
	holdBlock = -1;
	save_block = 0;
	save_motion = 0;
	score = 0;
	leveltime = 1000;
	isBlockCreated = FALSE;
	nextBlock[0] = random(7);
	nextBlock[1] = random(7);

	printStage();
	printInfo();
	printNextBlock();
	printHoldBlock();
	printGameStart();
}

void printInfo() {
	int i;
	setColor(WHITE);
	for (i = 0; i < 22; i++) {
		gotoxy(56, i); printf("|");
	}
	gotoxy(59, 1); printf("┏━━━━━━━━━━━━━━┓");
	gotoxy(59, 2); printf("┃  T E T R I S ┃ ");
	gotoxy(59, 3); printf("┗━━━━━━━━━━━━━━┛");

	gotoxy(2, 8); printf("스테이지 : %d", 11 - leveltime / 100);
	gotoxy(2, 10); printf("점수 : %d", score);

	gotoxy(66, 5); printf("회전");
	gotoxy(67, 6); printf("↑");
	gotoxy(60, 7); printf("LEFT ←  → RIGHT");
	gotoxy(67, 8); printf("↓");
	gotoxy(66, 9); printf("DOWN");
	gotoxy(60, 11); printf("Space Bar:퀵다운");
	gotoxy(60, 13); printf("Z Key:블록 홀드");
	gotoxy(60, 15); printf("C Key:블록 역회전");
	gotoxy(60, 17); printf("P Key:일시정지");
	gotoxy(60, 19); printf("R Key:게임 재시작");

}

void printStage() {
	int i, j;
	for (i = 0; i < 22; i++) {
		gotoxy(16, i);
		for (j = 0; j < 12; j++) {
			selectColor(stage[i][j]);
			if (stage[i][j] == 7) { setColor(WHITE); printf("▣"); }
			else if (stage[i][j] == 8) printf("  ");
			else printf("■");
		}
	}

	setColor(WHITE);
	char outline[8][17] = {
		"□□□□□□",
		"□        □",
		"□        □",
		"□        □",
		"□        □",
		"□□□□□□"
	};
	putsxy(43, 0, "Next Block");
	putsxy(3, 0, "Hold Block");

	for (i = 0; i < 8; i++) {
		putsxy(2, 1 + i, outline[i]);
		putsxy(42, 1 + i, outline[i]);
		putsxy(42, 8 + i, outline[i]);
	}

}
void printGameOver() {
	setColor(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME OVER      ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(17, 14); printf("━━  Press Enter Key ━━");

}
void printGameStart() {
	setColor(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME START     ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(17, 14); printf("━━  Press Enter Key ━━");
	getchar();

}
void printGamePause() {
	setColor(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME PAUSE     ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(18, 14); printf("━━  Press P Key  ━━");
}
void printNextBlock() {


	int x1 = nextBlock[0] == 5 ? 46 : 45;
	int y1 = nextBlock[0] == 6 ? 2 : 3;
	int x2 = nextBlock[1] == 5 ? 46 : 45;
	int y2 = nextBlock[1] == 6 ? 9 : 10;

	createBlock(x1, y1, nextBlock[0], 0);
	createBlock(x2, y2, nextBlock[1], 0);
}
void printHoldBlock() {

	if (holdBlock != -1) {
		int x = holdBlock == 5 ? 6 : 5;
		int y = holdBlock == 6 ? 2 : 3;
		if (holdBlock == 6 && (holdMotion == 1 || holdMotion == 3)) x = 4;
		createBlock(x, y, holdBlock, holdMotion);
	}
}


void createBlock(int x, int y, int block, int motion) {
	int i;
	selectColor(block);
	for (i = 0; i < 4; i++) {
		putsxy((x + blocks[block][motion][i][0] * 2), y + blocks[block][motion][i][1], "■"); // x,y 위치부터 block에 저장된 block값과 motion값의 블록을 +x +y 위치값을 더한 4개의 ■를 출력 
	}
}
void removeBlock() {
	int i;
	for (i = 0; i < 4; i++) {
		putsxy((save_x + blocks[save_block][save_motion][i][0] * 2), save_y + blocks[save_block][save_motion][i][1], "  ");
	}
}