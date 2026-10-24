#pragma once

#include <string.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "Diem.h"
using namespace std;

class SinhVien
{
	friend class DBHelper;
private:
	string MaSinhVien;
	string HoTen;
	string NgaySinh;
	string GioiTinh;
	string DiaChi;
	string Email;
	string MaLop;

public:
	SinhVien(string = "", string = "", string = "", string = "", string = "", string = "", string = "");
	~SinhVien();
	string GetMaSinhVien();
	string GetTenSinhVien();
	friend ostream& operator<<(ostream&, const SinhVien&);
	const SinhVien& operator=(const SinhVien&);
	SinhVien& Update(string, string, string, string, string, string);
};
