#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"
#include "../interfaces/IClientManager.h"
#include "ModuleObjectFactoryImpl.h"

#include "GetInfor.h"
#include "JsonToStruct.h"
#include "GenerateFileInfor.h"

#include <iostream>
#include <string>

void title(std::string _title)
{
	std::cout << "=============================================" << std::endl;
	std::cout << _title << std::endl;
	std::cout << "=============================================" << std::endl;
}

void UploadServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response)
{

	std::string name = request.getParameter("file_name");

	std::istream& in = request.getInputStream();
	std::string temp;
	std::string check_bound;
	in >> temp;
	std::string boundary = temp;
	boundary += '\r';

	std::string testJson = getDirName(in, boundary); //"{[\"Project\":\"Test\",\"ModuleName\":\"Sender\", \"Author\":\"TestAuthor\"]}";
	if (testJson == "Path Wrong!")
	{
		response.getOutputStream() << "Wrong Path, Please Check the Path!";
		return;
	}
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

	int count_file = 0;
		while (in.good())
		{
			std::string file_name = getFileName(in, boundary);
			if (file_name != "Not File!") // Upload file must have filename
			{
				in >> temp; // Content-Type:content
				std::ofstream savefile ;
				savefile.open(result_fullpath + file_name, std::ios::out | std::ios::binary);
				if (!savefile){
					response.sendErrorWithMessage(500, "Cannot open the file.");
				}
				bool isLastLine = true;
				while (in.good())
				{
					std::getline(in, temp);
					std::getline(in, temp);
					std::getline(in, temp);								
					while ( temp != boundary)
					{
						std::string next;
						std::getline(in, next);
						if (next != boundary)
						{
							isLastLine = false;
						}
						else
						{
							isLastLine = true;
						}
						if (!isLastLine)
						{
							savefile.write(temp.c_str(), temp.size());
							savefile.put('\n');
						}
						else
						{
							savefile.write(temp.c_str(), temp.size() - 1);
						}
						temp = next;
					}
					break;
				}
				savefile.flush();
				savefile.close();
				count_file++;
			}
			else
			{
				if (count_file == 0)
				{
					response.getOutputStream() << "No File Upload!";
					return;
				}
				break;
			}
			//break;
		}
		std::string return_msg = std::to_string(count_file) + "files Upload Succeed !";
		response.getOutputStream() << return_msg;
		
	
}

bool UploadServlet::checkRequest(IHttpServletRequest& request, IHttpServletResponse& response){
	// Check whether it is chunck mode
	if (request.getHeader("Transfer-Encoding") != "chunked"){
		response.sendErrorWithMessage(501, "Please use chunked mode");
		return false;
	}
	std::string name = request.getParameter("file_name");
	if (name.empty()){
		// PENDING 404?
		response.sendErrorWithMessage(404, "Invalid file name");
		return false;
	}
	return true;
}

bool UploadServlet::readOneChunk(std::istream& in, int& chunkSize, std::string& chunkSizeLine, bool& error, char*& buf, int& bufSize, std::ofstream& fout, IHttpServletResponse& response){
	std::string tmp;
	if (chunkSizeLine.empty() || chunkSizeLine[0]<48 || chunkSizeLine[0]>57){
		// it is an invalid chuncked format
		return false;
	}
	chunkSize = std::atoi(chunkSizeLine.c_str()); // ignore optional alphabets.
	if (chunkSize == 0){
		// read the empty line
		std::getline(in, tmp);
		error = false; // exit normally
		return false;
	}
	// check buf
	if (bufSize < chunkSize){
		if (buf != NULL){
			delete buf;
		}
		buf = new char[chunkSize];
		bufSize = chunkSize;
	}
	// read chunk
	in.read(buf, chunkSize);
	if (!in){
		return false;
	}
	// read the \r\n
	std::getline(in, tmp);
	if (tmp != "\r" && !tmp.empty()){
		return false;
	}
	// Save to the file
	fout.write(buf, chunkSize);
	if (!fout){
		response.sendErrorWithMessage(500, "Failed to save the file.");
		return false;
	}
	return true;
}



void TreeViewServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response)
{
	//response.getOutputStream() << "This is Test For TreeViewServlet!";
	//std::cout << "Enter TreeViewServlet" << std::endl;
	//std::cout << (std::string)request.getInputStream() << std::endl;
	std::cout << Directory::getCurrentDirectory() << std::endl;
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
	response.getOutputStream() << JsonMsg;

}


std::string UploadServlet::getFileName(std::istream& in, std::string boundary)
{
	std::string tmp;
	std::string file_name = "";
	std::string check_name = "name=\"file\";";
	int check_count = 0;
	while (in.good())
	{
		std::getline(in,tmp);
		while (tmp.find("Content-Disposition:")>=tmp.size() && in.good())
		{
			std::getline(in, tmp);
		}
		if (tmp.find("Content-Disposition:") < tmp.size())
		{
			if (tmp.find(check_name)>=tmp.size())
				return "Not File!";

			int name_start = tmp.find("filename=\"");
			tmp = tmp.substr(name_start + 10, tmp.size());
			int name_end = tmp.find_first_of("\"");
			file_name = tmp.substr(0, name_end);
			if (file_name=="")
					return "Not File!";
		}
		else
		{
			return "Not File!";
		}
		break;
	}
	return file_name;
}

std::string UploadServlet::getDirName(std::istream& in, std::string boundary)
{
	std::string tmp;
	std::string dir_name="";
	std::string check_name = "name=\"dir\"";
	int check_count = 0;
	while (in.good())
	{
		std::getline(in, tmp);
		while (tmp.find("Content-Disposition:") >= tmp.size() && in.good())
		{
			std::getline(in, tmp);
		}
		if (tmp.find("Content-Disposition:") < tmp.size())
		{
			if (tmp.find(check_name) >= tmp.size())
				return "Not Path!";
			std::getline(in, tmp);
			std::getline(in, tmp);
			dir_name += tmp;
		}
		else
		{
			return "Not Path!";
		}
		break;
	}

	//"{[\"Project\":\"CodeRepository\",\"ModuleName\":\"Sender\", \"Author\":\"TestAuthor\"]}"
	std::string Jsonmsg = "{[\"Project\":\"";
	std::string project_name;
	std::string module_name;
	size_t check_path_1 = dir_name.find("\r");
	if (dir_name.size()<=6)
		return "Path Wrong!";

	dir_name = dir_name.substr(6, dir_name.size() - 6);


	size_t check_path_2 = dir_name.find("\r");

	size_t tmp_slash = dir_name.find("/");

	if (tmp_slash >= dir_name.size())
		return "Path Wrong!";

	project_name = dir_name.substr(0, tmp_slash);
	dir_name = dir_name.substr(tmp_slash + 1, dir_name.size() - 6);

	size_t tmp_slash_ = dir_name.find("\r");

	

	module_name = dir_name.substr(0, tmp_slash_);
	Jsonmsg += project_name;
	Jsonmsg += "\",\"ModuleName\":\"";
	Jsonmsg += module_name;
	Jsonmsg += "\", \"Author\":\"TestAuthor\"]}";
	
	return Jsonmsg;
}
