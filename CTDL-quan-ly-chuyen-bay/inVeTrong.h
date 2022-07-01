#pragma once

void inDanhSachVeTrong(LISTCB& listCb, LISTMB& listMb, NODEPTR& tree)
{
	menuNhapMaChuyenBay();
NHAPMACHUYENBAY:

	string maCB;
	int x = XMAX + 25, y = YMAX + 6;
	int cot = 35, hang = 15;
	SetColor(11);
	SetBGColor(5);
	gotoxy(x + 35, y - 1); cout << " F2: DANH SACH CAC CHUYEN BAY ";
	gotoxy(x + 35, y + 1); cout << " ESC: QUAY LAI ";
	SetBGColor(7);
	gotoxy(x, y); cout << "                         ";
	gotoxy(x, y);
	SetColor(16);
	while (1)
	{
		if (_kbhit)
		{
			char c = _getch();
			if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
			{
				if (c >= 'a' && c <= 'z')
					c = c - 32;
				maCB.push_back(c);
				gotoxy(x, y); cout << c; x++;
				if (maCB.size() > 15)
					break;
			}
			if (c == BACK)
			{
				if (maCB.size() > 0)
				{
					maCB.erase(maCB.size() - 1);
					gotoxy(x, y); cout << "\b \b"; x--;
				}
			}
			if (c == F2)
			{
				system("cls");
				SetBGColor(0);
				inDanhSachCacChuyenBay(listCb);
				SetColor(11);
				SetBGColor(5);
				gotoxy(x + 80, y); cout << " ESC: QUAY LAI";
				SetColor(31);
				SetBGColor(0);
				while (1)
				{
					if (_kbhit)
					{
						char d = _getch();
						if (d == ESC)
						{
							system("cls");
							menuNhapMaChuyenBay();
							goto NHAPMACHUYENBAY;
						}
					}
				}
			}
			if (c == ESC)
			{
				SetBGColor(0);
				return;
			}
			if (c == ENTER)
				break;
		}
	}
	SetColor(12);
	SetBGColor(0);
	x = XMAX + 25;
	if (maCB.empty() == true)
	{
		gotoxy(x - 5, y + 2); cout << "HAY NHAP MA CHUYEN BAY !        ";
		goto NHAPMACHUYENBAY;
	}
	if (ktraMaCB(listCb, maCB) == false)
	{
		gotoxy(x - 5, y + 2);  cout << "MA CHUYEN BAY KHONG TON TAI!        ";
		goto NHAPMACHUYENBAY;
	}
	gotoxy(x + 5, y + 24); cout << "                                     ";
	SetColor(31);

	system("cls");
	int a = 50, b = 10;
	SetColor(11);
	SetBGColor(5);
	gotoxy(a + 130, b - 2); cout << " ESC: MENU ";
	gotoxy(a + 130, b); cout << " BACK: QUAY LAI ";
	gotoxy(a + 130, b + 2); cout << " F2: DAT VE ";
	SetColor(14);
	SetBGColor(0);
	gotoxy(a + 37, b - 2); cout << " DANH SACH CAC VE TRONG CUA CHUYEN BAY " << maCB << " ";
	SetColor(31);
	SetBGColor(0);
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.maCB == maCB)
		{
			for (int i = 0; i < k->data.mayBay.soCho; i++)
			{
				gotoxy(a, b);
				if (k->data.danhSachVe.ve[i].empty() == true)
				{
					if (i < 9)
					{
						cout << "00" + to_string(i + 1);
					}
					else if (i < 99 && i >= 9)
					{
						cout << "0" + to_string(i + 1);
					}
					else
					{
						cout << i + 1;
					}
				}
				else cout << "    ";
				a += 4;
				if ((i + 1) % 30 == 0)
				{
					b += 2;
					a = 50;

				}
			}
		}
	}

	while (1)
	{
		char c = _getch();
		if (c == -32)
			c = -getch();
		if (c == BACK)
		{
			system("cls");
			menuNhapMaChuyenBay();
			goto NHAPMACHUYENBAY;
		}
		if (c == ESC)
			return;
		if (c == F2)
		{
			loadFileDanhSachChuyenBay(listCb);
			datVe(listMb, listCb, tree);
			ghiFileDanhSachChuyenBay(listCb);
			system("cls");
			menuNhapMaChuyenBay();
			goto NHAPMACHUYENBAY;
		}
	}
}