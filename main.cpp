#pragma once
#include<iostream>
#include<graphics.h>
#include<Windows.h>
#include<ctime>
#include"Game.h"
using namespace std;
//9  9 10
//16 16 40
//30 16 99

int main()
{
	// the identifier of restart
restart:
	Map map;
	map.Init();
	Game game;
	game.Init();
	// get time
	int t1 = GetTickCount();
	int t2;
	while (true) {
		MOUSEMSG mmsg = GetMouseMsg();
		int* matrix = game.GetMatrix();
		int w = mmsg.x / 20;
		int h = (mmsg.y - 100) / 20;
		if (map.IsVised(h + 1, w + 1))
			continue;
		switch (mmsg.uMsg) {
		case WM_LBUTTONDOWN:
			if (mmsg.x >= 20 && mmsg.x <= 90 && mmsg.y >= 20 && mmsg.y <= 40) {
				closegraph();
				goto restart;
			}
			else if (!game.IsDanger(h, w))
				break;
			else if (map.IsBomb(h + 1, w + 1))
				goto end2;
			map.DFS(h + 1, w + 1, game);
			map.PutNum(game);
			break;
		case WM_RBUTTONUP:
			if (*(matrix + h * 35 + w) == 0) {
				game.PutImg(w * 20, h * 20 + 100, 0);
				*(matrix + h * 35 + w) = 1;
			}
			else if (*(matrix + h * 35 + w) == 1) {
				game.PutImg(w * 20, h * 20 + 100, 1);
				*(matrix + h * 35 + w) = 2;
			}
			else if (*(matrix + h * 35 + w) == 2) {
				game.PutImg(w * 20, h * 20 + 100, 2);
				*(matrix + h * 35 + w) = 0;
			}
			break;
		}
		if (map.NotVis()) {
			goto end1;
		}
	}
end1: 
	t2 = GetTickCount();
	game.ShowTime(t2 - t1);
	Sleep(2000);
	game.PutImg(0, 0, 4, map.getLevel());
	map.Show(1);
	system("pause");
	return 0;
end2:
	t2 = GetTickCount();
	game.ShowTime(t2 - t1);
	Sleep(2000);
	game.PutImg(0, 0, 5, map.getLevel());
	map.Show(0); 
	system("pause");
	return 0;
}
