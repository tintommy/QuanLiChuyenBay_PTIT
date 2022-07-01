#pragma once

void danhSachHK(LISTCB listCb, LISTMB listMb, NODEPTR tree)
{
	menuNhapMaChuyenBay();
NHAPMACHUYENBAY:
	string maCB;
	int trang = 0, tongTrang = 0;
	NODECB* p = NULL;
	bool flag = false;
	while (flag == false)
	{
		int x = XMAX + 25, y = YMAX + 6;
		SetColor(11);
		SetBGColor(5);
		gotoxy(x + 35, y - 1); cout << " ESC: QUAY LAI ";
		gotoxy(x + 35, y + 1); cout << " F2: DANH SACH CAC CHUYEN BAY ";
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
					gotoxy(x + 77, y); cout << " ESC: QUAY LAI ";
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
			gotoxy(x - 5, y + 2); cout << "HAY NHAP MA CHUYEN BAY!               ";
			Sleep(1500);
			goto NHAPMACHUYENBAY;
		}
		if (ktraMaCB(listCb, maCB) == false)
		{
			gotoxy(x - 5, y + 2);  cout << "MA CHUYEN BAY KHONG TON TAI!          ";
			Sleep(1500);
			goto NHAPMACHUYENBAY;
		}
		else
		{
			p = timMaCB(listCb, maCB);
			flag = true;
		}
		gotoxy(x + 5, y + 24); cout << "                                ";
		SetColor(31);
		if (p->data.danhSachVe.slVe <= 10)
		{
			trang = 0;
			tongTrang = 1;
		}
		else
		{
			tongTrang = (int)(p->data.danhSachVe.slVe / 10) + 1;
		}
	}

	int danhDauTrangTiepTheo;
	int *danhDauStt = new int[(p->data.danhSachVe.slVe / 10) + 1];
	danhDauStt[0] = 1;
	int stt;
	int* danhDau = new int[(p->data.danhSachVe.slVe / 10) + 1];
	danhDau[0] = 0;
	int t = 0;
XUAT:
	system("cls");
	menuDanhSachHK();
	hienThiTrang(tongTrang, trang, 80, 30);
	SetColor(45);
	gotoxy(105, 2); cout << maCB;
	gotoxy(73, 3); cout << p->data.ngayKh;
	gotoxy(90, 3); cout << p->data.gioKh;
	gotoxy(107, 3); cout << p->data.sanBayDen;
	SetColor(0);
	SetColor(31); SetBGColor(0);
	gotoxy(tabX + 4, tabY + 3);
	int soCho = getsoCho(listMb, p->data.mayBay.soHieuMB);
	int dem = 0;
	stt = danhDauStt[t];
	for (int i = danhDau[t]; i < soCho; i++)
	{
		if (p->data.danhSachVe.ve[i] != "") {
			string CCCD;
			CCCD = p->data.danhSachVe.ve[i];
			NODEHK* h = timHK(tree, CCCD);
			string hoTen;
			hoTen = h->data.ho + " " + h->data.ten;
			SetColor(31);
			gotoxy(tabX + 39, tabY + 3 + dem * 2);	cout << stt++; // STT
			gotoxy(tabX + 49, tabY + 3 + dem * 2);	cout << i + 1; // So ve
			gotoxy(tabX + 58, tabY + 3 + dem * 2);	cout << p->data.danhSachVe.ve[i]; // cccd
			gotoxy(tabX + 78, tabY + 3 + dem * 2);	cout << hoTen;
			gotoxy(tabX + 111, tabY + 3 + dem * 2);
			switch (h->data.phai)
			{
			case 0:
			{
				cout << "NU";
				break;
			}
			case 1:
			{
				cout << "NAM";
				break;
			}
			default:
				break;
			}
			dem++;
			danhDauTrangTiepTheo = i;
			if (dem == 10)
				break;
		}
	}
	gotoxy(72, 32);
	cout << "[<-] Tro lai | Tiep Theo [->]";
	int c = 0;
	while (1)
	{
		do {
			c = getch();
		} while (c != LEFT && c != RIGHT && c != ESC);
		if (c == LEFT)
		{
			if (tongTrang > 1 && trang > 0)
			{
				t--;
				trang--;		
				goto XUAT;
			}
		}
		else if (c == RIGHT)
		{
			if (tongTrang > 1 && trang + 1 < tongTrang)
			{
				t++;
				danhDau[t] = danhDauTrangTiepTheo+1;
				danhDauStt[t] = stt;
				trang++;
				goto XUAT;
			}
		}
		else if (c == ESC)
		{
			system("cls");
			delete[]danhDau;
			delete[]danhDauStt;
			danhSachHK(listCb, listMb, tree);
			return;
		}
	}
}
