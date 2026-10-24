#include "QuanLySinhVien.h"
#include "QuanLyLop.h"
#include "QuanLyKhoa.h"
#include "QuanLyDiem.h"
#include "QuanLyMonHoc.h"

#include "DBHelper.h"
#include "DBSinhVien.h"
#include "DBLop.h"
#include "DBKhoa.h"
#include "DBDiem.h"
#include "DBMonHoc.h"

#include <iostream>

using namespace std;
string MaLop;
string MaKhoa;
int CHECK;

void ShowMenu()
{
    std::cout << "\n";
    std::cout << "\t\t--------------TRUONG DAI HOC BACH KHOA - DAI HOC DA NANG-------------------" << endl;
    std::cout << "\t\t\t\t" << setw(5) << "I." << "  QUAN LY THONG TIN SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << setw(5) << "II." << "  QUAN LY THONG TIN LOP" << endl; // SINH VIEN
    std::cout << "\t\t\t\t" << setw(5) << "III." << "   QUAN LY THONG TIN KHOA" << endl; // SINH VIEN, TKB
    std::cout << "\t\t\t\t" << setw(5) << "IV." << "  QUAN LY THONG TIN MON HOC" << endl;// SINH VIEN, TKB, DIEM
    std::cout << "\t\t\t\t" << setw(5) << "V." << "   QUAN LY THONG TIN DIEM" << endl;// SINH VIEN, TKB, DIEM
    std::cout << "\t\t\t\t" << setw(5) << "  NHAP 0 DE THOAT !!!" << endl;
}

void ShowSinhVien()
{
    std::cout << "\n";
    std::cout << "\t\t----------------------------------HIEN THI THONG TIN SINH VIEN------------------------------------" << endl;
    std::cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   2.  HIEN THI THONG TIN CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   3.  THEM THONG TIN CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   4.  SUA THONG TIN CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   5.  XOA THONG TIN CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowLop()
{
    std::cout << "\n";
    std::cout << "\t\t----------------------------------HIEN THI THONG TIN LOP------------------------------------" << endl;
    std::cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA CAC LOP" << endl;
    std::cout << "\t\t\t\t" << "   2.  HIEN THI THONG TIN CUA MOT LOP" << endl;
    std::cout << "\t\t\t\t" << "   3.  THEM THONG TIN CUA MOT LOP" << endl;
    std::cout << "\t\t\t\t" << "   4.  SUA THONG TIN CUA MOT LOP" << endl;
    std::cout << "\t\t\t\t" << "   5.  XOA THONG TIN CUA MOT LOP" << endl;
    std::cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowKhoa()
{
    std::cout << "\n";
    std::cout << "\t\t----------------------------------HIEN THI THONG TIN KHOA------------------------------------" << endl;
    std::cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA CAC KHOA" << endl;
    std::cout << "\t\t\t\t" << "   2.  HIEN THI THONG TIN CUA MOT KHOA" << endl;
    std::cout << "\t\t\t\t" << "   3.  THEM THONG TIN CUA MOT KHOA" << endl;
    std::cout << "\t\t\t\t" << "   4.  SUA THONG TIN CUA MOT KHOA" << endl;
    std::cout << "\t\t\t\t" << "   5.  XOA THONG TIN CUA MOT KHOA" << endl;
    std::cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowMonHoc()
{
    std::cout << "\n";
    std::cout << "\t\t----------------------------------HIEN THI THONG TIN MON HOC------------------------------------" << endl;
    std::cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA CAC MON HOC" << endl;
    std::cout << "\t\t\t\t" << "   2.  HIEN THI THONG TIN CUA MOT MON HOC" << endl;
    std::cout << "\t\t\t\t" << "   3.  THEM THONG TIN CUA MOT MON HOC" << endl;
    std::cout << "\t\t\t\t" << "   4.  SUA THONG TIN CUA MOT MON HOC" << endl;
    std::cout << "\t\t\t\t" << "   5.  XOA THONG TIN CUA MOT MON HOC" << endl;
    std::cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void ShowDiem()
{
    std::cout << "\n";
    std::cout << "\t\t----------------------------------HIEN THI THONG TIN DIEM------------------------------------" << endl;
    std::cout << "\t\t\t\t" << "   1.  HIEN THI THONG TIN TAT CA CAC DIEM" << endl;
    std::cout << "\t\t\t\t" << "   2.  HIEN THI THONG TIN DIEM CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   3.  THEM DIEM CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   4.  SUA DIEM CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   5.  XOA DIEM CUA MOT SINH VIEN" << endl;
    std::cout << "\t\t\t\t" << "   6.  SAP XEP DIEM THEO THU TU TANG DAN" << endl;
    std::cout << "\t\t\t\t" << "   7.  SAP XEP DIEM THEO THU TU GIAM DAN" << endl;
    std::cout << "\t\t\t\t" << "NHAP 0 DE THOAT !!!" << endl;
}

void SelectSinhVien(QuanLySinhVien& db, DBSinhVien database)
{
    string MaSinhVien;
    int temp = 1;

    while (temp)
    {
        int m;
        ShowSinhVien();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            database.Display(); 
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma so sinh vien : ";
            getline(cin, MaSinhVien);
            database.Display1SinhVien(MaSinhVien);
            break;
        case 3:
            database.InsertSinhVien();
            break;
        case 4:
            database.UpdateSinhVien();
            break;
        case 5:
            std::cout << "\t\tNhap ma sinh vien : ";
            getline(cin, MaSinhVien);
            database.DeleteSinhVien(MaSinhVien);
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void SelectLop(QuanLyLop& db, DBLop database)
{
    string MaLop;
    int temp = 1;

    while (temp)
    {
        int m;
        ShowLop();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            database.Display();
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma lop : ";
            getline(cin, MaLop);
            database.Display1Lop(MaLop);
            break;
        case 3:
            database.InsertLop();
            break;
        case 4:
            database.UpdateLop();
            break;
        case 5:
            std::cout << "\t\tNhap ma lop can xoa: ";
            getline(cin, MaLop);
            database.DeleteLop(MaLop);
            break;
        default:
            temp = 0;
            break;
        }
    }
}


void SelectKhoa(QuanLyKhoa& db, DBKhoa& database)
{
    string MaKhoa;
    int temp = 1;

    while (temp)
    {
        int m;
        ShowKhoa();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            database.Display();
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma khoa : ";
            getline(cin, MaKhoa);
            database.Display1Khoa(MaKhoa);
            break;
        case 3:
            database.InsertKhoa();
            break;
        case 4:
            database.UpdateKhoa();
            break;
        case 5:
            std::cout << "\t\tNhap ma khoa can xoa: ";
            getline(cin, MaKhoa);
            database.DeleteKhoa(MaKhoa);
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void SelectMonHoc(QuanLyMonHoc& db, DBMonHoc& database)
{
    string MaMon;
    int temp = 1;

    while (temp)
    {
        int m;
        ShowMonHoc();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            database.Display();
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma mon hoc : ";
            getline(cin, MaMon);
            database.Display1MonHoc(MaMon);
            break;
        case 3:
            database.InsertMonHoc();
            break;
        case 4:
            database.UpdateMonHoc();
            break;
        case 5:
            std::cout << "\t\tNhap ma mon can xoa: ";
            getline(cin, MaMon);
            database.DeleteMonHoc(MaMon);
            break;
        default:
            temp = 0;
            break;
        }
    }
}

void SelectDiem(QuanLyDiem& db, DBDiem& database)
{
    string MaSinhVien;
    string MaMon;
    int temp = 1;

    while (temp)
    {
        int m;
        ShowDiem();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> m;
        cin.ignore(100, '\n');
        switch (m)
        {
        case 1:
            database.Display();
            break;
        case 2:
            cin.ignore(100, '\n');
            cout << "\t\tNhap ma sinh vien : ";
            getline(cin, MaSinhVien);
            cout << "\t\tNhap ma mon : ";
            getline(cin, MaMon);
            database.Display1Diem(MaSinhVien, MaMon);
            break;
        case 3:
            database.InsertDiem();
            break;
        case 4:
            database.UpdateDiem();
            break;
        case 5:
            std::cout << "\t\tNhap ma sinh vien can xoa diem: ";
            getline(cin, MaSinhVien);
            std::cout << "\t\tNhap ma mon can xoa diem: ";
            getline(cin, MaMon);
            database.DeleteDiem(MaSinhVien, MaMon);
            break;
        case 6:
            database.SortTangDan();
            break;
        case 7: 
            database.SortGiamDan();
        default:
            temp = 0;
            break;
        }
    }
}


int main()
{
    DBHelper connect;
    connect.init();

    QuanLySinhVien db1;
    DBSinhVien database1;
    database1.init();

    QuanLyLop db2;
    DBLop database2;
    database2.init();

    QuanLyKhoa db3;
    DBKhoa database3;
    database3.init();

    QuanLyMonHoc db4;
    DBMonHoc database4;
    database4.init();

    QuanLyDiem db5;
    DBDiem database5;
    database5.init();

    int k = 1;
    while (k) {
        int temp;
        ShowMenu();
        std::cout << "\t\tTHUC HIEN CHUC NANG SO : ";
        cin >> temp;
        switch (temp)
        {
        case 1:
            SelectSinhVien(db1, database1);
            break;
        case 2:
            SelectLop(db2, database2);
            break;
        case 3:
            SelectKhoa(db3, database3);
            break;
        case 4:
            SelectMonHoc(db4, database4);
            break;
        case 5:
            SelectDiem(db5, database5);
            break;
        default:
            k = 0;
            break;
        }
    }
    return 0;
}