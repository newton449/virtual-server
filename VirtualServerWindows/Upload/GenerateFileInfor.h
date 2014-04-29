#ifndef GENERATEFILEINFOR_H
#define GENERATEFILEINFOR_H

#include <string>
#include <vector>
#include "FileSystem.h"
#include "XmlReader.h"
#include "XmlWriter.h"
#include "LevelStruct.h"


using namespace FileSystem;

//enum LEVEL
//{
//	PROJECT, MODULE, VERSION, FILES, END
//};

class GenerateFileInfor
{
public:
	GenerateFileInfor(std::string _path = "../Data") :_root_path(_path)
	{
		_FinalResult = "{[";
	}
	std::string GetNextInfor(std::string current_dir, LEVEL level);
	std::string GetAllInfor();

private:
	std::string _FinalResult;
	std::string _root_path;
};

std::string GenerateFileInfor::GetNextInfor(std::string current_dir, LEVEL level)
{
	if (level == END)
		return "";

	std::string return_result="";
	std::string open_brace, close_brace;
	std::string search_tag;
	if (level == PROJECT)
		search_tag = "Project";
	else if (level == MODULE)
		search_tag = "Module";
	else if (level == VERSION)
		search_tag = "Version";
	if (level == FILES)
	{
		open_brace = "[";
		close_brace = "]";
	}
	else
	{
		open_brace = "{";
		close_brace = "}";
	}
	std::vector<std::string> values;
	std::string current_name;
	current_name = Path::getName(current_dir);


	std::string xmlpath = current_dir + "/Information.xml";
	File logxml(xmlpath);
	logxml.open(File::in, File::text);
	std::string inforxml;
	while (logxml.isGood())
		inforxml += logxml.getLine();
	XmlReader rdfile(inforxml);
	while (rdfile.next())
	{
		if (rdfile.tag() == search_tag)
		{
			XmlReader::attribElems elems = rdfile.attributes();
			if (search_tag == "Version")
			{
				std::string tmp = "version_";
				tmp += elems[0].second.c_str();
				values.push_back(tmp);
			}
			else
				values.push_back(elems[0].second.c_str());
		}
	}
	return_result ="\""+ current_name +"\""+ ":" + open_brace;

	if (level == FILES)
	{
		std::string version_dir;
		version_dir = current_dir + "/";
		std::vector<std::string> files = Directory::getFiles(version_dir);
		for (int j = 0; j < files.size(); j++)
		{
			return_result += "\"" + files[j] + "\"";
			if (j < files.size() - 1)
				return_result += ",";
		}
	}

	for (int i = 0; i < values.size(); i++)
	{
		std::string next_path = current_dir +"/" + values[i];
		return_result += GetNextInfor(next_path, (LEVEL) (level + 1));
		if (i<values.size()-1)
			return_result += ",";
	}
	return_result += close_brace;

	return return_result;
}

std::string GenerateFileInfor::GetAllInfor()
{
	std::string return_result = "{";
	return_result += GetNextInfor(_root_path, PROJECT) +"}";

	return return_result;
}



#endif