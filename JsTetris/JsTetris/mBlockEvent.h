#pragma once
#include "MultiMode.h"

#define PLAYER1_X 16

void mInitBlock() {
	mRemoveBlock();
	memcpy(stage, stageData, sizeof(stage));
	save_x = STARTX;
	save_y = STARTY;
	holdBlock = -1;
	save_block = 0;
	save_motion = 0;
	score = 0;
	nextBlock[0] = 0;
	nextBlock[1] = 0;
	leveltime = 1000;
	isBlockCreated = FALSE;
	nextBlock[0] = random(7);
	nextBlock[1] = random(7);

}



void mCreateNewBlock() {
	isBlockCreated = TRUE;
	int newBlock = nextBlock[0];
	if (isPreViewMode || score < 15000) mCreatePreViewBlock(STARTX, STARTY, newBlock, 0);
	mCreateBlock(STARTX, STARTY, newBlock, 0);
	saveBlock(STARTX, STARTY, newBlock, 0);
	nextBlock[0] = nextBlock[1];
	nextBlock[1] = random(7); //rand 함수 적용
	mPrintNextBlock();
	if (checkWalls(save_block, save_motion, 0, 0)) {
		mPrintGameOver();
		while (isPause) { delay(1); }
		mInitBlock();

	}
}
void mMoveBlock(int dx, int dy) {
	if (mCheckWalls(save_block, save_motion, dx, dy)) {
		if (dy == 1) mChangeBlockToWalll();
		return;
	}
	else {
		mRemoveBlock();
		if (isPreViewMode || score < 15000) {
			mRemovePreViewBlock();
			mCreatePreViewBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);
		}
		mCreateBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);
		mSaveBlock(save_x + dx * 2, save_y + dy, save_block, save_motion);

	}
}
void mTurnBlock(boolean isRight) {
	int next_motion;
	if (isRight) next_motion = save_motion == 3 ? 0 : save_motion + 1;
	else next_motion = save_motion == 0 ? 3 : save_motion - 1;
	if (mCheckWalls(save_block, next_motion, 0, 0)) return;
	mRemoveBlock();
	if (isPreViewMode || score < 15000) {
		mRemovePreViewBlock();
		mCreatePreViewBlock(save_x, save_y, save_block, next_motion);
	}

	mCreateBlock(save_x, save_y, save_block, next_motion);
	mSaveBlock(save_x, save_y, save_block, next_motion);

}
void mHoldingBlock() {
	if (holdBlock != -1) {
		mRemoveBlock();
		int tmp = save_block;
		int tmp2 = save_motion;
		save_block = holdBlock;
		save_motion = holdMotion;
		int checkx = 0;
		while (mCheckWalls(save_block, save_motion, checkx, 0)) { checkx += save_x > STARTX ? -1 : 1; }
		mMoveBlock(checkx, 0);
		holdBlock = tmp;
		holdMotion = tmp2;
		mloadStage();
		mMoveBlock(0, 0);
	}
	else {
		holdBlock = save_block;
		holdMotion = save_motion;
		mPrintHoldBlock();
		mRemoveBlock();
		mRemovePreViewBlock();
		isBlockCreated = FALSE;
	}
}
void mRemovePreViewBlock() {
	int i;
	for (i = 0; i < 4; i++) {
		putsxy((save_pv_x + blocks[save_block][save_motion][i][0] * 2), save_pv_y + blocks[save_block][save_motion][i][1], "  ");
	}
}
void mCreatePreViewBlock(int x, int y, int block, int motion) {
	int pvY = 1;
	int i;
	while (!mCheckPreViewWalls(block, motion, x, y, pvY)) { ++pvY; }
	selectColor(block);
	for (i = 0; i < 4; i++) {
		putsxy((x + blocks[block][motion][i][0] * 2), y + pvY - 1 + blocks[block][motion][i][1], "□");
	}
	save_pv_x = x;
	save_pv_y = y + pvY - 1;
}
boolean mCheckPreViewWalls(int block, int motion, int x, int y, int dy) {
	int i;
	boolean result = FALSE;
	for (i = 0; i<4; i++) {
		if (stage[y + (blocks[block][motion][i][1] + dy)][x / 2 - 8 + (blocks[block][motion][i][0])] != 8) {
			result = TRUE;
			break;
		}
	}
	return result;
}



boolean mCheckWalls(int block, int motion, int dx, int dy) {
	int i;
	boolean result = FALSE;
	for (i = 0; i<4; i++) {
		if (stage[(save_y + blocks[block][motion][i][1] + dy)][save_x / 2 - 8 + (blocks[block][motion][i][0]) + dx] != 8) {
			result = TRUE;
			break;
		}
	}
	return result;
}
void mChangeBlockToWalll() {
	//stage 에 현재 블록의 위치값을 전부 2로
	int i;
	for (i = 0; i<4; i++) {
		stage[(save_y + blocks[save_block][save_motion][i][1])][(save_x / 2 - 8 + blocks[save_block][save_motion][i][0])] = save_block;
	}
	mRemoveBlock();
	isBlockCreated = FALSE;
	ishold = TRUE;
	mloadStage();
	mCheckAllLine();
	//isBlockCreated = FALSE;
}
void mCheckAllLine() {
	int i, j;
	int count = 0;
	boolean isLineFull = TRUE;
	for (i = 20; i >= 1; i--) {
		for (j = 1; j <= 10; j++) {
			if (stage[i][j] == 8) {
				isLineFull = FALSE;
				break;
			}
			else isLineFull = TRUE;
		}
		if (isLineFull) {
			mClearLine(i++);
			count++;
		}
	}
	if (count == 0) {
		combo = 0;
		score += 5;
		mPrintInfo();
	}
	if (count == 1) combo = combo > 6 ? 6 : combo + 1;

	if (count > 1) {
		combo = combo > 6 ? 6 : combo + 1;
		score += count * 100;

		color(WHITE);
		EnterCriticalSection(&cs);
		gotoxy(MSG_X, MSG_Y); printf("라인보너스");
		gotoxy(MSG_X, MSG_Y + 1); printf("+%d", count * 100);

		if (count == 4) {
			color(PINK);
			gotoxy(MSG_X, MSG_Y + 4); printf("테트리스!!");
			gotoxy(MSG_X, MSG_Y + 5); printf("+%d", 300);
			score += 300;
		}
		LeaveCriticalSection(&cs);
		msgState = TRUE;
		mPrintInfo();
	}
	if (combo > 1) {
		int comboBonus = 0;
		gotoxy(MSG_X, MSG_Y + 2);
		switch (combo) {
		case 2: color(WHITE); printf("COMBO"); comboBonus = 200; break;
		case 3: color(GREEN); printf("DOUBLE!"); comboBonus = 350; break;
		case 4: color(BLUE); printf("TRIPLE!!"); comboBonus = 500; break;
		case 5: color(RED); printf("GREAT!!!"); comboBonus = 750; break;
		case 6: color(YELLOW);  printf("FANTASTIC!!!!"); comboBonus = 1000; break;
		}
		gotoxy(MSG_X, MSG_Y + 3); printf("+%d", comboBonus);
		score += comboBonus;
		msgState = TRUE;
		mPrintInfo();
	}
}

void mClearLine(int line) {
	int i, j;
	for (i = line - 1; i >= 1; i--) {
		for (j = 1; j <= 10; j++) {
			stage[i + 1][j] = stage[i][j];
			stage[i][j] = 8;
		}
	}
	score += 100;
	mPrintInfo();
	mloadStage();
}

void mRemoveBlock() {
	int i;
	for (i = 0; i < 4; i++) {
		putsxy((save_x + blocks[save_block][save_motion][i][0] * 2), save_y + blocks[save_block][save_motion][i][1], "  ");
	}
}
void mCreateBlock(int x, int y, int block, int motion) {
	int i;

	selectColor(block);
	for (i = 0; i < 4; i++) {
		putsxy((x + blocks[block][motion][i][0] * 2), y + blocks[block][motion][i][1], "■"); // x,y 위치부터 block에 저장된 block값과 motion값의 블록을 +x +y 위치값을 더한 4개의 ■를 출력 
	}

}
void mFastDown() {
	while (isBlockCreated) {
		mMoveBlock(0, 1);
	}
}
void mSaveBlock(int x, int y, int block, int motion) {
	save_x = x;
	save_y = y;
	save_block = block;
	save_motion = motion;
}
