#include "Lop.h"

Lop::Lop(string MaLop, string TenLop, string MaKhoa)
    : MaLop(MaLop), TenLop(TenLop), MaKhoa(MaKhoa)
{}

Lop::~Lop()
{}

const Lop& Lop::operator=(const Lop& lhp)
{
    this->MaLop = lhp.MaLop;
    this->TenLop = lhp.TenLop;
    this->MaKhoa = lhp.MaKhoa;
    return (*this);
}

ostream& operator<<(ostream& o, const Lop& Lop) {
    o << setw(15) << Lop.MaLop<< setw(30) << Lop.TenLop << setw(10) << Lop.MaKhoa << endl;
    return o;
}

string Lop::getMaLop() {
    return this->MaLop;
}

string Lop::getTenLop() {
    return this->TenLop;
}

string Lop::getMaKhoa() {
    return this->MaKhoa;
}
Lop& Lop::Update(Lop l)
{
    this->MaLop = l.MaLop;
    this->TenLop = l.TenLop;
    this->MaKhoa = l.MaKhoa;
    return (*this);
}

Lop& Lop::Update(string MaLop, string TenLop, string MaKhoa)
{
    this->MaLop = MaLop;
    this->TenLop = TenLop;
    this->MaKhoa = MaKhoa;
    return *this;
}