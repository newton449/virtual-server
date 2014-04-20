/////////////////////////////////////////////////////////////////////
//  FileMng.cpp - find files with a directory path or a file path  //
//  ver 1.1                                                        //
//  Language:      Visual C++ 2011                                 //
//  Platform:      Lenovo Thinkpad T430, Windows 7 professional    //
//  Application:   CIS 687 Project 1 Type Dependency Anal          //
//  Author:        Qiuyong Yang				                       //
//				   CS MS 2012Fall, Syracuse University             //
//                 (315) 897-7881, qyang13@syr.edu                 //
/////////////////////////////////////////////////////////////////////

#include "FileMng.h"

using namespace FileSystem;

void FileMng::addRange(std::string path, std::vector<std::string> &files, std::vector<std::string> adds)
{
	std::vector<std::string>::iterator it;
	for(it = adds.begin(); it != adds.end(); it++)
	{
		if (*it != "." && *it != "..")
			files.push_back(path + "\\" + *it);
	}

}

// copy dir recursively
void FileMng::copyDir(std::string src, std::string dest)
{
	std::vector<std::string> subdir = FileSystem::Directory::getDirectories(src);
	std::vector<std::string> files = FileSystem::Directory::getFiles(src);

	if (!FileSystem::Directory::exists(dest))
		FileSystem::Directory::create(dest);

	// copy files
	for (auto f : files)
		copyFile(src + '\\' + f, dest + '\\' + f);

	// copy subdirs
	for (auto d : subdir)
	{
		if (d != "." && d != "..")
			copyDir(src + '\\' + d, dest + '\\' + d);
	}

}

// copy file from one dir to another dir
void FileMng::copyFile(std::string src, std::string dest)
{
	FileSystem::File::copy(src, dest);
}

// delete the dir recursively
void FileMng::deleteDir(std::string path)
{
	std::vector<std::string> files;
	std::vector<std::string> dirs;

	dirs.push_back(path);

	// delete all files in each dir
	for (int i = 0; i < dirs.size(); i++)
	{
		files = FileSystem::Directory::getFiles(dirs[i]);
		for (auto f : files)
			FileSystem::File::remove(dirs[i] + '\\'+ f);
		addRange(dirs[i], dirs, FileSystem::Directory::getDirectories(dirs[i]));
	}

	// delete dirs
	while (dirs.size())
	{
		FileSystem::Directory::remove(dirs.back());
		dirs.pop_back();
	}
}


//--------------------<Test Stub>----------------------------
#ifdef TEST_FILEMNG

#include <iostream>
#include "FileMng.h"

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing FileMng class\n "
            << std::string(30,'=') << std::endl;

  try
  {
    FileSystem::FileMng FileFinder;
	std::vector<std::string> files;

	if(FileFinder.GetFiles(argc, argv))
		files = FileFinder.files();

	std::cout << "Found files:" << std::endl;

	for(auto file : files)
	{
		std::cout << "File :" << file << std::endl;
	}
    
	std::cout << "\n\n";
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what() << "\n\n";
  }
}
#endif