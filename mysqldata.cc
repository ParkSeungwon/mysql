#include <chrono>
#include<initializer_list>
#include<unordered_map>
#include <ctime>
#include "mysqldata.h"
using namespace std;

bool SqlData::insert()
{//d should be 1 record
	auto& record = contents[0];
	string q = "insert into " + table_name + " values (";
	for(int i=0; i<structure.size(); i++) {
		if(structure[i].second.find("INT") != string::npos) q += record[i] + ",";
		else q += "'" + record[i] + "',";
	}
	q.back() = ')';
	q += ";";
	return myQuery(q);
}


string SqlData::now()
{
	myQuery("select now();");
	res->next();
	return res->getString(1);
}

int SqlData::select(string table, string where)
{
	string q = "select * from " + table + ' ' + where + ';';
	myQuery(q);

	table_name = table;
	sql::ResultSetMetaData* mt = res->getMetaData();
	int c = mt->getColumnCount();
	for(int i = 0; i < c; i++) //populate structure
		structure.push_back({mt->getColumnName(i+1), mt->getColumnTypeName(i+1)});
	vector<string> record;
	contents.clear();
	while(res->next()) { //populate contents
		record.clear();
		for(int i = 0; i < c; i++) record.push_back(res->getString(i+1));
		contents.push_back(record);
	}
	return contents.size();
}

int SqlData::group_by(string cl)
{
	int idx;
	int sz = contents.size();
	for(idx=0; idx<structure.size(); idx++) if(cl == structure[idx].first) break;
	string before;
	for(int j=0; j<sz; j++) {
		if(contents[j][idx] == before) contents[j][idx] = "this_will@be&deleted";
		else before = contents[j][idx];
	}
	auto it = remove_if(contents.begin(), contents.end(), 
			[idx](const vector<string>& a) {
			return a[idx] == "this_will@be&deleted";});
	contents.erase(it, contents.end());
	return contents.size();
}

template <typename... Args>
void SqlData::order_by(int col, Args... args)
{
	sort(contents.begin(), contents.end(), 
			[=](vector<string>& a, vector<string> b) {
				if(a[col] == b[col]) return order_by(args...); 
				else return a[col] < b[col];
			});
}
/*string SqlData::now()
{
	auto now = chrono::system_clock::now();
	auto tp = chrono::system_clock::to_time_t(now);
	string t = ctime(&tp);
	unordered_map<string, string> months {
		{"Jan", "01"}, {"Feb", "02"}, {"Mar", "03"}, {"Apr", "04"}, 
		{"May", "05"}, {"Jun", "06"}, {"Jul", "07"}, {"Aug", "08"}, 
		{"Sep", "09"}, {"Oct", "10"}, {"Nov", "11"}, {"Dec", "12"}
	};

	string s = t.substr(20, 4) + "-" + months[t.substr(4, 3)] + "-";
	if(t[8] == ' ') s += '0';
	else s += t[8];
	s += t.substr(9, 10);
	return s;
}*/

vector<string> SqlData::show_tables()
{
	vector<string> record;
	myQuery("show tables;");
	while(res->next()) record.push_back(res->getString(1));
	return record;
}


