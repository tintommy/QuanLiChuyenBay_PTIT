#pragma once
#include<iostream>
#include<string>
#include"structData.h"
#include"xuLiFile.h"
#include"mylib.h"
#include"chuyenBay.h"
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
#define XMIN 18 
#define YMIN 15 
#define SMIN 60 
void inCacChuyenBay(string ngay, string noiDen, LISTCB listCb)
{

	system("cls");
	int x = 50, y = 10;
	int temp = 0;

	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.ngayKh == ngay && k->data.sanBayDen == noiDen&&k->data.trangThai!=0)
		{
			gotoxy(x, y + 4); cout << k->data.maCB;
			gotoxy(x + 30, y + 4); cout << k->data.gioKh;
			gotoxy(x + 60, y + 4); ;
			switch (k->data.trangThai)
			{
			case 0:
				cout << "HUY";
				break;
			case 1:
				cout << "CON VE";
				break;
			case 2:
				cout << "HET VE";
				break;
			case 3:
				cout << "HOAN TAT";
				break;
			default:
				break;
			}
			gotoxy(x + 90, y + 4); 
			switch (k->data.trangThai)
			{
			case 0:
				cout << "0";
				break;
			case 1:
				cout << k->data.mayBay.soCho - k->data.danhSachVe.slVe;
				break;
			case 2:
				cout << "0";
				break;
			case 3:
				cout << "0";
				break;
			default:
				break;
			}
			temp++;
			gotoxy(x - 10, y + 5); cout << string(120, 205);
			y += 2;
		}

	}
	y = 10;
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 120, y + 3); cout << " ESC: MENU ";
	gotoxy(x + 120, y + 5); cout << " BACK: NHAP LAI ";
	SetColor(31);
	SetBGColor(0);
	if (temp == 0)
	{
		SetBGColor(15);
		SetColor(13);
		gotoxy(x + 20, y - 2); cout << "KHONG CO CHUYEN BAY DEN " << noiDen << " VAO NGAY " << ngay;
		SetColor(14);
		SetBGColor(0);
	}
	else
	{
		SetBGColor(15);
		SetColor(13);
		gotoxy(x + 20, y - 2); cout << "NHUNG CHUYEN BAY DEN " << noiDen << " VAO NGAY " << ngay;
		SetColor(14);
		SetBGColor(0);
		gotoxy(x - 5, y + 2); cout << "MA CHUYEN BAY";
		gotoxy(x + 25, y + 2); cout << "GIO KHOI HANH";
		gotoxy(x + 58, y + 2); cout << "TRANG THAI";
		gotoxy(x + 85, y + 2); cout << "SO VE CON LAI";
		SetColor(31);
		gotoxy(x - 10, y + 3); cout << string(120, 205);
	}
}
void nhapNgayVaNoiDen(LISTCB listCb)
{
	int x = 90, y = 20;
	char c;
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 45, y); cout << " ESC: MENU ";
	gotoxy(x + 45, y + 2); cout << " F5: NHAP LAI ";
	SetBGColor(4);
	SetColor(11);
	gotoxy(x + 5, y - 2); cout << " TIM CHUYEN BAY ";
	SetColor(31);
	SetBGColor(13);
	gotoxy(x - 1, y); cout << "                                         ";
	gotoxy(x - 1, y + 1); cout << "                                         ";
	gotoxy(x - 1, y + 2); cout << "                                         ";
	gotoxy(x, y ); cout << "NGAY KHOI HANH: "; gotoxy(x + 20, y); cout << "THANG: "; gotoxy(x + 30, y); cout << "NAM: ";
	gotoxy(x, y + 2); cout << "Nhap noi den : ";

NHAPNGAY:
	string ngay;
	SetColor(14);
	x = 90;
	SetBGColor(13);
	gotoxy(x + 16, y); cout << "    ";
	gotoxy(x + 16, y );
	SetColor(14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				ngay.push_back(c);
				gotoxy(x + 16, y ); cout << c; x++;
				if (ngay.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (ngay.size() > 0)
				{
					ngay.erase(ngay.size() - 1);
					gotoxy(x + 16, y ); cout << "\b \b"; x--;
				}
			}
			
			if (c == ESC)
			{
				SetBGColor(0);
				return;
			}
			if (c == F5)
			{
				system("cls");
				SetColor(31);
				SetBGColor(0);
				goto NHAPNGAY;
			}
			if (c == ENTER)
				break;
		}
	}
	x = 90;
	SetColor(12);
	SetBGColor(0);
	if (ngay.empty() == true)
	{
		gotoxy(x , y + 4); cout << "HAY NHAP NGAY KHOI HANH!";
		goto NHAPNGAY;
	}
	if (stoi(ngay) > 31)
	{
		gotoxy(x , y + 4); cout << "HAY NHAP LAI NGAY KHOI HANH!";
		goto NHAPNGAY;
	}
	gotoxy(x, y + 4); cout << "                                  ";
	SetColor(31);
	//-------------
NHAPTHANG:
	string thang;
	SetColor(14);
	x = 90;
	SetBGColor(13);
	gotoxy(x + 27, y ); cout << "   ";
	gotoxy(x + 27, y );
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				thang.push_back(c);
				gotoxy(x + 27, y ); cout << c; x++;
				if (thang.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (thang.size() > 0)
				{
					thang.erase(thang.size() - 1);
					gotoxy(x + 27, y ); cout << "\b \b"; x--;
				}
			}
			
			if (c == ESC)
			{
				SetBGColor(0);
				return;
			}
			if (c == F5)
			{
				system("cls");
				SetColor(31);
				SetBGColor(0);
				goto NHAPNGAY;
			}
			if (c == ENTER)
				break;
		}
	}
	x = 90;
	SetColor(12);
	SetBGColor(0);
	if (thang.empty() == true)
	{
		gotoxy(x, y +4); cout << "HAY NHAP THANG KHOI HANH!";
		goto NHAPTHANG;
	}
	if (stoi(thang) > 12)
	{
		gotoxy(x, y + 4); cout << "HAY NHAP LAI THANG KHOI HANH!";
		goto NHAPTHANG;
	}
	gotoxy(x, y + 4); cout << "                                 ";
	SetColor(31);
	SetBGColor(13);
NHAPNAM:
	string nam;
	SetColor(14);
	x = 90;
	SetBGColor(13);
	gotoxy(x + 35, y ); cout << "     ";
	gotoxy(x + 35, y );
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				nam.push_back(c);
				gotoxy(x + 35, y ); cout << c; x++;
				if (nam.size() > 4)
					break;
			}
			if (c == BACK)
			{
				if (nam.size() > 0)
				{
					nam.erase(nam.size() - 1);
					gotoxy(x + 35, y ); cout << "\b \b"; x--;
				}
			}
			
			if (c == ESC)
			{
				SetBGColor(0);
				return;
			}
			if (c == F5)
			{
				nhapNgayVaNoiDen(listCb);
				return;
			}
			if (c == ENTER)
				break;
		}
	}
	x = 90;
	SetColor(12);
	SetBGColor(0);
	if (nam.empty() == true)
	{
		gotoxy(x, y + 4); cout << "HAY NHAP NAM KHOI HANH!";
		goto NHAPNAM;
	}
	if ( nam.size() > 4)
	{
		gotoxy(x, y +4); cout << "HAY NHAP LAI NAM KHOI HANH!";
		goto NHAPNAM;
	}
	gotoxy(x, y + 4); cout << "                              ";
	string ngayThangNam = ngay + "/" + thang + "/" + nam;
	chuanHoaNgay(ngayThangNam);
	if (kiemTraDinhDangNgay(ngayThangNam) == false)
	{
		gotoxy(x + 5, y + 5); cout << "HAY NHAP LAI NGAY KHOI HANH!";
		Sleep(1000);
		system("cls");
		nhapNgayVaNoiDen(listCb);
		return;
	}
	SetColor(31);
NHAPSANBAYDEN:
	
	SetColor(14);
	x = 90;
	SetBGColor(13);
	string sanBayDen;
	gotoxy(x + 15, y + 2); cout << "                         ";
	SetBGColor(0);
	gotoxy(x + 40, y + 2); cout << "  ";
	SetBGColor(13);
	gotoxy(x + 15, y +2);
	while (1)
	{
		if (_kbhit)
		{
			char c = _getch();
			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9' || c == 32)
			{
				if (c >= 'a' && c < +'z')
					c = c - 32;
				sanBayDen.push_back(c);
				gotoxy(x + 15, y + 2); cout << c; x++;
				if (sanBayDen.size() > 25  )
					break;
			}
			if (c == BACK)
			{
				if (sanBayDen.size() > 0)
				{
					sanBayDen.erase(sanBayDen.size() - 1);
					gotoxy(x + 15, y + 2); cout << "\b \b"; x--;
				}
			}
			if (c == ESC)
			{
				SetBGColor(0);
				return;
			}
			if (c == F5)
			{
				nhapNgayVaNoiDen(listCb);
				return;
			}
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	SetBGColor(0);
	x = 90;
	if (sanBayDen.empty() == true)
	{
		gotoxy(x, y + 4); cout << "HAY NHAP SAN BAY DEN !        ";
		goto NHAPSANBAYDEN;
	}
	if (sanBayDen.size() >=25 )
	{

		gotoxy(x, y + 4);  cout << "HAY NHAP LAI SAN BAY DEN !        ";
		goto NHAPSANBAYDEN;
	}
	gotoxy(x , y + 4); cout << "                                     ";
	
	SetColor(31);
	inCacChuyenBay(ngayThangNam, sanBayDen,listCb);
	while (1)
	{
		char c = _getch();
		if (c == -32)
			c = _getch();
		if (c == ESC)
			return;
		if (c == BACK)
		{
			system("cls");
			nhapNgayVaNoiDen(listCb);
		}
	}
}