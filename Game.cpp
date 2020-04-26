#include "Game.h"
#include<Windows.h>
#include<random>
#include<iostream>
#include<ctime>
using namespace std;
int width;//地图宽度
int height;//地图高度
int level;//难度等级
//光标跳跃
void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(handle, coord);
}
//界面初始化
void Map::init() {
	for (int i = 0; i <= 25; i++) {
		for (int j = 0; j <= 100; j++) {
			if (i == 0 || i == 25)
				cout << "=";
			else
				if (j == 0 || j == 100) {
					gotoxy(j, i);
					cout << "|";
				}
		}
		cout << endl;
	}
	gotoxy(46, 6);
	cout << "WELCOME";
	Sleep(1000);
	gotoxy(41, 8);
	cout << "这里是贪吃蛇的世界";
	Sleep(1000);
	gotoxy(39, 10);
	cout << "↑↓←→表示移动的方向";
	Sleep(1000);
	gotoxy(38, 12);
	cout << "P键表示暂停，O键表示开始";
	Sleep(1000);
	gotoxy(37, 14);
	cout << "请输入难度等级，只有三级哦:";
	cin >> level;
	gotoxy(40, 16);
	cout << "请输入地图宽度:";
	cin >> width;
	gotoxy(40, 18);
	cout << "请输入地图高度:";
	cin >> height;
	Sleep(1000);
	system("cls");
	gotoxy(43, 14);
	cout << "Now,let's begin,ready?";
	Sleep(2000);

	gotoxy(43, 16);
	cout << "GO GO GO!";
	Sleep(2000);
	gotoxy(0, 0);
	system("cls");
}
//构造界面
void Map::draw() {
	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= width; j++) {
			if (i == 0 || i == height)
				cout << "=";
			else
				if (j == 0 || j == width) {
					gotoxy(j, i);
					cout << "|";
				}
		}
		cout << endl;
	}
}
/*‘
     蛇的初始化
	 起始长度必须为三
*/
void Snack::init() {
	len = 3;
	speed = 1000 / level;
	co.push_back({});
	co.push_back({ width / 2,height / 2 });
	co.push_back({ width / 2 + 1,height / 2 });
	co.push_back({ width / 2 + 2,height / 2 });
	for (int i = 1; i <= 3; i++) {
		gotoxy(co[i].x, co[i].y);
		cout << "*";
	}
}
//蛇的伸长
void Snack::expand() {
	int dx = co[len].x - co[len - 1].x;
	int dy = co[len].y - co[len - 1].y;
	co.push_back(Coor{ co[len].x + dx,co[len].y + dy });
	len++;
	gotoxy(co[len].x, co[len].y);
	cout << "*";
}
//蛇的运动，蛇尾擦除，添加蛇头
void Snack::run(int dir) {
	gotoxy(co[len].x, co[len].y);
	cout << " ";
	for (int i = len; i >= 2; i--)
		co[i] = co[i - 1];
	if (dir == 1) {
		co[1].y -= 1;
	}
	else if (dir == 2) {
		co[1].y += 1;
	}
	else if (dir == 3) {
		co[1].x -= 1;
	}
	else {
		co[1].x += 1;
	}
	gotoxy(co[1].x, co[1].y);
	cout << "*";
	sleep();
}
//判断是否结束
bool Snack::collision() {
	if (co[1].x == 0 || co[1].x == width || co[1].y == 0 || co[1].y == height)
		return true;
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
	sd -= (length - 3) * 100;
	if (sd <= 100)
		sd = 100;
	speed = sd;
}
void Snack::sleep() {
	Sleep(getSpeed());
}
bool Snack::eat(int x,int y) {
	if (co[1].x == x && co[1].y == y)
		return true;
	return false;
}
void Food::setxy(Snack& snack) {
	srand(time(NULL));
	int xcoor, ycoor;
	while (1) {
		xcoor = rand() % (width - 1) + 1;
		ycoor = rand() % (height - 1) + 1;
		if (snack.Check(xcoor, ycoor))
			break;
	}
	x = xcoor;
	y = ycoor;
	gotoxy(xcoor, ycoor);
	cout << "O";
}
