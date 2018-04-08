#include "JsTetris.h"

void configPage() {
	clrscr();
	int i;
	int menuCount = 0;
	int save_menuCount = -1;
	boolean isconfig = TRUE;
	boolean isTurn = TRUE;
	boolean isSpeed = FALSE;
	boolean isPreView = FALSE;

	char rowLine[] = "━";
	char title[] = "환 경 설 정";
	char menus[4][35] = {
		{ "기본 회전" },
		{ "속도조절 버튼(+,-)" },
		{ "프리뷰 항상 켜기" }
	};
	
	boolean menusSwitch[3] = {TRUE,FALSE,FALSE};
	char turn[2][10] = {
		{"우회전"},
		{"좌회전"}
	};
	char isOnOff[2][10] = {
		{"ON"},
		{"OFF"}
	};
	putsxy(16, 5, title);
	for (i = 0; i < 42; i++) {
		putsxy(16 + i, 6, rowLine);
	}
	color(GREEN); putsxy(16, 8, menus[0]); color(WHITE);
	color(YELLOW); putsxy(44, 8, turn[0]); color(WHITE);
	putchxy(51, 8, '/');
	putsxy(53, 8, turn[1]);

	putsxy(16, 10, menus[1]);
	putsxy(44, 10, isOnOff[0]); 
	putchxy(48, 10, '/');
	color(YELLOW); putsxy(51, 10, isOnOff[1]); color(WHITE);

	putsxy(16, 12, menus[2]);
	putsxy(44, 12, isOnOff[0]);
	putchxy(48, 12, '/');
	color(YELLOW);  putsxy(51, 12, isOnOff[1]); color(WHITE);

	color(GRAY); putsxy(30, 15, "설정완료(ENTER)"); color(WHITE);

	while (isconfig) {
		
		for (i = 0; i < 3; i++) {
			if (i == menuCount) {
				color(GREEN); putsxy(16, 8 + (2 * i), menus[i]);
				if (save_menuCount != -1) { color(WHITE); putsxy(16, 8 + (2 * save_menuCount), menus[save_menuCount]); }
			}
			if (menusSwitch[i] == TRUE) {
				if (i == 0) {
					color(YELLOW); putsxy(44, 8, turn[0]);
					color(WHITE); putsxy(53, 8, turn[1]);
				}
				else if(i == 1){
					color(YELLOW); putsxy(44, 10, isOnOff[0]);
					color(WHITE); putsxy(51, 10, isOnOff[1]);
				}
				else if (i == 2) {
					color(YELLOW); putsxy(44, 12, isOnOff[0]);
					color(WHITE); putsxy(51, 12, isOnOff[1]);
				}
			}
			else {
				if (i == 0) {
					color(YELLOW); putsxy(53, 8, turn[1]);
					color(WHITE); putsxy(44, 8, turn[0]);
				}
				else if(i == 1) {
					color(YELLOW); putsxy(51, 10, isOnOff[1]);
					color(WHITE); putsxy(44, 10, isOnOff[0]);
				}
				else if (i == 2) {
					color(YELLOW); putsxy(51, 12, isOnOff[1]);
					color(WHITE); putsxy(44, 12, isOnOff[0]);
				}
			}
		}
		char ch = _getch();
		switch (ch) {
			case DOWN: {
				save_menuCount = menuCount;
				menuCount = menuCount == 2 ? 0 : menuCount + 1;
				break;
			}
			case UP: {
				save_menuCount = menuCount;
				menuCount = menuCount == 0 ? 2 : menuCount - 1;
				break;
			}
			case LEFT: {
				menusSwitch[menuCount] = TRUE;
				break;
			}
			case RIGHT: {
				menusSwitch[menuCount] = FALSE;
				break;
			}
			case ENTER: {
				isconfig = FALSE;
				break;
			}
		}
	}
	isTurnMode = menusSwitch[0];
	isSpeedMode = menusSwitch[1];
	isPreViewMode = menusSwitch[2];
}