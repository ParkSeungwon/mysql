#include <chrono>
#include <ctime>
#include "mysqldata.h"
using namespace std;

bool SqlData::create_table(const SqlData& d)
{
	string q = "create table " + d.table_name + " (";
	for(auto& a : d.structure) q += " " + a.first + " " + a.second + ", ";
	q += d.extra + " ) " + d.engine + ";";
	return myQuery(q);
}

bool SqlData::insert(const SqlData& d)
{//d should be 1 record
	string q = "insert into " + d.table_name + " values (";
	int i = 0;
	for(auto& a : d.structure) {
		if(a.second.find("int(") != string::npos) q += record[i] + ",";//int?
		else q += "'" + record[i] + "',";
		i++;
	}
	q.back() = ')';
	q += ";";
	return myQuery(q);
}

SqlData SqlData::select(string table, string where)
{
	string q = "select * from " + table;
	if(where != "") q += " where " + where;
	q += ";";
	myQuery(q);

	SqlData d;
	d.table_name = table;
	sql::ResultSetMetaData* mt = res->getMetaData();
	int c = mt->getColumnCount();
	for(int i = 0; i < c; i++) 
		d.structure[mt->getColumnName(i+1)] = mt->getColumnTypeName(i+1);
	while(res->next()) {
		for(int i = 0; i < c; i++) {
			d.contents.push_back(res->getString(i+1));
		}
	}
	return d;
}

string SqlData::now()
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
}


