#pragma once
#include <string>
#include <vector>
#include<unordered_map>
#include "mysqlquery.h"

class SqlData : public Mysqlquery
{
public:
	bool create_table(const SqlData& data);
	bool insert(const SqlData& data);
	SqlData select(std::string table, std::string where = "");
	static std::string now();//system clock->mysql datetime string

protected:
	std::string table_name;
	std::unordered_map<std::string, std::string> structure;
	std::string extra;
	std::string engine;
	std::vector<std::string> record;
	std::vector<record> contents;

};

