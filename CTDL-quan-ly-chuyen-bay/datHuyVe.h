#include"xuLiFile.h"
#include"chuyenBay.h"

#define BACKSPACE 8
#define XMIN 18
#define YMIN 15
#define SMIN 60

// ---------- CAC HAM KIEM TRA -------------

void chuyenVeChuThuong(string& s) {
	for (int i = 0; i < s.size(); i++) {
		if(s[i]>=65&&s[i]<=90)
		s[i] = s[i]+32;
	}
}

void xoaKhoangTrang(string& s)

{
	while (s[s.size() - 1] == 32)
	{
		s.erase(s.size() - 1, 1);
	}
	while (s[0] == 32)
	{
		s.erase(0, 1);
	}
	for (int i = 0; i < s.size() - 1; i++)
	{
		if (s[i] == 32 && s[i + 1] == 32)
		{
			s.erase(i, 1);
			i--;
		}
	}
}

void inHoaDauTien(string& s)
{
	s[0] = toupper(s[0]);
	for (int i = 1; i < s.size(); i++)
	{
		if (s[i - 1] == 32)
			s[i] = toupper(s[i]);
	}
}

void stringToChar(string s)
{
	char* c = new char[s.size() + 1];
	copy(s.begin(), s.end(), c);
}

int themVe(LISTVE& dsv, int soGhe, string CCCD)
{
	if (dsv.ve[soGhe - 1].length() > 0)
		return 0;
	else
	{
		dsv.ve[soGhe - 1] = CCCD;
		dsv.slVe++;
		return 1;
	}
}

int xoaVe(LISTVE& dsv, int soGhe)
{
	if (dsv.ve[soGhe].length() > 0) {
		dsv.ve[soGhe].clear();
		dsv.slVe--;
		return 1;
	}
	else {
		return 0;
	}
}

int getsoCho(LISTMB listMb, string soHieu)
{
	for (int i = 0; i < listMb.n; i++)
	{
		if (listMb.nodes[i]->soHieuMB == soHieu)
			return listMb.nodes[i]->soCho;
	}
	return 0;
}

bool ktraTrangThaiVe(CHUYENBAY cb, int soCho)
{
	int dem = 0;
	for (int i = 0; i < soCho; i++)
	{
		if (cb.danhSachVe.ve[i] != "") // vé khác rỗng
		{
			dem++;
		}
	}
	if (dem == soCho)
	{
		return true;
	}
	else
	{
		return false;
	}
}

NODECB* timMaCB(LISTCB listCB, string maCB)
{
	for (NODECB* p = listCB.head; p != NULL; p = p->next)
	{
		if (p->data.maCB == maCB)
			return p;
	}
	return NULL;
}

bool ktraMaCB(LISTCB listCB, string maCB)
{
	for (NODECB* p = listCB.head; p != NULL; p = p->next)
	{

		if (p->data.maCB == maCB)
		{
			return true;
		}
	}
	return false;
}

bool ktraHanhKhachTrongCB(LISTVE& dsv, int soCho, string CCCD)
{
	for (int i = 0; i < soCho; i++)
	{
		if (dsv.ve[i] == CCCD)
			return true;
	}
	return false;
}

bool ktraHK(LISTVE dsv, int soCho)
{
	for (int i = 0; i < soCho; i++)
	{
		if (dsv.ve[i] != "")
			return true;
	}
	return false;
}

bool kiemTraChuyenBayCach1Ngay(string ngayKh, string gioKh, LISTCB listCb, string cccd)
{
	string ngay = ngayKh.substr(0, 2);
	string thang = ngayKh.substr(3, 2);
	string nam = ngayKh.substr(ngayKh.size() - 4);
	int gio = stoi(gioKh.substr(0, 2));
	int temp = stoi(nam + thang + ngay);
	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if ((k->data.trangThai == 1 || k->data.trangThai == 2))
		{
			if (ktraHanhKhachTrongCB(k->data.danhSachVe, k->data.mayBay.soCho, cccd) == true)
			{

				string ngay2 = k->data.ngayKh.substr(0, 2);
				string thang2 = k->data.ngayKh.substr(3, 2);
				string nam2 = k->data.ngayKh.substr(k->data.ngayKh.size() - 4);
				int gio2 = stoi(k->data.gioKh.substr(0, 2));
				int temp2 = stoi(nam2 + thang2 + ngay2);
				if (temp == temp2)
					return false;
				if ((temp < temp2 && abs(temp - temp2) <= 1 && gio2 < gio) || (temp > temp2 && abs(temp2 - temp) <= 1 && gio < gio2))//cách < hơn 1 ngày
					return false;
			}
		}
	}
	return true;
}

NODEHK* timHK(NODEPTR tree, string CCCD)
{
	if (tree != NULL)
	{
		while (tree != NULL)
		{
			if (tree->data.soCCCD == CCCD)
				return tree;
			else if (tree->data.soCCCD > CCCD)
				tree = tree->left;
			else if (tree->data.soCCCD < CCCD)
				tree = tree->right;
		}
	}
	return NULL;
}


// --------------- CAY HANH KHACH ---------------------
void khoiTaoCay(NODEPTR& tree)
{
	tree = NULL;
}

int timLonNhat(int a, int b) {
	if (a > b) {
		return a;
	}
	else
		return b;
}

NODEPTR minValueNode(NODEPTR node)
{
	NODEHK* c = node;

	while (c->left != NULL)
		c = c->left;

	return c;
}

int height(NODEPTR tree)
{
	if (tree == NULL)
		return 0;
	return tree->height;
}

int bf(NODEPTR tree)
{
	if (tree == NULL)
		return 0;
	return height(tree->left) - height(tree->right);
}

NODEPTR xoayTrai(NODEPTR x)
{
	NODEPTR y = x->right;
	NODEPTR T2 = y->left;

	// xoay
	y->left = x;
	x->right = T2;

	// cap nhat chieu cao cay
	x->height = timLonNhat(height(x->left), height(x->right)) + 1;
	y->height = timLonNhat(height(y->left), height(y->right)) + 1;

	return y;
}

NODEPTR xoayPhai(NODEPTR y)
{
	NODEPTR x = y->left;
	NODEPTR T2 = x->right;

	x->right = y;
	y->left = T2;

	y->height = timLonNhat(height(y->left), height(y->right)) + 1;
	x->height = timLonNhat(height(x->left), height(x->right)) + 1;

	return x;
}

NODEPTR newNode(HANHKHACH hk)
{
	NODEHK* node = new NODEHK();
	node->data = hk;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return(node);
}

NODEPTR themHKvaoCay(NODEPTR& tree, HANHKHACH hk)
{
	// nut them la nut dau tien
	if (tree == NULL)
	{
		return newNode(hk);
	}

	// phan tu them vao nho hon goc => nhanh trai
	if (hk.soCCCD < tree->data.soCCCD)
		tree->left = themHKvaoCay(tree->left, hk);
	// phan tu them vao lon hon goc => nhanh phai
	else if (hk.soCCCD > tree->data.soCCCD)
		tree->right = themHKvaoCay(tree->right, hk);
	else 
		return tree;

	// cap nhat chieu cao cay
	tree->height = 1 + timLonNhat(height(tree->left), height(tree->right));

	int balance = bf(tree);

	// trai-trai
	if (balance > 1 && hk.soCCCD < tree->left->data.soCCCD)
		return xoayPhai(tree);

	// phai-phai
	if (balance < -1 && hk.soCCCD > tree->right->data.soCCCD)
		return xoayTrai(tree);

	// trai-phai
	if (balance > 1 && hk.soCCCD > tree->left->data.soCCCD)
	{
		tree->left = xoayTrai(tree->left);
		return xoayPhai(tree);
	}

	// phai-trai
	if (balance < -1 && hk.soCCCD < tree->right->data.soCCCD)
	{
		tree->right = xoayPhai(tree->right);
		return xoayTrai(tree);
	}
	return tree;
}

// --------------- FILE -------------------

void ghiHKvaoFile(HANHKHACH& hk, fstream& fileOut)
{
	fileOut << hk.soCCCD << endl;
	fileOut << hk.ho << endl;
	fileOut << hk.ten << endl;
	fileOut << hk.phai << endl;
}

void ghiDanhSachHK(NODEPTR& tree, fstream& fileOut)
{
	if (tree != NULL)
	{
		ghiHKvaoFile(tree->data, fileOut);
		ghiDanhSachHK(tree->left, fileOut);
		ghiDanhSachHK(tree->right, fileOut);
	}
}

void ghiFileHK(HANHKHACH& hk)
{
	fstream fileOut;
	fileOut.open("hanhkhach.txt", ios::out | ios::app);
	{
		ghiHKvaoFile(hk, fileOut);
	}
	fileOut.close();
}

void ghiFileHKCay(NODEPTR tree)
{
	ofstream fileout;
	fileout.open("hanhkhachCay.txt", ios::out);
	if (fileout.fail())
	{
		cout << "Loi mo file hanh khach";
		return;
	}
	const int STACKSIZE = 10000;
	NODEPTR Stack[STACKSIZE];
	NODEPTR p = tree;
	int sp = -1; //Khai bao Stack rong
	do
	{
		while (p != NULL)
		{
			Stack[++sp] = p;
			p = p->left;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			fileout << p->data.soCCCD << "," << p->data.ho << "," << p->data.ten << "," << p->data.phai << endl;
			p = p->right;
		}
		else break;
	} while (1);
}

void loadFileHK(NODEPTR& tree)
{
	ifstream fileIn;
	fileIn.open("hanhkhachCay.txt", ios::in | ios::app);
	string tmp; // lay ky tu xuong dong 		
	while (!fileIn.eof())
	{
		string cccd;
		getline(fileIn, cccd, ',');
		if (cccd.empty() == false)
		{
			HANHKHACH hk;
			hk.soCCCD = cccd;
			getline(fileIn, hk.ho, ',');
			getline(fileIn, hk.ten, ',');
			fileIn >> hk.phai;
			fileIn.ignore();
			tree = themHKvaoCay(tree, hk);

		}
	}
	fileIn.close();
}

NODEPTR xoaHK(NODEPTR& root, HANHKHACH hk)
{

	if (root == NULL)
		return root;

	// xoa node nhanh trai
	if (hk.soCCCD < root->data.soCCCD)
		root->left = xoaHK(root->left, hk);

	// xoa node nhanh phai
	else if (hk.soCCCD > root->data.soCCCD)
		root->right = xoaHK(root->right, hk);

	// xoa nhanh con cua 2 nhanh
	else
	{
		// node 1 nhanh hoac 0
		if ((root->left == NULL) || (root->right == NULL))
		{
			NODEPTR temp = root->left ? root->left : root->right;

			// 0 nhanh
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // 1 con
				*root = *temp;
			free(temp);
		}
		else
		{
			// node co 2 nhanh con
			// nho nhat nhanh con ben phai
			NODEPTR temp = minValueNode(root->right);

			root->data.soCCCD = temp->data.soCCCD;

			root->right = xoaHK(root->right, temp->data);
		}
	}

	// cay chi co 1 nut goc
	if (root == NULL)
		return root;

	// cat nhap chieu cao cay cua node hien tai
	root->height = 1 + max(height(root->left),
		height(root->right));

	int balance = bf(root);

	// Left Left Case
	if (balance > 1 && bf(root->left) >= 0)
		return xoayPhai(root);

	// Left Right Case
	if (balance > 1 && bf(root->left) < 0)
	{
		root->left = xoayTrai(root->left);
		return xoayPhai(root);
	}

	// Right Right Case
	if (balance < -1 && bf(root->right) <= 0)
		return xoayTrai(root);

	// Right Left Case
	if (balance < -1 && bf(root->right) > 0)
	{
		root->right = xoayPhai(root->right);
		return xoayTrai(root);
	}
	return root;
}

int xacNhanXoaHK()
{
	int x = 78;
	SetColor(45);
	SetBGColor(7); 
	gotoxy(66, 15); cout << "                                             ";
	gotoxy(66, 16); cout << "    BAN CO MUON XOA HANH KHACH NAY KHONG?    ";
	gotoxy(66, 17); cout << "                                             ";
	gotoxy(66, 18); cout << "            CO              KHONG            ";
	gotoxy(66, 19); cout << "                                             ";
	SetBGColor(0);
	int keyhit;
	do {
		gotoxy(78, 18);	
		SetColor(0);
		SetBGColor(7);
		switch (x)
		{
		case 78: gotoxy(78, 18); cout << "CO"; break;
		case 94: gotoxy(94, 18); cout << "KHONG"; break;
		}
		keyhit = getch();
		if (keyhit == LEFT)
		{
			gotoxy(78, 18);
			SetColor(45);
			switch (x)
			{
			case 78: gotoxy(78, 18); cout << "CO"; ; break;
			case 84: gotoxy(94, 18); cout << "KHONG"; ; break;
			}
			x -= 16;
			if (x != 78)
			{
				x = 94;
			}
		}
		else if (keyhit == RIGHT)
		{
			gotoxy(94, 18);
			SetColor(45);
			switch (x)
			{
			case 78: gotoxy(78, 18); cout << "CO"; ; break;
			case 94:  gotoxy(94, 18); cout << "KHONG"; ; break;
			}
			x += 16;
			if (x != 94)
			{
				x = 78;
			}
		}
		else if (x == 78 && keyhit == ENTER)
		{
			gotoxy(XMIN + 62, 20);
			cout << "   XOA THANH CONG   ";
			Sleep(1000);
			SetBGColor(0);
			system("cls");
			return 1;
		}
		else if (x == 94 && keyhit == ENTER)
		{
			SetBGColor(0);
			system("cls");
			return 0;
		}
	} while (true);
}

void NhapHanhKhach(NODEPTR& tree, HANHKHACH &hk, string CCCD, int& dem)
{
	int checkTH = 0;
	hk.soCCCD = CCCD;
	bool trung;
	int tbX = 70, tbY = 16;
	// NHAP HO
	
	do
	{
		trung = false;
		char c;
		string s;
		int x = 102, y = 7;
		gotoxy(x, y); cout << "               ";
		
		gotoxy(102, 7);

		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == 32)
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
				{
					dem = 1;
					return;
				}
				if (c == ENTER) {
					hk.ho = s;
					break;
				}
				if (c == F5)
				{
					SetColor(31);
					SetBGColor(0);
					 NhapHanhKhach(tree, hk, CCCD, dem);
					return;
					
				}
			}
		}
		if (hk.ho.empty() == true)
		{
			gotoxy(tbX + 8, tbY); cout << "KHONG DE TRONG";
			Sleep(1000);
			gotoxy(102, 7);  cout << "                   ";
			gotoxy(tbX + 8, tbY); cout << "               ";
			SetBGColor(0);
		}
		else if (hk.ho.length() > 15) {
			gotoxy(XMAX + 55, YMIN - 1); cout << "HO KHONG QUA 15 KI TU!";
			Sleep(1000);
			gotoxy(102, 7);  cout << "              ";
			gotoxy(105, 14);  cout << "                      ";

		}
		else
		{
			chuyenVeChuThuong(hk.ho); xoaKhoangTrang(hk.ho); inHoaDauTien(hk.ho);
			checkTH++; // 1
			gotoxy(102, 7);  cout << "                                 ";
			gotoxy(102, 7); cout << hk.ho;
			trung = true;
		}
	} while (trung == false);

	// NHAP TEN
	do
	{
		trung = false;
		string s;
		char c;
		int x = 102, y = 9;
		gotoxy(x, y); cout << "               ";
		gotoxy(102, 9);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == 32)
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
				{
					dem = 1;
					return;
				}
				if (c == ENTER) {
					hk.ten = s;
					break;
				}
				if (c == F5)
				{
					SetColor(31);
					SetBGColor(0);
					NhapHanhKhach(tree, hk, CCCD, dem);
					return;
				}
			}
		}
		if (hk.ten.empty() == true)
		{
			gotoxy(tbX + 8, tbY); cout << "KHONG DE TRONG";
			Sleep(1000);
			gotoxy(102, 9);  cout << "                   ";
			gotoxy(tbX + 8, tbY); cout << "               ";
			SetBGColor(0);
		}
		else
		{
			chuyenVeChuThuong(hk.ten); xoaKhoangTrang(hk.ten); inHoaDauTien(hk.ten);
			checkTH++; // 2
			gotoxy(102, 9);  cout << "                                 ";
			gotoxy(102, 9); cout << hk.ten;
			trung = true;
		}
	} while (trung == false);

	// CHON PHAI (NAM/NU)
	do
	{
		int x = 102, y = 11;
		trung = false;
		int keyhit;

		gotoxy(107, y); cout << "NU";    // tao lua chon
		do
		{
			gotoxy(x, y);
			SetColor(45);
			gotoxy(x + 5, y);
			SetColor(45);

			switch (x)
			{
			case 102: gotoxy(102, y); cout << "NAM"; break; // dieu khien nháy trỏ
			case 107: gotoxy(107, y); cout << "NU"; break;
			}
			keyhit = getch();
			if (keyhit == LEFT)
			{
				gotoxy(x, y);
				SetColor(31);
				switch (x)
				{
				case 102: gotoxy(102, y); cout << "NAM"; break;
				case 107: gotoxy(107, y); cout << "NU"; break;
				}
				x -= 5;
				if (x != 102)
				{
					x = 107;
				}
			}
			else if (keyhit == RIGHT)
			{
				gotoxy(x + 5, y);
				SetColor(31);
				switch (x)
				{
				case 102: gotoxy(102, y); cout << "NAM"; break;
				case 107: gotoxy(107, y); cout << "NU"; break;
				}
				x += 5;
				if (x != 107)
				{
					x = 102;
				}
			}
			else if (keyhit == ENTER)
			{
				if (x == 102)
				{
					hk.phai = true;
					checkTH++; //3
					break;
				}
				if (x == 107)
				{
					hk.phai = false;
					checkTH++; //3
					break;
				}
			}
		} while (true);
		// thoat nhap
		if (checkTH == 3)
			break;
	} while (trung == false);

	if (checkTH == 3)
	{
		SetColor(10);
		tree = themHKvaoCay(tree, hk);
		gotoxy(102, 14);  cout << "                          "; // 26
		gotoxy(103, 14);  cout << "THEM HANH KHACH THANH CONG";
		Sleep(1500);
		gotoxy(103, 14);  cout << "                           ";
		gotoxy(102, 11); cout << "                  ";
		SetColor(31);
		SetBGColor(0);
	//	ghiFileHK(hk);
		ghiFileHKCay(tree);
	}
}

void xoaHanhKhach(NODEPTR& tree, LISTCB listCb, string CCCD)
{
	string maCB;
	int soCho = -1;

NHAPCCCD:
	menuNhapCCCD();
	SetBGColor(0);
	int x = XMAX + 25, y = YMAX + 6;
	do 
	{
		SetBGColor(31);
		gotoxy(x, y); cout << "                        ";
		gotoxy(x, y);
		SetColor(0);
		string s;
		char c;
		gotoxy(x, y);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() == 12)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER) {
					CCCD = s;
					break;
				}
			}
		}
		CCCD = s;
	} while (CCCD.length() != 12);
XUAT:
	SetBGColor(0);
	NODEHK* p = timHK(tree, CCCD);
	if (p != NULL)
	{
		SetColor(61);
		for (int i = 63; i < 113; i++)
		{
			gotoxy(i, 10); cout << char(205);
			gotoxy(i, 8); cout << char(205);
		}
		SetColor(14);
		gotoxy(66, 7); cout << "  HO  ";
		SetColor(31);
		gotoxy(68, 9); 	cout << p->data.ho;
		SetColor(14);
		gotoxy(85, 7); cout << "  TEN  ";
		SetColor(31);
		gotoxy(87, 9); 	cout << p->data.ten;
		SetColor(14);
		gotoxy(103, 7); cout << "  GIOI  ";
		gotoxy(105, 9);
		SetColor(31);
		switch ((int)p->data.phai)
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
		SetBGColor(0);
		SetColor(31);
		int x = xacNhanXoaHK();
		if (x == 1)
		{

			for (NODECB* k = listCb.head; k != NULL; k = k->next)
			{
				soCho = k->data.mayBay.soCho;

				if (ktraHK(k->data.danhSachVe, soCho) == true) // kiem tra da co hanh khach chua
				{

					for (int i = 0; i < soCho; i++)
					{

						if (k->data.danhSachVe.ve[i] == CCCD) // kiem tra so CCCD dat ve
						{
							k->data.danhSachVe.ve[i].clear();
							k->data.danhSachVe.slVe--;
							break;
						}
					}
				}
			}
			tree = xoaHK(tree, p->data);
			ghiFileDanhSachVe(listCb);
			ghiFileHKCay(tree);

		}
	}
	else
	{
		SetColor(14);
		gotoxy(66, 11); cout << "KHONG TON TAI HANH KHACH CO SO CCCD NAY ";
		Sleep(1000);
		system("cls");
		goto NHAPCCCD;
	}
	goto NHAPCCCD;
}


// --------------- VE ---------------------

int xacNhanDatVe()
{
	int x = 80, y = 39;
	gotoxy(73, 15);
	SetColor(45);
	SetBGColor(31);
	cout << "                                ";
	gotoxy(73, 16); cout << "                                ";
	gotoxy(73, 17); cout << "   BAN CO MUON DAT VE KHONG?    ";
	gotoxy(73, 18); cout << "                                ";
	gotoxy(73, 19); cout << "       CO          KHONG        ";
	gotoxy(73, 20); cout << "                                ";
	int keyhit;
	do {
		gotoxy(80, 19);
		SetColor(0);
		switch (x)
		{
		case 80: gotoxy(80, 19); cout << "CO"; break;
		case 92: gotoxy(92, 19); cout << "KHONG"; break;
		}
		keyhit = getch();
		if (keyhit == LEFT)
		{
			gotoxy(80, 19);
			SetColor(45);
			switch (x)
			{
			case 80: gotoxy(80, 19); cout << "CO"; break;
			case 92: gotoxy(92, 19); cout << "KHONG"; break;
			}
			x -= 12;
			if (x != 80)
			{
				x = 92;
			}
		}
		else if (keyhit == RIGHT)
		{
			gotoxy(92, 19);
			SetColor(45);
			switch (x)
			{
			case 80: gotoxy(80, 19); cout << "CO"; break;
			case 92: gotoxy(92, 19); cout << "KHONG"; break;
			}
			x += 12;
			if (x != 92)
			{
				x = 80;
			}
		}
		else if (x == 80 && keyhit == ENTER)
		{
			gotoxy(XMIN + 60, 21);
			cout << "   DAT VE THANH CONG   ";
			Sleep(2000);
			system("cls");
			SetBGColor(0);
			return 1;
		}
		else if (x == 92 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(0);
			return 0;
		}
	} while (true);
}

int xacNhanHuyVe()
{
	int x = 80, y = 39;
	gotoxy(73, 15);
	SetColor(45);
	SetBGColor(31);
	cout << "                                ";
	gotoxy(73, 16); cout << "                                ";
	gotoxy(73, 17); cout << "   BAN CO MUON HUY VE KHONG?    ";
	gotoxy(73, 18); cout << "                                ";
	gotoxy(73, 19); cout << "       CO          KHONG        ";
	gotoxy(73, 20); cout << "                                ";
	int keyhit;
	do {
		gotoxy(80, 19);
		SetColor(0);
		switch (x)
		{
		case 80: gotoxy(80, 19); cout << "CO"; break;
		case 92: gotoxy(92, 19); cout << "KHONG"; break;
		}
		keyhit = getch();
		if (keyhit == LEFT)
		{
			gotoxy(80, 19);
			SetColor(45);
			switch (x)
			{
			case 80: gotoxy(80, 19); cout << "CO"; break;
			case 92: gotoxy(92, 19); cout << "KHONG"; break;
			}
			x -= 12;
			if (x != 80)
			{
				x = 92;
			}
		}
		else if (keyhit == RIGHT)
		{
			gotoxy(92, 19);
			SetColor(45);
			switch (x)
			{
			case 80: gotoxy(80, 19); cout << "CO"; break;
			case 92: gotoxy(92, 19); cout << "KHONG"; break;
			}
			x += 12;
			if (x != 92)
			{
				x = 80;
			}
		}
		else if (x == 80 && keyhit == ENTER)
		{
			gotoxy(XMIN + 60, 21);
			cout << "   HUY VE THANH CONG   ";
			Sleep(2000);
			system("cls");
			SetBGColor(0);
			return 1;
		}
		else if (x == 92 && keyhit == ENTER)
		{
			system("cls");
			SetBGColor(0);
			return 0;
		}
	} while (true);
}


void datVe(LISTMB listMb, LISTCB& listCb, NODEPTR& tree)
{
	CHUYENBAY cb;
	NODECB* nodeCb;
	HANHKHACH hk;

TIEPTUCDAT:
	system("cls");
	menuDatVe();
	SetColor(31);
	string maCB, CCCD, chonGheSo;
	int  soGhe = -1, soCho = 0;
	int tbX = 70, tbY = 16;
NHAPMACB:
	do
	{
		int x = 62, y = 7;
		string s;
		char c;
		gotoxy(62, 7);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
				{
					if (c >= 'a' && c <= 'z')
					{
						c = c - 32;
					}
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER) {
					maCB = s;
					break;
				}
				if (c == F2)
				{
					system("cls");
					inDanhSachCacChuyenBay(listCb);
					SetColor(11);
					SetBGColor(5);
					gotoxy(XMAX + 102, YMAX + 6); cout << " ESC: QUAY LAI ";
					SetColor(31);
					SetBGColor(0);
					while (1)
					{
						if (_kbhit)
						{
							char d = _getch();
							if (d == ESC)
								goto TIEPTUCDAT;
						}
					}
				}
				if (c == F5)
				{
					system("cls");
					SetColor(31);
					SetBGColor(0);
					goto TIEPTUCDAT;
				}
			}
		}
		maCB = s;
		if (ktraMaCB(listCb, maCB) == false)
		{
			gotoxy(tbX, tbY); cout << "MA CHUYEN BAY KHONG TON TAI";
			Sleep(1000);
			gotoxy(tbX, tbY); cout << "                           ";
			gotoxy(62, 7); cout << "                             ";
			maCB = "";
			goto NHAPMACB;
		}
		else
		{
			for (NODECB* k = listCb.head; k != NULL; k = k->next)
			{
				if (k->data.maCB == maCB)
				{
					if (k->data.trangThai == 1)
					{
						soCho = k->data.mayBay.soCho;
						int cot = 35, hang = 15;
						int dem = 0;
						for (int i = 0; i < soCho; i++) {
							if (k->data.danhSachVe.ve[i].empty() == true)
							{
								SetColor(31);
								if (i < 9)
								{
									gotoxy(cot, hang + 5); cout << "00" + to_string(i + 1);
								}
								else if (i < 99 && i >= 9)
								{
									gotoxy(cot, hang + 5); cout << "0" + to_string(i + 1);
								}
								else
								{
									gotoxy(cot, hang + 5); cout << i + 1;
								}
								cot += 4;
								dem++;
								if (dem % 30 == 0)
								{
									hang += 2;
									cot = 35;
									dem = 0;
								}
							}
							else {
								SetColor(31);
								SetBGColor(12);
								if (i < 9)
								{
									gotoxy(cot, hang + 5); cout << "00" + to_string(i + 1);
								}
								else if (i < 99 && i >= 9)
								{
									gotoxy(cot, hang + 5); cout << "0" + to_string(i + 1);
								}
								else
								{
									gotoxy(cot, hang + 5); cout << i + 1;
								}
								cot += 4;
								dem++;
								if (dem % 30 == 0)
								{
									hang += 2;
									cot = 35;
									dem = 0;
								}
							}
							SetBGColor(0);
						}
						SetBGColor(0);
						goto NHAPCCCD;
					}
					else if (k->data.trangThai == 2)
					{
						gotoxy(tbX, tbY); cout << "CHUYEN BAY DA HET VE";
						Sleep(1000);
						gotoxy(tbX, tbY); cout << "                    ";
						gotoxy(62, 7); cout << "                    ";
						maCB = "";
						goto NHAPMACB;
					}
					else if (k->data.trangThai == 3)
					{
						gotoxy(tbX, tbY); cout << "CHUYEN BAY DA CAT CANH";
						Sleep(1000);
						gotoxy(tbX, tbY); cout << "                      ";
						gotoxy(62, 7); cout << "                    ";
						maCB = "";
						goto NHAPMACB;
					}
					else
					{
						gotoxy(tbX, tbY); cout << "CHUYEN BAY DA BI HUY";
						Sleep(1000);
						gotoxy(tbX, tbY); cout << "                    ";
						gotoxy(62, 7); cout << "                    ";
						maCB = "";
						goto NHAPMACB;
					}
				}
			}
		}
	} while (maCB.empty());
NHAPCCCD:
	do {
		gotoxy(62, 9); cout << "                           ";
		gotoxy(62, 9);
		int x = 62, y = 9;
		string s;
		char c;
		gotoxy(62, 9);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() == 12)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER) {
					CCCD = s;
					break;
				}
				if (c == F5)
				{
					system("cls");
					SetColor(31);
					SetBGColor(0);
					goto TIEPTUCDAT;
				}
			}
		}
		CCCD = s;
	} while (CCCD.length() != 12);

	for (NODECB* k = listCb.head; k != NULL; k = k->next)
	{
		if (k->data.maCB == maCB)
		{
			bool check = ktraHanhKhachTrongCB(k->data.danhSachVe, soCho, CCCD);
			if (check == true)
			{
				NODEHK* p = timHK(tree, CCCD);
				if (p != NULL)
				{
					gotoxy(102, 7); chuyenVeChuThuong(p->data.ho); xoaKhoangTrang(p->data.ho); inHoaDauTien(p->data.ho);	cout << p->data.ho;
					gotoxy(102, 9); chuyenVeChuThuong(p->data.ten); xoaKhoangTrang(p->data.ten); inHoaDauTien(p->data.ten);	cout << p->data.ten;
					gotoxy(102, 11);
					switch ((int)p->data.phai)
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
				}
				gotoxy(tbX, tbY); cout << "BAN DA MUA VE TRONG CHUYEN BAY NAY ROI";
				Sleep(2000);
				gotoxy(tbX, tbY); cout << "                                      ";
				gotoxy(102, 7); cout << "                         ";
				gotoxy(102, 9); cout << "                         ";
				gotoxy(102, 11); cout << "                         ";
				goto NHAPCCCD;
			}
			else if (kiemTraChuyenBayCach1Ngay(k->data.ngayKh, k->data.gioKh, listCb, CCCD) == false)
			{
				SetBGColor(0);
				gotoxy(102, 7); cout << "              ";
				gotoxy(102, 9); cout << "              ";
				gotoxy(102, 11); cout << "                 ";
				NODEHK* p = timHK(tree, CCCD);
				gotoxy(102, 7); chuyenVeChuThuong(p->data.ho); xoaKhoangTrang(p->data.ho); inHoaDauTien(p->data.ho);	cout << p->data.ho;
				gotoxy(102, 9); chuyenVeChuThuong(p->data.ten); xoaKhoangTrang(p->data.ten); inHoaDauTien(p->data.ten);	cout << p->data.ten;
				gotoxy(102, 11);
				switch ((int)p->data.phai)
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
				gotoxy(tbX, tbY); cout << "BAN KHONG THE DAT 2 VE TRONG 1 NGAY";
				Sleep(2000);
				gotoxy(tbX, tbY); cout << "                                   ";
				gotoxy(102, 7); cout << "                         ";
				gotoxy(102, 9); cout << "                         ";
				gotoxy(102, 11); cout << "                         ";
				goto NHAPCCCD;
			}
			else if (check == false)
			{
				NODEHK* p = timHK(tree, CCCD);
				if (p == NULL)
				{
					int dem = 0;
					NhapHanhKhach(tree, hk, CCCD, dem);
					if (dem == 1)
						return;
			

					gotoxy(102, 7); cout << hk.ho;
					gotoxy(102, 9); cout << hk.ten;
					gotoxy(102, 11);
					switch ((int)hk.phai)
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
				}
				else
				{
					gotoxy(102, 7); chuyenVeChuThuong(p->data.ho); xoaKhoangTrang(p->data.ho); inHoaDauTien(p->data.ho);	cout << p->data.ho;
					gotoxy(102, 9); chuyenVeChuThuong(p->data.ten); xoaKhoangTrang(p->data.ten); inHoaDauTien(p->data.ten);	cout << p->data.ten;
					gotoxy(102, 11);
					switch ((int)p->data.phai)
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
				}
			}

			else
			{
				NODEHK* p = timHK(tree, CCCD);
				gotoxy(102, 7);	cout << p->data.ho;
				gotoxy(102, 9); cout << p->data.ten;
				gotoxy(102, 11);
				switch ((int)p->data.phai)
				{
				case 0:
				{
					cout << "nu";
					break;
				}
				case 1:
				{
					cout << "nam";
					break;
				}
				default:
					break;
				}
			}
			break;
		}
	}
CHONGHE:
	do
	{
		SetColor(31);
		gotoxy(62, 11);
		gotoxy(62, 11); cout << "     ";
		gotoxy(62, 11);
		int x = 62, y = 11;
		string s;
		char c;
		gotoxy(62, 11);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER) {
					chonGheSo = s;
					break;
				}
				if (c == F5)
				{
					system("cls");
					SetColor(31);
					SetBGColor(0);
					goto TIEPTUCDAT;
				}
			}
		}
		if (chonGheSo.empty() == true)
		{
			gotoxy(tbX, tbY); cout << "KHONG BO TRONG";
			Sleep(1000);
			gotoxy(tbX, tbY); cout << "               ";
			goto CHONGHE;
		}
		else
		{
			soGhe = stoi(chonGheSo);
			if (soGhe == 0)
			{
				gotoxy(tbX, tbY); cout << "VI TRI GHE KHONG HOP LE";
				Sleep(2000);
				gotoxy(tbX, tbY); cout << "                        ";
				chonGheSo = "";
				goto CHONGHE;
			}
			else
			{
				if (soGhe <= soCho)
				{
					for (NODECB* k = listCb.head; k != NULL; k = k->next)
					{
						if (k->data.maCB == maCB)
						{
							if (k->data.danhSachVe.ve[soGhe - 1].empty() != true)
							{
								gotoxy(tbX, tbY); cout << "VI TRI DA DUOC CHON, VUI LONG CHON LAI";
								Sleep(2000);
								gotoxy(tbX, tbY); cout << "                                      ";
								chonGheSo.clear();
								goto CHONGHE;
							}
							else
							{
								int x = xacNhanDatVe();
								if (x == 1)
								{
									themVe(k->data.danhSachVe, soGhe, CCCD);
									ghiFileDanhSachVe(listCb);
									if (ktraTrangThaiVe(timMaCB(listCb, maCB)->data, soCho) == 1)
									{
										k->data.trangThai = 2;
									}
									goto TIEPTUCDAT;
								}
								else
								{
									goto TIEPTUCDAT;
								}
							}
						}
					}
				}
				else
				{
					gotoxy(tbX - 3, tbY); cout << "VI TRI GHE KHONG TON TAI, VUI LONG CHON LAI";
					Sleep(2000);
					gotoxy(tbX - 3, tbY); cout << "                                           ";
					gotoxy(62, 12); cout << "                                 ";
					chonGheSo = "";
					goto CHONGHE;
				}
			}
		}
	} while (chonGheSo.empty() == true);
THOAT:
	Sleep(1000);
	system("cls");
}

void huyVe(LISTCB& listCb, LISTMB listMb, NODEPTR& tree)
{
	CHUYENBAY cb;
TIEPTUCHUYVE:
	system("cls");
	menuHuyVe();
	SetColor(31);
	string maCB, CCCD;
	int soCho = 0, cot = 35, hang = 15;
	int tbX = 70, tbY = 16;
NHAPMACB:
	do
	{
		int x = 62, y = 5;
		string s;
		char c;
		gotoxy(62, 5);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= 'A' && c <= 'z' || c >= '0' && c <= '9')
				{
					if (c >= 'a' && c <= 'z')
					{
						c = c - 32;
					}
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() > 15)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)

					return;
				if (c == ENTER) {
					maCB = s;
					break;
				}
				if (c == F2)
				{
					system("cls");
					inDanhSachCacChuyenBay(listCb);
					SetColor(11);
					SetBGColor(5);
					gotoxy(XMAX + 102, YMAX + 6); cout << " ESC: QUAY LAI ";
					SetColor(31);
					SetBGColor(0);
					while (1)
					{
						if (_kbhit)
						{
							char d = _getch();
							if (d == ESC)
								goto TIEPTUCHUYVE;
						}
					}
				}
				if (c == F5)
				{
					system("cls");
					SetColor(31);
					SetBGColor(0);
					goto TIEPTUCHUYVE;
				}
				if (c == F4)
				{
					system("cls");
					xoaHanhKhach(tree, listCb, CCCD);		
					SetColor(31);
					SetBGColor(0);
					while (1)
					{
						if (_kbhit)
						{
							char d = _getch();
							if (d == ESC)
								goto TIEPTUCHUYVE;
						}
					}
				}
			}
		}
		if (ktraMaCB(listCb, maCB) == false)
		{
			gotoxy(tbX, tbY); cout << "MA CHUYEN BAY KHONG TON TAI";
			Sleep(1000);
			gotoxy(tbX, tbY); cout << "                           ";
			gotoxy(62, 5); cout << "                             ";
			maCB = "";
			goto NHAPMACB;
		}
		else
		{
			for (NODECB* k = listCb.head; k != NULL; k = k->next)
			{
				if (k->data.maCB == maCB)
				{
					if (k->data.trangThai == 1)
					{
						goto NHAPCCCD;
					}
					else if (k->data.trangThai == 3)
					{
						gotoxy(tbX, tbY); cout << "CHUYEN BAY DA CAT CANH";
						Sleep(1000);
						gotoxy(tbX, tbY); cout << "                      ";
						gotoxy(62, 5); cout << "                    ";
						maCB = "";
						goto NHAPMACB;
					}
					else
					{
						gotoxy(tbX, tbY); cout << "CHUYEN BAY DA BI HUY";
						Sleep(1000);
						gotoxy(tbX, tbY); cout << "                    ";
						gotoxy(62, 5); cout << "                    ";
						maCB = "";
						goto NHAPMACB;
					}
				}
			}
		}
	} while (maCB.empty());
NHAPCCCD:
	do
	{
		gotoxy(62, 8); cout << "                          ";
		gotoxy(62, 8);
		int x = 62, y = 8;
		string s;
		char c;
		gotoxy(62, 8);
		while (1)
		{
			if (_kbhit)
			{
				c = _getch();
				if (c >= '0' && c <= '9')
				{
					s.push_back(c);
					gotoxy(x, y); cout << c; x++;
					if (s.size() == 12)
						break;
				}
				if (c == BACKSPACE)
				{
					if (s.size() > 0)
					{
						s.erase(s.size() - 1);
						gotoxy(x, y); cout << "\b \b"; x--;
					}
				}
				if (c == ESC)
					return;
				if (c == ENTER) {
					CCCD = s;
					break;
				}
				if (c == F5)
				{
					system("cls");
					SetColor(31);
					SetBGColor(0);
					goto TIEPTUCHUYVE;
				}
			}
		}
		CCCD = s;
		if (CCCD.length() != 12) {
			gotoxy(tbX, tbY); cout << "CCCD KHONG HOP LE, VUI LONG NHAP LAI";
			Sleep(1000);
			gotoxy(tbX, tbY); cout << "                                    ";
		}
		if (timHK(tree, CCCD) != NULL)
		{
			for (NODECB* k = listCb.head; k != NULL; k = k->next)
			{
				if (k->data.maCB == maCB)
				{
					soCho = k->data.mayBay.soCho;

					if (ktraHK(k->data.danhSachVe, soCho) == true) // kiem tra da co hanh khach chua
					{
						int check = 0;
						for (int i = 0; i < soCho; i++)
						{

							if (k->data.danhSachVe.ve[i] == CCCD) // kiem tra so CCCD dat ve
							{
								check = 1;
								if (k->data.trangThai == 1)
								{
									SetColor(31);
									if (i < 9)
									{
										gotoxy(105, 11); cout << "00" + to_string(i + 1);
									}
									else if (i < 99 && i >= 9)
									{
										gotoxy(105, 11); cout << "0" + to_string(i + 1);
									}
									else
									{
										gotoxy(105, 11); cout << i + 1;
									}
									SetColor(31);
									SetBGColor(0);
									if (ktraHanhKhachTrongCB(k->data.danhSachVe, soCho, CCCD) == 1)
									{
										NODEHK* p = timHK(tree, CCCD);
										gotoxy(102, 5); chuyenVeChuThuong(p->data.ho); xoaKhoangTrang(p->data.ho); inHoaDauTien(p->data.ho);	cout << p->data.ho;
										gotoxy(102, 7); chuyenVeChuThuong(p->data.ten); xoaKhoangTrang(p->data.ten); inHoaDauTien(p->data.ten);	cout << p->data.ten;
										gotoxy(102, 9);
										switch ((int)p->data.phai)
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
									}
								}
								int x = xacNhanHuyVe();
								SetBGColor(0);
								SetColor(31);
								if (x == 1)
								{
									if (xoaVe(k->data.danhSachVe, i) == 1)
									{
										gotoxy(XMAX + 63, 5);
										cout << "HUY VE THANH CONG";
										gotoxy(XMAX + 63, 5);
										cout << "                 ";
										ghiFileDanhSachVe(listCb);
										goto TIEPTUCHUYVE;
									}
								}
								else {
									goto TIEPTUCHUYVE;
								}
							}
						}
						if (check == 0)
						{
							gotoxy(tbX, tbY); cout << "BAN CHUA DAT VE TRONG CHUYEN BAY NAY";
							Sleep(1000);
							gotoxy(tbX, tbY); cout << "                                    ";
							goto NHAPCCCD;
						}
					}
				}
			}
		}
		else
		{
			gotoxy(tbX, tbY);
			cout << "CCCD CHUA CO TRONG HE THONG, VUI LONG NHAP LAI";
			Sleep(2000);
			gotoxy(tbX, tbY);
			cout << "                                              ";
			goto NHAPCCCD;
		}
	} while (CCCD.empty() == true);
THOAT:
	Sleep(1000);
	system("cls");
}
