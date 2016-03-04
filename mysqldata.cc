#include "mysqldata.h"
using namespace std;

bool QueryData::create_table(SqlData& d)
{
	string q = "create table '" + d.table_name + "(";
	for(auto& a : d.structure) q += "'" + a.first + "' " + a.second + ",";
	q += d.extra + ")" + d.engine + ";";
	return myQuery(q);
}

bool QueryData::insert(SqlData& d)
{
	string q = "insert into '" + d.table_name + "' values ('";
	for(int i = 0; i < d.structure.size(); i++) {
		if(d.structure[i].second.find("int(") != string::npos)//can find
			q += d.contents[i] + ",";
		else if(d.structure[i].second.find("char(") != string::npos)//can find
			q += "'" + d.contents[i] + "', ";
		else if(d.structure[i].second.find("date") != string::npos)
			q += "now(),";
	}
	q.back() = ')';
	q += ";";
	return myQuery(q);
}

vector<SqlData> QueryData::select(string table, string where)
{
	string q = "select * from " + table;
	if(where != "") q += " where " + where;
	q += ";";
	myQuery(q);

	SqlData d;
	vector<SqlData> v;
	sql::ResultSetMetaData* res_meta = res->getMetaData();
	int c = res_meta->getColumnCount();
	d.contents.resize(c);
	for(int i = 0; i < c; i++) {
		d.structure[i].first = res_meta->getColumnName(i+1);
		d.structure[i].second = res_meta->getColumnType(i+1);
	}
	while(res->next()) {
		for(int i = 0; i < c; i++) {
			if(d.structure[i].second.find("int") == string::npos)
				d.contents[i] = res->getString(i+1);
			else d.contents[i] = res->getInt(i+1);
		}
		v.push_back(d);
	}
	return v;
}

