#pragma once
#include<exception>
#include<string>

class Any
{
public:
	Any(int n);
	Any(float f);
	Any(std::string s);
	Any& operator=(int n);
	Any& operator=(float f);
	Any& operator=(std::string str);
	bool operator==(const Any& rhs);
	bool operator!=(const Any& rhs);
	bool operator<(const Any& rhs);
	operator int();
	operator float();
	operator std::string();

protected:
	std::string str;
	union {
		int n;
		float f;
		char c[4];
	} u;
	enum type {STRING, INT, FLOAT, CHAR} t;

private:
	class AnyException : public std::exception
	{
		public:
			virtual const char* what() const throw() {
				return "Data type mismatch!!";
			}
	};
};

std::ostream& operator<<(std::ostream& o, Any& rhs);
