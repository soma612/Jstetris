#pragma once
#include "server.h"
#include "MultiMode.h"



int mAutoDownBlock() {
	while (1) {
		delay(leveltime);
		EnterCriticalSection(&cs);
		if (isBlockCreated) mMoveBlock(0, 1);
		else mCreateNewBlock();
		LeaveCriticalSection(&cs);
	}
}
void mListenMsg() {
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

int playMultiGame() {
	clrscr();
	resz(100, 23);
	mInitBlock();
	mloadStage();
	//mPrintOtherPlayer();
	

	InitializeCriticalSection(&cs);
	thread1 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)mAutoDownBlock, NULL, 0, NULL);
	thread2 = _beginthreadex(NULL, 0, (_beginthreadex_proc_type)listenMsg, NULL, 0, NULL);
	multiPlaying();
	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	DeleteCriticalSection(&cs);
	return 0;
}

void multiPlaying() {
	EnterCriticalSection(&cs);
	putsxy(STARTX, 23, "[player1]");
	LeaveCriticalSection(&cs);
	while (1) {
		EnterCriticalSection(&cs);
		if (!isBlockCreated) mCreateNewBlock();
		LeaveCriticalSection(&cs);
		mPlayerMoveAction();
		if (!isSpeedMode)checkScore();
	}
}

int mPlayerMoveAction() {
	int dx = 0, dy = 0;
	char ch;
	ch = _getch();
	EnterCriticalSection(&cs);
	switch (ch) {
		case LEFT: { dx = -1; break; }
		case RIGHT: { dx = 1; break; }
		case UP: { mTurnBlock(isTurnMode);	break; }
		case DOWN: { dy = 1; break; }
		case SPACEBAR: { mFastDown(); break; }
		case TURNLEFT: {mTurnBlock(isTurnMode); break; }
		case 90: case HOLD: {
			if (ishold) mHoldingBlock();
			ishold = FALSE;
			break;
		}
		case 102: {
			
		}
	}
	gotoxy(MSG_X, MSG_Y); printf("ÀÔ·Â °ª : %d", ch);
	msgState = TRUE;
	if (dx != 0 || dy != 0) mMoveBlock(dx, dy);
	LeaveCriticalSection(&cs);
}