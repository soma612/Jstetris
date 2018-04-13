#pragma once
#include "MultiMode.h"


void mloadStage() {
	color(WHITE);
	int i, j;
	for (i = 0; i < 22; i++) {
		gotoxy(16, i);
		for (j = 0; j < 12; j++) {
			selectColor(stage[i][j]);
			if (stage[i][j] == 7) { color(WHITE); printf("▣"); }
			else if (stage[i][j] == 8) printf("  ");
			else printf("■");
		}
	}
	gotoxy(45, 23); printf("[player1]");
	mPrintInfo();
	mPrintNextBlock();
	mPrintHoldBlock();
}

void mPrintNextBlock() {
	int i;
	color(WHITE);
	char outline[8][17] = {
		"□□□□□□",
		"□        □",
		"□        □",
		"□        □",
		"□        □",
		"□□□□□□"
	};
	putsxy(43, 0, "Next Block");
	int x1 = nextBlock[0] == 5 ? 46 : 45;
	int y1 = nextBlock[0] == 6 ? 2 : 3;
	int x2 = nextBlock[1] == 5 ? 46 : 45;
	int y2 = nextBlock[1] == 6 ? 9 : 10;

	for (i = 0; i < 8; i++) {
		putsxy(42, 1 + i, outline[i]);
		putsxy(42, 8 + i, outline[i]);
	}
	createBlock(x1, y1, nextBlock[0], 0);
	createBlock(x2, y2, nextBlock[1], 0);
}
void mPrintHoldBlock() {
	int i;
	color(WHITE);
	char outline[8][17] = {
		"□□□□□□",
		"□        □",
		"□        □",
		"□        □",
		"□        □",
		"□□□□□□"
	};
	putsxy(3, 0, "Hold Block");
	for (i = 0; i < 8; i++) {
		putsxy(2, 1 + i, outline[i]);
	}
	if (holdBlock != -1) {
		int x = holdBlock == 5 ? 6 : 5;
		int y = holdBlock == 6 ? 2 : 3;
		if (holdBlock == 6 && (holdMotion == 1 || holdMotion == 3)) x = 4;
		mCreateBlock(x, y, holdBlock, holdMotion);
	}
}

void mPrintInfo() {
	color(WHITE);
	gotoxy(2, 8); printf("스테이지 : %d", 11 - leveltime / 100);
	gotoxy(2, 10); printf("점수 : %d", score);


}

void mPrintGameOver() {
	color(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME OVER      ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");
}

void mPrintOtherPlayer() {
	int i, j;
	for (i = 0; i < 21; i++) {
		putsxy(56, i, "l");
	}
	for (i = 0; i < 22; i++) {
		gotoxy(60, i);
		for (j = 0; j < 12; j++) {
			selectColor(stage[i][j]);
			if (stage[i][j] == 7) { color(WHITE); printf("▣"); }
			else if (stage[i][j] == 8) printf("  ");
			else printf("■");
		}
	}
	putsxy(STARTX + 40, 23, "[player2]");
}