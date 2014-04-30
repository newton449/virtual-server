/////////////////////////////////////////////////////////////////////
//  FileMng.h - find files with a directory path or a file path    //
//  ver 3.1                                                        //
//  Language:      Visual C++ 2011                                 //
//  Platform:      Lenovo Thinkpad T430, Windows 7 professional    //
//  Application:   CIS 687 Project 1 Type Dependency Anal          //
//  Author:        Qiuyong Yang				                       //
//				   CS MS 2012Fall, Syracuse University             //
//                 (315) 897-7881, qyang13@syr.edu                 //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module provides a FileMng class for finding files according to the path 
  given by user through command line. 
  This package support command line argument processing and recursive mode for finding 
  files in sub-directories of the current path.

  Public Interface:
  =================
  bool GetFiles(int argc, char* argv[]); // get files according to commmand line arguments
  std::vector<std::string> files(); // return files found by FileMng

  Build Process:
  ==============
  Required files
    - FileMng.h, FileMng.cpp, FileSystem.h, FileSystem.cpp

  Command Format:
  ===============
  MyProject.exe ../filepath/.. *.pattern1 *.pattern2 ... *.pattern_n /R

  -'/R': finding file recursively

  Maintenance History:
  ====================
  ver2.0 : 16 Apr 14
  - add copyDir, copyFile, deleteDir
  ver 1.1 : 23 Feb 14
  - change the GetFiles function for the use for TextSearcher class.
  ver 1.0 : 15 Feb 13
  - first release
*/
//


#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <thread>
#include <mutex>

#include "interface.h"

namespace FileSystem
{
	//----<class FileMngr>----
	class FileMng 
	{
	public:
		FileMng(){};
		~FileMng(){};
		//bool GetFiles(int argc, char* argv[]);
		bool GetFiles(std::string path, std::vector<std::string> pattern, bool Recurse);
		std::vector<std::string> files(){ return _files; }

		static void copyDir(std::string src, std::string dest);
		static void copyFile(std::string src, std::string dest);
		static void deleteDir(std::string path);

	private:
		std::vector<std::string> _files;

		void get(std::string path, std::vector<std::string> pattern, bool Recurse);
		static void addRange(std::string path, std::vector<std::string> &files, std::vector<std::string> adds);		
	};

	
}