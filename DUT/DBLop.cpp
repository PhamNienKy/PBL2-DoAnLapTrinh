#include "DBLop.h"
#include "QuanLyLop.h"
#include "Lop.h"

#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBLop::init()
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

void DBLop::Display()
{
	// Truy van danh sach Lop
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)
		"SELECT * FROM Lop",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	// Khai bao buffer
	SQLCHAR MaLop[32] = {};
	SQLCHAR TenLop[256] = {};
	SQLCHAR MaKhoa[256] = {};
	SQLLEN len = 0;
	int stt = 1;

	cout << "\n";
	cout << "\t\tDANH SACH LOP\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(15) << "MA LOP"
		<< setw(25) << "TEN Lop"
		<< setw(25) << "MA KHOA"
		<< '\n';

	cout << string(145, '-') << '\n';

	// Doc tung dong du lieu
	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaLop, sizeof(MaLop), &len);

		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			TenLop, sizeof(TenLop), &len);

		cout << left
			<< setw(5) << stt++
			<< setw(15) << (char*)MaLop
			<< setw(25) << (char*)TenLop
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}


void DBLop::Display1Lop(string maLop)
{
	// Tao cau truy van SQL
	string sql =
		"SELECT MaLop, TenLop, MaKhoa "
		"FROM Lop "
		"WHERE MaLop = '" + maLop + "'";

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
	SQLCHAR MaLop[32] = {};
	SQLCHAR TenLop[256] = {};
	SQLCHAR MaKhoa[32] = {};

	SQLLEN lenMaLop = 0;
	SQLLEN lenTenLop = 0;
	SQLLEN lenMaKhoa = 0;

	// Doc dong du lieu dau tien
	ret = SQLFetch(sqlStmtHandle);

	if (ret == SQL_NO_DATA)
	{
		cout << "\n\tKhong tim thay lop co ma: "
			<< maLop << '\n';

		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
		SQLCloseCursor(sqlStmtHandle);
		return;
	}

	// Lay du lieu 3 cot
	SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
		MaLop, sizeof(MaLop), &lenMaLop);

	SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
		TenLop, sizeof(TenLop), &lenTenLop);

	SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR,
		MaKhoa, sizeof(MaKhoa), &lenMaKhoa);

	// Hien thi thong tin lop
	cout << "\n\t\tTHONG TIN LOP\n\n";

	cout << left
		<< setw(15) << "MA LOP"
		<< setw(30) << "TEN LOP"
		<< setw(15) << "MA KHOA"
		<< '\n';

	cout << string(60, '-') << '\n';

	cout << left
		<< setw(15) << (char*)MaLop
		<< setw(30) << (char*)TenLop
		<< setw(15) << (char*)MaKhoa
		<< '\n';

	SQLCloseCursor(sqlStmtHandle);
}


void DBLop::SelectDB(QuanLyLop& db)
{

	//output
	db.Clear();
	std::cout << "\n";
	std::cout << "\t\tEXECUTING T-SQL QUERY...";
	std::cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Lop INNER JOIN Khoa ON Khoa.MaLop = MaLop", SQL_NTS)) {
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaLop[20];
		CHAR TenLop[50];
		CHAR MaKhoa[50];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaLop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenLop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, MaKhoa, SQL_RESULT_LEN, &ptrSqlVersion);


			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaLop << setw(20) << TenLop << setw(15) << MaKhoa << setw(15) << endl;
			Lop l(MaLop, TenLop, MaKhoa);
			db.Add(l);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBLop::SelectLop(QuanLyLop& db, string MaLop)
{
	db.Clear();
	string s = "SELECT MaLop, TenLop, MaKhoa FROM Lop WHERE Lop.MaLop = '" + MaLop + "'";
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
		CHAR MaLop[50];
		CHAR TenLop[100];
		CHAR MaKhoa[100];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaLop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenLop, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, MaKhoa, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaLop << setw(20) << TenLop << setw(15) << MaKhoa << setw(15) << endl;
			Lop l(MaLop, TenLop, MaKhoa);
			db.Add(l);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBLop::InsertLop()
{
	string MaLop;
	string TenLop;
	string MaKhoa;

	cin.ignore(100, '\n');
	std::cout << "\t\tNhap ma lop: ";
	getline(cin, MaLop);
	std::cout << "\t\tNhap ten lop: ";
	getline(cin, TenLop);
	std::cout << "\t\tNhap ma khoa: ";
	getline(cin, MaKhoa);


	string s = "INSERT INTO Lop VALUES('" + MaLop + "','" + TenLop + "','" + MaKhoa + "')";
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

void DBLop::UpdateLop()
{
	string MaLop;
	string TenLop;
	string MaKhoa;

	cin.ignore(100, '\n');
	std::cout << "\t\tMa Lop can cap nhat : ";
	getline(cin, MaLop);
	std::cout << "\t\tNhap ten lop can cap nhat: ";
	getline(cin, TenLop);
	std::cout << "\t\tNhap ma khoa can cap nhat: ";
	getline(cin, MaKhoa);

	string s = "UPDATE Lop SET MaLop = '" + MaLop + "', TenLop = '" + TenLop + "', MaKhoa = '" + MaKhoa + "'WHERE MaLop = '" + MaLop + "'";
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

void DBLop::DeleteLop(string MaLop)
{
	string s = "DELETE FROM Lop WHERE MaLop = '" + MaLop + "' ";
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

void DBLop::DeleteAllLop()
{
	string s = "DELETE FROM Lop";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tTOAN BO Lop DA DUOC XOA ";
		std::cout << "\n";
	}
	else {
		std::cout << "\n\t\tDELETE SUCCESS FACULTY";
		return;
	}
}

void DBLop::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
