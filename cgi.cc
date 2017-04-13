#include"cgi.h"
using namespace std;

string CGI::header_ = R"literal(
Content-type:text/html
<html><head>
<meta charset='utf-8' />
<title>Discussion & Democratic Decision making</title>
</head><body>
)literal";

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
