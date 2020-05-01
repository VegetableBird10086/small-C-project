#pragma once
#include "Game.h"
#include<graphics.h>
using namespace std;
/*
	this function is used to generate a matrix with bomb
	-1 stands for bomb 
	discrupt it
	and find out how many mines there are around a certain location 
*/
void Map::initMatrix() {
	srand(time(NULL));
	int sum = 0;
	bool fg = false;
	//generate a matrix
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			matrix[i][j] = -1;
			sum++;
			if (sum == bombSum[level]) {
				fg = true;
				break;
			}
		}
		if (fg)
			break;
	}
	// discrupt it
	for (int i = 0; i <= 100000; i++) {
		int x1 = rand() % (height[level]) + 1;
		int x2 = rand() % (height[level]) + 1;
		int y1 = rand() % (width[level]) + 1;
		int y2 = rand() % (width[level]) + 1;
		int temp = matrix[x1][y1];
		matrix[x1][y1] = matrix[x2][y2];
		matrix[x2][y2] = temp;
	}
	// find out how many mines there are around a certain location 
	int d[3] = { -1,0,1 };// the position matrix
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			for (int x = 0; x < 3; x++) {
				for (int y = 0; y < 3; y++) {
					if ((d[x] == 0 && d[y] == 0) || matrix[i][j] == -1)
						continue;
					if (matrix[i + d[x]][j + d[y]] == -1)
						matrix[i][j]++;
				}
			}
		}
	}
}
/*
	this function is used to get level input by players
	and do some basic work
*/
void Map::init() {
	while (1) {
		char s[10];
		InputBox(s, 10, "请输入难度");
		sscanf_s(s, "%d", &level);
		if (level <= 3 && level >= 1)
			break;
	}
	loadimage(&bomb, "bomb.jpg", size, size);
	loadimage(&zero, "0.jpg", size, size);
	loadimage(&one, "1.jpg", size, size);
	loadimage(&two, "2.jpg", size, size);
	loadimage(&three, "3.jpg", size, size);
	loadimage(&four, "4.jpg", size, size);
	loadimage(&five, "5.jpg", size, size);
	loadimage(&six, "6.jpg", size, size);
	loadimage(&seven, "7.jpg", size, size);
	loadimage(&eight, "8.jpg", size, size);
	loadimage(&win, "win.png", size, size);
	loadimage(&fail, "fail.png", size, size);
	loadimage(&flag, "flag.jpg", size, size);
	loadimage(&unknow, "unknow.jpg", size, size);
	loadimage(&wall, "wall.jpg", size, size);
	loadimage(&bomb1, "bomb1.jpg", size, size);
	initMatrix();
	initgraph(width[level] * size, height[level] * size + 100);
	putwall();
	settextcolor(WHITE);
	settextstyle(20, 0, _T("Consolas"));
	outtextxy(20, 20, "重新开始");
}
// put wall.jpg where is not visted
void Map::putwall() {
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			if (!vis[j][i]) {
				putimage((j - 1) * size, (i - 1) * size + 100, &wall);
			}

		}
	}
}
// put num.jpg where has been visted but not danger
// danger means it is covered by flag.jpg or unknow.jpg
void Map::putNum(Game& game) {
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			if (vis[i][j] && game.IsDanger(i - 1, j - 1)) {
				putimg((j - 1) * size, (i - 1) * size + 100, matrix[i][j]);
			}
		}
	}
}
void Map::putimg(int x, int y, int img) {
	if (img == -1)
		putimage(x, y, &bomb);
	else if (img == 0)
		putimage(x, y, &zero);
	else if (img == 1)
		putimage(x, y, &one);
	else if (img == 2)
		putimage(x, y, &two);
	else if (img == 3)
		putimage(x, y, &three);
	else if (img == 4)
		putimage(x, y, &four);
	else if (img == 5)
		putimage(x, y, &five);
	else if (img == 6)
		putimage(x, y, &six);
	else if (img == 7)
		putimage(x, y, &seven);
	else if (img == 8)
		putimage(x, y, &eight);
	else if (img == 9)
		putimage(x, y, &wall);
	else if (img == 10)
		putimage(x, y, &bomb1);
}
// search
void Map::dfs(int i, int j, Game& game) {
	int dx[4] = { 1,0,-1,0 };
	int dy[4] = { 0,1,0,-1 };
	if (matrix[i][j] == -1)
		return;
	else if (matrix[i][j] >= 1) {
		vis[i][j] = 1;
		return;
	}
	else if (game.IsDanger(i, j)) {
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				if (i + dx[x] >= 1 && i + dx[x] <= height[level]) {
					if (j + dy[y] >= 1 && j + dy[y] <= width[level]) {
						if (!vis[i + dx[x]][j + dy[y]]) {
							vis[i + dx[x]][j + dy[y]] = 1;
							dfs(i + dx[x], j + dy[y], game);
						}
					}
				}
			}
		}
	}
}
// to judge whether it is visited
bool Map::isvised(int i, int j) {
	return vis[i][j];
}
// to judge whether it is a bomb
bool Map::isBomb(int i, int j) {
	if (matrix[i][j] == -1)
		return true;
	else 
		return false;
}
// game over and show
void Map::show(bool win) {
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			if (matrix[i][j] == -1 && !win)
				putimg((j - 1) * size, (i - 1) * size + 100, 10);
			else if (matrix[i][j] == -1 && win)
				putimg((j - 1) * size, (i - 1) * size + 100, matrix[i][j]);
			else
				putimg((j - 1) * size, (i - 1) * size + 100, matrix[i][j]);
		}
	}
}
// to judge whether the player has won
bool Map::notVis() {
	int sum = 0;
	for (int i = 1; i <= height[level]; i++) {
		for (int j = 1; j <= width[level]; j++) {
			if (vis[i][j] == 0)
				sum++;
		}
	}
	if (sum == bombSum[level])
		return true;
	else 
		return false;
}
// to do some basic work
void Game::init() {
	loadimage(&bomb, "bomb.jpg", size, size);
	loadimage(&flag, "flag.jpg", size, size);
	loadimage(&unknow, "unknow.jpg", size, size);
	loadimage(&wall, "wall.jpg", size, size);
	loadimage(&bomb1, "bomb1.jpg", size, size);
}

bool Game::isDanger(int i, int j) {
	if (matrix[i][j] == 0)
		return true;
	else
		return false;
}
int* Game::getMatrix() {
	return &matrix[0][0];
}
void Game::putImg(int i, int j, int c, int level) {
	switch (c) {
	case 0:
		putimage(i, j, &flag);
		break;
	case 1:
		putimage(i, j, &unknow);
		break;
	case 2:
		putimage(i, j, &wall);
		break;
	case 3:
		putimage(i, j, &bomb1);
		break;
	case 4:
		loadimage(&win, "win.png", width[level] * 20, 100);
		putimage(i, j, &win);
		break;
	case 5:
		loadimage(&fail, "fail.png", width[level] * 20, 100);
		putimage(i, j, &fail);
		break;
	}
}
void Game::showTime(int t) {
	int temp = t;
	int k = 0;
	while (temp) {
		temp /= 10;
		k++;
	}
	int s = 0;
	time[k + 2] = '\0';
	time[k + 1] = 's';
	while (t) {
		if (s == 3)
			time[k--] = '.';
		time[k--] = t % 10 + '0';
		t /= 10;
		s++;
	}
	outtextxy(20, 60, time);
}
