#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "../include/Root.h"

int main()
{
	MySQLBankSafe bank;
	IMySQLBankSafe* bankI = (IMySQLBankSafe*)&bank;

	int res;

	if (res = checkConnectToDataBase())
	{
		(void)printf("No connection or no key: %d\n", res);
		exit(1);
	}

	(void)bankI->connect("../resource/dbticket.txt");
	

	if (res = setUpScheme())
	{
		(void)printf("Something went wrong with set up: %d\n", res);
		exit(1);
	}
	(void)printf("deleted and created database and created table\n");

	(void)bank.selectScheme("content_chooser");


	if (res = executePrepared())
	{
		(void)printf("Something went wrong with preparated execution: %d\n", res);
		exit(1);
	}

	(void)printf("Done!\n");

	//if (selectFrom())
	//{
	//	printf("Something went wrong with selection\n");
	//	exit(1);
	//}

	return 0;
}
