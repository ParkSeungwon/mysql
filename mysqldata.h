#pragma once
#include <vector>
using namespace std;
#include "mysqlquery.h"

class SqlData : public Mysqlquery
{
public:
	bool insert();
	int select(std::string table, std::string where = "");
	std::vector<std::string> show_tables();
	std::string now();//system clock->mysql datetime string
	std::vector<std::string>& operator[](int i) {return contents[i];}
	int group_by(std::string col);
	template <typename... Args> void order_by(int column, Args... args);
	bool order_by() {return true;}

	std::vector<std::string>* begin() {return &contents[0];}
	std::vector<std::string>* end() {return &contents[contents.size()];}

	std::string table_name;
	std::vector<std::pair<std::string, std::string>> structure;
	std::vector<std::vector<std::string>> contents;
};

