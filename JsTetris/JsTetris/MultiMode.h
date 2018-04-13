#pragma once

boolean isPause = TRUE;

//서버&클라이언트
int server(a);
int client();

//MultiMode.h
int startMultiMode();
int chosePlayerCount();

//MultiPlay.h
int mAutoDownBlock();
void mListenMsg();
int playMultiGame();
void multiPlaying();
int mPlayerMoveAction();

// mPrintInfo.h
void mloadStage();
void mPrintNextBlock();
void mPrintHoldBlock();
void mPrintInfo();
void mPrintGameOver();
void mPrintOtherPlayer();

// mBlockEvent.h
void mInitBlock();
void mCreateNewBlock();
void mMoveBlock(int dx, int dy);
void mTurnBlock(boolean isRight);
void mHoldingBlock();
void mRemovePreViewBlock();
void mCreatePreViewBlock(int x, int y, int block, int motion);
boolean mCheckPreViewWalls(int block, int motion, int x, int y, int dy);
boolean mCheckWalls(int block, int motion, int dx, int dy);
void mChangeBlockToWalll();
void mCheckAllLine();
void mClearLine(int line);
void mRemoveBlock();
void mCreateBlock(int x, int y, int block, int motion);
void mFastDown();
void mSaveBlock(int x, int y, int block, int motion);