#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"structData.h"
void loadFileDanhSachMayBay();
void ghiFileDanhSachMayBay();
void loadFileDanhSachChuyenBay();
void loadFileDanhSachMayBay(LISTMB& listMb)
{
	fstream f;
	f.open("danhSachMayBay.txt", ios::in);
	int i = 0;
	f >> listMb.n;
	f.ignore();
	for (i = 0; i < listMb.n; i++)
	{
		MAYBAY* mb = new MAYBAY;
		listMb.nodes[i] = new MAYBAY();
		f >> mb->loaiMB;
		f >> mb->soHieuMB;
		f >> mb->soCho;
		f.ignore();
		listMb.nodes[i] = mb;
	}
	f.close(); 
}
void ghiFileDanhSachMayBay(LISTMB& listMb)
{
	fstream f;
	f.open("danhSachMayBay.txt", ios::out);
	f << listMb.n << endl;
	for (int i = 0; i < listMb.n; i++)
	{
		f << listMb.nodes[i]->loaiMB << endl;
		f << listMb.nodes[i]->soHieuMB << endl;
		f << listMb.nodes[i]->soCho << endl;
	}
	f.close();
}
void loadFileDanhSachChuyenBay(LISTCB& listCb)
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	CHUYENBAY cb;
	fstream f;
	int n;
	int gio, phut, ngay, thang, nam;
	khoiTaoLCB(listCb);
	f.open("danhSachChuyenBay.txt", ios::in);
	f >> n;
	f.ignore();
	for (int i = 0; i < n; i++)
	{
		getline(f, cb.maCB);
		getline(f, cb.ngayKh);
		getline(f, cb.gioKh);
		gio = stoi(cb.gioKh.substr(0, 2));
		phut = stoi(cb.gioKh.substr(cb.gioKh.size() - 2));
		getline(f, cb.sanBayDen);
		f >> cb.trangThai;
		f.ignore();
		ngay = stoi(cb.ngayKh.substr(0, 2));
		thang = stoi(cb.ngayKh.substr(3, 2));
		nam = stoi(cb.ngayKh.substr(cb.ngayKh.size() - 4));
		if (nam < 1900 + ltm->tm_year || (nam == 1900 + ltm->tm_year && thang < 1 + ltm->tm_mon) || (nam == 1900 + ltm->tm_year && thang == 1 + ltm->tm_mon && ngay < ltm->tm_mday))
			cb.trangThai = 3;   //nếu ngày đã qua thì cho là hoàn thành
		if (nam == 1900 + ltm->tm_year && thang == 1 + ltm->tm_mon && ngay == ltm->tm_mday)
		{
			if ((gio < ltm->tm_hour) || (gio == ltm->tm_hour && phut < ltm->tm_min))
				cb.trangThai = 3;
		}
		getline(f, cb.mayBay.loaiMB);
		getline(f, cb.mayBay.soHieuMB);
		f >> cb.mayBay.soCho;
		f.ignore();
		cb.danhSachVe.ve = new string[cb.mayBay.soCho];
		NODECB* p = taoNodeCB(cb);
		pushBackLCB(listCb, p);
	}
	f.close();

}
void ghiFileDanhSachChuyenBay(LISTCB listCb)
{
	fstream f;
	int n;
	f.open("danhSachChuyenBay.txt", ios::out);
	f <<dem(listCb)<<endl;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		f << k->data.maCB << endl;
		f << k->data.ngayKh << endl;
		f << k->data.gioKh<< endl;
		f << k->data.sanBayDen << endl;
		f << k->data.trangThai << endl;
		f << k->data.mayBay.loaiMB<< endl;
		f << k->data.mayBay.soHieuMB << endl;
		f << k->data.mayBay.soCho << endl;
		
	}
	f.close();
}

void ghiFileDanhSachVe(LISTCB listCb)
{
	fstream f;
	f.open("danhSachVe.txt", ios::out);
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.danhSachVe.slVe > 0)
		{
			f << k->data.maCB << endl;
			f << k->data.danhSachVe.slVe << endl;
			int dem = 0;
			for (int i = 0; i < k->data.mayBay.soCho; i++)
			{
				if (k->data.danhSachVe.ve[i].empty() == false)
				{
					f << i << ",";
					f << k->data.danhSachVe.ve[i] << endl;
					dem++;
				}
				if (dem == k->data.danhSachVe.slVe)
					break;
			}
		}
	}
	f.close();
}
void loadFileDanhSachVe(LISTCB listCb)
{
	fstream f;
	f.open("danhSachVe.txt", ios::in);
	while (!f.eof())
	{
		string s;
		getline(f, s);
		for (NODECB* k = listCb.head; k != NULL; k = k->next)
		{
			if (k->data.maCB == s)
			{
				f >> k->data.danhSachVe.slVe;
				f.ignore();
				for (int j = 0; j < k->data.danhSachVe.slVe; j++)
				{
					int t;
					string soGhe;
					getline(f, soGhe, ',');
					t = stoi(soGhe);
					k->data.danhSachVe.ve[t].clear();
					getline(f, k->data.danhSachVe.ve[t]);
				}

			}
		}
	}
	f.close();
}