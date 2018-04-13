#pragma once
#include "MultiMode.h"


int chosePlayerCount() {
	char playerCount[40] = "플 레 이 어(최대 4인) : ◁ 2 ▷";
	clrscr();
	color(WHITE);
	putsxy(26, 7, playerCount);
	int pcount = 2;
	boolean isChosePlayer = TRUE;
	while(isChosePlayer) {
		putixy(53, 7, pcount);
		char ch2 = _getch();
		switch (ch2) {
			case LEFT: {
				pcount = pcount == 2 ? 2 : pcount - 1;
				putsxy(50, 7, "◀");
				delay(100);
				putsxy(50, 7, "◁");
				break;
			}
			case RIGHT: {
				pcount = pcount == 4 ? 4 : pcount + 1;
				putsxy(55, 7, "▶");
				delay(100);
				putsxy(55, 7, "▷");
				break;
			}
			case ENTER: {
				server(pcount);
				break;
			}
			case ESC: {
				isChosePlayer = FALSE;
				break;
			}
		}
	}
}

int startMultiMode() {
	int menuCount = 0;
	boolean isMultiPage = TRUE;
	char menus[4][24] = {
		{ "방 만 들 기" },
		{ "방 접 속 하 기"}, 
		{ "메 뉴 로  돌 아 가 기" }
	};
	char playerCount[40] = "플 레 이 어(최대 4인) : ◁ 1 ▷";
	

	while (isMultiPage) {
		clrscr();
		if (menuCount == 0) {
			color(GREEN); putsxy(26, 5, menus[0]);
			color(WHITE); putsxy(26, 7, menus[1]);
			putsxy(26, 9, menus[2]);
		}
		else if (menuCount == 1) {
			color(WHITE); putsxy(26, 5, menus[0]);
			color(GREEN); putsxy(26, 7, menus[1]);
			color(WHITE); putsxy(26, 9, menus[2]);
		}
		else if (menuCount == 2) {
			color(WHITE); putsxy(26, 5, menus[0]);
			color(WHITE); putsxy(26, 7, menus[1]);
			color(GREEN); putsxy(26, 9, menus[2]);
		}
		char ch = _getch();
		switch (ch) {
			case UP: {
				menuCount = menuCount == 0 ? 2 : menuCount-1;
				break;
			}
			case DOWN: {
				menuCount = menuCount == 2 ? 0 : menuCount+1;
				break;
			}
			case ENTER: {
				if (menuCount == 0) {
					chosePlayerCount();
					//if (server() == 1) printf("연결실패. 다시 시도해주세요");
					break;
				}
				else if (menuCount == 1) {
					if (client() == 1) printf("연결실패. 다시 시도해주세요");
					break;
				}
				else if (menuCount == 2) {
					isMultiPage = FALSE;
					break;
				}
			}
		}
	}
}