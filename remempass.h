#include<random>
#include<string>
#include<unordered_map>
#include"mysqldata.h"
using std::string;

class Remember {
public:
	Remember(string pass);
	void add(string site, string id, string pass);
	void show(string site);
	void show();

protected:
	string user;
	string home;
	string password;
	SqlQuery sq;

private:
	std::random_device rd;
	std::uniform_int_distribution<> di;
	string encode(string s);
	string decode(string s);
	char encode_c(char s);
	char decode_c(char s);
	void next(char& n);
	void previous(char& n);
};

