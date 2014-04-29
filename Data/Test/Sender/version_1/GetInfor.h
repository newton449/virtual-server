#ifndef GETINFOR_H
#define GETINFOR_H

#include "XmlReader.h"
#include "XmlWriter.h"
#include "JsonToStruct.h"
#include "FileSystem.h"
#include "LevelStruct.h"
#include "../interfaces/ILogger.h"
#include <vector>
#include <string>
#include <fstream>


//enum LEVEL
//{
//	PROJECT, MODULE, VERSION
//};

using namespace FileSystem;

class GetInfor
{
public:
	GetInfor(){}
	std::string AddFileInfor(JsonStruct UploadInfor);
private:
	bool isHad(std::string DirName, LEVEL level, std::string current_path);
	std::string CreateFileInfor(JsonStruct UploadInfor, LEVEL level, std::string current_path);
	std::string AddToXml(std::string path, std::string add_name, LEVEL level);
	std::string AddVerXml(std::string path);

};

bool GetInfor::isHad(std::string DirName, LEVEL level, std::string current_path)
{
	std::string search_tag;
	if (level == PROJECT)
		search_tag = "Project";
	else if (level == MODULE)
		search_tag = "Module";
	else if (level == VERSION)
		search_tag = "Version";

	std::string xmlpath = current_path + "Information.xml";
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
			if (DirName == elems[0].second.c_str())
				return true;
		}
	}
	return false;
}

std::string GetInfor::AddFileInfor(JsonStruct UploadInfor)
{
	std::string current_dir = Directory::getCurrentDirectory();
	std::string full_path = "../Data/";
	for (int i = 0; i < 3; i++)
	{
		if (!isHad(UploadInfor[i].second, (LEVEL)i, full_path))
		{
			full_path = CreateFileInfor(UploadInfor, (LEVEL)i, full_path);
			return full_path;
		}
		else
		{
			AddToXml(full_path, UploadInfor[i].second, (LEVEL)i);
		}
		full_path += UploadInfor[i].second + "/";
	}
	return full_path;
}

std::string GetInfor::AddToXml(std::string path, std::string add_name, LEVEL level)
{
	std::string root;
	std::string child_name;
	bool isExist = false;

	if (level == PROJECT)
	{
		root = "DataRepository";
		child_name = "Project";
	}
	else if (level == MODULE)
	{
		root = "Project";
		child_name = "Module";
	}
	else if (level == VERSION)
	{
		return AddVerXml(path);
	}

	std::string dir_ver_path = "";

	std::string xmlpath = path + "Information.xml";
	File logxml(xmlpath);
	logxml.open(File::in, File::text);
	std::string inforxml;
	while (logxml.isGood())
		inforxml += logxml.getLine();
	XmlReader rdfile(inforxml);
	std::vector<std::string> tmp;
	while (rdfile.next())
	{
		if (rdfile.tag() == child_name)
		{
			tmp.push_back(rdfile.attributes()[0].second);
			if (rdfile.attributes()[0].second == add_name)
				isExist = true;
		}
	}
	if (!isExist)
		tmp.push_back(add_name);

	XmlWriter wtr;
	wtr.addDeclaration();
	wtr.start(root);
	for (int i = 0; i < tmp.size(); i++)
	{
		XmlWriter sub;
		sub.start(child_name);
		if (level != VERSION)
			sub.addAttribute("name", tmp[i]);
		sub.end();
		wtr.addBody(sub.xml());
	}
	wtr.end();
	std::ofstream out(xmlpath);
	if (out.good())
	{
		out << wtr.xml().c_str();
		out.close();
	}
	return dir_ver_path;
}

std::string GetInfor::CreateFileInfor(JsonStruct UploadInfor, LEVEL level, std::string current_path)
{
	std::string return_path;

	for (int i = level; i < 3; i++)
	{
		if (i == 2)
			return_path = AddVerXml(current_path);
		else
		{
			return_path = current_path + UploadInfor[i].second + "/";
			if (!Directory::exists(return_path))
			{
				if (!Directory::create(return_path))
					LOG(TRACE) << "Fail to create Directory!" << std::endl;
				std::string infor_path = current_path + "Information.xml";
				if (!File::exists(infor_path))
				{
					XmlWriter wrt;
					XmlWriter subwrt;
					wrt.addDeclaration();
					if (i == 0)
					{
						wrt.start("DataRepository");
						subwrt.start("Project");
					}
					else if (i == 1)
					{
						wrt.start("Project");
						subwrt.start("Module");
					}

					subwrt.addAttribute("name", UploadInfor[i].second);
					subwrt.end();
					wrt.addBody(subwrt.xml());
					wrt.end();
					std::ofstream out(infor_path);
					if (out.good())
					{
						out << wrt.xml().c_str();
						out.close();
					}
				}
				else
				{
					AddToXml(current_path, UploadInfor[i].second, (LEVEL)i);
				}
			}
			else
			{
				LOG(TRACE) << "Curent Path Dir exixt, but enter the Create Function!" << std::endl;
			}
			current_path = return_path;
		}

	}
	return return_path;
}

std::string GetInfor::AddVerXml(std::string path)
{
	std::string xmlpath = path + "Information.xml";
	std::vector<std::string> tmp;
	if (File::exists(xmlpath))
	{
		File logxml(xmlpath);
		logxml.open(File::in, File::text);
		std::string inforxml;
		while (logxml.isGood())
			inforxml += logxml.getLine();
		XmlReader rdfile(inforxml);
		while (rdfile.next())
		{
			if (rdfile.tag() == "Version")
			{
				tmp.push_back(rdfile.attributes()[0].second);
				
			}
		}
			tmp.push_back(std::to_string(tmp.size()));
	}
	else
	{
		tmp.push_back("1");
	}
	XmlWriter wtr;
	wtr.addDeclaration();
	wtr.start("Module");
	for (int i = 0; i < tmp.size(); i++)
	{
		XmlWriter sub;
		sub.start("Version");
		sub.addAttribute("version", std::to_string(i+1));
		sub.end();
		wtr.addBody(sub.xml());
	}
	wtr.end();
	std::ofstream out(xmlpath);
	if (out.good())
	{
		out << wtr.xml().c_str();
		out.close();
	}
	std::string return_path = path + "version_" + std::to_string(tmp.size()) + "/";
	Directory::create(return_path);
	return return_path;
}


#endif