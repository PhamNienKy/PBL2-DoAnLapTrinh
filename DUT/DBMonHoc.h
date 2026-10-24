#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>

#include "MonHoc.h"
#include "QuanLyMonHoc.h"

class DBMonHoc
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
	void Display1MonHoc(string);

	void SelectDB(QuanLyMonHoc&);
	void SelectMonHoc(QuanLyMonHoc&, string);
	void InsertMonHoc();
	void UpdateMonHoc();
	void DeleteMonHoc(string);
	void DeleteAllMonHoc();

	void closeDB();
};
