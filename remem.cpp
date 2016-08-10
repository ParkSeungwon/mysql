#include<iostream>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include"remempass.h"
using namespace std;

Remember::Remember(string pass) : di(97, 122) {
	user = getenv("USER");
	home = getenv("HOME");
	ifstream f(home + "/.pass");
	array<string, 3> s;
	if(!f.is_open()) {
		ofstream f(home + "/.pass");
		f << encode(pass) << endl;
	} else {
		f >> s[0];
		if(decode(s[0]) == pass) {
			password = pass;
			while(f >> s[0] >> s[1] >> s[2]) {
				for(auto& a : s) a = decode(a);
				sq.push_back(s);
			}
		}
	}
}

void Remember::show(string site) {
	for(auto& a : sq) if(a[0] == site) cout << a[1] << ' ' << a[2] << endl;
}

void Remember::show() {
	for(auto& a : sq) cout << a[0] << ' ';
	cout << endl;
}


void Remember::add(string site, string id, string pass) {
	ofstream f(home + "/.pass", ofstream::app);
	f << encode(site) << ' ' << encode(id) << ' ' << encode(pass) << endl;
}

string Remember::encode(string s) {
	char rt[300]{};
	for(int i=0, j=0; i<s.size(); i++, j++) {
		for(int k=0; k<5; k++) rt[j++] = di(rd);
		rt[j] = encode_c(s[i]);// + password[i];// + s[i];
	}
	return rt;
}

string Remember::decode(string s) {
	char rt[20]{};
	for(int i=0, j=0; i<s.size(); i++, j++) {
		for(int k=0; k<5; k++) i++;
		rt[j] = decode_c(s[i]);// - password[i];
	}
	return rt;
}

char Remember::encode_c(char c) {
	if(c >= 'a' && c <= 'z') {
		c += 5;
		if(c > 'z') c = 'a' + c - 'z' - 1;
	}
	return c;
}

char Remember::decode_c(char c) {
	if(c >= 'a' && c <= 'z') {
		c -= 5;
		if(c < 'a') c =  c - 'a' + 'z' + 1;
	}
	return c;
}

string get_pass() {
	string s;
	cout << "Enter Password : ";
	system("stty -echo");
	cin >> s;
	cout << endl;
	system("stty echo");
	return s;
}

int main(int c, char** v) {
	Remember u{get_pass()};
	if(c > 4 && strcmp(v[1], "add") == 0) u.add(v[2], v[3], v[4]);
	else if(c == 2) u.show(v[1]);
	else u.show();
}
