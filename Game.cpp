#include "Game.h"
#include<Windows.h>
#include<random>
#include<iostream>
#include<ctime>
#include<graphics.h>
#include<conio.h>
#define width 600
#define height 600
using namespace std;
Coor choice;
//界面初始化
void Map::init() {
	initgraph(680, 600);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(RED);
	outtextxy(310, 50, "WECLOME");
	Sleep(1000);
	outtextxy(280, 100, "这里是贪吃蛇的世界");
	Sleep(1000);
	outtextxy(285, 150, "Now,let's begin,ready?");
	Sleep(1000);
	outtextxy(310, 200, "GO GO GO!");
	Sleep(1000);
	cleardevice();
}
//构造界面
void Map::draw() {
	choice.x = 250; choice.y = 150;
	GameInit();
	while (1) {
		int t;
		t = _getch();
		if (t == 224) {
			t = _getch();
			if (t == 72 && choice.y > 150) {
				cleardevice();
				choice.y -= 50;
				GameInit();
			}
			else if (t == 80 && choice.y < 200) {
				cleardevice();
				choice.y += 50;
				GameInit();
			}
		}
		else if (t == 13) {
			if (choice.y == 150)
				break;
			else {
				choice.y = 180;
				cleardevice();
				GameHelp();
				while (1) {
					int t = _getch();
					if (t == 13) {
						choice.y = 150;
						cleardevice();
						GameInit();
						break;
					}
				}
			}
		}
	}
}
void Map::gameInit() {
	settextstyle(30, 0, _T("Consolas"));
	outtextxy(choice.x, choice.y, "->");
	outtextxy(285, 150, "游戏开始");
	outtextxy(285, 200, "游戏帮助");
}
void Map::gameHelp() {
	settextstyle(16, 0, "Consolas");
	outtextxy(choice.x, choice.y, "->");
	outtextxy(285, 150, "↑↓←→表示移动的方向,P键表示暂停，O键表示开始");
	outtextxy(285, 180, "返回");
}
/*
	 蛇的初始化
	 起始长度必须为三
*/
void Snack::init() {
	len = 3;
	speed = 1000 ;
	co.push_back({});
	co.push_back({ 300,300 });
	co.push_back({ 320,300 });
	co.push_back({ 340,300 });
}
//蛇的伸长
void Snack::expand() {
	int dx = co[len].x - co[len - 1].x;
	int dy = co[len].y - co[len - 1].y;
	co.push_back({ co[len].x + dx,co[len].y + dy });
	len++;
	Faster();
}
//蛇的运动，蛇尾擦除，添加蛇头
void Snack::run(int dir) {
	for (int i = len; i >= 2; i--)
		co[i] = co[i - 1];
	if (dir == 1) {
		co[1].y -= 20;
	}
	else if (dir == 2) {
		co[1].y += 20;
	}
	else if (dir == 3) {
		co[1].x -= 20;
	}
	else {
		co[1].x += 20;
	}
	sleep();
}
//判断是否结束
bool Snack::collision() {
	
	for (int i = 2; i <= len; i++) {
		if (co[1].x == co[i].x && co[1].y == co[i].y)
			return true;
	}
	return false;
}
//判断食物是否与蛇相碰
bool Snack::check(int x, int y) {
	for (int i = 1; i <= len; i++) {
		if (co[i].x == x && co[i].y == y)
			return false;
	}
	return true;
}
//加速
void Snack::faster() {
	int length = getLen();
	int sd = getSpeed();
	sd -= (length - 3) * 50;
	if (sd <= 100)
		sd = 100;
	speed = sd;
}
void Snack::sleep() {
	Sleep(getSpeed());
}
bool Snack::eat(int x, int y) {
	if (co[1].x == x && co[1].y == y)
		return true;
	return false;
}
void Food::setxy(Snack& snack) {
	srand(time(NULL));
	int xcoor, ycoor;
	int dx, dy;
	while (1) {
		dx = rand() % 31;
		dy = rand() % 31;
		xcoor = dx * 20;
		ycoor = dy * 20;
		if (snack.Check(xcoor, ycoor))
			break;
	}
	x = xcoor;
	y = ycoor;
}
