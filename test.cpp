#include"mysqldata.h"
#include<iostream>
#include"cgi.h"
using namespace std;


int main()
{
	SqlQuery d;
	d.connect("localhost", "strategy", "strategy", "strategy");
	d.select("Units");
	for(auto& a : d) for(auto& b : a) cout << b << ' ';
	d.order_by(3);
	d.select("Units");
	SqlData sd{move(d)};
//	sd = move(d);
	for(auto& a : sd) for(auto& b : a) cout << b << ' ';
	cout << " d " << endl;
	for(auto& a : d) for(auto& b : a) cout << b << ' ';
	d.select("Units");
	for(auto& a : d) for(auto& b : a) cout << b << ' ';
	for(auto it = sd.begin(); it != sd.end(); it++) {
		for(auto& a : *it) cout << a << ' ';
	}


	{//usage example
		SqlQuery d;
		d.connect("localhost", "dndd", "dndddndd", "dndd");
		d.select("VotingBoard", "where page = 0 order by num, date");
		d.group_by("num", "page");
		SqlData data{move(d)};
		for(auto& a : data) {
			for(auto& b : a) cout << b << ' ';
			cout << endl;
		}
		d.select("수능"); 
		d.order_by("title");//, "email", "date", -7);
		d.group_by("title");
		//d.group_by("num");
		for(auto& a : d) {
			cout << a[0] << ' ' << a[1] << ' ' << a[3] << ' ' << a[5];
			cout << endl;
		}
		d.select("Users", "where email = 'zezeon@msn.com' order by date desc limit 1");
		

	}
	{
		auto m = CGI::parse_post("id=zezeon%40msn.com&password=cockcodk0");
		for(auto& a : m) cout << a.first << ' ' << a.second << endl;
	}


}
