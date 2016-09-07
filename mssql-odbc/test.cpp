#define _AFXDLL

#include <iostream>
#include <cstring>

//#include <Windows.h>
#include <afxdb.h>
#include <winsock2.h>

// Required header:
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>

void HandleDiagnosticRecord(SQLHANDLE      hHandle,
	SQLSMALLINT    hType,
	RETCODE        RetCode);

int main()
{
	CDatabase db;
	//if (db.OpenEx(CString("sqlODBC")) == 0)
	if (db.OpenEx(_T("sqlODBC")) == 0)
	{
		std::cout << "Database open error." << std::endl;
		exit(1);
	}

	CRecordset rSet(&db);

	db.ExecuteSQL(_T("select * from tb1"));

	if(rSet.Open()==0)
	{
		std::cout << "Recordset open error." << std::endl;
		exit(1);
	}


	db.Close();

	return 0;

	/////////////////////////////////////////////////////////////////////////////////////
	//SQLHENV hEnv;
	//SQLHDBC hDbc;
	//SQLHSTMT hStmt;

	//SQLWCHAR * dsnName = L"sqlODBC";
	//SQLCHAR * userID = (SQLCHAR *)"";
	//SQLCHAR * pswd = (SQLCHAR *)"";
	//SQLWCHAR * stmt = L"select * from tb1";

	//if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS) {
	//	std::cout << "Alloc handle error: SQL_HANDLE_ENV" << std::endl;
	//	exit(1);
	//}
	//if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS) {
	//	std::cout << "Set Attribute error: SQL_HANDLE_ENV" << std::endl;
	//	exit(1);
	//}

	//if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS) {
	//	std::cout << "Alloc handle error: SQL_HANDLE_DBC" << std::endl;
	//	exit(1);
	//}
	//SQLSetConnectAttr(hDbc, 5, (SQLPOINTER)SQL_LOGIN_TIMEOUT, 0);
	//if (RETCODE errmsg = SQLConnect(hDbc, dsnName, SQL_NTS, (SQLWCHAR*)userID, SQL_NTS, (SQLWCHAR*)pswd, SQL_NTS) == SQL_ERROR)			// ok
	////if (RETCODE errmsg = SQLDriverConnect(hDbc, GetDesktopWindow(), L"", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_COMPLETE) == SQL_ERROR)	// ok
	//// connection이 성공 시 SQL_SUCCESS, 혹은 SQL_SUCCESS_WITH_INFO 반환. 
	//{
	//	std::cout << "DB connection error." << std::endl;
	//	switch (errmsg) {
	//	case SQL_ERROR:
	//		std::cout << "SQL_ERROR" << std::endl;
	//		break;
	//	case SQL_SUCCESS_WITH_INFO:
	//		std::cout << "SQL_SUCCESS_WITH_INFO" << std::endl;
	//		break;
	//	case SQL_INVALID_HANDLE:
	//		std::cout << "SQL_INVALID_HANDLE" << std::endl;
	//		break;
	//	default:
	//		std::cout << "etc error" << std::endl;
	//		break;
	//	}
	//	HandleDiagnosticRecord(hDbc, SQL_HANDLE_DBC, errmsg);
	//	exit(1);
	//}

	//SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
	////RETCODE RetCode = SQLExecDirect(hStmt, (SQLWCHAR*)stmt, SQL_NTS);		// error 42000: systax error  (stmt should be given in wchar(L"~") type.)
	////RETCODE RetCode = SQLExecDirect(hStmt, stmt, SQL_NTS);	// ok	(stmt type changed to wchar(L"~") type.)
	//RETCODE RetCode = SQLExecDirect(hStmt, L"SELECT * FROM tb1", SQL_NTS);	// ok
	//// 성공 시 SQL_SUCCESS 반환

	//switch (RetCode)
	//{
	//case SQL_SUCCESS_WITH_INFO:
	//{
	//	std::cout << "SQL_SUCCESS_WITH_INFO" << std::endl;
	//	HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
	//	// fall through
	//}
	//case SQL_SUCCESS:
	//{
	//	std::cout << "SQLExecDirect(..) success!" << std::endl;

	//	SQLSMALLINT num;
	//	std::cout << "SQLNumResultCols: " << SQLNumResultCols(hStmt, &num) << std::endl;
	//	std::cout << "num: " << num << std::endl;
	//	break;
	//}

	//case SQL_ERROR:
	//{
	//	std::cout << "SQL_ERROR" << std::endl;
	//	HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
	//	break;
	//}

	//default:
	//	fwprintf(stderr, L"Unexpected return code %hd!\n", RetCode);

	//}

	//SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	//SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	//SQLFreeHandle(SQL_HANDLE_ENV, hEnv);  //End the connection

	//std::cout << "Program ends." << std::endl;

	//return 0;
}

void HandleDiagnosticRecord(SQLHANDLE      hHandle,
	SQLSMALLINT    hType,
	RETCODE        RetCode)
{
	SQLSMALLINT iRec = 0;
	SQLINTEGER  iError;
	WCHAR       wszMessage[1000];
	WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];

	if (RetCode == SQL_INVALID_HANDLE)
	{
		fwprintf(stderr, L"Invalid handle!\n");
		return;
	}

	while (SQLGetDiagRec(hType,
		hHandle,
		++iRec,
		wszState,
		&iError,
		wszMessage,
		(SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
		(SQLSMALLINT *)NULL) == SQL_SUCCESS)
	{
		// Hide data truncated..
		if (wcsncmp(wszState, L"01004", 5))
		{
			fwprintf(stderr, L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
		}
	}
}