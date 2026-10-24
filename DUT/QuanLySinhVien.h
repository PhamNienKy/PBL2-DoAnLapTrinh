#pragma once
#include "SinhVien.h"
#include "Lop.h"
#include "Khoa.h"
#include "Diem.h"
#include "MonHoc.h"

class QuanLySinhVien
{
    friend class DBHelper;
private:
    SinhVien* listSinhVien;
    int n;
public:
    QuanLySinhVien();
    ~QuanLySinhVien();

    friend ostream& operator<<(ostream&, const QuanLySinhVien&);
    int GetN();
    void Clear();
    void Add(SinhVien);
    void AddSinhVien();
    void Insert(const int&);
    SinhVien& operator[](const int&);
    int IndexOf(string);
    void Remove(string);
    void Search();
    void Update();
};