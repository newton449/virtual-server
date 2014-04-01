/////////////////////////////////////////////////////////////////////
//  StringUtils.cpp - provides opreations for handling strings.    //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr2, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////


#ifdef TEST_STRINGUTILS

#include <iostream>
#include "StringUtils.h"

typedef std::string String; 

// Test fixFilePath() for the str.
void testFixName(String str)
{
	std::cout<<str<<std::endl;
	std::cout<<"    BECOME: "<<StringUtils::fixFilePath(str)<<std::endl;;
}

void main()
{
	std::cout<<"Testing ActionsAndRulesSupport.cpp"<<std::endl;
	// Test StringUtils::split()
	String beforeSplit="aa::bbb::cccc";
	std::vector<String> tokens=StringUtils::split(beforeSplit, "::", true);
	for(auto& token : tokens)
	{
		std::cout<<token<<", ";
	}
	std::cout<<std::endl;
	// Test StringUtils::toLowerCase()
	std::cout<<StringUtils::toLowerCase("AbcDEFghIJklmNOpqrSTUvwxYz__")<<std::endl;
	std::cout<<StringUtils::toLowerCase("ABCDEFGHIJKLMNOPQRSTUVWXYZ__")<<std::endl;
	// Test StringUtils::removeFileNameExtension()
	std::cout<<StringUtils::removeFileNameExtension("aaa.txt")<<std::endl;
	std::cout<<StringUtils::removeFileNameExtension("aaa")<<std::endl;
	// Test fixFilePath()
	std::cout<<"/**** Should be the same or add a '\\' ****/"<<std::endl;
	testFixName("");
	testFixName("\\");
	testFixName(".");
	testFixName("..");
	testFixName("...");
	testFixName("..\\..");
	testFixName("..\\..\\");
	testFixName("\\..");
	testFixName("\\..\\..");
	testFixName("\\..\\..\\");
	std::cout<<"/**** Should delete something ****/"<<std::endl;
	testFixName("\\.");
	testFixName("\\..");
	testFixName("\\.\\..\\");
	testFixName("\\.\\.\\");
	testFixName(".\\..\\.");
	testFixName(".\\..\\.\\");
	testFixName(".\\..\\.\\..");
	testFixName("C:\\.");
	testFixName("C:\\.\\");
	testFixName("C:\\.\\.\\");
	testFixName("C:\\..\\.\\..");
	testFixName("C:\\.\\..\\");
	testFixName(".\\");
	testFixName(".\\.");
	testFixName(".\\.\\");
	testFixName("C:\\...\\aa\\bb\\cc");
	testFixName("C:\\/\\//\\..///..\\.\\.\\...\\.\\aa\\bb\\..\\bb//cc../../../../aa/bb/cc");
	testFixName(".\\..\\aa\\");
	testFixName(".\\..\\aa\\..\\aa\\aa\\..");
}

#endif