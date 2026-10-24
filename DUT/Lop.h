#pragma once
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

class Lop
{
private:
    string MaLop;
    string TenLop;
    string MaKhoa;
  
public:
    Lop(string = "", string = "", string = "");
    ~Lop();

    const Lop& operator=(const Lop&);
    friend ostream& operator<<(ostream&, const Lop&);
    string getMaLop();
    string getTenLop();
    string getMaKhoa();
    Lop& Update(Lop);
    Lop& Update(string, string, string);
};