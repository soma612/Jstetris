#pragma once
#include "SingleMode.h"

void initGame() {
	initBlock();
	printInfo();
	printGameStart();
	getchar();
	loadStage();
	InitializeCriticalSection(&cs);
	thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)autoDownBlock, NULL, 0, NULL);
	thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)listenMsg, NULL, 0, NULL);
	playing();
	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	DeleteCriticalSection(&cs);
}

void playing() {
	while (1) {
		EnterCriticalSection(&cs);
		if (!isBlockCreated) createNewBlock();
		LeaveCriticalSection(&cs);
		PlayerMoveAction();
		if (!isSpeedMode)checkScore();
	}
}
int autoDownBlock() {
	while (1) {
		delay(leveltime);
		EnterCriticalSection(&cs);
		if (isBlockCreated) moveBlock(0, 1);
		else createNewBlock();
		LeaveCriticalSection(&cs);
	}
}
void listenMsg() {
	while (1) {
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
			gotoxy(MSG_X, MSG_Y + 4); printf("              ");
			gotoxy(MSG_X, MSG_Y + 5); printf("              ");
			LeaveCriticalSection(&cs);
			//msgState = FALSE;

		}
		delay(1);
	}
}

int PlayerMoveAction() {
	int dx = 0, dy = 0;
	char ch;
	ch = _getch();
	EnterCriticalSection(&cs);
	switch (ch) {
	case ESC: {
		if (pausePage() == 1) {
			TerminateThread(thread1, 0);
			TerminateThread(thread2, 0);
			LeaveCriticalSection(&cs);
			DeleteCriticalSection(&cs);
			startPage();
		}
		loadStage();
	}
	case LEFT: { dx = -1; break; }
	case RIGHT: { dx = 1; break; }
	case UP: { turnBlock(isTurnMode);	break; }
	case DOWN: { dy = 1; break; }
	case SPACEBAR: { fastDown(); break; }
	case TURNLEFT: {turnBlock(isTurnMode); break; }
	case HOLD: {
		if (ishold) holdingBlock();
		ishold = FALSE;
		break;
	}
	case SHAKE: {
		if (isShaking) {
			isShaking = FALSE;
			nextBlock[0] = random(7);
			nextBlock[1] = random(7);
			loadStage();
			moveBlock(0, 0);
		}
		break;
	}
	case RESTART: {
		initBlock();
		printGameStart();
		while (_getch() != 13) { delay(1); }
		loadStage();
		break;
	}
	case PAUSE: {
		printGamePause();
		while (_getch() != PAUSE) { delay(1); }
		loadStage();
		moveBlock(0, 0);
		break;
	}
	case LEVELUP: {
		if (isSpeedMode) {
			leveltime = leveltime < 150 ? 150 : leveltime - 100;
			printInfo();
		}
		break;
	}
	case LEVELDOWN: {
		if (isSpeedMode) {
			leveltime = leveltime > 1000 ? 1000 : leveltime + 100;
			printInfo();
		}
		break;
	}
	}
	//gotoxy(MSG_X, MSG_Y); printf("ÀÔ·Â °ª : %d", ch);
	//msgState = TRUE;
	if (dx != 0 || dy != 0) moveBlock(dx, dy);
	LeaveCriticalSection(&cs);
}
void checkScore() {
	if (score < 1000) leveltime = 1000;
	else if (score < 2500) leveltime = 800;
	else if (score < 4000) leveltime = 600;
	else if (score < 5500) leveltime = 400;
	else if (score < 7000) leveltime = 250;
	else if (score < 10000) leveltime = 150;
}