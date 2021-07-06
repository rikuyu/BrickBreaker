#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

#define FPS 10
#define INTERVAL 1000 / FPS

#define PADDLE_WIDTH 6

#define PADDLE_VEROCITY 2

int ballX;
int ballY;
int ballVeroX = 1;
int ballVeroY = 1;

int paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
int paddleY = SCREEN_HEIGHT - 3;

void drawScreen() {
	system("cls");
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "¡");
		}
		else {
			fprintf_s(stdout, "¡\n");
		}
	}

	for (int h = 0; h < SCREEN_HEIGHT; h++) {
		fprintf_s(stdout, "¡");
		for (int w = 0; w < SCREEN_WIDTH; w++) {
			if (w == ballX && h == ballY) {
				fprintf_s(stdout, "œ");
			}
			else if (h == paddleY && w >= paddleX && w < (paddleX + PADDLE_WIDTH)) {
				fprintf_s(stdout, "Ÿ");
			}
			else {
				fprintf_s(stdout, "@");
			}

		}
		fprintf_s(stdout, "¡");
		fprintf_s(stdout, "\n");
	}

	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "¡");
		}
		else {
			fprintf_s(stdout, "¡\n");
		}
	}
}

int main() {
	// ‘O‰ñ‚Ì•`‰æŽžŠÔ
	clock_t lastDrawTime = clock();
	
	while (1){
		clock_t currentTime = clock();
		if (currentTime >= lastDrawTime + INTERVAL) {

			ballX += ballVeroX;
			ballY += ballVeroY;

			if (ballX <= 0) {
				ballVeroX = 1;
			}
			if (ballX >= SCREEN_WIDTH - 1) {
				ballVeroX = -1;
			}
			if (ballY <= 0) {
				ballVeroY = 1;
			}
			if (ballY >= SCREEN_HEIGHT - 1) {
				ballVeroY = -1;
			}

			drawScreen();

			lastDrawTime = currentTime;
		}
		
		if (_kbhit()) {
			switch (_getch()) {
				case 'z':
					paddleX -= PADDLE_VEROCITY;
					break;
				case 'c':
					paddleX += PADDLE_VEROCITY;
					break;
				}

			if (paddleX < 0) {
				paddleX = 0;
			}
			if (paddleX > SCREEN_WIDTH - PADDLE_WIDTH) {
				paddleX = SCREEN_WIDTH - PADDLE_WIDTH;
			}
			drawScreen();
		}
	}

	_getch();
}