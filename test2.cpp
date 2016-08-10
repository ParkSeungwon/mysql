#include<iostream>
#include<random>
using namespace std;

uniform_int_distribution<> di(48,128);
random_device rd;

char encode(char c) {
	if(c >= 'a' && c <= 'z') {
		c += 5;
		if(c > 'z') c = 'a' + c - 'z' - 1;
	}
	return c;
}

char decode(char c) {
	if(c >= 'a' && c <= 'z') {
		c -= 5;
		if(c < 'a') c =  c - 'a' + 'z' + 1;
	}
	return c;
}
string encode(string s) {
	char rt[300]{};
	for(int i=0, j=0; i<s.size(); i++, j++) {
		for(int k=0; k<5; k++) rt[j++] = di(rd);
		rt[j] = encode(s[i]);// + password[i];// + s[i];
	}
	return rt;
}

string decode(string s) {
	char rt[20]{};
	for(int i=0, j=0; i<s.size(); i++, j++) {
		for(int k=0; k<5; k++) i++;
		rt[j] = decode(s[i]);// - password[i];
	}
	return rt;
}

int main(int c, char** v)
{
	cout << encode(v[1]) << endl;
	cout << decode(encode(v[1])) << endl;
}
