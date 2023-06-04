#pragma once
#include "MySQLBank.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT int __stdcall checkConnectToDataBase()
{
	MySQLBankSafe bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	return 0;
}

DLL_EXPORT int __stdcall setUpScheme()
{
	MySQLBankSafe bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	const std::string scheme = "content_chooser";

	const std::vector<std::string> commands = {
		"DROP DATABASE IF EXISTS " + scheme + ";",
		"CREATE DATABASE " + scheme + ";",
		"CREATE TABLE content_name(id SERIAL PRIMARY KEY, title varchar(128), target varchar(24) NOT NULL DEFAULT \"self\", duration_m smallint unsigned NOT NULL DEFAULT 0, type varchar(4), status varchar(4));",
		"CREATE TABLE longterm(id_content INT UNIQUE, count smallint NOT NULL DEFAULT 0);",
		"CREATE TABLE progress_longterm (id_content INT UNIQUE, date_started date ,date_finished DATE NOT NULL);",
		"CREATE TABLE progress(id_content INT UNIQUE, date_watched date NOT NULL);"
	};

	if (bank.immediatelyExecute(commands[0]))
		return 1;
	else if (bank.immediatelyExecute(commands[1]))
		return 1;

	if (!bank.selectScheme(scheme))
		return 1;

	for (size_t ind = 2; ind < commands.size(); ind++)
	{
		if (bank.immediatelyExecute(commands[ind]))
			return 1;
	}

	return 0;
}

DLL_EXPORT int __stdcall selectFrom()
{
	MySQLBankSafe bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	std::ifstream fin("transit.sql");
	std::ofstream fout("transit.res");
	std::string line;

	if (!fin.is_open())
		return 1;

	std::getline(fin, line);
	bank.selectScheme(line);
	std::getline(fin, line);
	fin.close();

	if (!bank.executeQuery(line))
		return 1;

	const size_t scol = bank.getResultColomns();
	auto col = bank.getResultInstance();

	fout << scol << '\n';

	while (col->next())
	{
		for (size_t i = 1; i <= scol; i++)
		{
			fout << ((col->isNull(i)) ? "~null~" : col->getString(i));
			if (i != scol)
				fout << '\t';
		}

		if (!col->isLast())
			fout << '\n';
	}

	fout.close();
	
	return 0;
}

DLL_EXPORT int __stdcall prepareInsertInto()
{
	MySQLBankSafe bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	std::ifstream fin("transit.sql");
	std::string line;

	if (!fin.is_open())
		return 1;

	std::getline(fin, line);
	bank.selectScheme(line);
	std::getline(fin, line);

	fin.close();
	bank.prepareExecution(line);

	return 0;
}

#include <sstream>

DLL_EXPORT int __stdcall executePrepared()
{
	MySQLBankSafe bank;
	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	std::ifstream fin("transit.inp");
	
	{
		std::string scheme;

		if (!fin.is_open())
			return 1;

		std::getline(fin, scheme);
		bank.selectScheme(scheme);
		printf("selected\n");
	}

	std::string line;
	std::stringstream ssline; // for separating by std::getline
	std::string type;
	std::string value;
	size_t index;
	bool is_title = true;
	std::vector<std::string> datatype;

	while (!fin.eof())
	{
		std::getline(fin, line, '\n');
		ssline.str(line);

		index = 1;

		if (is_title)
		{
			while (!ssline.eof())
			{
				std::getline(ssline, type, '\t');
				std::getline(ssline, value, '\t');

				printf("%s -> %s\n", type.c_str(), value.c_str());

				if (type == "INT" || type == "SMALLINT UNSIGNED")
					bank.getPreparedStatementInstance()->setInt(index, std::stoi(value));
				else if (type == "DATETIME")
					bank.getPreparedStatementInstance()->setDateTime(index, value);
				else if (type == "STRING")
					bank.getPreparedStatementInstance()->setString(index, value);
				else if (type == "BIGINT UNSIGNED")
					bank.getPreparedStatementInstance()->setUInt64(index, std::stoull(value));

				index++;

				printf("next\n");
			}

			if (!bank.executePrepared())
				return 1;
		}
	}

	fin.close();

	return 0;
}

DLL_EXPORT int __stdcall factorial(int a)
{
	if (a != 1)
		return a * factorial(a - 1);
	else
		return 1;
}
