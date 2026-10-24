#include "QuanLyMonHoc.h"
#include <iostream>
#include <iomanip>

using namespace std;

QuanLyMonHoc::QuanLyMonHoc()
{
    this->n = 0;
    this->listMonHoc = nullptr;

}

QuanLyMonHoc::~QuanLyMonHoc()
{
    delete[] this->listMonHoc;

}

ostream& operator<<(ostream& o, const QuanLyMonHoc& db)
{
    cout << setw(5) << "STT" << setw(50) << "MA MON HOC" << setw(50) << "TEN MON HOC" << setw(50) << "SO TIN CHI" << setw(15) << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.listMonHoc + i) << endl << endl;
    }
    return o;
}

MonHoc& QuanLyMonHoc::operator[](const int& s)
{
    static MonHoc error;
    return ((s >= 0) && (s < this->n)) ? *(this->listMonHoc + s) : error;
}

void QuanLyMonHoc::Display() {
    cout << setw(5) << "STT"
        << setw(20) << "Ma Mon Hoc"
        << setw(25) << "Ten Mon Hoc"
        << setw(25) << "So Tin Chi" << endl;
    for (int i = 1; i < this->n; i++) {
        cout << setw(5) << i + 1
            << setw(20) << (*this)[i].getMaMonHoc()
            << setw(20) << (*this)[i].getTenMonHoc()
            << setw(20) << (*this)[i].getSoTinChi()
            << endl;
    }
}


int QuanLyMonHoc::GetN()
{
    return this->n;
}

void QuanLyMonHoc::Clear()
{
    this->n = 0;
    delete[] this->listMonHoc;
}
void QuanLyMonHoc::Add(MonHoc newMonHoc) {

    if (this->n == 0) {
        this->listMonHoc = new MonHoc[this->n + 1];
        this->listMonHoc[this->n] = newMonHoc;
    }
    else {
        QuanLyMonHoc temp;
        temp.listMonHoc = new MonHoc[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listMonHoc + i) = *(this->listMonHoc + i);
        }
        delete[] this->listMonHoc;
        this->listMonHoc = new MonHoc[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->listMonHoc + j) = *(temp.listMonHoc + j);
        }
        *(this->listMonHoc + this->n) = newMonHoc;
    }
    this->n++;
}



void QuanLyMonHoc::AddMonHoc() {

    string MaMonHoc;
    string TenMonHoc;
    int SoTinChi;

    cin.ignore(100, '\n');
    cout << "Nhap ma mon hoc: ";
    getline(cin, MaMonHoc);
    cout << "Nhap ten mon hoc: ";
    getline(cin, TenMonHoc);
    cout << "Nhap so tin chi: ";
    cin >> SoTinChi;

    MonHoc newMonHoc(MaMonHoc, TenMonHoc, SoTinChi);
    cout << newMonHoc;
    this->Add(newMonHoc);
}

void QuanLyMonHoc::Insert(const int& k) {
    string MaMonHoc;
    string TenMonHoc;
    int SoTinChi;

    cout << "Nhap ma MonHoc: ";
    getline(cin, MaMonHoc);
    cout << "Nhap ten MonHoc: ";
    getline(cin, TenMonHoc);
    cout << "Nhap so tin chi: ";
    cin >> SoTinChi;

    MonHoc newSv(MaMonHoc, TenMonHoc, SoTinChi);

    QuanLyMonHoc temp;
    temp.listMonHoc = new MonHoc[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.listMonHoc + i) = *(this->listMonHoc + i);
    }
    delete[] this->listMonHoc;
    this->listMonHoc = new MonHoc[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->listMonHoc + i) = *(temp.listMonHoc + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->listMonHoc + i) = *(this->listMonHoc + i - 1);
        }
        *(this->listMonHoc + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->listMonHoc + i) = *(temp.listMonHoc + i);
        }
        *(this->listMonHoc + this->n) = newSv;
    }
    this->n++;
}

int QuanLyMonHoc::IndexOf(string maMonHoc) {
    for (int i = 0; i < this->n; i++) {

        if (maMonHoc == (*this)[i].getMaMonHoc()) {
            return i + 1;
            break;
        }
    }
    return -1;
}

void QuanLyMonHoc::Remove(string MaMonHoc)
{
    int k = this->IndexOf(MaMonHoc) - 1;
    QuanLyMonHoc temp;
    if (k == -2) {
        cout << "Nhap sai ma mon hoc!!!" << endl;
    }
    else {
        temp.listMonHoc = new MonHoc[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listMonHoc + i) = *(this->listMonHoc + i);
        }
        delete[] this->listMonHoc;
        this->listMonHoc = new MonHoc[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->listMonHoc + i) = *(temp.listMonHoc + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->listMonHoc + i) = *(temp.listMonHoc + i + 1);
        }
        this->n--;
    }
}

void QuanLyMonHoc::Search() {
    QuanLyMonHoc dbSearch;
    string tenMonHoc;

    cout << "Nhap ten mon hoc can tim: ";
    getline(cin, tenMonHoc);
    for (int i = 0; i < this->n; i++) {
        string ten = (*this)[i].getTenMonHoc();
        if (ten.find(tenMonHoc) != -1) {
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QuanLyMonHoc::Update() {
    string MaMonHoc;
    string TenMonHoc;
    int SoTinChi;

    cin.ignore(100, '\n');
    cout << "Nhap ma mon hoc can update: ";
    getline(cin, MaMonHoc);
    cout << "Nhap ten mon hoc can sua: ";
    getline(cin, TenMonHoc);
    cout << "Nhap so tin chi can sua: ";
    cin >> SoTinChi;

    int k = this->IndexOf(MaMonHoc) - 1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(MaMonHoc, TenMonHoc, SoTinChi);
            break;
        }
    }
}



