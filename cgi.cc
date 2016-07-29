#include"cgi.h"
using namespace std;

string CGI::header_ = "Content-type:text/html\r\n\r\n"
	"<html>\n<head>\n"
	"<meta charset='utf-8' />\n"
	"<title>Discussion & Democratic Decision making</title>"
	"</head>\n<body>";

string CGI::param(const string& post, const string& par) 
{
	int pos = post.find(par);
	pos = pos + par.length() + 1;
	int end = post.find('&', pos);
	
	string s = post.substr(pos, end - pos);
	for(pos = s.find('+', 0); pos != string::npos; pos = s.find('+', pos))
		s.replace(pos, 1, 1, ' ');
	for(pos = s.find('%', 0); pos != string::npos; pos = s.find('%', pos))
		s.replace(pos, 3, 1, (char)stoi(s.substr(pos + 1, 2), nullptr, 16));
	return s;
}
