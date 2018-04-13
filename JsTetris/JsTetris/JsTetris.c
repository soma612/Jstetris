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
	srand((unsigned)time(NULL)); // �ð����� ���� ����
	setcursortype(NOCURSOR); //Ŀ�� ������ ����
	resz(80, 22);
	color(WHITE);
	startPage();

	return 0;
}

