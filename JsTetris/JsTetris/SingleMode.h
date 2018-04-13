#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <process.h>
#include "tools.h"

// blockEvent.h
void createNewBlock();
void moveBlock(int dx, int dy);
void turnBlock(boolean isRight);
void holdingBlock();
void removePreViewBlock();
void createPreViewBlock(int x, int y, int block, int motion);
boolean checkPreViewWalls(int block, int motion, int y, int dx, int dy);
boolean checkWalls(int block, int motion, int dx, int dy);
void changeBlockToWalll();
void checkAllLine();
void clearLine(int line);
void removeBlock();
void createBlock(int x, int y, int block, int motion);
void fastDown();
void selectColor(int block);
void saveBlock(int x, int y, int block, int motion);
void initBlock();

//printInfo.h
void loadStage();
void printInfo();
void printNextBlock();
void printHoldBlock();
void printGameOver();
void printGameStart();
void printGamePause();

// SinglePlay.h
int PlayerMoveAction();
void initGame();
void playing();
void checkScore();
// SinglePlay.h -> Threads
void listenMsg();
int autoDownBlock();

// 각 페이지들
void startPage();
int pausePage();
void configPage();

CRITICAL_SECTION cs;
HANDLE thread1;
HANDLE thread2;

int stage[22][12];
int holdBlock = -1;
int holdMotion = 0;
int save_x = STARTX;
int save_y = STARTY;
int save_block = 0;
int save_motion = 0;
int save_pv_y = 0;
int save_pv_x = 0;
int score = 0;
int combo = 0;
int nextBlock[2] = { 0,0 };
int leveltime = 1000;

boolean isTurnMode = TRUE;
boolean isSpeedMode = FALSE;
boolean isPreViewMode = FALSE;
boolean msgState = FALSE;
boolean isBlockCreated = FALSE;
boolean ishold = TRUE;
boolean isShaking = TRUE;
boolean isConnected = TRUE;

