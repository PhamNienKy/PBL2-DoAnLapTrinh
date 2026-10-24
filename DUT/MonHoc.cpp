#pragma once
#include "MonHoc.h"
#include <iomanip>

MonHoc::MonHoc(string MaMonHoc, string TenMonHoc, int SoTinChi)
    :MaMonHoc(MaMonHoc), TenMonHoc(TenMonHoc), SoTinChi(SoTinChi)
{}

MonHoc::~MonHoc() {}

const MonHoc& MonHoc::operator=(const MonHoc& mh)
{
    this->MaMonHoc = mh.MaMonHoc;
    this->TenMonHoc = mh.TenMonHoc;
    this->SoTinChi = mh.SoTinChi;
    return (*this);
}

ostream& operator<<(ostream& o, const MonHoc& MonHoc) {
    o << setw(15) << MonHoc.MaMonHoc << setw(30) << MonHoc.TenMonHoc << setw(10) << MonHoc.SoTinChi << endl;
    return o;
}

string MonHoc::getMaMonHoc() {
    return this->MaMonHoc;
}

string MonHoc::getTenMonHoc() {
    return this->TenMonHoc;
}

int MonHoc::getSoTinChi() {
    return this->SoTinChi;
}
MonHoc& MonHoc::Update(MonHoc l)
{
    this->MaMonHoc = l.MaMonHoc;
    this->TenMonHoc = l.TenMonHoc;
    this->SoTinChi = l.SoTinChi;
    return (*this);
}

MonHoc& MonHoc::Update(string MaMonHoc, string TenMonHoc, int SoTinChi)
{
    this->MaMonHoc = MaMonHoc;
    this->TenMonHoc = TenMonHoc;
    this->SoTinChi = SoTinChi;
    return *this;
}
