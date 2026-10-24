#include "DBMonHoc.h"
#include "QuanLyMonHoc.h"
#include "MonHoc.h"

#include <iostream>
#include <sstream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBMonHoc::init()
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

void DBMonHoc::Display()
{
	// Truy van danh sach MonHoc
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)"SELECT * FROM MonHoc",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	// Khai bao buffer
	SQLCHAR MaMonHoc[32] = {};
	SQLCHAR TenMonHoc[256] = {};
	SQLINTEGER SoTinChi = 0;

	SQLLEN lenMaMonHoc = 0;
	SQLLEN lenTenMonHoc = 0;
	SQLLEN lenSoTinChi = 0;

	int stt = 1;

	cout << "\n";
	cout << "\t\tDANH SACH MON HOC\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(15) << "MA MON HOC"
		<< setw(25) << "TEN MON HOC"
		<< setw(15) << "SO TIN CHI"
		<< '\n';

	cout << string(60, '-') << '\n';

	// Doc tung dong du lieu
	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		// Lay ma mon hoc
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaMonHoc, sizeof(MaMonHoc), &lenMaMonHoc);

		// Lay ten mon hoc
		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			TenMonHoc, sizeof(TenMonHoc), &lenTenMonHoc);

		// Lay so tin chi
		SQLGetData(sqlStmtHandle, 3, SQL_C_SLONG,
			&SoTinChi, sizeof(SoTinChi), &lenSoTinChi);

		// Hien thi
		cout << left
			<< setw(5) << stt++
			<< setw(15) << (char*)MaMonHoc
			<< setw(25) << (char*)TenMonHoc
			<< setw(15) << SoTinChi
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}


void DBMonHoc::Display1MonHoc(string maMonHoc)
{
	// Truy van mon hoc theo ma mon hoc
	string sql = "SELECT MaMon, TenMon, SoTinChi FROM MonHoc WHERE MaMon = '" + maMonHoc + "'";
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
	SQLCHAR MaMonHoc[32] = {};
	SQLCHAR TenMonHoc[256] = {};
	SQLINTEGER SoTinChi = 0;

	SQLLEN lenMaMonHoc = 0;
	SQLLEN lenTenMonHoc = 0;
	SQLLEN lenSoTinChi = 0;

	// Doc dong du lieu
	ret = SQLFetch(sqlStmtHandle);

	if (ret == SQL_NO_DATA)
	{
		cout << "\n\tKhong tim thay mon hoc co ma: "
			<< maMonHoc << '\n';

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
		MaMonHoc, sizeof(MaMonHoc), &lenMaMonHoc);

	SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
		TenMonHoc, sizeof(TenMonHoc), &lenTenMonHoc);

	SQLGetData(sqlStmtHandle, 3, SQL_C_SLONG,
		&SoTinChi, sizeof(SoTinChi), &lenSoTinChi);

	// Hien thi thong tin mon hoc
	cout << "\n";
	cout << "\t\tTHONG TIN MON HOC\n\n";

	cout << left
		<< setw(15) << "MA MON HOC"
		<< setw(25) << "TEN MON HOC"
		<< setw(15) << "SO TIN CHI"
		<< '\n';

	cout << string(55, '-') << '\n';

	cout << left
		<< setw(15) << (char*)MaMonHoc
		<< setw(25) << (char*)TenMonHoc
		<< setw(15) << SoTinChi
		<< '\n';

	SQLCloseCursor(sqlStmtHandle);
}



void DBMonHoc::SelectDB(QuanLyMonHoc& db)
{

	//output
	db.Clear();
	std::cout << "\n";
	std::cout << "\t\tEXECUTING T-SQL QUERY...";
	std::cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM MonHoc", SQL_NTS)) {
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaMon[100];
		CHAR TenMon[100];
		SQLINTEGER SoTinChi[50];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaMon, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenMon, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_DEFAULT, SoTinChi, SQL_RESULT_LEN, &ptrSqlVersion);


			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaMon << setw(20) << TenMon << setw(15) << SoTinChi << setw(15) << endl;
			MonHoc mh(string((char*)MaMon), string((char*)TenMon), (int)SoTinChi);
			db.Add(mh);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBMonHoc::SelectMonHoc(QuanLyMonHoc& db, string MaMonHoc)
{
	db.Clear();
	string s1 = "SELECT MonHoc.MaMon, TenMon, MaKhoa FROM MonHoc ";
	string s2 = "INNER JOIN Diem ON MonHoc.MaMon = Diem.MaMon WHERE MonHoc.MaMon = '" + MaMonHoc + "'";
	string s = s1 + s2;
	char m[500];
	snprintf(m, size(m), "%s", s.c_str());
	std::cout << "\n";
	std::cout << "\t\tExecuting T-SQL query...";
	std::cout << "\n";

	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaMon[50];
		CHAR TenMon[100];
	    SQLINTEGER SoTinChi[100];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaMon, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenMon, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_INTEGER, SoTinChi, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaMon << setw(20) << TenMon << setw(15) << SoTinChi << setw(15) << endl;
			MonHoc mh(string((char*)MaMon), string((char*)TenMon), (int)SoTinChi);
			db.Add(mh);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBMonHoc::InsertMonHoc()
{
	string MaMon;
	string TenMon;
	int SoTinChi;

	cin.ignore(100, '\n');
	std::cout << "\t\tNhap ma mon hoc: ";
	getline(cin, MaMon);
	std::cout << "\t\tNhap ten mon hoc: ";
	getline(cin, TenMon);
	std::cout << "\t\tNhap so tin chi: ";
	cin >> SoTinChi;
	ostringstream convert;
	convert << SoTinChi;
	string SoTinChi1;
	SoTinChi1 = convert.str();

	string s = "INSERT INTO MonHoc VALUES('" + MaMon + "','" + TenMon + "','" + SoTinChi1 + "')";
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


void DBMonHoc::UpdateMonHoc()
{
	string MaMon;
	string TenMon;
	int SoTinChi;

	cin.ignore(100, '\n');

	cout << "\t\tMa mon hoc can cap nhat: ";
	getline(cin, MaMon);

	cout << "\t\tNhap ten mon hoc moi: ";
	getline(cin, TenMon);

	cout << "\t\tNhap so tin chi moi: ";
	cin >> SoTinChi;

	// Chuyen so tin chi thanh chuoi
	ostringstream convert;
	convert << SoTinChi;
	string SoTinChi1 = convert.str();

	// Tao cau lenh UPDATE
	string s =
		"UPDATE MonHoc SET TenMon = '" + TenMon + "', SoTinChi = " + SoTinChi1 + " WHERE MaMon = '" + MaMon + "'";

	char m[1000];
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
		cout << "\n\t\tUPDATE SUCCESS";
	}
	else
	{
		cout << "\n\t\tKHONG TIM THAY MA MON HOC CAN CAP NHAT";
	}

	SQLCloseCursor(sqlStmtHandle);
}



void DBMonHoc::DeleteMonHoc(string MaMonHoc)
{
	// Tao cau lenh DELETE
	string s =
		"DELETE FROM MonHoc WHERE MaMon = '" +
		MaMonHoc + "'";

	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)s.c_str(),
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\t\tXOA MON HOC THAT BAI!\n";

		// Hien thi chi tiet loi ODBC
		SQLCHAR sqlState[6] = {};
		SQLINTEGER nativeError = 0;
		SQLCHAR message[SQL_MAX_MESSAGE_LENGTH] = {};
		SQLSMALLINT messageLength = 0;

		SQLGetDiagRecA(
			SQL_HANDLE_STMT,
			sqlStmtHandle,
			1,
			sqlState,
			&nativeError,
			message,
			sizeof(message),
			&messageLength
		);

		cout << "\tSQL State: " << sqlState << '\n';
		cout << "\tMa loi: " << nativeError << '\n';
		cout << "\tChi tiet: " << message << '\n';

		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	// Kiem tra so dong bi xoa
	SQLLEN rowsAffected = 0;
	SQLRowCount(sqlStmtHandle, &rowsAffected);

	if (rowsAffected > 0)
	{
		cout << "\n\t\tDELETE SUCCESS";
	}
	else
	{
		cout << "\n\t\tKhong tim thay mon hoc co ma: "
			<< MaMonHoc;
	}

	SQLCloseCursor(sqlStmtHandle);
}



void DBMonHoc::DeleteAllMonHoc()
{
	string s = "DELETE FROM MonHoc";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tTOAN BO MonHoc DA DUOC XOA ";
		std::cout << "\n";
	}
	else {
		std::cout << "\n\t\tDELETE SUCCESS FACULTY";
		return;
	}
}

void DBMonHoc::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
