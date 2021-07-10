#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "GameAlgorithm.h"
#include "HandleData.h"

// ボールのプロパティ
int ballX;
int ballY;
int ballVeloX;
int ballVeloY;

// パドルのプロパティ
int paddleX;
int paddleY;

bool isGameClear = false;
bool isGameOver = false;
bool isSuccessWriteFile = false;
bool handleDrawTitle = true;

double clearTime;

// ゲームフィールドの座標を定義
int field[SCREEN_HEIGHT][SCREEN_WIDTH];

// setting.iniを利用したボールの初期化
void initBall() {
	Ball ball;
	ball.veloX = 1;
	ball.veloY = 1;

	if (readSettingFile(ball)) {
		ballVeloX = ball.veloX;
		ballVeloY = ball.veloY;
	}
}

void drawTitle() {
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w == 0) {
			fprintf_s(stdout, "【ボール運び】上の壁にボールを当てる\n ");
			fprintf_s(stdout, "左移動：zキー 右移動： cキー");
		}
		else if (w == SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "　\n");
		}
		else {
			fprintf_s(stdout, "　");
		}
	}
}

void drawGameMsg(const char* msg, char c, char * time) {
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1){
			if (c == 'r' && w == 0) {
				fprintf_s(stdout, "\x1b[31m%s\033[m", msg);
			}else if (c == 'y' && w == 0) {
				fprintf_s(stdout, "\x1b[33m%s\033[m Time：%s(s)",msg, time);
			}
				
		}else {
			fprintf_s(stdout, "　\n");
		}
	}
}

// 上下の壁描画用
void drawWall() {
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "■");
		}
		else {
			fprintf_s(stdout, "■\n");
		}
	}
}

void drawScreen() {
	system("cls");
	char str[BUFFSIZE];
	char t[BUFFSIZE];

	if (isGameClear) {
	
		handleDrawTitle = false;

		snprintf(str, BUFFSIZE, "%f", clearTime);
		strncpy_s(t, str, 4);

		drawGameMsg("GAME CLEAR", 'y', t);

		ballVeloX = 0;
		ballVeloY = 0;

		FILE* fp;
		errno_t error = fopen_s(&fp, "ClearTimes.csv", "a");

		if (fp != 0 && !isSuccessWriteFile) {
			fprintf(fp, "%s(s)\n", t);
			fclose(fp);
			isSuccessWriteFile = true;
		}
	}
	if (!isGameOver) {

		if (handleDrawTitle) {
			// タイトルの表示
			drawTitle();
		}
	}else {
		// Gameoverの文字を表示
		drawGameMsg("GAME OVER", 'r', t);
	}
	
	// 上の壁の描画
	drawWall();

	// 左右の壁、ボール、パドルの描画
	for (int h = 0; h < SCREEN_HEIGHT; h++) {
		fprintf_s(stdout, "■");
		for (int w = 0; w < SCREEN_WIDTH; w++) {
			if (!isGameOver) {
				if (w == ballX && h == ballY) {
					fprintf_s(stdout, "\x1b[36m●\033[m");
				}
				else if (h == paddleY && w >= paddleX && w < (paddleX + PADDLE_WIDTH)) {
					fprintf_s(stdout, "◆");
				}
				else if (h != 0 && h != 2 && h != 4 && field[h][w]) {
					fprintf_s(stdout, "\x1b[33m★\033[m");
				}
				else {
					fprintf_s(stdout, "　");
				}
			}
			else {
				fprintf_s(stdout, "　");
			}
			
		}
		fprintf_s(stdout, "■");
		fprintf_s(stdout, "\n");
	}

	// 下の壁の描画
	drawWall();
}

void initGame() {

	ballY = SCREEN_HEIGHT / 4;

	// パドルの大きさ設定
	paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
	paddleY = SCREEN_HEIGHT - 3;

	for (int i = 0; i < SCREEN_HEIGHT / 4; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			if (i % 2 == 1) {
				field[i][j] = 1;
			}
		}
	}

	drawScreen();
}

// パドルの移動仕様設定
void movePaddle() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'z':
			paddleX -= PADDLE_VELOCITY;
			break;
		case 'c':
			paddleX += PADDLE_VELOCITY;
			break;
		}
		// パドルの移動範囲設定
		if (paddleX < 0) {
			paddleX = 0;
		}
		if (paddleX > SCREEN_WIDTH - PADDLE_WIDTH) {
			paddleX = SCREEN_WIDTH - PADDLE_WIDTH;
		}
		drawScreen();
	}
}

double calcClaerTime(clock_t startTime, clock_t endTime) {
	return (double)(endTime - startTime) / 1000;
}

void controlGame() {
	// 前回の描画時間（画面描画のFPSに使用）
	clock_t lastDrawTime = clock();

	// ゲーム終了タイムの取得
	clock_t startTime = clock();

		while (1) {
			clock_t currentTime = clock();

			if (currentTime >= lastDrawTime + INTERVAL) {

				// ボールの移動
				if (!isGameOver) {
					ballX += ballVeloX;
					ballY += ballVeloY;
				}

				// ボールと壁の衝突判定
				if (ballX <= 0) {
					ballVeloX = 1;
				}
				if (ballX >= SCREEN_WIDTH - 1) {
					ballVeloX = -1;
				}
				if (ballY <= 0) {
					ballVeloY = 1;
				}
				if (ballY >= SCREEN_HEIGHT - 1) {
					ballVeloY = -1;
				}
				// パドルとボールの衝突判定
				if ((ballY == paddleY - 1 || ballY == paddleY)
					&& ballX >= paddleX - 1
					&& ballX < paddleX + PADDLE_WIDTH + 1) {

					// パドルの右半部に衝突
					if (ballX < paddleX + PADDLE_WIDTH / 2) {
						ballVeloX = -1;
					}
					else {
						ballVeloX = 1;
					}

					ballVeloY = -1;
				}

				// ボールとブロックのあたり判定
				for (int x = ballX - 1; x <= ballX + 1; x++) {
					int y = ballY - 1;

					if (x < 0 || x >= SCREEN_WIDTH || y < 0) {
						continue;
					}
					if (field[y][x] == 1) {
						field[y][x] = 0;
						ballVeloY = 1;
					}
				}

				drawScreen();

				lastDrawTime = currentTime;

				if (ballY >= SCREEN_HEIGHT - 1) {
					// GameOver判定
					isGameOver = true;
				}
				if (ballY == 1) {
					// GameClear判定
					isGameClear = true;

					// ゲーム終了タイムの取得
					clock_t endTime = clock();
					clearTime = calcClaerTime(startTime, endTime);
				}
			}
			movePaddle();
		}
}