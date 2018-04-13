#include "SingleMode.h"

void loadStage() {
	clrscr();
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
	printInfo();
	printNextBlock();
	printHoldBlock();
}


void printInfo() {
	int i;
	color(WHITE);
	for (i = 0; i < 22; i++) {
		gotoxy(56, i); printf("|");
	}
	gotoxy(59, 0); printf("┏━━━━━━━━━━━━━━┓");
	gotoxy(59, 1); printf("┃  T E T R I S ┃ ");
	gotoxy(59, 2); printf("┗━━━━━━━━━━━━━━┛");

	gotoxy(2, 8); printf("스테이지 : %d", 11 - leveltime / 100);
	gotoxy(2, 10); printf("점수 : %d", score);

	gotoxy(66, 4); printf("회전");
	gotoxy(67, 5); printf("↑");
	gotoxy(60, 6); printf("LEFT ←  → RIGHT");
	gotoxy(67, 7); printf("↓");
	gotoxy(66, 8); printf("DOWN");
	gotoxy(60, 10); printf("Space Bar:퀵다운");
	gotoxy(60, 12); printf("Z Key:블록 홀드");
	gotoxy(60, 14); printf("C Key:블록 역회전");
	gotoxy(60, 16); printf("P Key:일시정지");
	gotoxy(60, 18); printf("R Key:게임 재시작");
	gotoxy(60, 20); printf("Tab Key: 블록 섞기");

}
void printNextBlock() {
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
void printHoldBlock() {
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
		createBlock(x, y, holdBlock, holdMotion);
	}
}

void printGameOver() {
	color(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME OVER      ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");
	
	gotoxy(17 , 14); printf("━━  Press Enter Key ━━");

}
void printGameStart() {
	color(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME START     ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(17, 14); printf("━━  Press Enter Key ━━");
}

void printGamePause() {
	color(WHITE);
	gotoxy(16, 2); printf("┏━━━━━━━━━━━━━━━━━━━━━┓");
	gotoxy(16, 3); printf("┃      GAME PAUSE     ┃ ");
	gotoxy(16, 4); printf("┗━━━━━━━━━━━━━━━━━━━━━┛");

	gotoxy(18, 14); printf("━━  Press P Key  ━━");
}