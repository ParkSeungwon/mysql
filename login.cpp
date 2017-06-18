#include<iostream>
#include<string>
#include"mysqldata.h"
#include"cgi.h"
using namespace std;

int main()
{
	string s;
	cin >> s;
	auto param = CGI::parse_post(s);
	string id = param["id"];
	string pass = param["password"];
	SqlQuery sq;
	sq.connect("localhost", "dndd", "dndddndd", "dndd");
	sq.select("Users", "where email='" + id + "' order by date desc limit 1");
	auto it = sq.begin();
	bool login =false;//id=zezeon%40msn.com&password=cockcodk0
	if((*it)[1] == sq.password(pass)) {
		cout << "Set-Cookie:UserID=" + id + ";\r\n";
		cout << "Set-Cookie:Level=" << (*it)[2] << ";\r\n";
		login=true;
	}                   
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
	if(login) {
		for(auto& a : sq.show_tables()) {
			if(a != "Users" && a != "Vote" && a != "Follow") 
				cout << "<a href='/cgi-bin/table.cgi?table=" + a +"'>" + a + "</a><br>\n";
		} 
	} else cout << "Login failed";
	cout << "</body></html>";
}
