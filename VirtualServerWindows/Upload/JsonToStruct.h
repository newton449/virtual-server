#ifndef JSONTOSTRUCT_H
#define JSONTOSTRUCT_H

#include <utility>
#include <string>
#include <complex>
#include <tuple>
#include <iostream>
#include <vector>



using JsonPair = std::pair<std::string, std::string>;
using JsonStruct = std::vector<JsonPair>;

class JsonToStruct
{
public:
	JsonToStruct(){}
	JsonStruct getStruct(std::string jsonstring);


private:
	void interpret(std::string jsonstring);
	JsonStruct _ResultStruct;
};

JsonStruct JsonToStruct::getStruct(std::string jsonstring)
{
	interpret(jsonstring);
	return _ResultStruct;
}

void JsonToStruct::interpret(std::string jsonstring)
{
	std::string substring;
	size_t find = 0;
	size_t sub_len = 0;
	size_t str_len = jsonstring.length();
	find = jsonstring.find("{[");
	substring = jsonstring.substr(find+1, str_len-find);
	size_t json_end = jsonstring.find("]}");

	size_t startq = substring.find_first_of("\"");
	std::string temp_substring = substring.substr(startq + 1, str_len - startq);
	size_t endq = temp_substring.find_first_of("\"") + startq + 1;
	size_t colum = 0;
	size_t comma = 0;

	while (true)
	{
		startq = substring.find_first_of("\"");
		std::string temp_substring = substring.substr(startq + 1, str_len - startq);
		endq = temp_substring.find_first_of("\"") + startq+1;

		colum = substring.find(":");
		comma = substring.find(",");
		
		std::string name = substring.substr(startq + 1, endq - startq -1);
		std::string value;
		std::string temp_value;
		if (comma < substring.length())
		{
			 temp_value = substring.substr(colum+1, comma-colum-1);
			 value = temp_value;
		}
		else
		{
			temp_value = substring.substr(colum + 1, substring.length()-colum-3);
			value = temp_value;
		}
		
		if (value.find("\"") < value.length())
			temp_value = value.substr(1, value.find_last_of("\"")-1);
		JsonPair temp;
		temp.first = name;
		temp.second = temp_value;
		_ResultStruct.push_back(temp);
		if (comma < substring.length())
			substring = substring.substr(comma + 1, str_len - comma);
		else
			substring = substring.substr(colum + value.length() + 1, str_len);

		startq = substring.find_first_of("\"");
		temp_substring = substring.substr(startq + 1, substring.length() - startq);
		if (temp_substring == "]}" || temp_substring.length()<=2)
			break;
		endq = temp_substring.find_first_of("\"") + startq + 1;
	}
	

}

#endif