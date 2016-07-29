#include<iostream>
#include"cgi.h"
using namespace std;

int main()
{
	cout << CGI::param("id=zezeon@msn.com&pass=coc+kc%67dk0", "pass") << endl;
	string s = "id=zezeon@msn.com&pass=coc+kc%67dk0";
	cout << (char)stoi(s.substr(s.find('%') + 1, 2), nullptr, 16);
}
