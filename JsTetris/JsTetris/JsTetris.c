#include "StartPage.h"
#include "tools.h"

// SingleMode
#include "SingleMode.h"
#include "SinglePlay.h"
#include "blockEvent.h"
#include "printInfo.h"
#include "PausePage.h"
#include "ConfigPage.h"

// MultiMode
#include "MultiModePage.h"
#include "server.h"
#include "client.h"


int main() {
	hd = GetStdHandle(STD_OUTPUT_HANDLE);
	srand((unsigned)time(NULL)); // 시간으로 랜덤 설정
	setcursortype(NOCURSOR); //커서 깜박임 제거
	resz(80, 22);
	color(WHITE);
	startPage();

	return 0;
}

