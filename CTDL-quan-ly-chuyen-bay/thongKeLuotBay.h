#pragma once
#include"xuLiFile.h"
#include"veMenu.h"

int thongKeLuotBay(LISTCB listCb, string soHieu)
{
	int dem = 0;
	NODECB* p = listCb.head;
	while (p != NULL)
	{
		if (p->data.mayBay.soHieuMB.compare(soHieu) == 0)
			if (p->data.trangThai == 3)
				dem++;
		p = p->next;
	}
	return dem;
}

void thongKeLuotBay(LISTCB listCb, LISTMB listMb)
{
	int trang = 0, tongTrang = 0, soMayBay = 0;
	string* sh = new string[listMb.n]; // mang chua so Hieu
	int* soLuot = new int[listMb.n]; // mang chua so luot
	int index = 0;
	for (int i = 0; i < listMb.n; i++)
	{
		sh[index] = string(listMb.nodes[i]->soHieuMB);
		soLuot[index] = thongKeLuotBay(listCb, listMb.nodes[i]->soHieuMB);
		index++; 
		soMayBay++;
	}
	for (int i = 0; i < listMb.n - 1; i++) {
		for (int j = listMb.n - 1; j > i; j--) {
			if (soLuot[j - 1] < soLuot[j]) {
				int m = soLuot[j - 1];
				string n = sh[j - 1];

				soLuot[j - 1] = soLuot[j];
				sh[j - 1] = sh[j];

				soLuot[j] = m;
				sh[j] = n;
			}
		}
	}
	if (soMayBay <= 13)
	{
		trang = 0;
		tongTrang = 1;
	}
	else
	{
		tongTrang = (int)(soMayBay / 13) + 1;
	}
	XUAT:
		system("cls");
		int a = 50, b = 10;
		SetColor(11);
		SetBGColor(5);
		gotoxy(a + 66, b - 2); cout << " ESC: MENU ";
		gotoxy(a + 66, b); cout << " BACK: QUAY LAI ";
		SetColor(31);
		SetBGColor(0);
		menuLuotBay();
		hienThiTrang(tongTrang, trang, 77, 34);
		gotoxy(tabX + 30, tabY + 3);
		// it hon 13 chuyen
		int dem = 0;
		for (int i = trang * 13; i < 13 + trang * 13 && i < listMb.n; i++)
		{
			SetColor(31);
			gotoxy(tabX + 70, tabY + 3 + dem * 2); cout << sh[i];
			gotoxy(tabX + 89, tabY + 3 + dem * 2); cout << soLuot[i];
			dem++;
		}
		gotoxy(72, 36);
		cout << "[<-] Tro lai | Tiep Theo [->]";

		int c = 0;
		while(1)
		{
		do {
			c = getch();
		} while (c != LEFT && c != RIGHT && c != ESC);
		if (c == LEFT)
		{
			if (tongTrang > 1 && trang > 0)
			{
				trang--;
				goto XUAT;
			}
		}
		else if (c == RIGHT)
		{
			if (tongTrang > 1 && trang + 1 < tongTrang)
			{
				trang++;
				goto XUAT;
			}
		}
		else if (c == ESC)
		{
			break;
		}
	}
}