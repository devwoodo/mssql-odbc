#include "test-header.h"	

int main()
{
	DBConnector dbc("sqlODBC");
	
	dbc.connect();
	dbc.excute("select * from tb1");
	dbc.close();

	std::cout << "Program ends." << std::endl;

	return 0;
}
