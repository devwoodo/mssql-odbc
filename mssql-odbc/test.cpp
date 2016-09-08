#include "test-header.h"	

int main()
{
	DBConnector dbc("sqlODBC");
	
	dbc.connect();
	dbc.excute("select * from tb1");
	
	SQLSMALLINT resultNum;
	dbc.getResultNum(resultNum);

	std::cout << "Result number: " << resultNum << std::endl;

	dbc.close();
	std::cout << "Program ends." << std::endl;

	return 0;
}