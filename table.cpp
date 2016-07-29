#include<iostream>
#include"mysqldata.h"
#include"cgi.h"
using namespace std;

int main()
{
	string tb = CGI::param(getenv("QUERY_STRING"), "table");
	SqlQuery sq;
	sq.connect("localhost", "dndd", "dndddndd", "dndd");
	sq.select(tb, "where page=0 order by num, date, email, edit desc");
	sq.group_by("num");
	cout << CGI::header();
	for(auto it = sq.begin(); it != sq.end(); it++) {
		cout << "<a href='/cgi-bin/book.cgi?table=" + tb;
		cout << "&book=" << (*it)[0] << "'>";
		cout << (*it)[0] << ". " << (*it)[3] << "</a><br>\n";
	}
	cout << "</body></html>";
}
