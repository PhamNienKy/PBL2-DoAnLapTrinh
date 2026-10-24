#include "DBKhoa.h"
#include "QuanLyKhoa.h"
#include "Khoa.h"

#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBKhoa::init()
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

void DBKhoa::Display()
{
	// Truy van danh sach khoa
	SQLRETURN ret = SQLExecDirectA(
		sqlStmtHandle,
		(SQLCHAR*)
		"SELECT * FROM Khoa",
		SQL_NTS
	);

	if (!SQL_SUCCEEDED(ret))
	{
		cout << "\n\tERROR QUERYING SQL SERVER\n";
		closeDB();
		return;
	}

	// Khai bao buffer
	SQLCHAR MaKhoa[32] = {};
	SQLCHAR TenKhoa[256] = {};
	SQLLEN len = 0;
	int stt = 1;

	cout << "\n";
	cout << "\t\tDANH SACH KHOA\n\n";

	cout << left
		<< setw(5) << "STT"
		<< setw(15) << "MA KHOA"
		<< setw(25) << "TEN KHOA"
		<< '\n';

	cout << string(145, '-') << '\n';

	// Doc tung dong du lieu
	while ((ret = SQLFetch(sqlStmtHandle)) == SQL_SUCCESS ||
		ret == SQL_SUCCESS_WITH_INFO)
	{
		SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR,
			MaKhoa, sizeof(MaKhoa), &len);

		SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
			TenKhoa, sizeof(TenKhoa), &len);

		cout << left
			<< setw(5) << stt++
			<< setw(15) << (char*)MaKhoa
			<< setw(25) << (char*)TenKhoa
			<< '\n';
	}

	if (ret != SQL_NO_DATA)
	{
		cout << "\n\tLoi khi doc du lieu tu SQL Server.\n";
	}

	SQLCloseCursor(sqlStmtHandle);
}


void DBKhoa::Display1Khoa(string maKhoa)
{
	// Truy van khoa theo ma khoa
	string sql =
		"SELECT MaKhoa, TenKhoa "
		"FROM Khoa "
		"WHERE MaKhoa = '" + maKhoa + "'";

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
	SQLCHAR MaKhoa[32] = {};
	SQLCHAR TenKhoa[256] = {};

	SQLLEN len = 0;

	// Doc du lieu khoa
	ret = SQLFetch(sqlStmtHandle);

	if (ret == SQL_NO_DATA)
	{
		cout << "\n\tKhong tim thay khoa co ma: "
			<< maKhoa << '\n';

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
		MaKhoa, sizeof(MaKhoa), &len);

	SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR,
		TenKhoa, sizeof(TenKhoa), &len);

	// Hien thi thong tin khoa
	cout << "\n";
	cout << "\t\tTHONG TIN KHOA\n\n";

	cout << left
		<< setw(15) << "MA KHOA"
		<< setw(30) << "TEN KHOA"
		<< '\n';

	cout << string(45, '-') << '\n';

	cout << left
		<< setw(15) << (char*)MaKhoa
		<< setw(30) << (char*)TenKhoa
		<< '\n';

	SQLCloseCursor(sqlStmtHandle);
}


void DBKhoa::SelectDB(QuanLyKhoa& db)
{

	//output
	db.Clear();
	std::cout << "\n";
	std::cout << "\t\tEXECUTING T-SQL QUERY...";
	std::cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Khoa", SQL_NTS)) {
		std::cout << "\t\tERROR QUERYING SQL SERVER";
		std::cout << "\n";
		closeDB();
	}
	else {
		//declare output variable and pointer
		SQLINTEGER ptrSqlVersion;
		CHAR MaKhoa[20];
		CHAR TenKhoa[50];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaKhoa, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenKhoa, SQL_RESULT_LEN, &ptrSqlVersion);


			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaKhoa << setw(20) << TenKhoa << setw(15) << endl;
			Khoa k(MaKhoa, TenKhoa);
			db.Add(k);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBKhoa::SelectKhoa(QuanLyKhoa& db, string MaKhoa)
{
	db.Clear();
	string s1 = "SELECT Khoa.MaKhoa, TenKhoa FROM Khoa ";
	string s2 = "INNER JOIN Lop ON Khoa.MaKhoa = Lop.MaKhoa WHERE Lop.MaKhoa = '" + MaKhoa + "'";
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
		CHAR MaKhoa[50];
		CHAR TenKhoa[100];

		int i = 0;
		static int j = 1;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, MaKhoa, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, TenKhoa, SQL_RESULT_LEN, &ptrSqlVersion);

			//display query result
			if (i == 0)
			{
				std::cout << "\n\t\tQUERY RESULT : " << endl;
			}
			std::cout << j++ << ".  " << MaKhoa << setw(20) << TenKhoa << setw(15) << endl;
			Khoa k(MaKhoa, TenKhoa);
			db.Add(k);
			//std::cout << db;
			i++;
		}
		j = 1;
	}
	SQLCancel(sqlStmtHandle);
}

void DBKhoa::InsertKhoa()
{
	string MaKhoa;
	string TenKhoa;

	cin.ignore(100, '\n');
	std::cout << "\t\tNhap ma khoa: ";
	getline(cin, MaKhoa);
	std::cout << "\t\tNhap ten khoa: ";
	getline(cin, TenKhoa);


	//string s = "INSERT INTO Sinh_Vien VALUES('" + sv.MaSinhVien + "','" + sv.Ho_Ten + "','2001','" + sv.Que_Quan + "','" + sv.Dan_Toc
	//	+ "','" + sv.Ma_Lop + "','" + sv.Bao_Hiem + "')";
	string s = "INSERT INTO Khoa VALUES('" + MaKhoa + "','" + TenKhoa + "')";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	//char m[] = "INSERT INTO Sinh_Vien VALUES('102190333','Duc','2001','Hue','Kinh','19TCLC_DT2','BHYT66')";

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

void DBKhoa::UpdateKhoa()
{
	string MaKhoa;
	string TenKhoa;

	cin.ignore(100, '\n');
	std::cout << "\t\tMa khoa can cap nhat : ";
	getline(cin, MaKhoa);
	std::cout << "\t\tNhap ten khoa: ";
	getline(cin, TenKhoa);

	string s = "UPDATE Khoa SET MaKhoa = '" + MaKhoa + "', TenKhoa = '" + TenKhoa + "'WHERE MaKhoa = '" + MaKhoa + "'";
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

void DBKhoa::DeleteKhoa(string MaKhoa)
{
	string s = "DELETE FROM Khoa WHERE MaKhoa = '" + MaKhoa + "' ";
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

void DBKhoa::DeleteAllKhoa()
{
	string s = "DELETE FROM Khoa";
	char m[200];
	snprintf(m, size(m), "%s", s.c_str());
	if (SQL_SUCCESS != SQLExecDirectA(sqlStmtHandle, (SQLCHAR*)m, SQL_NTS)) {
		std::cout << "\n";
		std::cout << "\t\tTOAN BO KHOA DA DUOC XOA ";
		std::cout << "\n";
	}
	else {
		std::cout << "\n\t\tDELETE SUCCESS FACULTY";
		return;
	}
}

void DBKhoa::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
