#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include<stdlib.h>

#include "SinhVien.h"
#include "QuanLySinhVien.h"
#include "Diem.h"
class DBSinhVien
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
	void Display1SinhVien(string);
	void InsertSinhVien();
	void SelectSinhVien(QuanLySinhVien&);
	void UpdateSinhVien();
	void DeleteSinhVien(string);

	void closeDB();
};
