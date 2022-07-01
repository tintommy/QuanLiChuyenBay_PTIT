#pragma once
#include<iostream>
#include"mylib.h"
#include<fstream>
#include<windows.h>
#include<cwchar>
#include<iomanip>
#include<chrono>
#pragma warning(disable:4996)
using namespace std;
#define XMAX 50
#define YMAX 10
#define ESC 27
#define ENTER 13
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
//#define DELETE 83
#define SPACE 42
#define F1 59
#define F2 60
#define F4 62
#define tabX 6
#define tabY 4
#define tabS 83
#define tabW 23
#define XMIN 18 
#define YMIN 15 
#define SMIN 60 


void veMenu();
void veCacLuaChon();
void veTenDoAn();

void hienThiTrang(int tongtrang, int tranghientai, int x, int y)
{
	//textcolor(62);
	gotoxy(x, y + 1);
	cout << "Trang :  " << (tranghientai + 1) << " / " << tongtrang << "   ";
}

void veTenDoAn()
{	
	SetColor(45);
	gotoxy(84, 8);
	cout << " HOC VIEN CONG NGHE BUU CHINH VIEN THONG ";
	gotoxy(97, 9);
	SetColor(45);
	cout << " KHOA: CNTT2 ";
	gotoxy(87, 10);
	SetColor(11);
	cout << "MON: CAU TRUC DU LIEU & GIAI THUAT";

	SetColor(31);
	int x = XMAX + 10, y = YMAX + 5;
	gotoxy(x + 12, y + 0); cout << "  #######   ##     ##     ###     ##    ##     ##       ##    ## \n";
	gotoxy(x + 12, y + 1); cout << " ##     ##  ##     ##    ## ##    ###   ##     ##        ##  ##  \n";
	gotoxy(x + 12, y + 2); cout << " ##     ##  ##     ##   ##   ##   ####  ##     ##         ####   \n";
	gotoxy(x + 12, y + 3); cout << " ##     ##  ##     ##  ##     ##  ## ## ##     ##          ##    \n";
	gotoxy(x + 12, y + 4); cout << " ##  ## ##  ##     ##  #########  ##  ####     ##          ##    \n";
	gotoxy(x + 12, y + 5); cout << " ##    ##   ##     ##  ##     ##  ##   ###     ##          ##    \n";
	gotoxy(x + 12, y + 6); cout << "  ##### ##   #######   ##     ##  ##    ##     ########    ##    \n";
	gotoxy(x, y + 8); cout << " ######   ##     ##  ##     ##  ##    ##  ########  ##    ##     ########      ###     ##    ## \n";
	gotoxy(x, y + 9); cout << "##    ##  ##     ##  ##     ##   ##  ##   ##        ###   ##     ##     ##    ## ##     ##  ##  \n";
	gotoxy(x, y + 10); cout << "##        ##     ##  ##     ##    ####    ##        ####  ##     ##     ##   ##   ##     ####   \n";
	gotoxy(x, y + 11); cout << "##        #########  ##     ##     ##     ######    ## ## ##     ########   ##     ##     ##    \n";
	gotoxy(x, y + 12); cout << "##        ##     ##  ##     ##     ##     ##        ##  ####     ##     ##  #########     ##    \n";
	gotoxy(x, y + 13); cout << "##    ##  ##     ##  ##     ##     ##     ##        ##   ###     ##     ##  ##     ##     ##    \n";
	gotoxy(x, y + 14); cout << " ######   ##     ##   #######      ##     ########  ##    ##     ########   ##     ##     ##    \n";
	SetColor(13);
	gotoxy(86,40);
	cout<<"NGUYEN TRAN TRONG TIN - N20DCCN065";
	gotoxy(86,41);
	cout<<"NGUYEN TRONG TIN      - N20DCCN066";
	gotoxy(86, 43);
	system("PAUSE");
	system("cls");
	SetColor(31);
}

void veMenu()
{
	SetColor(45);
	gotoxy(58, 2); cout << "::::     ::::       ::::::::::       ::::    :::       :::    :::";
	gotoxy(58, 3); cout << "+:+:+: :+:+:+       :+:              :+:+:   :+:       :+:    :+:";
	gotoxy(58, 4); cout << "+:+ +:+:+ +:+       +:+              :+:+:+  +:+       +:+    +:+";
	gotoxy(58, 5); cout << "+#+  +:+  +#+       +#++:++#         +#+ +:+ +#+       +#+    +:+";
	gotoxy(58, 6); cout << "+#+       +#+       +#+              +#+  +#+#+#       +#+    +#+";
	gotoxy(58, 7); cout << "#+#       #+#       #+#              #+#   #+#+#       #+#    #+#";
	gotoxy(58, 8); cout << "###       ###       ##########       ###    ####        ########";
	SetColor(45);
	SetBGColor(0);
	int x = XMAX;
	int y = YMAX;
	int size = 80;
	char c = 205;
	char d = 186;
	for (int i = 0; i < 9; i++)
	{
		gotoxy(x, y);
		for (int t = 0; t < size; t++)
		{
			cout << c;
		}
		y += 2;
	}
	y = YMAX + 1;
	for (int i = 0; i < 8; i++)
	{

		gotoxy(x, y);
		cout << d;
		gotoxy(x + size, y);
		cout << d;
		y += 2;
	}
	SetColor(31);
	SetColor(0);
	SetBGColor(31);
	gotoxy(50, 40); cout << " ESC: THOAT    |    LEN/XUONG: LUA CHON CHUC NANG    |    ENTER: CHON CHUC NANG ";
	SetColor(31);
	SetBGColor(0);
}

void menuNhapCCCD()
{
	SetColor(11);
	SetBGColor(5);
	gotoxy(XMAX + 62, YMAX + 6); cout << " ESC: QUAY LAI ";
	gotoxy(XMAX + 20, YMAX + 5);
	SetBGColor(45);  // khung chu
	SetColor(31);	// mau chu title
	cout << "           NHAP SO CCCD           ";
	gotoxy(XMAX + 20, YMAX + 6); SetBGColor(45);
	cout << "     "; // goc trai
	gotoxy(XMAX + 25, YMAX + 6);  SetBGColor(31);
	cout << "                      "; // khung nhap
	gotoxy(XMAX + 49, YMAX + 6); SetBGColor(45);
	cout << "     ";   // goc phai
	gotoxy(XMAX + 20, YMAX + 7); SetBGColor(45);
	cout << "                                  ";  // vien duoi
}

void menuDatVe() 
{
	system("cls");
	SetColor(14);
	gotoxy(60, 2); cout << "DAT VE CHUYEN BAY";
	gotoxy(105, 2);  cout << "THONG TIN HANH KHACH ";
	gotoxy(42, 7);  cout << "Ma chuyen bay    : ";
	gotoxy(42, 9);  cout << "Kiem tra so CCCD : ";
	gotoxy(42, 11); cout << "Chon ghe so      : ";
	gotoxy(95, 7); cout << "Ho  : ";
	gotoxy(95, 9); cout << "Ten : ";
	gotoxy(95, 11); cout << "Phai: ";
	SetColor(11);
	SetBGColor(45);
	gotoxy(145, 5); cout << " F2: DANH SACH CHUYEN BAY ";
	gotoxy(145, 7); cout << " F5: NHAP LAI ";
	gotoxy(145, 9); cout << " ESC: QUAY LAI ";
	SetBGColor(0);
	SetColor(31);
	SetColor(14);
	gotoxy(75, 17); cout << "----------CHO NGOI----------";
	SetColor(45);
	for (int i = 40; i <= 140; i++) // hang ngang
	{
		gotoxy(i, 1);  cout << char(205);
		gotoxy(i, 3);  cout << char(205);
		gotoxy(i, 14); cout << char(205);

	}
	for (int i = 1; i < 14; i++) // hàng doc
	{
		gotoxy(40, 1); cout << char(201);
		gotoxy(40, 3); cout << char(204);
		gotoxy(140, 3); cout << char(185);
		gotoxy(40, i); cout << char(186);
		gotoxy(140, 1); cout << char(187);
		gotoxy(140, 14); cout << char(188);
		gotoxy(40, 14); cout << char(200);
		gotoxy(140, i); cout << char(186);
	}
	SetColor(14);
	SetBGColor(0);
	gotoxy(103, 14); cout << "                           ";
	gotoxy(104, 13); cout << "        THONG BAO        ";
	gotoxy(104, 12); cout << "                         ";
	SetBGColor(0);

}

void menuHuyVe()
{
	system("cls");
	SetColor(14);
	gotoxy(60, 2); cout << "HUY VE CHUYEN BAY";
	gotoxy(105, 2);  cout << "THONG TIN HANH KHACH ";
	gotoxy(42, 5);  cout << "Ma chuyen bay    : ";
	gotoxy(42, 8);  cout << "Kiem tra so CCCD : ";
	gotoxy(95, 5); cout << "Ho  : ";
	gotoxy(95, 7); cout << "Ten : ";
	gotoxy(95, 9); cout << "Phai: ";
	gotoxy(95, 11); cout << "Cho ngoi: ";
	SetColor(11);
	SetBGColor(45);
	gotoxy(142, 5); cout << " F2: DANH SACH CHUYEN BAY ";
	gotoxy(142, 7); cout << " F5: NHAP LAI ";
	gotoxy(142, 9); cout << " ESC: QUAY LAI ";
	gotoxy(142, 11); cout << " F4: XOA HANH KHACH ";
	SetBGColor(0);
	SetColor(31);
	SetColor(45);
	for (int i = 40; i <= 140; i++) // hang ngang
	{
		gotoxy(i, 1);  cout << char(205);
		gotoxy(i, 3);  cout << char(205);
		gotoxy(i, 14); cout << char(205);

	}
	for (int i = 1; i < 14; i++) // hàng doc
	{
		gotoxy(40, 1); cout << char(201);
		gotoxy(40, 3); cout << char(204);
		gotoxy(140, 3); cout << char(185);
		gotoxy(40, i); cout << char(186);
		gotoxy(140, 1); cout << char(187);
		gotoxy(140, 14); cout << char(188);
		gotoxy(40, 14); cout << char(200);
		gotoxy(140, i); cout << char(186);
	}
	SetColor(31);
	SetBGColor(0);
}

void veMayBay() {

}

void menuDanhSachHK()
{
	SetColor(14);
	gotoxy(62, 2);
	cout << "DANH SACH HANH KHACH CUA CHUYEN BAY CO MA: "; // 80,2
	gotoxy(57, 3);
	cout << "Ngay khoi hanh: "; // 49,3
	gotoxy(85, 3);
	cout << "Gio: ";
	gotoxy(98, 3);
	cout << "Noi den:"; // 77,3
	SetColor(5);
	gotoxy(tabX + 35, tabY);
	cout << char(218);
	//-------- dong dau
	for (int i = 1; i < tabS; i++)
	{
		cout << char(196); // __
	}
	cout << char(191);  // `|

	//cot dau
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 35, tabY + i);
		cout << char(179); // |
	}
	//cot cuoi
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + tabS + 35, tabY + i);
		cout << char(179); // |
	}

	gotoxy(tabX + 35, tabY + tabW);
	cout << char(192);
	//dong cuoi
	for (int i = 1; i < tabS + 1; i++)
	{
		gotoxy(tabX + 35 + i, tabY + tabW);
		cout << char(196);
	}
	gotoxy(tabX + tabS + 35, tabY + tabW);
	cout << char(217);

	// STT
	gotoxy(tabX + 43, tabY); cout << char(194);
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 43, tabY + i); cout << char(179); // cot stt
	}

	gotoxy(tabX + 35, tabY + 2);
	cout << char(195);
	// dong hai
	for (int i = 1; i < tabS; i++)
	{
		gotoxy(tabX + 35 + i, tabY + 2);
		cout << char(196);
	}
	gotoxy(tabX + 43, tabY + 2); cout << char(197);
	gotoxy(tabX + 35 + tabS, tabY + 2); cout << char(180);
	gotoxy(tabX + 43, tabY + tabW); cout << char(193);

	// SO HIEU
	gotoxy(tabX + 55, tabY); cout << char(194);
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 55, tabY + i); cout << char(179);
	}
	gotoxy(tabX + 55, tabY + 2); cout << char(197);
	gotoxy(tabX + 55, tabY + tabW); cout << char(193);

	// LOAI
	gotoxy(tabX + 73, tabY); cout << char(194);
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 73, tabY + i); cout << char(179);
	}
	gotoxy(tabX + 73, tabY + 2); cout << char(197);
	gotoxy(tabX + 73, tabY + tabW); cout << char(193);

	// SO CHO
	gotoxy(tabX + 105, tabY); cout << char(194);
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 105, tabY + i); cout << char(179);
	}
	gotoxy(tabX + 105, tabY + 2); cout << char(197);
	gotoxy(tabX + 105, tabY + tabW); cout << char(193);

	SetColor(14);
	gotoxy(tabX + 38, tabY + 1); cout << "STT";
	gotoxy(tabX + 47, tabY + 1); cout << "SO VE";
	gotoxy(tabX + 61, tabY + 1); cout << "CCCD";
	gotoxy(tabX + 85, tabY + 1); cout << "HO TEN";
	gotoxy(tabX + 110, tabY + 1); cout << "PHAI";

}

void menuNhapMaChuyenBay()
{
	gotoxy(XMAX+ 20, YMAX + 5); 
	SetBGColor(45);  // khung chu
	SetColor(31);	// mau chu title
	cout << "        NHAP MA CHUYEN BAY        ";
	gotoxy(XMAX + 20, YMAX + 6); SetBGColor(45);		
	cout << "     "; // goc trai
	gotoxy(XMAX + 25, YMAX + 6);  SetBGColor(31); 	
	cout << "                         "; // khung nhap
	gotoxy(XMAX + 49, YMAX + 6); SetBGColor(45); 
	cout << "     ";   // goc phai
	gotoxy(XMAX + 20, YMAX + 7); SetBGColor(45);		
	cout << "                                  ";  // vien duoi
	SetBGColor(0); SetColor(31);
	gotoxy(70, YMAX + 10);
}

void menuLuotBay()
{
	SetColor(14);
	gotoxy(70, 2);
	cout << "THONG KE SO LUOT BAY CUA MAY BAY";
	// hang 
	SetColor(45);
	for (int i = 1; i <= 35 ; i++) 
	{
		gotoxy(68 + i, 4); cout << char(196);
		gotoxy(68, 4); cout << char(218);
		gotoxy(103, 4); cout << char(191);
		gotoxy(68, 6); cout << char(195);
		gotoxy(103, 6); cout << char(180);
	}
	// cot 
	for (int i = 1; i <= 28; i++) 
	{
		gotoxy(68, 4 + i); cout << char(179);
		gotoxy(87, 4); cout << char(194);
		gotoxy(87, 4 + i); cout << char(179);
		gotoxy(103, 4 + i); cout << char(179);
	}
	// tach hang dau
	for (int i = 1; i <= 35; i++)
	{
		gotoxy(68 + i, 6); cout << char(196);
		gotoxy(68, 6); cout << char(195);
		gotoxy(103, 6); cout << char(180);
		gotoxy(87, 6); cout << char(197);
	}
	// tach cac hang
	int dem = 1;
	for (int i = 1; i <= 13; i++) 
	{
		for (int j = 0; j < 35; j++)
		{
			gotoxy(68 + j, 6 + dem * 2); cout << char(196);
		}
		gotoxy(68, 6 + dem * 2); cout << char(195);
		gotoxy(103, 6 + dem * 2); cout << char(180);
		gotoxy(87, 6 + dem * 2); cout << char(197);
		dem++;
	}
	// hang cuoi 
	for (int i = 1; i <= 34; i++)
	{
		gotoxy(68 + i, 32); cout << char(196);
		gotoxy(68, 32); cout << char(192);
		gotoxy(103, 32); cout << char(217);
		gotoxy(87, 32); cout << char(193);
	}

	SetColor(12);
	gotoxy(tabX + 44, tabY);
	SetColor(31);
	//SO HIEU MB
	gotoxy(tabX + 64, tabY + 1); cout << "SO HIEU MAY BAY";
	// SO LUOT BAY
	gotoxy(tabX + 85, tabY + 1); cout << "SO LUOT BAY";
}

void veBangDanhSachCacMayBay(LISTMB listMb);

void veKhungThemMayBay();

void veCacLuaChonChuyenBay();

void veBangDanhSachCacMayBay(LISTMB listMb)
{
	int x = XMAX;
	int y = YMAX - 5;
	int x1 = x;
	int y1 = y;
	char c = 205;
	char d = 186;
	for (int i = 0; i < listMb.n; i++)
	{
		gotoxy(x1, y1);
		for (int t = 0; t < 90; t++)
		{
			cout << c;
		}
		y1 += 2;
	}
	for (int i = 0; i < listMb.n + 1; i++)
	{

		for (int i = 0; i < 4; i++)
		{
			gotoxy(x, y + 1);
			cout << d;
			x += 30;
		}
		x = XMAX;
		y += 2;
	}
	SetColor(30);
	gotoxy(x + 10, YMAX - 4); cout << "SO HIEU";
	gotoxy(x + 43, YMAX - 4); cout << "LOAI";
	gotoxy(x + 73, YMAX - 4); cout << "SO CHO";
	SetColor(31);

}

void veCacLuaChon()
{
	int x = XMAX + 100;
	int y = YMAX;
	SetColor(11);
	SetBGColor(5);
	gotoxy(x, y + 1); cout << " ESC: QUAY LAI ";
	gotoxy(x, y + 3); cout << " F2: THEM ";
	gotoxy(x, y + 5); cout << " F4: SUA ";
	gotoxy(x, y + 7); cout << " DEL: XOA ";
	SetColor(31);
	SetBGColor(0);
}

void veKhungThemMayBay()
{
	int x = XMAX + 105;
	int y = YMAX + 11;
	char c = 205;
	for (int i = 0; i < 4; i++)
	{
		gotoxy(x, y);
		for (int t = 0; t < 50; t++)
		{
			cout << c;
		}
		y += 2;
	}
	y = YMAX + 11;
	for (int i = 0; i < 3; i++)
	{
		gotoxy(x, y + 1);
		cout << "|";
		gotoxy(x + 50, y + 1);
		cout << "|";
		y += 2;
	}

}

void veCacLuaChonChuyenBay()
{
	int x = XMAX + 100;
	int y = YMAX;
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 5, y - 1); cout << " ESC: QUAY LAI ";
	gotoxy(x + 5, y + 1); cout << " F1: XEM DANH SACH MAY BAY ";
	gotoxy(x + 5, y + 3); cout << " F2: THEM ";
	gotoxy(x + 5, y + 5); cout << " F4: SUA NGAY GIO ";
	gotoxy(x + 5, y + 7); cout << " BACK: HUY CHUYEN BAY ";
	gotoxy(x + 5, y + 9); cout << " DEL: XOA CHUYEN BAY ";
	SetColor(31);
	SetBGColor(0);
}

void menuDanhSachVeTrong()
{

	gotoxy(35, 2);
	cout << "DANH SACH VE TRONG CUA CHUYEN BAY";
	gotoxy(42, 3); cout << "Ma: "; // 46,3

	gotoxy(tabX + 30, tabY);
	cout << char(218);
	//-------- dong dau
	for (int i = 1; i < tabS - 53; i++)
	{
		cout << char(196);
	}
	cout << char(191);

	//cot dau
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + 30, tabY + i);
		cout << char(179);
	}
	//cot cuoi
	for (int i = 1; i < tabW + 1; i++)
	{
		gotoxy(tabX + tabS - 23, tabY + i);
		cout << char(179);
	}

	gotoxy(tabX + 30, tabY + tabW);
	cout << char(192);
	//	//dong cuoi
	for (int i = 1; i < tabS - 53; i++)
	{
		gotoxy(tabX + i + 30, tabY + tabW);
		cout << char(196);
	}
	gotoxy(tabX + tabS - 23, tabY + tabW);
	cout << char(217);

	// STT
	gotoxy(tabX + 40, tabY + 1); cout << "VE TRONG";
	// dong hai
	for (int i = 1; i < tabS - 53; i++)
	{
		gotoxy(tabX + i + 30, tabY + 2);
		cout << char(196);
	}
	//	gotoxy(tabX + 10, tabY + 2); cout << char(197);
	gotoxy(tabX + tabS - 23, tabY + 2); cout << char(180);
	gotoxy(tabX + 30, tabY + 2); cout << char(195);
	//	gotoxy(tabX + 45, tabY + tabW); cout << char(193);
	//
	//	// VE TRONG
	//	gotoxy(tabX + 55, tabY + 1); cout << "VE TRONG";

}
