#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "GameAlgorithm.h"
#include "HandleData.h"

void getCurrentDirectory(char* currentDir) {
	GetCurrentDirectory(BUFFSIZE, currentDir);
}

bool readSettingFile(Ball ball) {
	char currentDirectory[BUFFSIZE];
	getCurrentDirectory(currentDirectory);

	char section[BUFFSIZE];
	sprintf_s(section, "Ball");
	
	char keyX[BUFFSIZE];
	sprintf_s(keyX, "velocityX");
	char keyY[BUFFSIZE];
	sprintf_s(keyY, "velocityX");

	char settingFile[BUFFSIZE];

	sprintf_s(settingFile, "%s¥¥setting.ini", currentDirectory);

	int veloX = GetPrivateProfileInt(section, keyX, -1, settingFile);
	int veloY = GetPrivateProfileInt(section, keyY, -1, settingFile);

	if (veloX == -1 || veloY == -1) {
		return false;
	}
	else {
		ball.veloX = veloX;
		ball.veloY = veloY;
	}

	return true;
}