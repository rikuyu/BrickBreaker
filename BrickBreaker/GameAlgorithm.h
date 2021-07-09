#pragma once

#define SCREEN_WIDTH 26
#define SCREEN_HEIGHT 24

#define FPS 10
#define INTERVAL 1000 / FPS

#define PADDLE_WIDTH 6

#define PADDLE_VEROCITY 2

#define BUFFSIZE 1024

struct Ball {
	int veroX;
	int veroY;
};

void drawScreen();
void resetGame();
void movePaddle();
void controlGame();
void getCurrentDirectory(char* currentDir);
bool readSettingFile(Ball ball);
