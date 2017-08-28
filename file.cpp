#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	char c;
	ofstream f("/tmp/a.txt");
	while(cin >> noskipws >> c) f << c;
	cout << "Content-type:text/html\r\n\r\n";                                     
	cout << "<html>\n";
	cout << "<head>\n";
	cout << "<meta charset='utf-8' />\n";
	cout << "<title>Discussion & Democratic Decision making</title>\n"; 
	cout << "<body>upload done</body></html>" ;
}
