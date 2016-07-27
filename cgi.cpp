#include"mysqldata.h"
using namespace std;

int main()
{
	SqlQuery d;
	d.connect("localhost", "dndd", "dndddndd", "dndd");
	d.select("수능", "where num=1 order by page");
	d.group_by("page");
	cout << "Content-type:text/html\r\n\r\n";                                     
	cout << "<html>\n";                                                           
	cout << "<head>\n";                                                           
	cout << "<meta charset='utf-8' />\n";
	cout << "<title>Hello World - First CGI Program</title>\n";                   
	cout << "<style> table { width:100%; } \
		table, th, td { border: 1px solid black; border-collapse: collapse; } \
		th, td { padding: 5px; text-align: left; } \
		table tr:nth-child(even) { background-color: #eee; } \
		table tr:nth-child(odd) { background-color:#fff; } \
		table th { background-color: black; color: white; } </style>";
	cout << "</head>\n";                                                          
	cout << "<body>\n";                                                           
	cout << "<h2>Hello World! This is my first CGI program</h2>\n";               
	cout << d.to_html_table(3,1,2,4,6,7);
	cout << "</body>\n";                                                          
	cout << "</html>\n";               
	//cout << "</body></html>";
}
