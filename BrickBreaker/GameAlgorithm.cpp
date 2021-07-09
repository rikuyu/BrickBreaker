#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GameAlgorithm.h"

int ballX;
int ballY;
int ballVeroX = 1;
int ballVeroY = 1;

int paddleX;
int paddleY;

// �c��u���b�N���J�E���g
int rBlock = SCREEN_HEIGHT * SCREEN_WIDTH;

bool isGameOver = false;

// �Q�[���t�B�[���h�̍��W���`
int field[SCREEN_HEIGHT][SCREEN_WIDTH];

void drawScreen() {
	system("cls");

	if (!isGameOver) {
		// �^�C�g���̕\��
		for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
			if (w == SCREEN_WIDTH / 6) {
				fprintf_s(stdout, "�u���b�N���� ���ړ��Fz�L�[ �E�ړ��F c�L�[");
			}
			else if (w == SCREEN_WIDTH + 1) {
				fprintf_s(stdout, "�@\n");
			}
			else {
				fprintf_s(stdout, "�@");
			}
		}
	}
	else {
		// Gameover�̕�����\��
		for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
			if (w == SCREEN_WIDTH / 2 - 2) {
				fprintf_s(stdout, "\x1b[31mGAME OVER\033[m");
			}
			else if (w == SCREEN_WIDTH + 1) {
				fprintf_s(stdout, "�@\n");
			}
			else {
				fprintf_s(stdout, "�@");
			}
		}
	}
	
	// ��̕ǂ̕`��
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "��");
		}
		else {
			fprintf_s(stdout, "��\n");
		}
	}

	// ���E�̕ǁA�{�[���A�p�h���̕`��
	for (int h = 0; h < SCREEN_HEIGHT; h++) {
		fprintf_s(stdout, "��");
		for (int w = 0; w < SCREEN_WIDTH; w++) {
			if (!isGameOver) {
				if (w == ballX && h == ballY) {
					fprintf_s(stdout, "\x1b[36m��\033[m");
				}
				else if (h == paddleY && w >= paddleX && w < (paddleX + PADDLE_WIDTH)) {
					fprintf_s(stdout, "��");
				}
				else if (w != 0 && w != SCREEN_WIDTH - 1 && h != 0 && field[h][w] == 1) {
					fprintf_s(stdout, "\x1b[33m��\033[m");
				}
				else {
					fprintf_s(stdout, "�@");
				}
			}
			else {
				fprintf_s(stdout, "�@");
			}
			
		}
		fprintf_s(stdout, "��");
		fprintf_s(stdout, "\n");
	}

	// ���̕ǂ̕`��
	for (int w = 0; w < SCREEN_WIDTH + 2; w++) {
		if (w != SCREEN_WIDTH + 1) {
			fprintf_s(stdout, "��");
		}
		else {
			fprintf_s(stdout, "��\n");
		}
	}
}

void resetGame() {

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

void movePaddle() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'z':
			paddleX -= PADDLE_VEROCITY;
			break;
		case 'c':
			paddleX += PADDLE_VEROCITY;
			break;
		}
		// �p�h���̈ړ��͈͐ݒ�
		if (paddleX < 0) {
			paddleX = 0;
		}
		if (paddleX > SCREEN_WIDTH - PADDLE_WIDTH) {
			paddleX = SCREEN_WIDTH - PADDLE_WIDTH;
		}
		drawScreen();
	}
}

void controlGame() {
	// �O��̕`�掞��
	clock_t lastDrawTime = clock();

		while (1) {
			clock_t currentTime = clock();

			if (currentTime >= lastDrawTime + INTERVAL) {

				if (!isGameOver) {
					ballX += ballVeroX;
					ballY += ballVeroY;
				}

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
					&& ballX < paddleX + PADDLE_WIDTH + 1) {

					// �p�h���̉E�����ɏՓ�
					if (ballX < paddleX + PADDLE_WIDTH / 2) {
						ballVeroX = -1;
					}
					else {
						ballVeroX = 1;
					}

					ballVeroY = -1;
				}

				// �{�[���ƃu���b�N�̂����蔻��
				for (int x = ballX - 1; x <= ballX + 1; x++) {
					int y = ballY - 1;

					if (x < 1 || x >= SCREEN_WIDTH - 1 || y < 0) {
						continue;
					}
					if (field[y][x] == 1) {
						field[y][x] = 0;
						ballVeroY = 1;
					}
				}

				drawScreen();

				lastDrawTime = currentTime;

				if (ballY >= SCREEN_HEIGHT - 1) {
					// GameOver����
					isGameOver = true;
				}
			}
			movePaddle();
		}
}