#include<iostream>
#include"mysqldata.h"
#include"cgi.h"
using namespace std;

int main()
{
	string qs = getenv("QUERY_STRING");
	string tb = CGI::param(qs, "table");
	string book = CGI::param(qs, "book");
	SqlQuery sq;
	sq.connect("localhost", "dndd", "dndddndd", "dndd");
	sq.select(tb, "where num=" + book + " order by page, date, edit desc");
	sq.group_by("page");
	cout << CGI::header();
	for(auto it = sq.begin(); it != sq.end(); it++) {
		cout << "<a href='/cgi-bin/page.cgi?table=" + tb;
		cout << "&book=" << (*it)[0];
		cout << "&page=" << (*it)[1] << "'>";
		cout << (*it)[1] << ". " << (*it)[3] << "</a><br>\n";
	}
	cout << "</body></html>";
}
