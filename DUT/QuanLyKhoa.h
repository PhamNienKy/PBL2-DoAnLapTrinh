#pragma once

#include "Khoa.h"

class QuanLyKhoa
{
    friend class DBHelper;
private:
    Khoa* listKhoa;
    int n;
public:
    QuanLyKhoa();
    ~QuanLyKhoa();

    friend ostream& operator<<(ostream&, const QuanLyKhoa&);
    Khoa& operator[](const int&);
    void Display();
    int GetN();
    void Clear();
    void Add(Khoa);
    void AddKhoa();
    void Insert(const int&);
    int IndexOf(string);
    void Search();
    void Update();
    void Remove(string);
}; 
