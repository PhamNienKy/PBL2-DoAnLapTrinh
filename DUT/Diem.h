#pragma once

#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Diem
{
    //  friend class DBHelper;
private:
    string MaSinhVien;
    string MaMon;
    float DiemSo;
public:
    Diem(string = "", string = "", float = 0);
    ~Diem();

    const Diem& operator =(const Diem&);
    friend ostream& operator<<(ostream&, const Diem&);
    friend istream& operator>>(istream&, Diem&);
    string GetMaSinhVien();
    string GetMaMon();
    float GetDiemSo();
    Diem& Update(float);
    Diem& Update(string, string, float);
    void Remove(const Diem&);
};
