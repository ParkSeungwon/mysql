#include"mysqldata.h"
#include<iostream>
using namespace std;


int main()
{
	SqlData d;
	d.connect("localhost", "strategy", "strategy", "strategy");
	d.select("Units");
	for(auto& a : d) for(auto& b : a) cout << b << ' ';
}
