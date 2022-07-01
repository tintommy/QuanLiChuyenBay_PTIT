#include<iostream>
#include<string>
#include<conio.h>
#include"mylib.h"
#include"structData.h"
#include"veMenu.h"
#include"menu.h"
using namespace std;
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
int main()
{	
	LISTMB listMb;
	LISTCB listCb;
	NODEPTR tree;

	khoiTaoCay(tree);
	khoiTaoLCB(listCb);
	resizeConsole(1600, 800);
	veTenDoAn();
	menu(listMb, listCb, tree);
}
