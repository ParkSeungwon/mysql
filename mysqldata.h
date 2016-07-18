#pragma once
#include <vector>
#include<functional>
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
	int select(std::string table, std::string where = "");
	int group_by(std::string col);

	bool insert();
	std::string password(std::string pass);
	std::vector<std::string> show_tables();
	std::string now();//system clock->mysql datetime string

	template <typename... Args>
	bool order_by(Args... args)
	{//buggy
		std::sort(contents.begin(), contents.end(), 
				std::bind(&SqlQuery::order_lambda, this, std::placeholders::_1, 
					std::placeholders::_2, args...));
	}

	template <typename... Args>
	bool order_lambda(const std::vector<std::string>& a, 
			const std::vector<std::string>& b, int col, Args... args)
	{
		if(a[col] == b[col]) {
			if (sizeof...(args) == 0) return true;
			else return order_lambda(a, b, args...);
		} else return a[col] < b[col];
	}

//	bool order_lambda(std::vector<std::string>, std::vector<std::string>) 
//	{
//		return true;
//	}
};

