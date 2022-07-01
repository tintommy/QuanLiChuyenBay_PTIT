#pragma once
#include<iostream>
#include<string>
#define MAXLIST 300
using namespace std;
// ------- MAY BAY --------
struct MAYBAY
{
	string soHieuMB;
	string loaiMB;
	int soCho;
};

struct LISTMB
{
	int n = 0;
	MAYBAY* nodes[MAXLIST];
};

// ------- HANH KHACH ---------

struct HANHKHACH
{
	string soCCCD;
	string ho;
	string ten;
	bool phai; // true la nam, false la nu
}; typedef struct HANHKHACH HK;

struct NODEHK
{	
	HK data;
	int height;
	NODEHK* left;
	NODEHK* right;
}; 
typedef NODEHK* NODEPTR;

// -------- VE ---------

struct LISTVE
{
	int slVe = 0;
	string* ve;// 
	NODEPTR hk;

};

// ------- CHUYEN BAY ----------

struct CHUYENBAY
{
	string maCB;
	string ngayKh;
	string gioKh;
	string sanBayDen;
	int trangThai; // 0: huy 1: con 2: het vé 3: hoàn thành
	MAYBAY mayBay;
	LISTVE danhSachVe;
};

struct NODECB
{
	CHUYENBAY data;
	NODECB* next;
}; typedef struct NODECB* p;
struct LISTCB
{
	NODECB* head;
	NODECB* tail;
};

void khoiTaoLCB(LISTCB& lCb)
{
	lCb.head = NULL;
	lCb.tail = NULL;
}
NODECB* taoNodeCB(CHUYENBAY cb)
{
	NODECB* p = new NODECB;
	p->data = cb;
	p->next = NULL;
	return p;
}
void pushBackLCB(LISTCB& listCb, NODECB* p)
{
	if (listCb.head == NULL)
	{
		listCb.head = listCb.tail = p;
	}
	else
	{
		listCb.tail->next = p;
		listCb.tail = p;
	}
}
int dem(LISTCB listCb)
{
	int i = 0;
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		i++;
	}
	return i;
}

