#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 24

#define FPS 10
#define INTERVAL 1000 / FPS

#define PADDLE_WIDTH 6

#define PADDLE_VEROCITY 2

int ballX;
int ballY;
int ballVeroX = 1;
int ballVeroY = 1;

int paddleX;
int paddleY;

// �Q�[���t�B�[���h�̍��W���`
int field[SCREEN_HEIGHT][SCREEN_WIDTH];

void drawScreen() {
	system("cls");
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "��");
		}
		else {
			fprintf_s(stdout, "��\n");
		}
	}

	for (int h = 0; h < SCREEN_HEIGHT; h++) {
		fprintf_s(stdout, "��");
		for (int w = 0; w < SCREEN_WIDTH; w++) {
			if (w == ballX && h == ballY) {
				fprintf_s(stdout, "��");
			}
			else if (h == paddleY && w >= paddleX && w < (paddleX + PADDLE_WIDTH)) {
				fprintf_s(stdout, "��");
			}
			else if (w != 0 && w != SCREEN_WIDTH - 1 && h != 0 && field[h][w]) {
				fprintf_s(stdout, "��");
			}
			else {
				fprintf_s(stdout, "�@");
			}

		}
		fprintf_s(stdout, "��");
		fprintf_s(stdout, "\n");
	}

	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "��");
		}
		else {
			fprintf_s(stdout, "��\n");
		}
	}
}

void resetGame(){

	ballY = SCREEN_HEIGHT / 4;

	ballVeroY = 1;

	paddleX = (SCREEN_WIDTH - PADDLE_WIDTH) / 2;
	paddleY = SCREEN_HEIGHT - 3;

	for (int i = 0; i < SCREEN_HEIGHT / 4; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			field[i][j] = 1;
		}
	}

	drawScreen();
}
int main() {

	resetGame();

	// �O��̕`�掞��
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
			// �p�h���ƃ{�[���̏Փ˔���
			if (ballY == paddleY - 1 
				&& ballX >= paddleX - 1 
				&& ballX < paddleX + PADDLE_WIDTH	+ 1) {
				
				// �p�h���̉E�����ɏՓ�
				if (ballX < paddleX + PADDLE_WIDTH / 2) {
					ballVeroX = -1;
				}
				else{
					ballVeroX = 1;
				}

				ballVeroY = -1;
			}

			for (int x = ballX - 1; x <= ballX + 1; x++) {
				int y = ballY - 1;

				if (x < 1 || x >= SCREEN_WIDTH - 1 || y < 0) {
					continue;
				}
				if (field[y][x]) {
					field[y][x] = 0;
					ballVeroY = 1;
				}
			}

			drawScreen();

			lastDrawTime = currentTime;

			if (ballY >= SCREEN_HEIGHT - 1) {
				resetGame();
			}
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