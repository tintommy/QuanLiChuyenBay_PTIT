#pragma once
#include<iostream>
#include<string>
#include<windows.h>
#include <ctime>
#include"mylib.h"
#include"mayBay.h"
#include"structData.h"
#include<fstream>

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
#define F5 63

using namespace std;
void chuanHoaNgay(string& s)
{
	string A = s;
	if (A[2] != '/')
		A = '0' + A;
	if (A[5] != '/')
		A.insert(A.begin() + 3, '0');
	s = A;
}
bool kiemTraNgayKhSoVoiThoiGianThat(string ngayKh)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	int ngay = stoi(ngayKh.substr(0, 2));
	int thang = stoi(ngayKh.substr(3, 2));
	int nam = stoi(ngayKh.substr(ngayKh.size() - 4));
	if (nam < 1900 + ltm->tm_year || (nam == 1900 + ltm->tm_year && thang < 1 + ltm->tm_mon) || (nam == 1900 + ltm->tm_year && thang == 1 + ltm->tm_mon && ngay < ltm->tm_mday))
		return false;
	return true;
}
bool kiemTraDinhDangNgay(string ngayKh)
{
	int ngay = stoi(ngayKh.substr(0, 2));
	int thang = stoi(ngayKh.substr(3, 2));
	int nam = stoi(ngayKh.substr(ngayKh.size() - 4));
	if (ngayKh.size() != 10)
		return false;
	if (ngay > 31 || thang > 12)
		return false;
	if (ngay == 29 && thang == 2 && nam % 4 == 0)// năm nhuận
		return true;
	if (ngay > 29 && thang == 2)
		return false;
	if (ngay == 31 && (thang == 4 || thang == 6 || thang == 9 || thang == 11))
		return false;
	return true;
}
bool kiemTraDinhDangGio(string&gioKh,string ngayKh)
{
	 tm ltm;
	time_t now = time(0);
	localtime_s(&ltm, &now);
	int ngay = stoi(ngayKh.substr(0, 2));
	int thang = stoi(ngayKh.substr(3, 2));
	int nam = stoi(ngayKh.substr(ngayKh.size() - 4));
	int gio = stoi(gioKh.substr(0, 2));
	int phut = stoi(gioKh.substr(gioKh.size() - 2));

	if (gioKh.find(':') != 2 || gioKh.find_last_of(':') != 2)
		return false;
	if (gio > 23 || phut > 59 )
		return false;
	if (nam == 1900 + ltm.tm_year && thang == 1 + ltm.tm_mon && ngay == ltm.tm_mday)
	{
		if ((gio < ltm.tm_hour ) || (gio == ltm.tm_hour && phut < ltm.tm_min ))
			return false;
	}
	return true;
}
bool kiemTraMayBayCoTonTaiKhong(LISTMB listMb, string s,int &mayBay)
{
	for (int i = 0; i < listMb.n; i++)
	{
		if (listMb.nodes[i]->soHieuMB == s)
		{
			mayBay = i;
			return true;
		}
	}
	return false;
}
bool kiemTraMaChuyenBayCoTonTaiKhong(LISTCB listCb, string s)
{
	for (NODECB*k=listCb.head;k!=NULL;k=k->next)
	{
		if (k->data.maCB==s)
		{
			return true;
		}
	}
	return false;
}
bool kiemTraChuyenBayCach1Ngay(string soHieuMB, string ngayKh, string gioKh, LISTCB listCb, string& maCb)
{
	string ngay = ngayKh.substr(0, 2);
	string thang = ngayKh.substr(3, 2);
	string nam = ngayKh.substr(ngayKh.size() - 4);
	int gio = stoi(gioKh.substr(0, 2));
	int temp = stoi(nam + thang + ngay);
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.mayBay.soHieuMB == soHieuMB && (k->data.trangThai == 1 || k->data.trangThai == 2))
		{
			string ngay2 = k->data.ngayKh.substr(0, 2);
			string thang2 = k->data.ngayKh.substr(3, 2);
			string nam2 = k->data.ngayKh.substr(k->data.ngayKh.size() - 4);
			int gio2 = stoi(k->data.gioKh.substr(0, 2));
			int temp2 = stoi(nam2 + thang2 + ngay2);
			maCb = k->data.maCB;
			if (temp == temp2)
				return false;
			if ((temp < temp2 && abs(temp - temp2) <= 1 && gio2 < gio) || (temp > temp2 && abs(temp2 - temp) <= 1 && gio < gio2))//cách < hơn 1 ngày
				return false;

		}
	}
	return true;
}
string tachNgay(NODECB* k)
{
	string ngay, thang, nam;
	ngay = k->data.ngayKh.substr(0, 2);
	thang = k->data.ngayKh.substr(3, 2);
	nam = k->data.ngayKh.substr(k->data.ngayKh.size() - 4);
	return nam + thang + ngay;
}
void sapXepChuyenBayTangDanTheoNgay(LISTCB& listCb)
{
	string ngayKh1, ngayKh2;
	NODECB* temp = new NODECB;
	for (NODECB* k = listCb.head; k->next != NULL; k = k->next)
	{
		ngayKh1 = tachNgay(k);
		for (NODECB* t = k->next; t != NULL; t = t->next)
		{
			ngayKh2 = tachNgay(t);
			if (ngayKh1 > ngayKh2)
			{
				temp->data = k->data;
				k->data = t->data;
				t->data = temp->data;
				ngayKh1 = tachNgay(k);
				ngayKh2 = tachNgay(t);

			}
			else if (ngayKh1 == ngayKh2)
			{
				if (k->data.gioKh > t->data.gioKh)
				{
					temp->data = k->data;
					k->data = t->data;
					t->data = temp->data;
					ngayKh1 = tachNgay(k);
					ngayKh2 = tachNgay(t);
				}
			}
		}
	}
}
void inDanhSachCacChuyenBay(LISTCB& listCb)
{
	if (listCb.head == NULL)
	{
		SetBGColor(4);
		SetColor(15);
		gotoxy(85, 10); cout << " DANH SACH CHUYEN BAY TRONG ";
		Sleep(2000);
		return;
	}
	int x = XMAX-20;
	int y = YMAX - 1;
	system("cls");
	char c = 205;
	SetColor(46);
	gotoxy(85, 4); cout << "DANH SACH CHUYEN BAY";
	gotoxy(x + 5, y - 3); cout << "MA CHUYEN BAY";
	gotoxy(x + 28, y - 3); cout << "NGAY KHOI HANH";
	gotoxy(x + 48, y - 3); cout << "GIO KHOI HANH";
	gotoxy(x + 68, y - 3); cout << "SAN BAY DEN";
	gotoxy(x + 88, y - 3); cout << "TRANG THAI";
	gotoxy(x + 103, y - 3); cout << "SO HIEU MAY BAY";
	SetColor(31);
	gotoxy(x, y-2);
	for (int t = 0; t < 120; t++)
	{
		cout << c;
	}
	for (NODECB*k=listCb.head;k!=NULL;k=k->next)
	{
		gotoxy(x + 10, y - 1);
		cout <<k->data.maCB;
		gotoxy(x + 30, y - 1);
		cout << k->data.ngayKh;
		gotoxy(x + 50, y - 1);
		cout << k->data.gioKh;
		gotoxy(x + 70, y - 1);
		cout << k->data.sanBayDen;
		gotoxy(x + 90, y - 1);
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
		gotoxy(x + 110, y - 1);
		cout << k->data.mayBay.soHieuMB;
			gotoxy(x, y);
			char c = 205;
			for (int t = 0; t < 120; t++)
			{
				cout << c;
			}
			y += 2;
		
	}

}
void themChuyenBay(LISTCB& listCb,LISTMB& listMb)
{
	QUAYLAI:
	int x = XMAX + 100;
	int y = YMAX;
	string s;
	CHUYENBAY cb;
	SetBGColor(7);
	SetColor(13);
	gotoxy(x + 20, y + 11); cout << " THEM CHUYEN BAY ";     
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 40, y + 9); cout << " F5: NHAP LAI ";
	SetColor(31);
	SetBGColor(0);
	gotoxy(x + 5, y + 12); cout << "MA CHUYEN BAY: ";
	gotoxy(x + 5, y + 14); cout << "NGAY KHOI HANH: "; gotoxy(x + 25, y + 14); cout << "THANG: "; gotoxy(x + 35, y + 14); cout << "NAM: ";
	gotoxy(x + 5, y + 16); cout << "GIO KHOI HANH(hh:mm): ";
	gotoxy(x + 5, y + 18); cout << "SAN BAY DEN: ";
	gotoxy(x + 5, y + 20); cout << "TRANG THAI(O:HUY,1:CON,2:HET,3:HOAN THANH): ";
	gotoxy(x + 5, y + 22); cout << "SO HIEU MAY BAY: ";
	gotoxy(x + 20, y + 12); cout << "                                                 ";
	gotoxy(x + 21, y + 14); cout << "    ";
	gotoxy(x + 32, y + 14); cout << "   ";
	gotoxy(x + 40, y + 14); cout << "     ";
	gotoxy(x + 30, y + 16); cout << "                                     ";
	gotoxy(x + 20, y + 18); cout << "                                                 ";
	gotoxy(x + 49, y + 20); cout << "                   ";
	gotoxy(x + 25, y + 22); cout << "                                                 ";
	                                   //-------------
NHAPMACHUYENBAY:
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 20, y + 12); cout << "                                                 ";
	gotoxy(x + 20, y + 12);
	s.clear();
	char c;
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
				gotoxy(x + 20, y + 12); cout << c; x++;
				if (s.size() > 15)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 20, y + 12); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d== BACK)
							goto QUAYLAI;
						if (d == ESC)
							 return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	x = XMAX + 100;
	if (s.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP MA CHUYEN BAY !        ";
		goto NHAPMACHUYENBAY;
	}
	for(NODECB*k=listCb.head;k!=NULL;k=k->next)
	{
		if (k->data.maCB == s)
		{
			gotoxy(x+ 5, y + 24);  cout << "MA CHUYEN BAY DA TON TAI!        ";
			goto NHAPMACHUYENBAY;
		}
	}
	if (s.size() > 15)
	{

		gotoxy(x + 5, y + 24);  cout << "HAY NHAP LAI MA CHUYEN BAY !        ";
		goto NHAPMACHUYENBAY;
	}
	gotoxy(x+ 5, y + 24); cout<< "                                     ";
	cb.maCB = s;
	SetColor(31);
	                               //-------------
NHAPNGAY:
	string ngay;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 21, y + 14); cout << "    ";
	gotoxy(x + 21, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				ngay.push_back(c);
				gotoxy(x + 21, y + 14); cout << c; x++;
				if (ngay.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (ngay.size() > 0)
				{
					ngay.erase(ngay.size() - 1);
					gotoxy(x + 21, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (ngay.empty() == true)
	{
		gotoxy(x+5, y + 24); cout << "HAY NHAP NGAY KHOI HANH !                             ";
		goto NHAPNGAY;
	}
	if (stoi(ngay)>31)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP LAI NGAY KHOI HANH !                             ";
		goto NHAPNGAY;
	}
	gotoxy(x, y + 24); cout << "                                               ";
	SetColor(31);
                                     	//-------------
NHAPTHANG:
	string thang;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 32, y + 14); cout << "   ";
	gotoxy(x + 32, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				thang.push_back(c);
				gotoxy(x + 32, y + 14); cout << c; x++;
				if (thang.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (thang.size() > 0)
				{
					thang.erase(thang.size() - 1);
					gotoxy(x + 32, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (ngay.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP THANG KHOI HANH !                             ";
		goto NHAPTHANG;
	}
	if (stoi(thang) > 12)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP LAI THANG KHOI HANH !                             ";
		goto NHAPTHANG;
	}
	gotoxy(x, y + 24); cout << "                                               ";
	SetColor(31);
NHAPNAM:
	string nam;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 40, y + 14); cout << "     ";
	gotoxy(x + 40, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				nam.push_back(c);
				gotoxy(x + 40, y + 14); cout << c; x++;
				if (nam.size() > 4)
					break;
			}
			if (c == BACK)
			{
				if (nam.size() > 0)
				{
					nam.erase(nam.size() - 1);
					gotoxy(x + 40, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (nam.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP NAM KHOI HANH !                             ";
		goto NHAPNAM;
	}
	if (nam.size()>4)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP LAI NAM KHOI HANH !                             ";
		goto NHAPNAM;
	}
	gotoxy(x, y + 24); cout << "                                               ";
	cb.ngayKh = ngay+"/" + thang+"/" + nam;
	chuanHoaNgay(cb.ngayKh);
	if (kiemTraDinhDangNgay(cb.ngayKh) == false|| kiemTraNgayKhSoVoiThoiGianThat(cb.ngayKh)==false)
	{
		SetColor(12);
		gotoxy(x + 5, y + 24); cout << "NGAY KHOI HANH KHONG HOP LY !                             ";
		gotoxy(x + 32, y + 14); cout << "   ";
		gotoxy(x + 40, y + 14); cout << "     ";
		goto NHAPNGAY;
	}
NHAPGIO:
	x = XMAX + 100;
	SetColor(14);
	gotoxy(x + 30, y + 16); cout << "                                     ";
	gotoxy(x + 30, y + 16);
	s.clear();
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9' || c == ':')
			{
				s.push_back(c);
				gotoxy(x + 30, y + 16); cout << c; x++;
				if (s.size() > 5)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 30, y + 16); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (s.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP GIO KHOI HANH !                             ";
		goto NHAPGIO;
	}
	if (s.size() != 5 || kiemTraDinhDangGio(s, cb.ngayKh) == false)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP LAI GIO KHOI HANH !                             ";
		goto NHAPGIO;
	}
	gotoxy(x, y + 24); cout << "                                               ";

	cb.gioKh = s;
	SetColor(31);
	                                //-------------
NHAPSANBAYDEN:
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 20, y + 18); cout << "                                                 ";
	gotoxy(x + 20, y + 18);
	s.clear();
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9'||c==32)
			{
				if (c >= 'a' && c < +'z')
					c = c - 32;
				s.push_back(c);
				gotoxy(x + 20, y + 18); cout << c; x++;
				if (s.size() > 40)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 20, y + 18); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	x = XMAX + 100;
	if (s.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP SAN BAY DEN !        ";
		goto NHAPSANBAYDEN;
	}
	if (s.size() > 40)
	{

		gotoxy(x + 5, y + 24);  cout << "HAY NHAP LAI SAN BAY DEN !        ";
		goto NHAPSANBAYDEN;
	}
	gotoxy(x + 5, y + 24); cout << "                                     ";
	cb.sanBayDen = s;
	SetColor(31);
	                                 //-------------
	NHAPTRANGTHAI:
	x = XMAX + 100;
	SetColor(14);
	gotoxy(x + 49, y + 20); cout << "                   ";
	gotoxy(x + 49, y + 20);
	s.clear();
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '3' )
			{
				
				 s.push_back(c);
				gotoxy(x + 49, y + 20); cout << c; x++;
				if (s.size() > 1)
					break;

			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 49, y + 20); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	gotoxy(x, y + 24); cout << "                                        ";
	SetColor(31);
	if (stoi(s) > 3 || stoi(s) < 0)
	{
		SetColor(12);
		gotoxy(x + 5, y + 24);  cout << "HAY NHAP LAI TRANG THAI !        ";
		goto NHAPTRANGTHAI;
	}
	cb.trangThai = stoi(s);
	             //--------------
NHAPSOHIEUMAYBAY:
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 25, y + 22); cout << "                                                 ";
	gotoxy(x + 25, y + 22);
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
				gotoxy(x + 25, y + 22); cout << c; x++;
				if (s.size() > 40)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 25, y + 22); cout << "\b \b"; x--;
				}
			}
			if (c == F1)
			{
				system("cls");
				inDanhSachCacMayBay(listMb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 5, y + 5); cout << "NHAN BACK DE HIEN BANG THEM CHUYEN BAY";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == BACK)
							goto QUAYLAI;
						if (d == ESC)
							return;
					}
				}
			}
			if (c == F5)
			{
				themChuyenBay(listCb, listMb);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	x = XMAX + 100;
	if (s.empty() == true)
	{
		gotoxy(x + 5, y + 24); cout << "HAY NHAP SO HIEU MAY BAY!                         ";
		goto NHAPSOHIEUMAYBAY;
	}
	if (s.size() > 15)
	{

		gotoxy(x + 5, y + 24);  cout << "HAY NHAP LAI SO HIEU MAY BAY !                ";
		goto NHAPSOHIEUMAYBAY;
	}

	int mayBay; //lấy máy bay
	string maCb;
	if (kiemTraMayBayCoTonTaiKhong(listMb, s,mayBay) == false)
	{
		gotoxy(x + 5, y + 24);  cout << "MAY BAY KHONG TON TAI !!                ";
		goto NHAPSOHIEUMAYBAY;
	}
	if (kiemTraChuyenBayCach1Ngay(s, cb.ngayKh, cb.gioKh, listCb, maCb) == false)
	{
		gotoxy(x + 5, y + 24);  cout << "MAY BAY DANG CO CHUYEN BAY " << maCb << " !";
		goto NHAPSOHIEUMAYBAY;
	}
	gotoxy(x + 5, y + 24); cout << "                                     ";
	cb.mayBay.soHieuMB= listMb.nodes[mayBay]->soHieuMB;
	cb.mayBay.loaiMB = listMb.nodes[mayBay]->loaiMB;
	cb.mayBay.soCho = listMb.nodes[mayBay]->soCho;
	cb.danhSachVe.ve = new string[listMb.nodes[mayBay]->soCho];
	SetColor(31);
	NODECB* p = taoNodeCB(cb);
	pushBackLCB(listCb, p);
	SetColor(46);
	gotoxy(x + 10, y + 26); cout << "THONG BAO";
	gotoxy(x + 5, y + 28); cout << "THEM CHUYEN BAY " << cb.maCB << " THANH CONG !";
	Sleep(1000);
	system("cls");
	SetColor(31);
	sapXepChuyenBayTangDanTheoNgay(listCb);
	ghiFileDanhSachChuyenBay(listCb);
}
void suaChuyenBay(LISTCB listCb, int i)
{
QUAYLAI:
	int x = XMAX + 100;
	int y = YMAX;
	string s;
	char c;
	CHUYENBAY cb;
	NODECB* nodeCb=new NODECB ;
	int temp = 0;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (temp++ == i)
		{
			nodeCb = k;
			break;
		}
	}
	if (nodeCb->data.trangThai == 0 || nodeCb->data.trangThai == 3)
	{
		SetColor(16);
		SetBGColor(3);
		gotoxy(x + 10, y + 12); cout << " CHUYEN BAY DA HOAN TAT NEN KHONG THE SUA ";
		SetColor(31);
		SetBGColor(0);
		Sleep(2000);
		return;
	}


	SetBGColor(7);
	SetColor(13);
	gotoxy(x + 10, y + 12); cout << " SUA CHUYEN BAY ";
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 40, y + 12); cout << " F5: NHAP LAI ";
	SetColor(31);
	SetBGColor(0);
	gotoxy(x + 5, y + 14); cout << "NGAY KHOI HANH: "; gotoxy(x + 25, y + 14); cout << "THANG: "; gotoxy(x + 35, y + 14); cout << "NAM: ";
	gotoxy(x + 5, y + 16); cout << "GIO KHOI HANH MOI(hh:mm): ";
	gotoxy(x + 32, y + 14); cout << "   ";
	gotoxy(x + 40, y + 14); cout << "     ";
	gotoxy(x + 35, y + 16); cout << "                                     ";
	//-------------
	
NHAPNGAY:
	string ngay;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 21, y + 14); cout << "    ";
	gotoxy(x + 21, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				ngay.push_back(c);
				gotoxy(x + 21, y + 14); cout << c; x++;
				if (ngay.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (ngay.size() > 0)
				{
					ngay.erase(ngay.size() - 1);
					gotoxy(x + 21, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F5)
			{
				suaChuyenBay(listCb, i);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (ngay.empty() == true)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP NGAY KHOI HANH !                             ";
		goto NHAPNGAY;
	}
	if (stoi(ngay) > 31)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP LAI NGAY KHOI HANH !                             ";
		goto NHAPNGAY;
	}
	gotoxy(x, y + 24); cout << "                                                         ";
	SetColor(31);
	//-------------
NHAPTHANG:
	string thang;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 32, y + 14); cout << "   ";
	gotoxy(x + 32, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				thang.push_back(c);
				gotoxy(x + 32, y + 14); cout << c; x++;
				if (thang.size() > 2)
					break;
			}
			if (c == BACK)
			{
				if (thang.size() > 0)
				{
					thang.erase(thang.size() - 1);
					gotoxy(x + 32, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F5)
			{
				suaChuyenBay(listCb, i);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (ngay.empty() == true)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP THANG KHOI HANH !                             ";
		goto NHAPTHANG;
	}
	if (stoi(thang) > 12)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP LAI THANG KHOI HANH !                             ";
		goto NHAPTHANG;
	}
	gotoxy(x, y + 18); cout << "                                                           ";
	SetColor(31);
NHAPNAM:
	string nam;
	SetColor(14);
	x = XMAX + 100;
	gotoxy(x + 40, y + 14); cout << "     ";
	gotoxy(x + 40, y + 14);
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9')
			{
				nam.push_back(c);
				gotoxy(x + 40, y + 14); cout << c; x++;
				if (nam.size() > 4)
					break;
			}
			if (c == BACK)
			{
				if (nam.size() > 0)
				{
					nam.erase(nam.size() - 1);
					gotoxy(x + 40, y + 14); cout << "\b \b"; x--;
				}
			}
			if (c == F5)
			{
				suaChuyenBay(listCb, i);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (nam.empty() == true)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP NAM KHOI HANH !                             ";
		goto NHAPNAM;
	}
	if (nam.size() > 4)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP LAI NAM KHOI HANH !                             ";
		goto NHAPNAM;
	}
	gotoxy(x, y + 24); cout << "                                                        ";

	cb.ngayKh = ngay + "/" + thang + "/" + nam;
	chuanHoaNgay(cb.ngayKh);
	if (kiemTraDinhDangNgay(cb.ngayKh) == false || kiemTraNgayKhSoVoiThoiGianThat(cb.ngayKh) == false)
	{
		SetColor(12);
		gotoxy(x + 5, y + 18); cout << "NGAY KHOI HANH KHONG HOP LY !                             ";
		gotoxy(x + 32, y + 14); cout << "   ";
		gotoxy(x + 40, y + 14); cout << "     ";
		goto NHAPNGAY;
	}
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		string ngay1, thang1, nam1, ngay2, thang2, nam2;
		int gio1, gio2, temp1, temp2;
		ngay1 = k->data.ngayKh.substr(0, 2);
		thang1 = k->data.ngayKh.substr(3, 2);
		nam1 = k->data.ngayKh.substr(k->data.ngayKh.size() - 4);
		gio1 = stoi(k->data.gioKh.substr(0, 2));
		temp1 = stoi(nam + thang + ngay);
		ngay2 = nodeCb->data.ngayKh.substr(0, 2);
		thang2 = nodeCb->data.ngayKh.substr(3, 2);
		nam2 = nodeCb->data.ngayKh.substr(nodeCb->data.ngayKh.size() - 4);
		gio2 = stoi(nodeCb->data.gioKh.substr(0, 2));
		temp2 = stoi(nam2 + thang2 + ngay2);
		if ((k->data.ngayKh == cb.ngayKh)&&(nodeCb->data.mayBay.soHieuMB==k->data.mayBay.soHieuMB)&&(k->data.maCB!=nodeCb->data.maCB))
		{
			SetColor(46);
			gotoxy(x + 10, y + 18); cout << " MAY BAY DA CO CHUYEN BAY KHAC VAO NGAY NAY    ";
			gotoxy(x + 32, y + 14); cout << "   ";
			gotoxy(x + 40, y + 14); cout << "     ";
			goto NHAPNGAY;
		}
		else if (((k->data.ngayKh == cb.ngayKh)||(temp1-temp2==1&&gio1<gio2)|| (temp2- temp1==1 && gio1 > gio2)) && (k->data.maCB != nodeCb->data.maCB))
		{
		
			for (int i = 0; i < k->data.mayBay.soCho; i++)
			{
				for (int t = 0; t < nodeCb->data.mayBay.soCho; t++)
				{
					if (k->data.danhSachVe.ve[i] == nodeCb->data.danhSachVe.ve[t])
					{
						
						SetColor(46);
							gotoxy(x + 10, y + 18); cout << " DA CO HANH KHACH DAT CHUYEN BAY VAO NGAY NAY    ";
							gotoxy(x + 32, y + 14); cout << "   ";
							gotoxy(x + 40, y + 14); cout << "     ";
							goto NHAPNGAY;

					}
				}
			}
		}
	
	}
	gotoxy(x + 10, y + 18); cout << "                                                      ";
NHAPGIOKHOIHANH:
	x = XMAX + 100;
	SetColor(14);
	gotoxy(x + 35, y + 16); cout << "                                     ";
	gotoxy(x + 35, y + 16);
	s.clear();
	while (1)
	{
		if (_kbhit)
		{
			c = _getch();
			if (c >= '0' && c <= '9' || c == ':')
			{
				s.push_back(c);
				gotoxy(x + 35, y + 16); cout << c; x++;
				if (s.size() > 5)
					break;
			}
			if (c == BACK)
			{
				if (s.size() > 0)
				{
					s.erase(s.size() - 1);
					gotoxy(x + 35, y + 16); cout << "\b \b"; x--;
				}
			}
			if (c == F5)
			{
				suaChuyenBay(listCb, i);
				return;
			}
			if (c == ESC)
				return;
			if (c == ENTER)
				break;
		}
	}
	x = XMAX + 100;
	SetColor(12);
	if (s.empty() == true)
	{
		gotoxy(x + 5, y + 18); cout << "HAY NHAP GIO KHOI HANH !                             ";
		goto NHAPGIOKHOIHANH;
	}
	if (s.size() != 5 || kiemTraDinhDangGio(s, cb.ngayKh) == false)
	{

		gotoxy(x + 5, y + 18);  cout << "HAY NHAP LAI GIO KHOI HANH !        ";
		goto NHAPGIOKHOIHANH;
	}
	gotoxy(x, y + 18); cout << "                                                       ";
	cb.gioKh = s;	
	//cập nhật
				nodeCb->data.gioKh = cb.gioKh;
				nodeCb->data.ngayKh = cb.ngayKh;
		
		SetColor(46);
		gotoxy(x + 10, y + 20); cout << "THONG BAO";
		gotoxy(x + 5, y + 22); cout << "CAP NHAT CHUYEN BAY " << nodeCb->data.maCB << " THANH CONG !";
		Sleep(1000);
		system("cls");
		SetColor(31);
		sapXepChuyenBayTangDanTheoNgay(listCb);
		ghiFileDanhSachChuyenBay(listCb);
	
}
void luaChonSuaChuyenBay(LISTCB listCb)
{
	if (listCb.head == NULL)
	{
		SetBGColor(4);
		SetColor(15);
		gotoxy(85, 10); cout << " DANH SACH CHUYEN BAY TRONG ";
		return;
	}
	inDanhSachCacChuyenBay(listCb);
	SetColor(11);
	SetBGColor(5);
	gotoxy(XMAX + 105, YMAX - 2); cout << " ESC : QUAY LAI ";
	gotoxy(XMAX + 105, YMAX); cout << "ENTER DE SUA CHUYEN BAY !";
	SetColor(31);
	SetBGColor(0);
	int x = XMAX - 10;
	int y = YMAX - 2;
	int x1 = x;
	int y1 = y;
	string* s = new string[dem(listCb)];
	int temp = 0;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		s[temp] = k->data.maCB;
		gotoxy(x, y);
		cout << s[temp];
		y += 2;
		temp++;
	}
	y = YMAX - 2;
	gotoxy(x, y);
	SetBGColor(4);
	int i = 0;
	cout << s[i];
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}
			if (c == UP) {
				if (y == 8) {
					y = YMAX + dem(listCb) * 2 - 4;
					i = dem(listCb) - 1;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == YMAX + dem(listCb) * 2 - 4) {
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
				suaChuyenBay(listCb, i);
				luaChonSuaChuyenBay(listCb);
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << s[i1];
			gotoxy(x, y);
			SetBGColor(4);
			cout << s[i];
			SetBGColor(0);
			y1 = y;
			i1 = i;
		}
	}
	SetBGColor(0);

}
void huyChuyenBay(LISTCB &listCb, int i)
{

	int x = XMAX + 110;
	int y = YMAX + 10;
	int x1 = x;
	int y1 = y + 4;
	int i1 = 1;
	int temp = 0;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (temp++ == i && (k->data.trangThai == 3|| k->data.trangThai == 0))
		{
			SetColor(46);
			SetBGColor(0);
			gotoxy(XMAX + 120, y + 1); cout << "          THONG BAO";
			gotoxy(XMAX + 115, y + 3); cout << "CHUYEN BAY DA HOAN TAT NEN KHONG THE HUY !";
			Sleep(1500);
			system("cls");
			return;
		}
	}
	SetBGColor(0);
	SetColor(29);
	string thaoTac[2] = { "CO","KHONG" };
	gotoxy(x + 10, y); cout << "THONG BAO";
	gotoxy(x, y + 2); cout << "BAN CO CHAC MUON HUY CHUYEN BAY NAY ?";
	SetColor(31);
	gotoxy(x, y + 4); cout << "CO";
	gotoxy(x + 20, y + 4); cout << "KHONG";
	SetBGColor(41);
	gotoxy(XMAX + 110, y + 4); cout << "CO";
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
			gotoxy(x, y1);
			SetBGColor(41);
			cout << thaoTac[i2];
			SetBGColor(0);
			x1 = x;
			i2 = i1;
		}
	}
	if (i1 == 1)
	{
		int temp = 0;
		for (NODECB* k = listCb.head; k != NULL; k = k->next)
		{
			
			 if (temp++ == i)
			{
				k->data.trangThai = 0;
				break;
			}
		}
		ghiFileDanhSachChuyenBay(listCb);
		SetColor(46);
		SetBGColor(0);
		gotoxy(XMAX + 120, y + 8); cout << "THONG BAO";
		gotoxy(XMAX + 115, y + 10); cout << "DA HUY THANH CONG !";
		Sleep(500);
		system("cls");
	}
	SetColor(31);
	SetBGColor(0);
}
void luaChonHuyChuyenBay(LISTCB& listCb)
{
	if (listCb.head == NULL)
	{
		SetBGColor(4);
		SetColor(15);
		gotoxy(85, 10); cout << " DANH SACH CHUYEN BAY TRONG ";
		return;
	}
	inDanhSachCacChuyenBay(listCb);
	SetColor(11);
	SetBGColor(5);
	gotoxy(XMAX + 105, YMAX-2); cout << " ESC : QUAY LAI ";
	gotoxy(XMAX + 105, YMAX); cout << " ENTER DE HUY CHUYEN BAY !";
	SetColor(31);
	SetBGColor(0);
	int x = XMAX - 10;
	int y = YMAX - 2;
	int x1 = x;
	int y1 = y;
	string* s = new string[dem(listCb)];
	int temp = 0;
	for (NODECB*k=listCb.head;k!=NULL;k=k->next)
	{
		s[temp] = k->data.maCB;
		gotoxy(x, y );
		cout << s[temp];
		y += 2;
		temp++;
	}
	y = YMAX - 2;
	gotoxy(x, y);
	SetBGColor(4);
	int i = 0;
	cout << s[i];
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}
			if (c == UP) {
				if (y == 8) {
					y = YMAX + dem(listCb) * 2-4;
					i = dem(listCb) - 1;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == YMAX + dem(listCb) * 2-4 ) {
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
				huyChuyenBay(listCb,i);
				luaChonHuyChuyenBay(listCb);
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << s[i1];
			gotoxy(x, y);
			SetBGColor(4);
			cout << s[i];
			SetBGColor(0);
			y1 = y;
			i1 = i;
		}
	}
	SetBGColor(0);
	
}
void xoaChuyenBay(LISTCB& listCb, int i)
{

	int x = XMAX + 110;
	int y = YMAX + 10;
	int x1 = x;
	int y1 = y + 4;
	int i1 = 1;
	int temp;
	SetBGColor(0);
	SetColor(29);
	string thaoTac[2] = { "CO","KHONG" };
	gotoxy(x + 10, y ); cout << "THONG BAO";
	gotoxy(x, y + 2); cout << "BAN CO CHAC MUON XOA CHUYEN BAY NAY ?";
	SetColor(31);
	gotoxy(x, y + 4); cout << "CO";
	gotoxy(x + 20, y + 4); cout << "KHONG";
	SetBGColor(41);
	gotoxy(XMAX + 110, y + 4); cout << "CO";
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
			gotoxy(x, y + 4);
			SetBGColor(41);
			cout << thaoTac[i2];
			SetBGColor(0);
			x1 = x;
			i2 = i1;
		}
	}
	if (i1 == 1)
	{
		if (i == 0)
		{
			NODECB* k = listCb.head;
			NODECB* p = k->next;
			k->next = NULL;
			listCb.head = p;
			delete k;
		}
		else if (i == dem(listCb) - 1)
		{
			NODECB* g=new NODECB;
			for (NODECB* k = listCb.head; k != NULL; k = k->next)
			{
				if (k == listCb.tail)
				{
					g->next = NULL;
					listCb.tail = g;
					
				}
				g = k;
			}
		}
		else
		{
			int temp = 0;
			for (NODECB* k = listCb.head; k->next != NULL; k = k->next)
			{
				if (++temp == i)
				{

					NODECB* p = k->next;
					k->next = p->next;
					delete p;
					break;
				}
			}
		}
		ghiFileDanhSachChuyenBay(listCb);
		SetColor(46);
		SetBGColor(0);
		gotoxy(XMAX + 120, y + 8); cout << "THONG BAO";
		gotoxy(XMAX + 115, y + 10); cout << "DA XOA THANH CONG !";
		Sleep(500);
		system("cls");
	}
	SetColor(31);
	SetBGColor(0);
}
void luaChonXoaChuyenBay(LISTCB& listCb)
{
	if (listCb.head == NULL)
	{
		SetBGColor(4);
		SetColor(15);
		gotoxy(85, 10); cout << " DANH SACH CHUYEN BAY TRONG ";
		return;
	}
	inDanhSachCacChuyenBay(listCb);
	SetColor(11);
	SetBGColor(5);
	gotoxy(XMAX + 105, YMAX - 2); cout << " ESC : QUAY LAI ";
	gotoxy(XMAX + 105, YMAX); cout << "ENTER DE XOA CHUYEN BAY !";
	SetColor(31);
	SetBGColor(0);
	int x = XMAX - 10;
	int y = YMAX - 2;
	int x1 = x;
	int y1 = y;
	string* s = new string[dem(listCb)];
	int temp = 0;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		s[temp] = k->data.maCB;
		gotoxy(x, y);
		cout << s[temp];
		y += 2;
		temp++;
	}
	y = YMAX - 2;
	gotoxy(x, y);
	SetBGColor(4);
	int i = 0;
	cout << s[i];
	int i1 = i;
	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
			}
			if (c == UP) {
				if (y == 8) {
					y = YMAX + dem(listCb) * 2 - 4;
					i = dem(listCb) - 1;
				}
				else {
					y -= 2;
					i--;
				}
			}
			if (c == DOWN) {
				if (y == YMAX + dem(listCb) * 2 - 4) {
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
				xoaChuyenBay(listCb, i);
				luaChonXoaChuyenBay(listCb);
				break;
			}
			gotoxy(x1, y1);
			SetBGColor(0);
			cout << s[i1];
			gotoxy(x, y);
			SetBGColor(4);
			cout << s[i];
			SetBGColor(0);
			y1 = y;
			i1 = i;
		}
	}
	SetBGColor(0);

}
//void inDanhSachVeTrong(LISTCB& listCb,LISTMB&listMb,NODEHK &tree)
//{
//	menuNhapMaChuyenBay();
//NHAPMACHUYENBAY:
//	
//	string maCB;
//	int x=XMAX+25, y=YMAX+6;
//	SetColor(11);
//	SetBGColor(5);
//	gotoxy(x+35, y); cout << " F1: DANH SACH CAC CHUYEN BAY ";
//	SetBGColor(7);
//	gotoxy(x, y ); cout << "                         ";
//	gotoxy(x, y );
//	SetColor(16);
//	while (1)
//	{
//		if (_kbhit)
//		{
//			char c = _getch();
//			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
//			{
//				if (c >= 'a' && c <= 'z')
//					c = c - 32;
//				maCB.push_back(c);
//				gotoxy(x +5, y); cout << c; x++;
//				if (maCB.size() > 15)
//					break;
//			}
//			if (c == BACK)
//			{
//				if (maCB.size() > 0)
//				{
//					maCB.erase(maCB.size() - 1);
//					gotoxy(x + 5, y ); cout << "\b \b"; x--;
//				}
//			}
//			if (c == F1)
//			{
//				system("cls");
//				SetBGColor(0);
//				inDanhSachCacChuyenBay(listCb);
//				SetColor(11);
//				SetBGColor(5);
//				gotoxy(x +80, y); cout << "NHAN ESC DE QUAY LAI";
//				SetColor(31);
//				SetBGColor(0);
//				while (1)
//				{
//					if (_kbhit)
//					{
//						char d = _getch();
//						if (d == ESC)
//						{
//							system("cls");
//							menuNhapMaChuyenBay();
//							goto NHAPMACHUYENBAY;
//						}
//					}
//				}
//			}
//			if (c == ESC)
//			{
//				SetBGColor(0);
//				return;
//			}
//			if (c == ENTER)
//				break;
//		}
//	}
//	SetColor(12);
//	SetBGColor(0);
//	x = XMAX + 25;
//	if (maCB.empty() == true)
//	{
//		gotoxy(x -5, y + 2); cout << "HAY NHAP MA CHUYEN BAY !        ";
//		goto NHAPMACHUYENBAY;
//	}
//		if (checkMaChuyenBayCoTonTaiKhong(listCb,maCB)==false)
//		{
//			gotoxy(x -5 , y + 2);  cout << "MA CHUYEN BAY KHONG TON TAI!        ";
//			goto NHAPMACHUYENBAY;
//		}
//	gotoxy(x + 5, y + 24); cout << "                                     ";
//	SetColor(31);
//
//	system("cls");
//	int a = 50, b = 10;
//	SetColor(11);
//	SetBGColor(5);
//	gotoxy(a + 130, b - 2); cout << " ESC: VE MENU ";
//	gotoxy(a + 130, b); cout << " BACK: NHAP MA CHUYEN BAY KHAC ";
//	gotoxy(a + 130, b+2); cout << " F2: DAT VE ";
//	SetColor(31);
//	SetBGColor(0);
//	gotoxy(a + 37, b - 2); cout << "DANH SACH CAC VE TRONG CUA CHUYEN BAY " << maCB;
//	SetColor(14);
//	for (NODECB* k = listCb.head; k != NULL; k = k->next)
//	{
//		if (k->data.maCB == maCB)
//		{
//			for (int i = 0; i < k->data.mayBay.soCho; i++)
//			{  
//				gotoxy(a, b);
//				if (k->data.danhSachVe.ve[i].empty() == true)
//					cout << i+1<<" ";
//				else cout << "    ";
//				a+=4;
//				if ((i+1) % 30 == 0)
//				{
//					b++;
//					a= 50;
//				}
//			}
//		}
//	}
//
//	while (1)
//	{
//		char c = _getch();
//		if (c == -32)
//			c = -getch();
//		if (c == BACK)
//		{
//			system("cls");
//			menuNhapMaChuyenBay();
//			goto NHAPMACHUYENBAY;
//		}
//		if (c == ESC)
//			return;
//	/*	if (c == F2)
//		{
//			loadFileDanhSachChuyenBay(listCb);
//			datVe(listMb, listCb, tree);
//			ghiFileDanhSachChuyenBay(listCb);
//			system("cls");
//			menuNhapMaChuyenBay();
//			goto NHAPMACHUYENBAY;
//		}*/
//	}
//}

