#pragma once

#include "MonHoc.h"

class QuanLyMonHoc
{
    friend class DBHelper;
private:
    MonHoc* listMonHoc;
    int n;
public:
    QuanLyMonHoc();
    ~QuanLyMonHoc();

    friend ostream& operator<<(ostream&, const QuanLyMonHoc&);
    MonHoc& operator[](const int&);
    void Display();
    int GetN();
    void Clear();
    void Add(MonHoc);
    void AddMonHoc();
    void Insert(const int&);
    int IndexOf(string);
    void Search();
    void Update();
    void SortAZ();
    void Remove(string);
};

