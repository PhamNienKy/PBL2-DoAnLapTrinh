#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>

#include "Lop.h"
#include "QuanLyLop.h"

class DBLop
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
	void Display1Lop(string);

	void SelectDB(QuanLyLop&);
	void SelectLop(QuanLyLop&, string);
	void InsertLop();
	void UpdateLop();
	void DeleteLop(string);
	void DeleteAllLop();

	void closeDB();
};
