#include "QuanLyDiem.h"
#include <iostream>
#include <algorithm>

using namespace std;

QuanLyDiem::QuanLyDiem()
{
    this->n = 0;
    this->listDiem = nullptr;

}

QuanLyDiem::~QuanLyDiem()
{
    delete[] this->listDiem;

}

ostream& operator<<(ostream& o, const QuanLyDiem& db)
{
    cout << setw(5) << "STT" << setw(50) << "MA SINH VIEN" << setw(50) << "MA MON" << setw(50) << "DIEM SO" << setw(15) << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < db.n; i++) {
        o << setw(5) << i + 1 << *(db.listDiem + i) << endl << endl;
    }
    return o;
}

Diem& QuanLyDiem::operator[](const int& s)
{
    static Diem error;
    return ((s >= 0) && (s < this->n)) ? *(this->listDiem + s) : error;
}

void QuanLyDiem::Display() {
    cout << setw(5) << "STT"
        << setw(20) << "Ma Sinh Vien"
        << setw(25) << "Ma Mon Hoc"
        << setw(25) << "Diem So" << endl;
    for (int i = 1; i < this->n; i++) {
        cout << setw(5) << i + 1
            << setw(20) << (*this)[i].GetMaSinhVien()
            << setw(20) << (*this)[i].GetMaMon()
            << setw(20) << (*this)[i].GetDiemSo()
            << endl;
    }
}


int QuanLyDiem::GetN()
{
    return this->n;
}

void QuanLyDiem::Clear()
{
    this->n = 0;
    delete[] this->listDiem;
}
void QuanLyDiem::Add(Diem newDiem) {

    if (this->n == 0) {
        this->listDiem = new Diem[this->n + 1];
        this->listDiem[this->n] = newDiem;
    }
    else {
        QuanLyDiem temp;
        temp.listDiem = new Diem[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listDiem + i) = *(this->listDiem + i);
        }
        delete[] this->listDiem;
        this->listDiem = new Diem[this->n + 1];
        for (int j = 0; j < this->n; j++) {
            *(this->listDiem + j) = *(temp.listDiem + j);
        }
        *(this->listDiem + this->n) = newDiem;
    }
    this->n++;
}



void QuanLyDiem::AddDiem() {

    string MaSinhVien;
    string MaMonHoc;
    float DiemSo;

    cin.ignore(100, '\n');
    cout << "Nhap ma so sinh vien: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ten Diem: ";
    getline(cin, MaMonHoc);
    cout << "Nhap ma khoa: ";
    cin >> DiemSo;

    Diem newDiem(MaSinhVien, MaMonHoc, DiemSo);
    cout << newDiem;
    this->Add(newDiem);
}

void QuanLyDiem::Insert(const int& k) {
    string MaSinhVien;
    string MaMonHoc;
    float DiemSo;

    cout << "Nhap ma sinh vien: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ma mon hoc: ";
    getline(cin, MaMonHoc);
    cout << "Nhap ma khoa: ";
    cin >> DiemSo;

    Diem newSv(MaSinhVien, MaMonHoc, DiemSo);

    QuanLyDiem temp;
    temp.listDiem = new Diem[this->n];
    for (int i = 0; i < this->n; i++) {
        *(temp.listDiem + i) = *(this->listDiem + i);
    }
    delete[] this->listDiem;
    this->listDiem = new Diem[this->n + 1];
    if (k <= this->n) {
        for (int i = 0; i < this->n; i++) {
            *(this->listDiem + i) = *(temp.listDiem + i);
        }
        for (int i = this->n; i >= k; i--) {
            *(this->listDiem + i) = *(this->listDiem + i - 1);
        }
        *(this->listDiem + k) = newSv;
    }
    else {
        for (int i = 0; i < this->n; i++) {
            *(this->listDiem + i) = *(temp.listDiem + i);
        }
        *(this->listDiem + this->n) = newSv;
    }
    this->n++;
}

int QuanLyDiem::IndexOf(float DiemSo) {
    for (int i = 0; i < this->n; i++) {

        if (DiemSo == (*this)[i].GetDiemSo()) {
            return i + 1;
            break;
        }
    }
    return -1;
}

void QuanLyDiem::Remove(float DiemSo)
{
    int k = this->IndexOf(DiemSo) - 1;
    QuanLyDiem temp;
    if (k == -2) {
        cout << "Nhap sai diem so!!!" << endl;
    }
    else {
        temp.listDiem = new Diem[this->n];
        for (int i = 0; i < this->n; i++) {
            *(temp.listDiem + i) = *(this->listDiem + i);
        }
        delete[] this->listDiem;
        this->listDiem = new Diem[this->n - 1];
        for (int i = 0; i < k; i++) {
            *(this->listDiem + i) = *(temp.listDiem + i);
        }
        for (int i = k; i < (this->n - 1); i++) {
            *(this->listDiem + i) = *(temp.listDiem + i + 1);
        }
        this->n--;
    }
}

void QuanLyDiem::Search() {
    QuanLyDiem dbSearch;
    float DiemSo;
    cout << "Nhap diem so can tim: ";
    cin >> DiemSo;
    for (int i = 0; i < this->n; i++) {
        if (float ten = (*this)[i].GetDiemSo()) 
        {
            ;
            dbSearch.Add((*this)[i]);
        }
    }
    cout << dbSearch;
}

void QuanLyDiem::Update() {
    string MaSinhVien;
    string MaMonHoc;
    float DiemSo;

    cin.ignore(100, '\n');
    cout << "Nhap ma so sinh vien: ";
    getline(cin, MaSinhVien);
    cout << "Nhap ma mon hoc: ";
    getline(cin, MaMonHoc);
    cout << "Nhap diem so can sua: ";
    cin >> DiemSo;

    int k = this->IndexOf(DiemSo) - 1;

    for (int i = 0; i < this->n; i++) {
        if (i == k) {
            (*this)[i].Update(MaSinhVien, MaMonHoc, DiemSo);
            break;
        }
    }
}

void QuanLyDiem::SortAZ() {
    for (int i = 0; i < this->n - 1; i++)
    {
        for (int j = i + 1; j < this->n; j++)
        {
            if ((*this)[i].GetDiemSo() > (*this)[j].GetDiemSo())
            {
                swap((*this)[i], (*this)[j]);
            }
        }
    }
}


