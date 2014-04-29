#ifdef TEST_GETINFOR
#include "GetInfor.h"
#include "JsonToStruct.h"

void title(std::string _title)
{
	std::cout << "=============================================" << std::endl;
	std::cout << _title << std::endl;
	std::cout << "=============================================" << std::endl;
}

int main()
{
	std::string testJson = "{[\"Project\":\"CodeRepository\",\"ModuleName\":\"Sender\", \"Author\":\"TestAuthor\"]}";
	JsonStruct input_Json;
	JsonToStruct test;
	input_Json = test.getStruct(testJson);
	title("Input Json Information");
	for (int i = 0; i < input_Json.size(); i++)
	{
		std::cout << input_Json[i].first << " : " << input_Json[i].second << std::endl;
	}

	GetInfor input_infor;
	std::string result_fullpath = input_infor.AddFileInfor(input_Json);
	std::cout << "Full path is " << result_fullpath << std::endl;

}




#endif