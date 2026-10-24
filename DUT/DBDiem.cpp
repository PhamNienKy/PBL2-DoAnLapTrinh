#include "DBDiem.h"
#include "QuanLyDiem.h"
#include "Diem.h"

#include <iostream>
#include <sstream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBDiem::init()
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


void DBDiem::Display()
{
	// Truy van danh sach Diem
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)"SELECT * FROM Diem",
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
	SQLCHAR MaMon[256] = {};
	SQLREAL DiemSo = 0;

	SQLLEN lenMaSV = 0;
	SQLLEN lenMaMon = 0;
	SQLLEN lenDiemSo = 0;

	int stt = 1;

	cout << "\n";
	cout << "\t\tDANH SACH DIEM\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(20) << "MA SO SINH VIEN"
		<< setw(20) << "MA MON HOC"
		<< setw(15) << "DIEM SO"
		<< '\n';

	cout << string(60, '-') << '\n';

	// Doc tung dong du lieu
	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		// Lay ma sinh vien
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaSinhVien, sizeof(MaSinhVien), &lenMaSV);

		// Lay ma mon hoc
		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			MaMon, sizeof(MaMon), &lenMaMon);

		// Lay diem so
		SQLGetData(sqlStmtHandle, 3, SQL_C_FLOAT,
			&DiemSo, sizeof(DiemSo), &lenDiemSo);

		// Hien thi du lieu
		cout << left
			<< setw(5) << stt++
			<< setw(20) << (char*)MaSinhVien
			<< setw(20) << (char*)MaMon
			<< setw(15) << DiemSo
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}



void DBDiem::Display1Diem(string MaSV, string MaMon)
{
	// Truy van diem theo ma sinh vien va ma mon hoc
	string sql =
		"SELECT * FROM Diem WHERE MaSinhVien = '" + MaSV + "' AND MaMon = '" + MaMon + "'";

	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)sql.c_str(),
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
	SQLCHAR MaMonHoc[256] = {};
	SQLREAL DiemSo = 0;

	SQLLEN lenMaSV = 0;
	SQLLEN lenMaMon = 0;
	SQLLEN lenDiemSo = 0;

	// Doc du lieu
	ret = SQLFetch(sqlStmtHandle);

	if (ret == SQL_NO_DATA)
	{
		cout << "\n\tKhong tim thay diem cua sinh vien "
			<< MaSV << " o mon " << MaMon << '\n';

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
		MaSinhVien, sizeof(MaSinhVien), &lenMaSV);

	SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
		MaMonHoc, sizeof(MaMonHoc), &lenMaMon);

	SQLGetData(sqlStmtHandle, 3, SQL_C_FLOAT,
		&DiemSo, sizeof(DiemSo), &lenDiemSo);

	// Hien thi thong tin diem
	cout << "\n";
	cout << "\t\tTHONG TIN DIEM\n\n";

	cout << left
		<< setw(20) << "MA SO SINH VIEN"
		<< setw(20) << "MA MON HOC"
		<< setw(15) << "DIEM SO"
		<< '\n';

	cout << string(55, '-') << '\n';

	cout << left
		<< setw(20) << (char*)MaSinhVien
		<< setw(20) << (char*)MaMonHoc
		<< setw(15) << DiemSo
		<< '\n';

	SQLCloseCursor(sqlStmtHandle);
}


void DBDiem::InsertDiem()
{
	string MaSinhVien;
	string MaMon;
	float DiemSo;

	cin.ignore(100, '\n');

	cout << "\t\tNhap ma sinh vien: ";
	getline(cin, MaSinhVien);

	cout << "\t\tNhap ma mon: ";
	getline(cin, MaMon);

	cout << "\t\tNhap diem so: ";
	cin >> DiemSo;

	// Chuyen diem so thanh chuoi
	ostringstream convert;
	convert << DiemSo;
	string DiemSo1 = convert.str();

	// Tao cau lenh INSERT
	string s =
		"INSERT INTO Diem (MaSinhVien, MaMon, DiemSo) VALUES ('"
		+ MaSinhVien + "', '"
		+ MaMon + "', "
		+ DiemSo1 + ")";

	char m[500];
	snprintf(m, sizeof(m), "%s", s.c_str());

	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)m,
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\t\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	cout << "\n\t\tINSERT SUCCESS\n";
}

void DBDiem::UpdateDiem()
{
	string MaSinhVien;
	string MaMon;
	float DiemSo;

	cin.ignore(100, '\n');

	cout << "\t\tNhap ma sinh vien can cap nhat: ";
	getline(cin, MaSinhVien);

	cout << "\t\tNhap ma mon hoc can cap nhat: ";
	getline(cin, MaMon);

	cout << "\t\tNhap diem so moi: ";
	cin >> DiemSo;

	// Chuyen diem so thanh chuoi
	ostringstream convert;
	convert << DiemSo;
	string DiemSo1 = convert.str();

	// Tao cau lenh UPDATE
	string s =
		"UPDATE Diem SET DiemSo = " + DiemSo1 +
		" WHERE MaSinhVien = '" + MaSinhVien +
		"' AND MaMon = '" + MaMon + "'";

	char m[500];
	snprintf(m, sizeof(m), "%s", s.c_str());

	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)m,
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\t\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	// Kiem tra so dong duoc cap nhat
	SQLLEN rowsAffected = 0;
	SQLRowCount(sqlStmtHandle, &rowsAffected);

	if (rowsAffected > 0)
	{
		cout << "\n\t\tUPDATE SUCCESS\n";
	}
	else
	{
		cout << "\n\t\tKHONG TIM THAY DIEM CAN CAP NHAT\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}

void DBDiem::DeleteDiem(string MaSinhVien, string MaMon)
{
	string s = "DELETE FROM Diem WHERE MaSinhVien = '" + MaSinhVien + "' " + " AND MaMon = '" + MaMon + "'";
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

void DBDiem::DeleteAllDiem()
{
	string s = "DELETE FROM Diem";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tTOAN BO Diem DA DUOC XOA ";
		std::cout << "\n";
	}
	else {
		std::cout << "\n\t\tDELETE SUCCESS FACULTY";
		return;
	}
}

void DBDiem::SortTangDan()
{
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)"SELECT * FROM Diem ORDER BY DiemSo ASC",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tLoi khi sap xep diem!\n";
		closeDB();
		return;
	}

	SQLCHAR MaSinhVien[32] = {};
	SQLCHAR MaMon[256] = {};
	SQLREAL DiemSo = 0;

	SQLLEN lenMaSV = 0;
	SQLLEN lenMaMon = 0;
	SQLLEN lenDiemSo = 0;

	int stt = 1;

	cout << "\n\t\tDANH SACH DIEM TANG DAN\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(20) << "MA SO SINH VIEN"
		<< setw(20) << "MA MON HOC"
		<< setw(15) << "DIEM SO"
		<< '\n';

	cout << string(60, '-') << '\n';

	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaSinhVien, sizeof(MaSinhVien), &lenMaSV);

		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			MaMon, sizeof(MaMon), &lenMaMon);

		SQLGetData(sqlStmtHandle, 3, SQL_C_FLOAT,
			&DiemSo, sizeof(DiemSo), &lenDiemSo);

		cout << left
			<< setw(5) << stt++
			<< setw(20) << (char*)MaSinhVien
			<< setw(20) << (char*)MaMon
			<< setw(15) << DiemSo
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}

void DBDiem::SortGiamDan()
{
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)"SELECT * FROM Diem ORDER BY DiemSo DESC",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tLoi khi sap xep diem!\n";
		closeDB();
		return;
	}

	SQLCHAR MaSinhVien[32] = {};
	SQLCHAR MaMon[256] = {};
	SQLREAL DiemSo = 0;

	SQLLEN lenMaSV = 0;
	SQLLEN lenMaMon = 0;
	SQLLEN lenDiemSo = 0;

	int stt = 1;

	cout << "\n\t\tDANH SACH DIEM GIAM DAN\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(20) << "MA SO SINH VIEN"
		<< setw(20) << "MA MON HOC"
		<< setw(15) << "DIEM SO"
		<< '\n';

	cout << string(60, '-') << '\n';

	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaSinhVien, sizeof(MaSinhVien), &lenMaSV);

		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			MaMon, sizeof(MaMon), &lenMaMon);

		SQLGetData(sqlStmtHandle, 3, SQL_C_FLOAT,
			&DiemSo, sizeof(DiemSo), &lenDiemSo);

		cout << left
			<< setw(5) << stt++
			<< setw(20) << (char*)MaSinhVien
			<< setw(20) << (char*)MaMon
			<< setw(15) << DiemSo
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}

void DBDiem::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
