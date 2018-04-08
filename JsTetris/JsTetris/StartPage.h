#include "JsTetris.h"

int menu_Y = 12;
int menusCount = 0;
int save_menusCount = -1;
char menus[4][30] = {
	{ "G A M E  S T A R T" },
	{ "S E T T I N G" },
	{ "E X I T" }
};

int tetris[6][5][3] = {
	{
		{ 1,1,1 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 }
	},
	{
		{ 1,1,1 },
		{ 1,0,0 },
		{ 1,1,1 },
		{ 1,0,0 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 }
	},
	{
		{ 1,1,0 },
		{ 1,0,1 },
		{ 1,1,1 },
		{ 1,0,1 },
		{ 1,0,1 }
	},
	{
		{ 1,1,1 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 0,1,0 },
		{ 1,1,1 }
	},
	{
		{ 1,1,1 },
		{ 1,0,0 },
		{ 1,1,1 },
		{ 0,0,1 },
		{ 1,1,1 }
	}

};
void printTetris() {
	clrscr();
	int i, j, k;
	color(WHITE);
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 5; j++) {
			gotoxy(16 + i * 8, 4 + j);
			for (k = 0; k < 3; k++) {
				selectColor(i);
				if (tetris[i][j][k] == 1) printf("бс");
				else printf("  ");
			}
		}
	}
	color(WHITE); putsxy(26, 12, menus[0]);
	putsxy(26, 14, menus[1]);
	putsxy(26, 16, menus[2]);
	color(WHITE);
	putsxy(65, 20, "made by SOMA");
}

void startPage() {
	int i; 
	
	printTetris();
	while (1) {
		for (i = 0; i < 3; i++) {
			if (menusCount == i) {
				color(GREEN);
				putsxy(26, menu_Y + (i * 2), menus[i]);
				color(WHITE);
				if(save_menusCount != -1)putsxy(26, menu_Y + (save_menusCount * 2), menus[save_menusCount]);
			}
		}
		char ch = _getch();
		switch (ch) {
			case DOWN: {
				save_menusCount = menusCount;
				menusCount = menusCount == 2 ? 0 : menusCount + 1;
				break;
			}
			case UP: {
				save_menusCount = menusCount;
				menusCount = menusCount == 0 ? 2 : menusCount - 1;
				break;
			}
			case ENTER: {
				if (menusCount == 0) playGame();
				else if (menusCount == 1) { configPage(); printTetris(); }
				else if (menusCount == 2) exit(1);
				break;
			}
		}
	}
}
