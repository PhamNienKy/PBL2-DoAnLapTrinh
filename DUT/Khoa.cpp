#include "Khoa.h"
#include <iomanip>

Khoa::Khoa(string MaKhoa, string TenKhoa)
    :MaKhoa(MaKhoa), TenKhoa(TenKhoa)
{}

Khoa::~Khoa() {};

const Khoa& Khoa::operator=(const Khoa& l)
{
    this->MaKhoa = l.MaKhoa;
    this->TenKhoa = l.TenKhoa;
    return (*this);
}

ostream& operator<<(ostream& o, const Khoa& Khoa) {
    o << setw(15) << Khoa.MaKhoa << setw(30) << Khoa.TenKhoa << endl;
    return o;
}

string Khoa::getMaKhoa() {
    return this->MaKhoa;
}

string Khoa::getTenKhoa() {
    return this->TenKhoa;
}

Khoa& Khoa::Update(Khoa k)
{
    this->MaKhoa = k.MaKhoa;
    this->TenKhoa = k.TenKhoa;
    return (*this);
}

Khoa& Khoa::Update(string MaKhoa, string TenKhoa)
{
    this->MaKhoa = MaKhoa;
    this->TenKhoa = TenKhoa;
    return *this;
}
