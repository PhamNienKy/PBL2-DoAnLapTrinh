#include "SinhVien.h"
#include "Diem.h"

#include <iomanip>

SinhVien::SinhVien(string MaSinhVien, string HoTen,
	string NgaySinh, string GioiTinh, string DiaChi,
	string Email, string MaLop)
	: MaSinhVien(MaSinhVien),
	HoTen(HoTen),
	NgaySinh(NgaySinh),
	GioiTinh(GioiTinh),
	DiaChi(DiaChi),
	Email(Email),
	MaLop(MaLop)
{
}

SinhVien::~SinhVien()
{
}
string SinhVien::GetMaSinhVien()
{
	return this->MaSinhVien;
}
string SinhVien::GetTenSinhVien()
{
	return this->HoTen;
}
ostream& operator<<(ostream& o, const SinhVien& SinhVien)
{
	cout << setw(15) << SinhVien.MaSinhVien << setw(20) << SinhVien.HoTen << setw(15) << SinhVien.NgaySinh << setw(15) << SinhVien.GioiTinh
		<< setw(15) << SinhVien.DiaChi << setw(50) << SinhVien.Email << setw(30) << SinhVien.MaLop << endl;
	return o;
}
const SinhVien& SinhVien::operator=(const SinhVien& SinhVien)
{
	this->MaSinhVien = SinhVien.MaSinhVien;
	this->HoTen = SinhVien.HoTen;
	this->NgaySinh = SinhVien.NgaySinh;
	this->GioiTinh = SinhVien.GioiTinh;
	this->DiaChi = SinhVien.DiaChi;
	this->Email = SinhVien.Email;
	this->MaLop = SinhVien.MaLop;
	return (*this);
}
SinhVien& SinhVien::Update(string HoTen, string NgaySinh, string GioiTinh, string DiaChi, string Email, string MaLop)
{
	this->HoTen = HoTen;
	this->NgaySinh = NgaySinh;
	this->DiaChi = DiaChi;
	this->Email = Email;
	this->MaLop = MaLop;
	return *this;
}


