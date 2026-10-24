#pragma once

#include<iostream>
#include<string>
using namespace std;

class MonHoc {
private:
    string MaMonHoc;
    string TenMonHoc;
    int SoTinChi;
public:
    MonHoc(string = "", string = "", int = 0);
    ~MonHoc();

    const MonHoc& operator=(const MonHoc&);
    friend ostream& operator<<(ostream&, const MonHoc&);
    string getMaMonHoc();
    string getTenMonHoc();
    int getSoTinChi();
    MonHoc& Update(MonHoc);
    MonHoc& Update(string, string, int);
};