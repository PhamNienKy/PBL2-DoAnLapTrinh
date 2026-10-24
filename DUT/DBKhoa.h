#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>

#include "Khoa.h"
#include "QuanLyKhoa.h"

class DBKhoa
{
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1024
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	void init();
	void Display();
	void Display1Khoa(string);

	void SelectDB(QuanLyKhoa&);
	void SelectKhoa(QuanLyKhoa&, string);
	void InsertKhoa();
	void UpdateKhoa();
	void DeleteKhoa(string);
	void DeleteAllKhoa();

	void closeDB();
};
