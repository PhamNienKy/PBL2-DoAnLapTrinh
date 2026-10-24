#include "QuanLySinhVien.h"
#include <iostream>

using namespace std;


QuanLySinhVien::QuanLySinhVien()
{
    this->n = 0;
    this->listSinhVien = nullptr;
    
}

QuanLySinhVien::~QuanLySinhVien()
{
    delete[] this->listSinhVien;

}

ostream& operator<<(ostream& o, const QuanLySinhVien& db)
{
    cout << setw(5) << "STT" << setw(15) << "MA SINH VIEN" << setw(50) << "HO TEN" << setw(50) << "NGAY SINH" << setw(15)
        << "GIOITINH" << setw(30) << "DIACHI" << setw(50) << "EMAIL" << setw(50) << "MA LOP" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.listSinhVien + i) << endl << endl;
    }
    return o;
}


SinhVien& QuanLySinhVien::operator[](const int& s)
{
    static SinhVien error;
    return ((s >= 0) && (s < this->n)) ? *(this->listSinhVien + s) : error;
}


int  QuanLySinhVien::GetN()
{
    return this->n;
}

void QuanLySinhVien::Clear()
{
    this->n = 0;
    delete[] this->listSinhVien;
}
void QuanLySinhVien::Add(SinhVien newSinhVien) {

    if (this->n == 0) {
        this->listSinhVien = new SinhVien[this->n + 1];
        this->listSinhVien[this->n] = newSinhVien;
    }
    else {
        QuanLySinhVien temp;
        temp.listSinhVien = new SinhVien[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listSinhVien + i) = *(this->listSinhVien + i);
        }
        delete[] this->listSinhVien;
        this->listSinhVien = new SinhVien[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->listSinhVien + j) = *(temp.listSinhVien + j);
        }
        *(this->listSinhVien + this->n) = newSinhVien;
    }
    this->n++;
}



void QuanLySinhVien::AddSinhVien() {

    string MaSinhVien;
    string HoTen;
    string NgaySinh;
    string GioiTinh;
    string DiaChi;
    string Email;
    string MaLop;
    cin.ignore(100, '\n');
    std::cout << "Nhap ma sinh vien: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ho ten: ";
    getline(cin, HoTen);
    cout << "Nhap ngay sinh (dd/mm/yy): ";
    cin >> NgaySinh;
    cin.ignore(100, '\n');
    cout << "Nhap gioi tinh (Nam/Nu/Khac): "; ;
    getline(cin, GioiTinh);
    cout << "Nhap dia chi: ";
    getline(cin, DiaChi);
    cout << "Nhap email: ";
    getline(cin, Email);
    cout << "Nhap ma lop: ";
    getline(cin, MaLop);
    SinhVien newSinhVien(MaSinhVien, HoTen, NgaySinh, GioiTinh, DiaChi, Email, MaLop);
    cout << newSinhVien;
    this->Add(newSinhVien);
}

void QuanLySinhVien::Insert(const int& k) {
    string MaSinhVien;
    string HoTen;
    string NgaySinh;
    string GioiTinh;
    string DiaChi;
    string Email;
    string MaLop;
    cout << "Nhap ma sinh vien: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ho ten sinh vien: ";
    getline(cin, HoTen);
    cout << "Nhap ngay sinh (dd/mm/yy): ";
    cin >> NgaySinh;
    cin.ignore(100, '\n');
    cout << "Nhap gioi tinh (Nam/Nu/Khac): ";
    getline(cin, GioiTinh);
    cout << "Nhap dia chi: ";
    getline(cin, DiaChi);
    cout << "Nhap email: ";
    getline(cin, Email);
    cout << "Nhap ma lop: ";
    getline(cin, MaLop);
    SinhVien newSv(MaSinhVien, HoTen, NgaySinh, GioiTinh, DiaChi, Email, MaLop);

    QuanLySinhVien temp;
    temp.listSinhVien = new SinhVien[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.listSinhVien + i) = *(this->listSinhVien + i);
    }
    delete[] this->listSinhVien;
    this->listSinhVien = new SinhVien[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->listSinhVien + i) = *(temp.listSinhVien + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->listSinhVien + i) = *(this->listSinhVien + i - 1);
        }
        *(this->listSinhVien + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->listSinhVien + i) = *(temp.listSinhVien + i);
        }
        *(this->listSinhVien + this->n) = newSv;
    }
    this->n++;
}

int QuanLySinhVien::IndexOf(string maSinhVien) {
    for (int i = 0; i < this->n; i++) {

        if (maSinhVien == (*this)[i].GetMaSinhVien()) {
            return i + 1;
            break;
        }
    }
    return -1;
}

void QuanLySinhVien::Remove(string MaSinhVien)
{
    int k = this->IndexOf(MaSinhVien) - 1;
    QuanLySinhVien temp;
    if (k == -2) {
        cout << "Nhap sai ma sinh vien!!!" << endl;
    }
    else {
        temp.listSinhVien = new SinhVien[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listSinhVien + i) = *(this->listSinhVien + i);
        }
        delete[] this->listSinhVien;
        this->listSinhVien = new SinhVien[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->listSinhVien + i) = *(temp.listSinhVien + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->listSinhVien + i) = *(temp.listSinhVien + i + 1);
        }
        this->n--;
    }
}

void QuanLySinhVien::Search() {
    QuanLySinhVien dbSearch;
    string tenSinhVien;
    cout << "Nhap ten sinh vien can tim: ";
    getline(cin, tenSinhVien);
    for (int i = 0; i < this->n; i++) {
        string ten = (*this)[i].GetTenSinhVien();
        if (ten.find(tenSinhVien) != -1) {
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QuanLySinhVien::Update() {
    string MaSinhVien;
    string HoTen;
    string NgaySinh;
    string GioiTinh;
    string DiaChi;
    string Email;
    string MaLop;
    cin.ignore(100, '\n');
    cout << "Nhap ma sinh vien cua sinh vien can update: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ho ten can sua: ";
    getline(cin, HoTen);
    cout << "Nhap ngay sinh can sua: ";
    cin >> NgaySinh;
    cin.ignore(100, '\n');
    cout << "Nhap gioi tinh  can sua: ";
    getline(cin, GioiTinh);
    cout << "Nhap dia chi can sua: ";
    getline(cin, DiaChi);
    cout << "Nhap email can sua : ";
    getline(cin, Email);
    cout << "Nhap ma lop can sua: ";
    getline(cin, MaLop);
    int k = this->IndexOf(MaSinhVien) - 1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(HoTen, NgaySinh, GioiTinh, DiaChi, Email, MaLop);
            break;
        }
    }
}

