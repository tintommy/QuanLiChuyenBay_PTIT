#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include"veMenu.h"
#include"structData.h"
#include"datHuyVe.h"
#include"mayBay.h"
#include"chuyenBay.h"
#include"danhSachHK.h"
#include"xuLiFile.h"
#include"thongKeLuotBay.h"
#include"timChuyenBayTheoNgayGioVaNoiDen.h"
#include"inVeTrong.h"

#define XMAX 50
#define YMAX 10
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define DELETE 83
#define SPACE 42
#define F1 59
#define F2 60
#define F4 62
#define F5 63
#define XMIN 18 
#define YMIN 15 
#define SMIN 60 
using namespace std;

int xacNhanThoatChuongTrinh()
{
	int x = 81;
	SetColor(45);
	SetBGColor(7);  
	gotoxy(66, 15); cout << "                                                  ";
	gotoxy(66, 16); cout << "    BAN CO MUON THOAT KHOI CHUONG TRINH KHONG?    ";
	gotoxy(66, 17); cout << "                                                  ";
	gotoxy(66, 18); cout << "               CO                KHONG            ";
	gotoxy(66, 19); cout << "                                                  ";
	SetBGColor(0);
	int keyhit;
	do {
		gotoxy(81, 18);
		SetColor(0);
		SetBGColor(7);
		switch (x)
		{
		case 81: gotoxy(81, 18); cout << "CO"; break;
		case 99: gotoxy(99, 18); cout << "KHONG"; break;
		}
		keyhit = getch();
		if (keyhit == LEFT)
		{
			gotoxy(81, 18);
			SetColor(45);
			switch (x)
			{
			case 81: gotoxy(81, 18); cout << "CO"; ; break;
			case 99: gotoxy(99, 18); cout << "KHONG"; ; break;
			}
			x -= 18;
			if (x != 81)
			{
				x = 99;
			}
		}
		else if (keyhit == RIGHT)
		{
			gotoxy(99, 18);
			SetColor(45);
			switch (x)
			{
			case 81: gotoxy(81, 18); cout << "CO"; ; break;
			case 99:  gotoxy(99, 18); cout << "KHONG"; ; break;
			}
			x += 18;
			if (x != 99)
			{
				x = 81;
			}
		}
		else if (x == 81 && keyhit == ENTER)
		{
			gotoxy(XMIN + 62, 20);
			cout << "   THOAT THANH CONG   ";
			Sleep(500);
			SetBGColor(0);
			return 1;
		}
		else if (x == 99 && keyhit == ENTER)
		{
			SetBGColor(0);
			system("cls");
			return 0;
		}
	} while (true);
}

void menu(LISTMB listMb, LISTCB listCb, NODEPTR tree)
{
	
MENU:
	loadFileDanhSachChuyenBay(listCb);
	loadFileDanhSachMayBay(listMb);
	loadFileDanhSachVe(listCb);
	loadFileHK(tree);
	system("cls");
	veMenu();
	string thaoTac[8] = { "1.Cap nhat danh sach cac may bay","2.Cap nhat chuyen bay","3.Dat ve","4.Huy ve",
		"5.In danh sach cac hanh khach theo ma chuyen bay","6.In danh sach cac chuyen bay khoi hanh theo ngay dd/mm/yyyy den noi XXXX","7.In danh sach cac ve con trong cua 1 chuyen bay","8.Thong ke so luot thuc hien chuyen bay" };
	int x = XMAX + 3;
	int y = YMAX + 1;
	int x1 = x;
	int y1 = y;
	for (int i = 0; i < 8; i++)
	{
		gotoxy(x, y);
		cout << thaoTac[i] << endl;
		y += 2;
	}
	y = YMAX + 1;
	int i = 0;
	gotoxy(x, y);
	SetBGColor(4);
	cout << thaoTac[i];
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}

			if (c == UP) {
				if (y == 11) {
					y = 25;
					i = 7;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == 25) {
					y = 11;
					i = 0;
				}
				else {
					y += 2;
					i++;
				}
			}
			if (c == 13) {
				break;
			}

			if (c == ESC)
			{
				int x = xacNhanThoatChuongTrinh();
				if (x == 1)
				{
					for (NODECB* k = listCb.head; k != NULL; k = k->next)
					{
						delete[]k->data.danhSachVe.ve;
					}
					system("cls");
					SetColor(31);
					return;
				}
				else
				{
					system("cls");
					goto MENU;
				}
				
			}

			gotoxy(x1, y1);
			SetBGColor(0);
			cout << thaoTac[i1];
			gotoxy(x, y);
			SetBGColor(4);
			cout << thaoTac[i];
			SetBGColor(0);

			y1 = y;
			i1 = i;
		}
	}
	switch (i)
	{
		{
	case 0:
	{
	QUAYLAI1:
		SetBGColor(0);
		system("cls");
		inDanhSachCacMayBay(listMb);
		veBangDanhSachCacMayBay(listMb);
		veCacLuaChon();
		while (1)
		{
			if (_kbhit)
			{
				char c = _getch();
				if (c == -32) {
					c = _getch();
				}

				if (c == ESC) {
					system("cls");
					goto MENU;
				}
				if (c == F2) {
					themMayBay(listMb);
					goto QUAYLAI1;
				}
				if (c == F4) {
					luaChonSuaMayBay(listMb,listCb);
					goto QUAYLAI1;
				}
				if (c == DELETE) {
					luaChonXoaMayBay(listMb,listCb);
					goto QUAYLAI1;
				}

			}
		}
		break;
	}
	case 1:
	{
	QUAYLAI2:
		SetBGColor(0);
		system("cls");
		inDanhSachCacChuyenBay(listCb);	
		veCacLuaChonChuyenBay();
		
		while (1)
		{
			if (_kbhit)
			{
				char c = _getch();
				if (c == -32) {
					c = _getch();
				}

				if (c == ESC) {
					system("cls");
					goto MENU;
				}
				if (c == F1)
				{
					system("cls");
					inDanhSachCacMayBay(listMb);
					SetColor(11);
					SetBGColor(5);
					gotoxy(XMAX + 100, YMAX); cout << " ESC: QUAY LAI ";
					SetColor(31);
					SetBGColor(0);
					while (1)
					{
						if (_kbhit)
						{
							char d = _getch();
							if (d == ESC)
								goto QUAYLAI2;
						}
					}
				}
				if (c == F2) {
					themChuyenBay(listCb, listMb);
					goto QUAYLAI2;
				}
				if (c == F4) {
					luaChonSuaChuyenBay(listCb);
					goto QUAYLAI2;
				}
				if (c == BACK) {
					luaChonHuyChuyenBay(listCb);
					goto QUAYLAI2;
				}
				if (c == DELETE) {
					luaChonXoaChuyenBay(listCb);
					goto QUAYLAI2;
				}
			}
		}
		break;
	}
	case 2: 
	{
		SetBGColor(0);
		SetColor(15);
		system("cls");
		datVe(listMb, listCb, tree);
		goto MENU;
		break;
	}
	case 3:
	{
		SetBGColor(0);
		system("cls");
		huyVe(listCb, listMb, tree);
		goto MENU;
		break;
	}

	case 4:
	{
		SetBGColor(0);
		system("cls");
		danhSachHK(listCb, listMb, tree);
		goto MENU;
		break;
	}
	case 5:
	{
		SetBGColor(0);
		system("cls");
		nhapNgayVaNoiDen(listCb);
		goto MENU;
		break;
	}
	case 6:
	{
		SetBGColor(0);
		system("cls");
		inDanhSachVeTrong(listCb, listMb, tree);
		goto MENU;
		break;
	}

	case 7:
	{
		SetBGColor(0);
		system("cls");
		thongKeLuotBay(listCb, listMb);
		goto MENU;
		break;
	}

	default:
		break;
		}
	}
}