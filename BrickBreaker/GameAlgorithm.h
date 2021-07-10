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

void initBall();		// �{�[���̏�����
void drawScreen();		// ��ʕ`��
void initGame();		// �p�h���A�t�B�[���h�ݒ�
void movePaddle();		// �p�h���̈ړ��ݒ�
void controlGame();		// �Q�[���̐���
void drawTitle();		// �^�C�g���A������@�̕`��
void drawWall();		// �㉺�̕ǂ̕`��
// GAME OVER �Ȃǂ̃��b�Z�[�W�\���p
void drawGameMsg(const char * msg, char c, char * time);

