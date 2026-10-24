#pragma once

#include "SinhVien.h"
#include "Diem.h"

class QuanLyDiem
{
    friend class DBHelper;
private:
    Diem* listDiem;
    int n;
public:
    QuanLyDiem();
    ~QuanLyDiem();

    friend ostream& operator<<(ostream&, const QuanLyDiem&);
    Diem& operator[](const int&);
    void Display();
    int GetN();
    void Clear();
    void Add(Diem);
    void AddDiem();
    void Insert(const int&);
    int IndexOf(float);
    void Search();
    void Update();
    void SortAZ();
    void Remove(float);
};

