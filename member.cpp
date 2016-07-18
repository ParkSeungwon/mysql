#include <iostream>
#include "mysqldata.h"
using namespace std;

int main()
{
	SqlQuery member;
//	member.structure =  {
//		{"email", "char(30) NOT NULL"},
//		{"password", "char(45) DEFAULT NULL"},
//		{"level", "tinyint(4) DEFAULT NULL"},
//		{"name", "varchar(45) DEFAULT NULL"},
//		{"tel", "varchar(20) DEFAULT NULL"},
//		{"date", "datetime NOT NULL"}
//	};
//	member.table_name = "Users";
//	member.extra = "primary key (email, date)";
//	member.engine = "ENGINE=MyISAM DEFAULT CHARSET=utf8";
	
	member.connect("localhost", "dndd", "dndddndd", "dndd");//host, id, pass, database
	//member.create_table(member);
//	member.contents = { "zezeon@msn.com", "cockcodk", "1", "Park Seungwon",
//		"031-255-6698", member.now()};
//	member.insert(member);
	member.select("수능", "where num=1 order by date, edit desc");
	int n = 0;
	int k;
//	cout << "structure size = " << member.structure.size() << endl;
	//for(auto& a : member.structure) {
	//	cout << a.first << ' ' << a.second << endl;
	//}
	for(auto& b : member) for(auto& a : b) {
		n++;
		k = n % 7;
		if(k == 4 || k == 6 || k == 0)  cout << a << ' ';
	}
}

