#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "../include/Root.h"

int main()
{
	MySQLBankSafe bank;
	IMySQLBankSafe* bankI = (IMySQLBankSafe*)&bank;

	if (checkConnectToDataBase())
	{
		printf("No connection or no key");
		exit(1);
	}

	bankI->connect("../resource/dbticket.txt");
	

	if (setUpScheme())
	{
		printf("Something went wrong with set up\n");
		exit(1);
	}
	printf("deleted and created database and created table\n");

	bank.selectScheme("content_chooser");
	
	if (prepareInsertInto())
	{
		printf("Something went wrong with preparation\n");
		exit(1);
	}

	if (executePrepared())
	{
		printf("Something went wrong with preparated execution\n");
		exit(1);
	}

	//if (selectFrom())
	//{
	//	printf("Something went wrong with selection\n");
	//	exit(1);
	//}

	return 0;
}
