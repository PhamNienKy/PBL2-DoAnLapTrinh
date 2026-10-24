#include "QuanLyKhoa.h"
#include <iostream>
#include <iomanip>

using namespace std;

QuanLyKhoa::QuanLyKhoa()
{
    this->n = 0;
    this->listKhoa = nullptr;

}

QuanLyKhoa::~QuanLyKhoa()
{
    delete[] this->listKhoa;

}

ostream& operator<<(ostream& o, const QuanLyKhoa& db)
{
    cout << setw(5) << "STT" << setw(50) << "MA KHOA" << setw(50) << "MA LOP" << setw(15) << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.listKhoa + i) << endl << endl;
    }
    return o;
}

Khoa& QuanLyKhoa::operator[](const int& s)
{
    static Khoa error;
    return ((s >= 0) && (s < this->n)) ? *(this->listKhoa + s) : error;
}

void QuanLyKhoa::Display() {
    cout << setw(5) << "STT"
        << setw(20) << "MA KHOA"
        << setw(25) << "TEN KHOA" << endl;
    for (int i = 1; i < this->n; i++) {
        cout << setw(5) << i + 1 
            << setw(20) << (*this)[i].getMaKhoa()
            << setw(20) << (*this)[i].getTenKhoa() << endl;
    }
}


int QuanLyKhoa::GetN()
{
    return this->n;
}

void QuanLyKhoa::Clear()
{
    this->n = 0;
    delete[] this->listKhoa;
}
void QuanLyKhoa::Add(Khoa newKhoa) {

    if (this->n == 0) {
        this->listKhoa = new Khoa[this->n + 1];
        this->listKhoa[this->n] = newKhoa;
    }
    else {
        QuanLyKhoa temp;
        temp.listKhoa = new Khoa[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listKhoa + i) = *(this->listKhoa + i);
        }
        delete[] this->listKhoa;
        this->listKhoa = new Khoa[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->listKhoa + j) = *(temp.listKhoa + j);
        }
        *(this->listKhoa + this->n) = newKhoa;
    }
    this->n++;
}



void QuanLyKhoa::AddKhoa() {

    string MaKhoa;
    string TenKhoa;

    cin.ignore(100, '\n');
    cout << "Nhap ma khoa: ";
    getline(cin, MaKhoa);
    cout << "Nhap ten khoa: ";
    getline(cin, TenKhoa);

    Khoa newKhoa(MaKhoa,TenKhoa);
    cout << newKhoa;
    this->Add(newKhoa);
}

void QuanLyKhoa::Insert(const int& k) {
    string MaKhoa;
    string TenKhoa;

    cout << "Nhap ma khoa: ";
    getline(cin, MaKhoa);
    cout << "Nhap ten khoa: ";
    getline(cin, TenKhoa);
    
    Khoa newSv(MaKhoa, TenKhoa);

    QuanLyKhoa temp;
    temp.listKhoa = new Khoa[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.listKhoa + i) = *(this->listKhoa + i);
    }
    delete[] this->listKhoa;
    this->listKhoa = new Khoa[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->listKhoa + i) = *(temp.listKhoa + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->listKhoa + i) = *(this->listKhoa + i - 1);
        }
        *(this->listKhoa + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->listKhoa + i) = *(temp.listKhoa + i);
        }
        *(this->listKhoa + this->n) = newSv;
    }
    this->n++;
}

int QuanLyKhoa::IndexOf(string maKhoa) {
    for (int i = 0; i < this->n; i++) {

        if (maKhoa == (*this)[i].getMaKhoa()) {
            return i + 1;
            break;
        }
    }
    return -1;
}

void QuanLyKhoa::Remove(string MaKhoa)
{
    int k = this->IndexOf(MaKhoa) - 1;
    QuanLyKhoa temp;
    if (k == -2) {
        cout << "Nhap sai ma khoa!!!" << endl;
    }
    else {
        temp.listKhoa = new Khoa[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listKhoa + i) = *(this->listKhoa + i);
        }
        delete[] this->listKhoa;
        this->listKhoa = new Khoa[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->listKhoa + i) = *(temp.listKhoa + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->listKhoa + i) = *(temp.listKhoa + i + 1);
        }
        this->n--;
    }
}

void QuanLyKhoa::Search() {
    QuanLyKhoa dbSearch;
    string tenKhoa;

    cout << "Nhap ten khoa can tim: ";
    getline(cin, tenKhoa);
    for (int i = 0; i < this->n; i++) {
        string ten = (*this)[i].getTenKhoa();
        if (ten.find(tenKhoa) != -1) {
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QuanLyKhoa::Update() {
    string MaKhoa;
    string TenKhoa;

    cin.ignore(100, '\n');
    cout << "Nhap ma khoa can update: ";
    getline(cin, MaKhoa);
    cout << "Nhap ten khoa can sua: ";
    getline(cin, TenKhoa);

    int k = this->IndexOf(MaKhoa) - 1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(MaKhoa, TenKhoa);
            break;
        }
    }
}




