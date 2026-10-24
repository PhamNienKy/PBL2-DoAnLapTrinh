#include "DBSinhVien.h"
#include "SinhVien.h"
#include "Diem.h"
#include "Lop.h"

#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBSinhVien::init()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		closeDB();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		closeDB();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		closeDB();

	//output
	std::cout << "\t\tCONNECTING TO SQL SERVER...";
	std::cout << "\n";

	SQLRETURN ret;

	ret = SQLDriverConnectW(
		sqlConnHandle,
		NULL,
		(SQLWCHAR*)L"DRIVER={ODBC Driver 18 for SQL Server};"
		L"SERVER=localhost\\SQLEXPRESS;"
		L"DATABASE=DUT;"
		L"UID=sa;"
		L"PWD=123456;"
		L"Encrypt=Yes;"
		L"TrustServerCertificate=Yes;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT
	);

	if (SQL_SUCCEEDED(ret))
	{
		std::cout << "CONNECTED SUCCESSFULLY!\n";
	}
	else
	{
		SQLWCHAR state[6] = {};
		SQLWCHAR message[1024] = {};
		SQLINTEGER nativeError = 0;
		SQLSMALLINT messageLength = 0;

		SQLGetDiagRecW(
			SQL_HANDLE_DBC,
			sqlConnHandle,
			1,
			state,
			&nativeError,
			message,
			1024,
			&messageLength
		);

		std::wcout << L"SQLSTATE: " << state << L'\n';
		std::wcout << L"ERROR: " << message << L'\n';
	}
	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		closeDB();
}

void DBSinhVien::Display()
{
	// Truy van danh sach sinh vien
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)
		"SELECT MaSinhVien, HoTen, NgaySinh, "
		"GioiTinh, DiaChi, Email, MaLop "
		"FROM SinhVien",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	// Khai bao buffer
	SQLCHAR MaSinhVien[32] = {};
	SQLCHAR HoTen[256] = {};
	SQLCHAR NgaySinh[32] = {};
	SQLCHAR GioiTinh[32] = {};
	SQLCHAR DiaChi[256] = {};
	SQLCHAR Email[256] = {};
	SQLCHAR MaLop[32] = {};

	SQLLEN len = 0;
	int stt = 1;

	cout << "\n";
	cout << "\t\tDANH SACH SINH VIEN\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(15) << "MA SINH VIEN"
		<< setw(25) << "HO TEN"
		<< setw(15) << "NGAY SINH"
		<< setw(15) << "GIOI TINH"
		<< setw(25) << "DIA CHI"
		<< setw(30) << "EMAIL"
		<< setw(15) << "MA LOP"
		<< '\n';

	cout << string(145, '-') << '\n';

	// Doc tung dong du lieu
	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaSinhVien, sizeof(MaSinhVien), &len);

		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			HoTen, sizeof(HoTen), &len);

		SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR,
			NgaySinh, sizeof(NgaySinh), &len);

		SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR,
			GioiTinh, sizeof(GioiTinh), &len);

		SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR,
			DiaChi, sizeof(DiaChi), &len);

		SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR,
			Email, sizeof(Email), &len);

		SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR,
			MaLop, sizeof(MaLop), &len);

		cout << left
			<< setw(5) << stt++
			<< setw(15) << (char*)MaSinhVien
			<< setw(25) << (char*)HoTen
			<< setw(15) << (char*)NgaySinh
			<< setw(15) << (char*)GioiTinh
			<< setw(25) << (char*)DiaChi
			<< setw(50) << (char*)Email
			<< setw(15) << (char*)MaLop
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}


void DBSinhVien::Display1SinhVien(string maSV)
{
	// Truy van sinh vien theo ma so sinh vien
	string sql =
		"SELECT MaSinhVien, HoTen, NgaySinh, "
		"GioiTinh, DiaChi, Email, MaLop "
		"FROM SinhVien "
		"WHERE MaSinhVien = '" + maSV + "'";

	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)sql.c_str(),
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tERROR QUERYING SQL SERVER\n";
		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	// Khai bao buffer
	SQLCHAR MaSinhVien[32] = {};
	SQLCHAR HoTen[256] = {};
	SQLCHAR NgaySinh[32] = {};
	SQLCHAR GioiTinh[32] = {};
	SQLCHAR DiaChi[256] = {};
	SQLCHAR Email[256] = {};
	SQLCHAR MaLop[32] = {};

	SQLLEN len = 0;

	// Doc dong du lieu
	ret = SQLFetch(sqlStmtHandle);

	if (ret == SQL_NO_DATA)
	{
		cout << "\n\tKhong tim thay sinh vien co ma: "
			<< maSV << '\n';

		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	// Lay du lieu tung cot
	SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
		MaSinhVien, sizeof(MaSinhVien), &len);

	SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
		HoTen, sizeof(HoTen), &len);

	SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR,
		NgaySinh, sizeof(NgaySinh), &len);

	SQLGetData(sqlStmtHandle, 4, SQL_C_CHAR,
		GioiTinh, sizeof(GioiTinh), &len);

	SQLGetData(sqlStmtHandle, 5, SQL_C_CHAR,
		DiaChi, sizeof(DiaChi), &len);

	SQLGetData(sqlStmtHandle, 6, SQL_C_CHAR,
		Email, sizeof(Email), &len);

	SQLGetData(sqlStmtHandle, 7, SQL_C_CHAR,
		MaLop, sizeof(MaLop), &len);

	// Hien thi thong tin sinh vien
	cout << "\n";
	cout << "\t\tTHONG TIN SINH VIEN\n\n";

	cout << left
		<< setw(15) << "MA SINH VIEN"
		<< setw(25) << "HO TEN"
		<< setw(15) << "NGAY SINH"
		<< setw(15) << "GIOI TINH"
		<< setw(25) << "DIA CHI"
		<< setw(30) << "EMAIL"
		<< setw(15) << "MA LOP"
		<< '\n';

	cout << string(140, '-') << '\n';

	cout << left
		<< setw(15) << (char*)MaSinhVien
		<< setw(25) << (char*)HoTen
		<< setw(15) << (char*)NgaySinh
		<< setw(15) << (char*)GioiTinh
		<< setw(25) << (char*)DiaChi
		<< setw(30) << (char*)Email
		<< setw(15) << (char*)MaLop
		<< '\n';

	SQLCloseCursor(sqlStmtHandle);
}


void DBSinhVien::SelectSinhVien(QuanLySinhVien& db)
{

	//output
	db.Clear();
	std::cout << "\n";
	std::cout << "\t\tEXECUTING T-SQL QUERY...";
	std::cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM SinhVien INNER JOIN Lop ON SinhVien.MaLop = MaLop", SQL_NTS)) {
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaSinhVien[20];
		CHAR HoTen[50];
		CHAR NgaySinh[20];
		CHAR GioiTinh[20];
		CHAR DiaChi[20];
		CHAR Email[50];
		CHAR MaLop[10];
		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaSinhVien, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, HoTen, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, NgaySinh, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, GioiTinh, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_CHAR, DiaChi, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 6, SQL_CHAR, Email, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 7, SQL_CHAR, MaLop, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaSinhVien << setw(20) << HoTen << setw(30) << NgaySinh << " " << setw(15) << GioiTinh
				<< setw(15) << DiaChi << setw(20) << Email << setw(50) << MaLop << setw(15) << endl;
			SinhVien s1(MaSinhVien, HoTen, NgaySinh, GioiTinh, DiaChi, Email, MaLop);
			db.Add(s1);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBSinhVien::InsertSinhVien()
{
	string MaSinhVien;
	string HoTen;
	string NgaySinh;
	string GioiTinh;
	string DiaChi;
	string Email;
	string MaLop;
	cin.ignore(100, '\n');
	std::cout << "\t\tNhap ma sinh vien: ";
	getline(cin, MaSinhVien);
	std::cout << "\t\tNhap ho ten sinh vien: ";
	getline(cin, HoTen);
	std::cout << "\t\tNhap ngay sinh (dd/mm/yy): ";
	getline(cin, NgaySinh);
	cin.ignore(100, '\n');
	std::cout << "\t\tNhap gioi tinh sinh vien (Nam/Nu/Khac): ";
	getline(cin, GioiTinh);
	std::cout << "\t\tNhap dia chi: ";
	getline(cin, DiaChi);
	std::cout << "\t\tNhap email: ";
	getline(cin, Email);
	std::cout << "\t\tNhap ma lop: ";
	getline(cin, MaLop);
	ostringstream convert;
	convert << NgaySinh;

	string s = "INSERT INTO SinhVien VALUES('" + MaSinhVien + "','" + HoTen + "','" + NgaySinh + "','" + GioiTinh + "','" + DiaChi
		+ "','" + Email + "','" + MaLop + "')";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {

		std::cout << "\n";
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		std::cout << "\n\t\tINSERT SUCCESS";
		std::cout << "\n";
		return;
	}
}

void DBSinhVien::UpdateSinhVien()
{
	string MaSinhVien;
	string HoTen;
	string NgaySinh;
	string GioiTinh;
	string DiaChi;
	string Email;
	string MaLop;
	cin.ignore(100, '\n');
	std::cout << "\t\tMa sinh vien can cap nhat : ";
	getline(cin, MaSinhVien);
	std::cout << "\t\tNhap ho ten sinh vien: ";
	getline(cin, HoTen);
	std::cout << "\t\tNhap ngay sinh (dd/mm/yy): ";
	getline(cin, NgaySinh);
	cin.ignore(100, '\n');
	std::cout << "\t\tNhap gioi tinh sinh vien (Nam/Nu/Khac): ";
	getline(cin, GioiTinh);
	std::cout << "\t\tNhap dia chi: ";
	getline(cin, DiaChi);
	std::cout << "\t\tNhap email: ";
	getline(cin, Email);
	std::cout << "\t\tNhap ma lop: ";
	getline(cin, MaLop);
	ostringstream convert;
	convert << NgaySinh;
	string s = "UPDATE SinhVien SET HoTen = '" + HoTen + "', NgaySinh = '" + NgaySinh + "', GioiTinh = '" + GioiTinh + "', DiaChi = '" + DiaChi
		+ "', Email = '" + Email + "', MaLop = '" + MaLop + "'WHERE MaSinhVien = '" + MaSinhVien + "'";
	char m[300];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		std::cout << "\n\t\tUPDATE SUCCESS";
		return;
	}
}

void DBSinhVien::DeleteSinhVien(string MaSinhVien)
{
	string s = "DELETE FROM SinhVien WHERE MaSinhVien = '" + MaSinhVien + "' ";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {

		std::cout << "\n\t\tDELETE SUCCESS";
		return;
	}
}

void DBSinhVien::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
