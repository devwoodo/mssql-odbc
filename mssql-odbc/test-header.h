#pragma once

#include <iostream>
#include <string>

#include <Windows.h>

// Required header:
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>



/************************************************************************************
 * etc. Function

************************************************************************************/
void HandleDiagnosticRecord(SQLHANDLE      hHandle,
	SQLSMALLINT    hType,
	RETCODE        RetCode);

std::string convCharT(const std::wstring & wstr);
std::wstring convCharT(const std::string & str);



/************************************************************************************
 * DBConnector class
	- 

************************************************************************************/
typedef struct DBConnector
{
public:
	/* member method */
	DBConnector(const std::string dsnName);
	~DBConnector();

	RETCODE connect();
	void close();
	RETCODE excute(const std::string & stmt);
	//void getResultSet();	//rev result set 자료형..?
	RETCODE getResultNum(SQLSMALLINT & number);

	// accessor
	SQLHENV hEnv() const;
	SQLHDBC hDbc() const;
	SQLHSTMT hStmt() const;
public:
	/* member field */
private:
	/* member method */
	DBConnector();

	void _init();
private:
	/* member field */
	SQLHENV _hEnv;
	SQLHDBC _hDbc;
	SQLHSTMT _hStmt;

	std::wstring _dsnName;
	std::wstring _userID;
	std::wstring _pswd;

	bool _connectionFlag;
} DBC;

//rev
// 1.result를 어떤 식으로 얻을지 정해야 함. 필요한 결과는 '검색된 result 수' 정도.
//	그러나 일반성을 획득하기 위해 result record set 을 얻도록 해야할까..?