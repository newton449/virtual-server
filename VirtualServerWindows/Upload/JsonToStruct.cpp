


#ifdef TEST_JSONTOSTRUCT
#include "JsonToStruct.h"
int main()
{
	std::string testJson = "{[\"ProjectName\":\" TestProjectName\",\"ModuleName\":\"TestModuleName\", \"Author\":\"TestAuthor\", \"Bool\":true]}";
	JsonStruct test_result;
	JsonToStruct test;
	test_result = test.getStruct(testJson);
	for (int i = 0; i < test_result.size(); i++)
	{
		std::cout << test_result[i].first << " : " << test_result[i].second << std::endl;
	}

}



#endif