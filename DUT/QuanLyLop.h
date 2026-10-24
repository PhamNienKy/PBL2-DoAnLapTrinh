#pragma once

#include "Khoa.h"
#include "Lop.h"

class QuanLyLop
{
    friend class DBHelper;
private:
    Lop* listLop;
    int n;
public:
    QuanLyLop();
    ~QuanLyLop();

    friend ostream& operator<<(ostream&, const QuanLyLop&);
    Lop& operator[](const int&);
    void Display();
    int GetN();
    void Clear();
    void Add(Lop);
    void AddLop();
    void Insert(const int&);
    int IndexOf(string);
    void Search();
    void Update();
    void Remove(string);
};

