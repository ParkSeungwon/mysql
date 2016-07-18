#pragma once
#include <vector>
#include "mysqlquery.h"

class SqlData
{
public:
	std::vector<std::string>* begin() {return &contents[0];}
	std::vector<std::string>* end() {return &contents[contents.size()];}
	bool is_int(int nth_column);

protected:
	std::string table_name;
	std::vector<std::pair<std::string, std::string>> structure;
	std::vector<std::vector<std::string>> contents;
};

class SqlQuery : public Mysqlquery, public SqlData
{
public:
	bool insert();
	int select(std::string table, std::string where = "");
	std::vector<std::string> show_tables();
	std::string now();//system clock->mysql datetime string
	int group_by(std::string col);

	template <typename... Args>
	bool order_by(int col, Args... args)
	{//buggy
		std::sort(contents.begin(), contents.end(), 
				[=](std::vector<std::string>& a, std::vector<std::string> b) {
				if(a[col] == b[col]) return order_by(args...); 
				else return a[col] < b[col];
				});
	}
	bool order_by() {return true;}
};

