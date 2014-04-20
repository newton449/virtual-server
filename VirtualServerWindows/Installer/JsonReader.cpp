#include "JsonReader.h"
#include <iostream>


bool JsonReader::next()
{
	_pos = _req.find(':', _pos);

	if (_pos > _len)
		return false;

	_pos = _pos - 2;
	while (_req[_pos] != '"')
		_pos--;
	
	_pos++;

	return true;

}

std::string JsonReader::tag()
{
	std::string str = "";

	while (_req[_pos] != '"')
		str += _req[_pos++];

	_pos = _pos + 2;

	return str;
}

std::vector<std::string> JsonReader::value()
{
	std::string str = "";
	std::string tmp = "";
	std::vector<std::string> vec;
	std::stack<char> scope_stk;

	while (_req[_pos] == ' ' || _req[_pos] == '\n')
		++_pos;

	// get the value as one string
	if (_req[_pos] == '[')
	{
		do{
			scopeMatch(_req[_pos], scope_stk);
			str += _req[_pos++];
		} while (scope_stk.size());
		str = str.substr(1, str.size() - 2);

		// split the subvalues
		for (int i = 0; i < str.size(); i++)
		{
			tmp = "";

			while (i < str.size())
			{
				scopeMatch(str[i], scope_stk);
				if (!scope_stk.size() && str[i + 1] == ',' )
				{
					tmp += str[i++];
					break;
				}

				tmp += str[i++];
			}

			if (tmp.size() > 0)
			{
				if (!containSpecialChar(tmp))
					tmp = rmBlank(tmp);

				vec.push_back(tmp);
			}
		}
	}
	else
	{
		while (_pos < _len && _req[_pos] != ',' && _req[_pos] !='\n')
		{
			str += _req[_pos++];
		}
		str = rmBlank(str);
		vec.push_back(str);
	}

	return vec;	
}

bool JsonReader::isSpecialChar(char c)
{
	char set[4] = {'[', ']', '{', '}'};

	for (auto s : set)
	{
		if (s == c)
			return true;
	}

	return false;
}

bool JsonReader::scopeMatch(char c, std::stack<char> &stack)
{
	if (c == '[' || c == '{')
	{
		stack.push(c);
		return false;
	}	

	if (!stack.size())
		return true;

	if ((c == ']' && stack.top() == '[') || (c == '}' && stack.top() == '{'))
	{
		stack.pop();
		return true;
	}

	return false;

}

std::string JsonReader::rmBlank(std::string s)
{
	//int c = s.find('\"', 0);
	std::string str = "";
	int c = 0;

	while (s[c] == ' ' || s[c] == '\n' || s[c] == '"')
		c++;

	if (c == 0 && !containSpecialChar(s))
		return s;

	for (int i = c; i < s.size() && s[i] != '"' && s[i] != ',' && s[i] != '\n' && !isSpecialChar(s[i]); i++)
		str += s[i];

	return str;
}

bool JsonReader::containSpecialChar(std::string s)
{
	for (int i = 0; i < s.size(); i++)
	{
		if (isSpecialChar(s[i]))
			return true;
	}

	return false;
}