#pragma once
#include <vector>
#include<functional>
#include "mysqlquery.h"

class SqlData
{
public:
	std::vector<std::string>* begin();
	std::vector<std::string>* end(); 
	bool is_int(int nth_column);

protected:
	std::string table_name;
	std::vector<std::pair<std::string, std::string>> structure;
	std::vector<std::vector<std::string>> contents;
};

class SqlQuery : public Mysqlquery, public SqlData
{
public:
	int select(std::string table, std::string where = "");
	int group_by(std::string col);
	bool insert();
	
	std::string password(std::string pass);
	std::vector<std::string> show_tables();
	std::string now();//system clock->mysql datetime string

	template <typename... Args> bool order_by(Args... args) {
		arguments.clear();
		get_args(args...);
		std::sort(contents.begin(), contents.end(), 
				std::bind(&SqlQuery::order_lambda, this, std::placeholders::_1, 
					std::placeholders::_2, arguments));
	}

private:
	std::vector<int> arguments;
	template<typename... Args> void get_args(int col, Args... args) {
		arguments.push_back(col);
		get_args(args...);
	}
	template<typename... Args> void get_args(std::string col, Args... args) {
		int i = 0;
		while(structure[i].first != col) i++;
		get_args(i, args...);
	}
	void get_args() {}

	bool order_lambda(const std::vector<std::string>& a, 
			const std::vector<std::string>& b, std::vector<int> cols);
};

