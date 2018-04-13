#include "SingleMode.h"

int pausePage() {
	int menuCount = 0;
	boolean isPausePage = TRUE;
	char menus[3][24] = {
		{ "계 속 하 기" },
		{ "메 뉴 로  돌 아 가 기" }
	};

	while (isPausePage) {
		clrscr();
		if (menuCount == 0) {
			color(GREEN); putsxy(26, 5, menus[0]); 
			color(WHITE); putsxy(26, 7, menus[1]);
		}
		else if (menuCount == 1) {
			color(WHITE); putsxy(26, 5, menus[0]);
			color(GREEN); putsxy(26, 7, menus[1]);
		}
		char ch = _getch();
		switch (ch) {
			case UP:case DOWN: {
				menuCount = menuCount == 0 ? 1 : 0;
				break;
			}
			case ENTER: {
				if (menuCount == 0) {
					isPausePage = FALSE;
					break;
				}
				else if (menuCount == 1) {
					return 1;
					break;
				}
			}
			
		}
	}

}