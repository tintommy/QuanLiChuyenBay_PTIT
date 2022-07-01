#pragma once
#include<iostream>
#include<fstream>
#include "mylib.h"
#include"structData.h"
#include"veMenu.h"
#include"xuLiFile.h"
using namespace std;
#define XMAX 50
#define YMAX 10
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define DELETE 83
#define BACK 8
#define SPACE 42
#define F1 59
#define F2 60
#define F4 62
void inDanhSachCacMayBay();
void themMayBay();
void luaChonSuaMayBay();
void suaMayBay();
void luaChonXoaMayBay();
void xoaMayBay();
bool kiemTraMayBayCoChuyenBayKhong(int i, LISTMB& listMb, LISTCB& listCb, string& maCb)
{
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.mayBay.soHieuMB == listMb.nodes[i]->soHieuMB && k->data.trangThai != 1 && k->data.trangThai != 2)//chuyến bay còn vé và hết vé thì chỉ được sửa số ghế tăng
		{
			maCb = k->data.maCB;
			return true;
		}
	}
	return false;
}
void inDanhSachCacMayBay(LISTMB& listMb)
{
	SetColor(30);
	gotoxy(XMAX + 35, YMAX - 7); cout << " DANH SACH CAC MAY BAY ";
	SetColor(31);
	int x = XMAX;
	int y = YMAX - 1;
	char c = 196;
	for (int i = 0; i < listMb.n; i++)
	{

		gotoxy(x + 10, y - 1);
		cout << listMb.nodes[i]->soHieuMB;
		gotoxy(x + 43, y - 1);
		cout << listMb.nodes[i]->loaiMB;
		gotoxy(x + 75, y - 1);
		cout << listMb.nodes[i]->soCho;
		gotoxy(x, y);
		for (int t = 0; t < 91; t++)
		{
			cout << c;
		}
		y += 2;

	}
	veBangDanhSachCacMayBay(listMb);

}
void themMayBay(LISTMB& listMb)
{
	int y = YMAX + 10;
	MAYBAY* mb = new MAYBAY;
	string s;
	char c;
	if (listMb.n == 300)
	{
		SetBGColor(4);
		gotoxy(XMAX + 120, y); cout << " DANH SACH CHUYEN BAY DA DAY ";
		return;
	}
	veKhungThemMayBay();
	gotoxy(XMAX + 120, y); cout << "THEM MAY BAY";
	gotoxy(XMAX + 110, y + 2); cout << "SO HIEU MAY BAY : ";
	gotoxy(XMAX + 110, y + 4); cout << "LOAI MAY BAY : ";
	gotoxy(XMAX + 110, y + 6); cout << "SO CHO : ";
NHAPSOHIEUMAYBAY:
	SetColor(14);
	int x = XMAX + 110;
	gotoxy(x + 20, y + 2); cout << "                  ";
	gotoxy(x + 20, y + 2);
	s.clear();
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
			{
				if (c >= 'a' && c <= 'z')
					c = c - 32;
				s.push_back(c);
				gotoxy(x + 20, y + 2); cout << c; x++;
				if (s.size() > 15)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 20, y + 2); cout << "\b \b"; x--;
				}
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	if (s.empty() == true)
	{
		gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP SO HIEU MAY BAY !        ";
		goto NHAPSOHIEUMAYBAY;
	}
	for (int i = 0; i < listMb.n; i++)
	{
		if (listMb.nodes[i]->soHieuMB == s)
		{
			gotoxy(XMAX + 120, y + 8); cout << "SO HIEU MAY BAY DA TON TAI!        ";
			goto NHAPSOHIEUMAYBAY;
		}
	}
	if (s.size() > 15)
	{

		gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LAI SO HIEU MAY BAY !        ";
		goto NHAPSOHIEUMAYBAY;
	}
	gotoxy(XMAX + 120, y + 8); cout << "                                     ";
	mb->soHieuMB = s;
	SetColor(31);
NHAPLOAIMAYBAY:
	SetColor(14);
	x = XMAX + 110;
	s.clear();
	gotoxy(x + 15, y + 4); cout << "                                       ";
	gotoxy(x + 45, y + 4); cout << "|";
	gotoxy(x + 15, y + 4);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
			{
				if (c >= 'a' && c <= 'z')
					c = c - 32;
				s.push_back(c);
				gotoxy(x + 15, y + 4); cout << c; x++;
				if (s.size() > 40)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 15, y + 4); cout << "\b \b"; x--;
				}
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	if (s.empty() == true)
	{
		gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LOAI MAY BAY !      ";
		goto NHAPLOAIMAYBAY;
	}
	if (s.size() > 40)
	{
		gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LOAI MAY BAY <40 KI TU !      ";
		goto NHAPLOAIMAYBAY;
	}
	gotoxy(XMAX + 120, y + 8); cout << "                                       ";
	mb->loaiMB = s;
	SetColor(31);
NHAPSOCHO:
	SetColor(14);
	s.clear();
	x = XMAX + 110;
	gotoxy(x + 15, y + 6); cout << "                             ";
	gotoxy(x + 15, y + 6);
	while (1)
	{

		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				s.push_back(c);
				gotoxy(x + 15, y + 6); cout << c; x++;
				if (s.size() > 5)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 15, y + 6); cout << "\b \b"; x--;
				}
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	if (s.empty() == true || stoi(s) < 20 || s.size() > 4)
	{
		gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP SO CHO MAY BAY>=20 !";
		goto NHAPSOCHO;
	}
	gotoxy(XMAX + 120, y + 8); cout << "                         ";
	SetColor(31);
	mb->soCho = stoi(s);
	listMb.nodes[listMb.n++] = mb;
	ghiFileDanhSachMayBay(listMb);
	SetColor(46);
	gotoxy(XMAX + 115, y + 8); cout << "      THONG BAO                          ";
	gotoxy(XMAX + 115, y + 10); cout << "DA THEM THANH CONG !";
	Sleep(500);
	system("cls");
	SetColor(31);
}
void suaMayBay(int i, LISTMB& listMb, LISTCB& listCb)
{
	int x = XMAX + 110;
	int y = YMAX + 10;
	MAYBAY* mb = new MAYBAY;
	string s, maCb;
	char c;
	char d = 205;
	if (kiemTraMayBayCoChuyenBayKhong(i, listMb, listCb, maCb))//chuyến bay còn vé và hết vé thì chỉ được sửa số ghế tăng
	{
		SetColor(14);
		gotoxy(x + 5, y - 2); cout << "==== MAY BAY DANG CO CHUYEN BAY " << maCb << " ==== ";
		SetColor(31);
		gotoxy(x + 10, y); cout << "HIEU CHINH MAY BAY";
		gotoxy(x, y + 2); cout << "SO CHO : ";
		for (int i = 0; i < 2; i++)
		{
			gotoxy(x - 5, y + 1);
			for (int t = 0; t < 50; t++)
			{
				cout << d;//vẽ khung
			}
			y += 2;
		}
		y = YMAX + 10;
		gotoxy(x - 5, y + 2);
		cout << "|";
		gotoxy(x + 44, y + 2);
		cout << "|";
		y = YMAX + 10;
	NHAPLAI:
		SetColor(14);
		s.clear();
		x = XMAX + 110;
		gotoxy(x + 15, y + 2); cout << "                             ";
		gotoxy(x + 15, y + 2);
		while (1)
		{

			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x + 15, y + 2); cout << c; x++;
					if (s.size() > 15)
						break;

				}
				if (c == BACK)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x + 15, y + 2); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER)
					break;
			}
		}
		SetColor(12);
		if (s.empty() == true || stoi(s) < listMb.nodes[i]->soCho || s.size() > 4)
		{
			gotoxy(XMAX + 120, y + 4); cout << "HAY NHAP SO CHO MAY BAY> " << listMb.nodes[i]->soCho << " !";
			goto NHAPLAI;
		}
		listMb.nodes[i]->soCho = stoi(s);
		ghiFileDanhSachMayBay(listMb);
		SetColor(46);
		gotoxy(XMAX + 115, y + 8); cout << "        THONG BAO                   ";
		gotoxy(XMAX + 115, y + 10); cout << "DA CAP NHAT THANH CONG !";
		Sleep(500);
		system("cls");
		SetColor(31);
	}
	else
	{
		veKhungThemMayBay();
		gotoxy(XMAX + 120, y); cout << "HIEU CHINH MAY BAY";
		gotoxy(XMAX + 110, y + 2); cout << "SO HIEU MAY BAY : ";
		gotoxy(XMAX + 110, y + 4); cout << "LOAI MAY BAY : ";
		gotoxy(XMAX + 110, y + 6); cout << "SO CHO : ";
	NHAPSOHIEUMAYBAY:
		SetColor(14);

		gotoxy(x + 20, y + 2); cout << "                 ";
		gotoxy(x + 20, y + 2);
		s.clear();
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
				{
					if (c >= 'a' && c < +'z')
						c = c - 32;
					s.push_back(c);
					gotoxy(x + 20, y + 2); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACK)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x + 20, y + 2); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER)
					break;
			}
		}
		SetColor(12);
		if (s.empty() == true)
		{
			gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP SO HIEU MAY BAY !        ";
			goto NHAPSOHIEUMAYBAY;
		}
		for (int i = 0; i < listMb.n; i++)
		{
			if (listMb.nodes[i]->soHieuMB == s)
			{
				gotoxy(XMAX + 120, y + 8); cout << "SO HIEU MAY BAY DA TON TAI!        ";
				goto NHAPSOHIEUMAYBAY;
			}
		}
		if (s.size() > 15)
		{

			gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LAI SO HIEU MAY BAY !        ";
			goto NHAPSOHIEUMAYBAY;
		}
		gotoxy(XMAX + 120, y + 8); cout << "                                       ";
		mb->soHieuMB = s;
		SetColor(31);
	NHAPLOAIMAYBAY:
		SetColor(14);
		x = XMAX + 110;
		s.clear();
		gotoxy(x + 15, y + 4); cout << "                                                ";
		gotoxy(x + 45, y + 4); cout << "|";
		gotoxy(x + 15, y + 4);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
				{
					if (c >= 'a' && c < +'z')
						c = c - 32;
					s.push_back(c);
					gotoxy(x + 15, y + 4); cout << c; x++;
					if (s.size() > 40)
						break;
				}
				if (c == BACK)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x + 15, y + 4); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER)
					break;
			}
		}
		SetColor(12);
		if (s.empty() == true)
		{
			gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LOAI MAY BAY !      ";
			goto NHAPLOAIMAYBAY;
		}
		if (s.size() > 40)
		{
			gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP LOAI MAY BAY <40 KI TU !      ";
			goto NHAPLOAIMAYBAY;
		}
		gotoxy(XMAX + 120, y + 8); cout << "                                     ";
		mb->loaiMB = s;
		SetColor(31);
	NHAPSOCHO:
		SetColor(14);
		s.clear();
		x = XMAX + 110;
		gotoxy(x + 15, y + 6); cout << "                             ";
		gotoxy(x + 15, y + 6);
		while (1)
		{

			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x + 15, y + 6); cout << c; x++;
					if (s.size() > 15)
						break;

				}
				if (c == BACK)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x + 15, y + 6); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER)
					break;
			}
		}
		SetColor(12);
		if (s.empty() == true || stoi(s) < 20 || s.size() > 4)
		{
			gotoxy(XMAX + 120, y + 8); cout << "HAY NHAP SO CHO MAY BAY>=20 !";
			goto NHAPSOCHO;
		}
		mb->soCho = stoi(s);
		listMb.nodes[i] = mb;
		ghiFileDanhSachMayBay(listMb);
		SetColor(46);
		gotoxy(XMAX + 115, y + 8); cout << "        THONG BAO                   ";
		gotoxy(XMAX + 115, y + 10); cout << "DA CAP NHAT THANH CONG !";
		Sleep(500);
		system("cls");
		SetColor(31);
	}
}
void luaChonSuaMayBay(LISTMB& listMb, LISTCB& listCb)
{
	int t = YMAX + 10;
	SetColor(48);
	SetBGColor(9);
	gotoxy(XMAX + 100, t); cout << " ENTER DE CHON !";
	SetColor(31);
	SetBGColor(0);
	inDanhSachCacMayBay(listMb);
	int x = XMAX + 10;
	int y = YMAX - 2;
	int x1 = x;
	int y1 = y;
	for (int i = 0; i < 8; i++)
	{
		gotoxy(x, y);
		cout << listMb.nodes[i]->soHieuMB;
		y += 2;
	}
	y = YMAX - 2;
	gotoxy(x, y);
	SetBGColor(4);
	int i = 0;
	cout << listMb.nodes[i]->soHieuMB;
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}
			if (c == UP) {
				if (y == 8) {
					y = YMAX + listMb.n * 2 - 4;
					i = listMb.n - 1;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == YMAX + listMb.n * 2 - 4) {
					y = 8;
					i = 0;
				}
				else {
					y += 2;
					i++;
				}
			}
			if (c == 27)
				break;
			if (c == 13) {
				suaMayBay(i, listMb, listCb);
				luaChonSuaMayBay(listMb, listCb);
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << listMb.nodes[i1]->soHieuMB;
			gotoxy(x, y);
			SetBGColor(4);
			cout << listMb.nodes[i]->soHieuMB;
			SetBGColor(0);
			y1 = y;
			i1 = i;
		}
	}
	SetBGColor(0);
}
void xoaMayBay(int i, LISTMB& listMb, LISTCB& listCb)
{
	int x = XMAX + 110;
	int y = YMAX + 10;
	int x1 = x;
	int y1 = y + 6;
	int i1 = 1;
	SetBGColor(0);
	SetColor(29);
	string thaoTac[2] = { "CO","KHONG" };
	gotoxy(x + 10, y + 2); cout << "THONG BAO";
	gotoxy(x, y + 4); cout << "BAN CO CHAC MUON XOA MAY BAY NAY ?";
	SetColor(31);
	gotoxy(x, y + 6); cout << "CO";
	gotoxy(x + 20, y + 6); cout << "KHONG";
	SetBGColor(41);
	gotoxy(XMAX + 110, y + 6); cout << "CO";
	int i2 = i1;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}

			if (c == RIGHT) {
				if (x == XMAX + 130) {
					x = XMAX + 110;
					i1 = 1;
				}
				else
				{
					x += 20;
					i1--;
				}
			}
			if (c == LEFT) {
				if (x == XMAX + 110) {
					x = XMAX + 130;
					i1 = 0;
				}
				else {
					x -= 20;
					i1++;
				}
			}
			if (c == 13) {
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << thaoTac[i1];
			gotoxy(x, y + 6);
			SetBGColor(41);
			cout << thaoTac[i2];
			SetBGColor(0);
			x1 = x;
			i2 = i1;
		}
	}
	
	if (i1 == 1)
	{
		for (NODECB* k = listCb.head; k != NULL; k = k->next)
		{
			if (k->data.mayBay.soHieuMB == listMb.nodes[i]->soHieuMB && k->data.trangThai != 3)
				k->data.trangThai = 0;
		}
		for (int t = i; t < listMb.n - 1; t++)
		{
			listMb.nodes[t] = listMb.nodes[t + 1];
		}
		listMb.n--;
		ghiFileDanhSachMayBay(listMb);
		ghiFileDanhSachChuyenBay(listCb);
		SetColor(46);
		SetBGColor(0);
		gotoxy(XMAX + 120, y + 8); cout << "THONG BAO";
		gotoxy(XMAX + 115, y + 10); cout << "DA XOA THANH CONG !";

	}

	Sleep(500);
	system("cls");
	SetColor(31);
	SetBGColor(0);

}
void luaChonXoaMayBay(LISTMB& listMb, LISTCB& listCb)
{
	int t = YMAX + 10;
	SetColor(48);
	SetBGColor(9);
	gotoxy(XMAX + 100, t); cout << " ENTER DE CHON !";
	SetColor(31);
	SetBGColor(0);
	inDanhSachCacMayBay(listMb);
	int x = XMAX + 10;
	int y = YMAX - 2;
	int x1 = x;
	int y1 = y;
	for (int i = 0; i < 8; i++)
	{
		gotoxy(x, y);
		cout << listMb.nodes[i]->soHieuMB;
		y += 2;
	}
	y = YMAX - 2;
	gotoxy(x, y);
	SetBGColor(4);
	int i = 0;
	cout << listMb.nodes[i]->soHieuMB;
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}
			if (c == UP) {
				if (y == 8) {
					y = YMAX + listMb.n * 2 - 4;
					i = listMb.n - 1;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == YMAX + listMb.n * 2 - 4) {
					y = 8;
					i = 0;
				}
				else {
					y += 2;
					i++;
				}
			}
			if (c == 27)
				break;
			if (c == 13) {
				xoaMayBay(i, listMb, listCb);
				luaChonXoaMayBay(listMb, listCb);
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << listMb.nodes[i1]->soHieuMB;
			gotoxy(x, y);
			SetBGColor(4);
			cout << listMb.nodes[i]->soHieuMB;
			SetBGColor(0);
			y1 = y;
			i1 = i;
		}
	}
	SetBGColor(0);
}
