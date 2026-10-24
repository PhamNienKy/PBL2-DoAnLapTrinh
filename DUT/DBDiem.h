#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>

#include "Diem.h"
#include "QuanLyDiem.h"

class DBDiem
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
	void Display1Diem(string, string);
	void InsertDiem();
	void UpdateDiem();
	void DeleteDiem(string, string);
	void DeleteAllDiem();
	void SortTangDan();
	void SortGiamDan();

	void closeDB();
};

