#include"mysqldata.h"
#include<iostream>
using namespace std;


int main()
{
	SqlQuery d;
	d.connect("localhost", "strategy", "strategy", "strategy");
	d.select("Units");
	for(auto& a : d) for(auto& b : a) cout << b << ' ';
	d.order_by(3,2);
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


	{
		SqlQuery d;
		d.connect("localhost", "dndd", "dndddndd", "dndd");
		d.select("VotingBoard", "where page = 0 order by num, date");
		d.group_by("num");
		SqlData data{move(d)};
		for(auto& a : data) {
			for(auto& b : a) cout << b << ' ';
			cout << endl;
		}
		d.select("수능", "where page = 0 order by num, date");
		data = move(d);
		for(auto& a : data) {
			for(auto& b : a) cout << b << ' ';
			cout << endl;
		}

	}

}
