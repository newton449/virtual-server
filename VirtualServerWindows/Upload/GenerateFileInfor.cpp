#ifdef TEST_GENERATEFILEINFOR

#include "GenerateFileInfor.h"
#include <iostream>
#include <string>

int main()
{
	std::string current_path = "../Data";  // No / for the last
	GenerateFileInfor testobj;
	std::string JsonMsg = testobj.GetAllInfor();
	std::cout << JsonMsg << std::endl;
	std::ofstream out("../temp.txt");
	if (out.good())
	{
		out << JsonMsg;
		out.close();
	}
}






#endif