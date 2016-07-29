#include<string>

class CGI
{
public:
	static std::string header() {return header_;}
	static std::string param(const std::string& post_string, 
			const std::string& parameter);

private:
	static std::string header_;
};
