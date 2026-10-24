#pragma once

#include<iostream>
#include<string>
using namespace std;

class Khoa {
private:
    string MaKhoa;
    string TenKhoa;
public:
    Khoa(string = "", string = "");
    ~Khoa();

    const Khoa& operator=(const Khoa&);
    friend ostream& operator<<(ostream&, const Khoa&);
    string getMaKhoa();
    string getTenKhoa();
    Khoa& Update(Khoa);
    Khoa& Update(string, string);

};

