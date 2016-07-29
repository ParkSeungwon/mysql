#include"mysqldata.h"
#include"cgi.h"
using namespace std;

int main(int argc, char** argv)
{
	string qs = getenv("QUERY_STRING");
	string tb = CGI::param(qs, "table");
	string book = CGI::param(qs, "book");
	string page = CGI::param(qs, "page");
	SqlQuery d;
	d.connect("localhost", "dndd", "dndddndd", "dndd");

	d.select(tb, "where num=" + book +" and page=" + page + " order by date, email, edit desc");
	d.group_by("date", "email");
	cout << "Content-type:text/html\r\n\r\n";                                     
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<meta charset='utf-8' />\n";
	cout << "<title>Discussion & Democratic Decision making</title>\n"; 
	cout << "<style> table { width:100%; } \
		table, th, td { border: 1px solid black; border-collapse: collapse; } \
		th, td { padding: 5px; text-align: left; } \
		table tr:nth-child(even) { background-color: #eee; } \
		table tr:nth-child(odd) { background-color:#fff; } \
		table th { background-color: black; color: white; } \
		header{background-color:black; color:white;text-align:center;padding:5px;}\
		nav { line-height:30px; background-color:#eeeeee;  \
			width:27%; float:right; padding:1%; } \
		section { width:67%; float:left; padding:2%; }\
		footer { background-color:black; color:white; clear:both;\
			text-align:center; padding:5px;	} </style>";
	cout << "</head>\n";                                                          
	cout << "<body>\n";                                                           
	auto it = d.begin();
	cout << "<header><h2>" << (*it)[3] << "</h2></header>\n";  
	cout << "<section>" << (*it)[4] << "<br><p align='right'>on " << (*it)[5] << " by " << (*it)[2] <<"</p></section>";
	cout << "<nav>";
	for(it++; it!= d.end(); it++) {
		cout << (*it)[4] << "<p align='right'>on " << (*it)[5] << " by " << (*it)[2] << "</p><hr>";
	}
	cout << getenv("HTTP_COOKIE") << "<br>";
	cout << "<form method='post' action='/cgi-bin/mysql.cgi'><textarea name='comment' rows='7' cols=27%></textarea><br><input type='submit'></form>";
	cout << "</nav>";
	cout << "</body>\n";                                                          
	cout << "</html>\n";               
	//cout << "</body></html>";
}
