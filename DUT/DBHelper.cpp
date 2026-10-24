#include "DBHelper.h"
#include "SinhVien.h"
#include "Diem.h"
#include "Lop.h"

#include <iostream>
#include<iomanip>
#include<conio.h>
#include<string.h>

using namespace std;

void DBHelper::init()
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

void DBHelper::closeDB()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	system("pause");
	exit(0);
}
