#pragma once
#include<vector>
#include<graphics.h>
using namespace std;

//坐标结构体
struct Coor {
	int x;
	int y;	
};

//地图类
class Map
{
private:
	//初始化地图
	void init();
	//绘制界面
	void draw();
	void gameInit();
	void gameHelp();
public:
	void Init() {
		init();
	}
	void Draw() {
		draw();
	}
	void GameInit() {
		gameInit();
	}
	void GameHelp() {
		gameHelp();
	}
};
class Snack
{
private:
	int len;
	int speed;
	void init();
	void expand();
	bool check(int x, int y);
	void run(int dir);
	bool collision();
	void faster();
	void sleep();
	bool eat(int x, int y);
public:
	vector<Coor> co;
	Snack() = default;
	int getLen() {
		return len;
	}
	int getSpeed() {
		return speed;
	}
	void Init() {
		init();
	}
	void Expand() {
		expand();
		faster();
	}
	bool Check(int x, int y) {
		return check(x, y);
	}
	void Run(int dir) {
		run(dir);
	}
	bool Collision() {
		return collision();
	}
	void Faster() {
		faster();
	}
	bool Eat(int x, int y) {
		return eat(x, y);
	}
};
class Food
{
private:
	int x;//横坐标
	int y;//纵坐标
	void setxy(Snack& snack);
public:
	Food() = default;
	Food(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void Setxy(Snack& snack) {
		setxy(snack);
	}
	Coor getxy() {
		return Coor({ this->x,this->y });
	}
};



