#include "QuanLyLop.h"
#include <iostream>

using namespace std;

QuanLyLop::QuanLyLop()
{
    this->n = 0;
    this->listLop = nullptr;

}

QuanLyLop::~QuanLyLop()
{
    delete[] this->listLop;

}

ostream& operator<<(ostream& o, const QuanLyLop& db)
{
    cout << setw(5) << "STT" << setw(50) << "MA LOP" << setw(50) << "TEN LOP" << setw(50) << "MA KHOA" << setw(15) << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.listLop + i) << endl << endl;
    }
    return o;
}

Lop& QuanLyLop::operator[](const int& s)
{
    static Lop error;
    return ((s >= 0) && (s < this->n)) ? *(this->listLop + s) : error;
}

void QuanLyLop::Display() {
    cout << setw(5) << "STT"
        << setw(20) << "Ma Lop"
        << setw(25) << "Ten Lop" 
        << setw(25) << "Ma Khoa" << endl;
    for (int i = 1; i < this->n; i++) {
        cout << setw(5) << i + 1
            << setw(20) << (*this)[i].getMaLop()
            << setw(20) << (*this)[i].getTenLop() 
            << setw(20) << (*this)[i].getMaKhoa() 
            << endl;
    }
}


int QuanLyLop::GetN()
{
    return this->n;
}

void QuanLyLop::Clear()
{
    this->n = 0;
    delete[] this->listLop;
}
void QuanLyLop::Add(Lop newLop) {

    if (this->n == 0) {
        this->listLop = new Lop[this->n + 1];
        this->listLop[this->n] = newLop;
    }
    else {
        QuanLyLop temp;
        temp.listLop = new Lop[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listLop + i) = *(this->listLop + i);
        }
        delete[] this->listLop;
        this->listLop = new Lop[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->listLop + j) = *(temp.listLop + j);
        }
        *(this->listLop + this->n) = newLop;
    }
    this->n++;
}



void QuanLyLop::AddLop() {

    string MaLop;
    string TenLop;
    string MaKhoa;

    cin.ignore(100, '\n');
    cout << "Nhap ma Lop: ";
    getline(cin, MaLop);
    cout << "Nhap ten Lop: ";
    getline(cin, TenLop);
    cout << "Nhap ma khoa: ";
    getline(cin, MaKhoa);

    Lop newLop(MaLop, TenLop, MaKhoa);
    cout << newLop;
    this->Add(newLop);
}

void QuanLyLop::Insert(const int& k) {
    string MaLop;
    string TenLop;
    string MaKhoa;

    cout << "Nhap ma Lop: ";
    getline(cin, MaLop);
    cout << "Nhap ten Lop: ";
    getline(cin, TenLop);
    cout << "Nhap ma khoa: ";
    getline(cin, MaKhoa);

    Lop newSv(MaLop, TenLop);

    QuanLyLop temp;
    temp.listLop = new Lop[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.listLop + i) = *(this->listLop + i);
    }
    delete[] this->listLop;
    this->listLop = new Lop[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->listLop + i) = *(temp.listLop + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->listLop + i) = *(this->listLop + i - 1);
        }
        *(this->listLop + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->listLop + i) = *(temp.listLop + i);
        }
        *(this->listLop + this->n) = newSv;
    }
    this->n++;
}

int QuanLyLop::IndexOf(string maLop) {
    for (int i = 0; i < this->n; i++) {

        if (maLop == (*this)[i].getMaLop()) {
            return i + 1;
            break;
        }
    }
    return -1;
}

void QuanLyLop::Remove(string MaLop)
{
    int k = this->IndexOf(MaLop) - 1;
    QuanLyLop temp;
    if (k == -2) {
        cout << "Nhap sai ma lop!!!" << endl;
    }
    else {
        temp.listLop = new Lop[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listLop + i) = *(this->listLop + i);
        }
        delete[] this->listLop;
        this->listLop = new Lop[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->listLop + i) = *(temp.listLop + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->listLop + i) = *(temp.listLop + i + 1);
        }
        this->n--;
    }
}

void QuanLyLop::Search() {
    QuanLyLop dbSearch;
    string tenLop;
    cout << "Nhap ten lop can tim: ";
    getline(cin, tenLop);
    for (int i = 0; i < this->n; i++) {
        string ten = (*this)[i].getTenLop();
        if (ten.find(tenLop) != -1) {
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QuanLyLop::Update() {
    string MaLop;
    string TenLop;
    string MaKhoa;

    cin.ignore(100, '\n');
    cout << "Nhap ma Lop can update: ";
    getline(cin, MaLop);
    cout << "Nhap ten Lop can sua: ";
    getline(cin, TenLop); 
    cout << "Nhap ma khoa can sua: ";
    getline(cin, MaKhoa);

    int k = this->IndexOf(MaLop) - 1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(MaLop, TenLop, MaKhoa);
            break;
        }
    }
}

