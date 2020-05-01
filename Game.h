#pragma once
#include<graphics.h>
#include<ctime>
#include<random>
#include<cstdlib>
using namespace std;
#define size 20
class Game {
private:
	//pictures
	IMAGE bomb, flag, win, fail, wall, unknow, bomb1;
	int bombSum = 0;
	int width[4] = { 0,9,16,30 };
	int matrix[35][35] = { 0 };
	//to record the time
	TCHAR time[20];
	MOUSEMSG mmsg;
	int mmsgx;
	int mmsgy;
	// return a message of a mouse hit
	void init();
	// to judge whther it is covered flag.jpg or unknow.jpg
	bool isDanger(int i, int j);
	// return the adress of matrix[0][0]
	int* getMatrix();
	void putImg(int i, int j, int c, int level);
	// show the use of time
	void showTime(int t);
public:
	void Init() {
		init();
	}
	bool IsDanger(int i, int j) {
		return isDanger(i, j);
	}
	int* GetMatrix() {
		return getMatrix();
	}
	void PutImg(int i, int j, int c, int level) {
		putImg(i, j, c, level);
	}
	void PutImg(int i, int j, int c) {
		putImg(i, j, c, 0);
	}
	void ShowTime(int t) {
		showTime(t);
	}
};

class Map {
private:
	int matrix[35][35] = { 0 };
	bool vis[35][35] = { 0 };
	int level;
	int width[4] = { 0,9,16,30 };
	int height[4] = { 0,9,16,16 };
	int bombSum[4] = { 0,10,40,99 };
	IMAGE bomb, flag, zero, one, two, three, four, five, six, seven, eight, win, fail, wall, unknow, bomb1;
	void init();
	// init the matrix
	void initMatrix();
	void putimg(int img, int x, int y);
	void putwall();
	// search
	void dfs(int i, int j, Game& game);
	// to judge whether it is visited
	bool isvised(int i, int j);
	// put the image of numbers
	void putNum(Game& game);
	// to judge whether it is a bomb
	bool isBomb(int i, int j);
	// game over and show
	void show(bool win);
	// use for checking if you win
	bool notVis();
public:
	void Init() {
		init();
	}
	void DFS(int i, int j, Game& game) {
		dfs(i, j, game);
	}
	bool IsVised(int i, int j) {
		return isvised(i, j);
	}
	void Putwall() {
		putwall();
	}
	void PutNum(Game& game) {
		putNum(game);
	}
	bool IsBomb(int i, int j) {
		return isBomb(i, j);
	}
	int getLevel() {
		return level;
	}
	void Show(bool win) {
		show(win);
	}
	int GetBombSum() {
		return bombSum[level];
	}
	int* GetMatrix() {
		return &matrix[0][0];
	}
	bool NotVis() {
		return notVis();
	}
};



