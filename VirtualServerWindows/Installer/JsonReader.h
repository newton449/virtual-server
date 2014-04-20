#include <string>
#include <vector>
#include "pf_data.h"
#include <stack>

class JsonReader
{
public:
	JsonReader(std::string req) : _req(req), _pos(0){ _len = req.length(); }
	~JsonReader(){}

	bool next();
	std::string tag();
	std::vector<std::string> value();

private:
	std::string _req;
	size_t _pos;
	size_t _len;

	bool isSpecialChar(char c);
	bool scopeMatch(char c, std::stack<char> &stack);
	bool containSpecialChar(std::string s);
	std::string rmBlank(std::string s);
};