#include "Diem.h"

Diem::Diem(string MaSinhVien, string MaMonHoc, float DiemSo)
    : MaSinhVien(MaSinhVien), MaMon(MaMonHoc), DiemSo(DiemSo)
{}

Diem::~Diem()
{}

string Diem::GetMaSinhVien()
{
    return this->MaSinhVien;
}

float Diem::GetDiemSo()
{
    return this->DiemSo;
}

string Diem::GetMaMon()
{
    return this->MaMon;
}

const Diem& Diem::operator=(const Diem& d)
{
    this->MaSinhVien = d.MaSinhVien;
    this->MaMon = d.MaMon;
    this->DiemSo = d.DiemSo;
    return (*this);
}

ostream& operator<<(ostream& o, const Diem& Diem)
{
    o << setw(15) << Diem.MaSinhVien << setw(10) << Diem.MaMon << setw(12) << Diem.DiemSo << endl;
    return o;
}

istream& operator>>(istream& i, Diem& Diem)
{
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien : ";
    getline(cin, Diem.MaSinhVien);
    cout << "Nhap ma mon hoc : ";
    getline(cin, Diem.MaMon);
    cout << "Nhap diem so : ";
    i >> Diem.DiemSo;
    return i;
}

Diem& Diem::Update(float DiemSo)
{
    this->DiemSo = DiemSo;
    return *this;
}

Diem& Diem::Update(string MaSinhVien, string MaMonHoc, float DiemSo)
{
    this->MaSinhVien = MaSinhVien;
    this->MaMon = MaMonHoc;
    this->DiemSo = DiemSo;
    return *this;
}

void Diem::Remove(const Diem& diem)
{
    if (MaSinhVien == diem.MaSinhVien &&
        MaMon == diem.MaMon)
    {
        MaSinhVien = "";
        MaMon = "";
        DiemSo = 0;
    }
}