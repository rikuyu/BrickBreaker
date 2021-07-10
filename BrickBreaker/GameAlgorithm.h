#pragma once

#define SCREEN_WIDTH 14
#define SCREEN_HEIGHT 24

#define FPS 10
#define INTERVAL 1000 / FPS

#define PADDLE_WIDTH 6

#define PADDLE_VELOCITY 2

struct Ball {
	int veloX;
	int veloY;
};

void initBall();		// ボールの初期化
void drawScreen();		// 画面描画
void initGame();		// パドル、フィールド設定
void movePaddle();		// パドルの移動設定
void controlGame();		// ゲームの制御
void drawTitle();		// タイトル、操作方法の描画
void drawWall();		// 上下の壁の描画
// GAME OVER などのメッセージ表示用
void drawGameMsg(const char * msg, char c, char * time);

