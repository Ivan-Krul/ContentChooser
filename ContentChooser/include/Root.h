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

int prepareInsertInto(MySQLBankSafe& bank)
{
	std::ifstream finsql("transit.sql");
	std::string line;

	if (!finsql.is_open())
		return 1;

	std::getline(finsql, line);
	bank.selectScheme(line);
	std::getline(finsql, line);

	finsql.close();
	bank.prepareExecution(line);
}

#include <sstream>

DLL_EXPORT int __stdcall executePrepared()
{
	MySQLBankSafe bank;

	if (bank.connect("../resource/dbticket.txt") != 0)
		return 1;

	if (!prepareInsertInto(bank))
		return 2;

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
	size_t index;
	size_t index_1;
	bool is_title = true;
	std::vector<std::string> datatype;

	while (!fin.eof())
	{
		(void)printf("looped\n");
		std::getline(fin, line, '\n');
		(void)printf("%s\n", line.c_str());
		ssline.clear();
		ssline.str(line);

		index = 1;

		if (!is_title)
		{
			while (!ssline.eof())
			{

				index_1 = index - 1;

				std::getline(ssline, line, '\t');

				(void)printf("got: %s\nthink as: %s\n", line.c_str(), datatype[index_1].c_str());

				if (datatype[index_1] == "INT" || datatype[index_1] == "SMALLINT UNSIGNED")
					bank.getPreparedStatementInstance()->setInt(index, std::stoi(line));
				else if (datatype[index_1] == "DATETIME")
					bank.getPreparedStatementInstance()->setDateTime(index, line);
				else if (datatype[index_1] == "STRING")
					bank.getPreparedStatementInstance()->setString(index, line);
				else if (datatype[index_1] == "BIGINT UNSIGNED")
				{
					bank.getPreparedStatementInstance()->setUInt64(index, std::stoull(line));

				}

				index++;
			}

			if (bank.executePrepared() == false)
				return 3;
		}
		else
		{
			while (!ssline.eof())
			{
				std::getline(ssline, line, '\t');
				(void)printf("writed title: %s\n", line.c_str());
				datatype.push_back(line);
			}

			is_title = false;
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
