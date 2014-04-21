#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"
#include "XmlReader.h"
#include "XmlHelper.h"
#include "JsonReader.h"

void ModulesListServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	
	LOG(TRACE) << "Sending module list.";

	std::string path = ".";

	// check how many modules are supported in this server
	std::map<std::string, std::string> map;
	std::vector<m_data> mdls;

	std::vector<std::string> subdir = FileSystem::Directory::getDirectories(path);
	for (auto d : subdir)
	{
		if (d == ".." && d == ".")
			continue;

		// this is a Module.xml in the dir, then the dir is a module dir.
		if (FileSystem::File::exists(path + '\\' + d + "\\Module.xml"))
		{
			// check which platform is supported by the module
			m_data m = loadMdInfo(path + '\\' + d, "Module.xml", map);
			mdls.push_back(m);
		}

	}

	// pad the platform list to be the same as the longest list exist in the mdls
	for (int i = 0; i < mdls.size(); i++)
		checkPf(mdls[i], map);

	// create response
	response.getOutputStream() << createRsp(mdls, map);

}

m_data ModulesListServlet::loadMdInfo(std::string path, std::string file, std::map<std::string, std::string> &map)
{
	// open the file and read the xml
	std::ifstream ifs(path + '\\' + file);
	std::string xml;

	if (ifs.good())
	{
		xml.assign((std::istreambuf_iterator<char>(ifs)),
			std::istreambuf_iterator<char>());
	}

	// parse the xml
	m_data m;
	std::vector<std::string> libs;

	XmlReader rdr(xml);
	while (rdr.next())
	{
		if (rdr.tag() == "displayName")
			m.name = rdr.body();

		if (rdr.tag() == "description")
			m.des = rdr.body();

		if (rdr.tag() == "dynamicLibrary")
			libs.push_back(rdr.body());
	}

	for (auto lib : libs)
	{
		XmlReader rdr(lib);
		std::string k, v;
		while (rdr.next())
		{
			if (rdr.tag() == "path")
				v = rdr.body();

			if (rdr.tag() == "platform")
				k = rdr.body();
		}

		map[k] = v;
	}

	// check if the lib really exists
	for (auto t : map)
	{
		if (FileSystem::File::exists(path + '\\' + t.second))
			m.pfs.push_back(t.first);
	}

	return m;
}

void ModulesListServlet::checkPf(m_data &m, std::map<std::string, std::string> &map)
{
	std::vector<std::string> vec;
	for (auto m : map)
		vec.push_back(m.first);


	for (int i = 0; i < (int)vec.size(); i++)
	{
		// static module supported for all platforms
		if ((int)m.pfs.size() <= i)
			m.pfs.push_back("true");
		// platform is supported
		else if (vec[i] == m.pfs[i])
			m.pfs[i] = "true";
		// platform is not supported
		else
			m.pfs.insert(m.pfs.begin() + i, "false");

	}

}

std::string ModulesListServlet::createRsp(std::vector<m_data> mdls, std::map<std::string, std::string> &map)
{
	std::vector<std::string> pfs;
	for (auto m : map)
		pfs.push_back(m.first);

	std::stringstream ss;

	ss << "{"
		<< "    \"versions\": [";

	// list platforms' names
	for (int i = 0; i < pfs.size(); i++)
	{
		ss << "        \"" << pfs[i] << "\"";

		if (i != pfs.size() - 1)
			ss << ",";
		ss << "\n";
	}

	ss << "    ],"
		<< "    \"items\": [";

	// update platform supported info for each module;
	for (int i = 0; i < mdls.size(); i++)
	{
		ss << "        {"
			<< "            \"name\": \"" << mdls[i].name << "\","
			<< "            \"description\": \"" << mdls[i].des << "\","
			<< "            \"versionStates\": [\n";

		for (int j = 0; j < mdls[i].pfs.size(); j++)
		{
			ss << "{"
				<< "                    \"enabled\":" << mdls[i].pfs[j] << ","
				<< "                    \"selected\": false"
				<< "                }";

			if (j == mdls[i].pfs.size() - 1)
				ss << "";
			else
				ss << ",";
		}

		ss << "            ]";

		if (i == mdls.size() - 1)
			ss << "        }";
		else
			ss << "        },";
	}

	ss << "    ]"
		<< "}";

	return ss.str();
}


void CheckDependenciesServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    /*response.getOutputStream()
        << "{\n"
        << "    \"packTypes\": [\n"
        << "        \"zip\",\n"
        << "        \"tar\"\n"
        << "    ],\n"
        << "    \"modules\": {\n"
        << "        \"versions\": [\n"
        << "            \"Windows\",\n"
        << "            \"Linux x86\",\n"
        << "            \"Linux x64\"\n"
        << "        ],\n"
        << "        \"items\": [\n"
        << "            {\n"
        << "                \"name\": \"Main Program\",\n"
        << "                \"description\": \"The main server program.\",\n"
        << "                \"versionStates\": [\n"
        << "                    {\n"
        << "                        \"enabled\": false,\n"
        << "                        \"selected\": true\n"
        << "                    },\n"
        << "                    {\n"
        << "                        \"enabled\": false,\n"
        << "                        \"selected\": false\n"
        << "                    },\n"
        << "                    {\n"
        << "                        \"enabled\": false,\n"
        << "                        \"selected\": false\n"
        << "                    }\n"
        << "                ]\n"
        << "            },\n"
        << "            {\n"
        << "                \"name\": \"Installer\",\n"
        << "                \"description\": \"Allows others to clone your server.\",\n"
        << "                \"versionStates\": [\n"
        << "                    {\n"
        << "                        \"enabled\": true,\n"
        << "                        \"selected\": true\n"
        << "                    },\n"
        << "                    {\n"
        << "                        \"enabled\": true,\n"
        << "                        \"selected\": false\n"
        << "                    },\n"
        << "                    {\n"
        << "                        \"enabled\": true,\n"
        << "                        \"selected\": false\n"
        << "                    }\n"
        << "                ]\n"
        << "            }\n"
        << "        ]\n"
        << "    }\n"
        << "}";*/

	std::istream& in = request.getInputStream();
	std::string line;
	std::getline(in, line);
	LOG(DEBUG) << "Got: " << line;

	response.getOutputStream()
		<< "{\n"
		<< "    \"packTypes\": [\n"
		<< "        \"zip\",\n"
		<< "        \"tar\"\n"
		<< "    ],\n"
		<< "    \"modules\":"
		<< line
		<< "}";

}


void CreateServerServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	// get Json info
	LOG(TRACE) << "Creating new pkg for download.";
	std::istream& in = request.getInputStream();
	std::string req;
	std::getline(in, req);
	LOG(DEBUG) << "Got: " << req;

	// create pkg
	std::vector<m_data> mdls;
	parseMList(mdls, req);

	PkgCreater pc(".", "_file", "VirtualServer");
	pc.createPkg(mdls);
	std::string path = pc.pkgZipper();

	LOG(TRACE) << "Finished creating pkg";
	LOG(TRACE) << "Updating files map";

	std::string key = "Download";
	Downloads[key] = path;

	response.getOutputStream() << "{\n"
		<< "    \"fileKey\":\"" << key << "\"\n"
		<< "}";

}

void CreateServerServlet::parseMList(std::vector<m_data> &mdls, std::string request)
{
	JsonReader rdr(request);
	std::vector<std::string> vs;
	std::map<int, std::string> vmap;
	std::string str;

	while (rdr.next())
	{
		str = rdr.tag();
		if (str == "versions")
			updateMap(vmap, rdr.value());
		if (str == "items")
			updateMList(mdls, vmap, rdr.value());
	}
}

void CreateServerServlet::updateMap(std::map<int, std::string> &map, std::vector<std::string> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		map[i] = list[i];
	}
}

void CreateServerServlet::updateMList(std::vector<m_data> &mdls, std::map<int, std::string> &map, std::vector<std::string> rs)
{
	std::string str;

	for (int i = 0; i < rs.size(); i++)
	{
		m_data m;
		JsonReader rdr(rs[i]);
		while (rdr.next())
		{
			str = rdr.tag();
			if (str == "name")
				m.name = rmBlank(rdr.value()[0]);
			if (str == "description")
				m.des = rdr.value()[0];
			if (str == "versionStates")
				updateMInfo(m, map, rdr.value());
		}

		if (m.pfs.size())
			mdls.push_back(m);
	}
}

void CreateServerServlet::updateMInfo(m_data &m, std::map<int, std::string> &map, std::vector<std::string> rs)
{
	std::string str;
	for (int i = 0; i < rs.size(); i++)
	{
		JsonReader rdr(rs[i]);
		while (rdr.next())
		{
			if (rdr.tag() == "selected")
			{
				str = rdr.value()[0];

				if (str == "true")
					m.pfs.push_back(map[i]);
			}
		}
	}
}

std::string CreateServerServlet::rmBlank(std::string s)
{
	std::string str;

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;

		str += s[i];
	}
	return str;
}


int GetUrlServlet::COUNT = 0;

void GetUrlServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
   
	LOG(TRACE) << "Creating link for downloading the newly created pkg";

	std::istream& in = request.getInputStream();
	std::string line;
	std::getline(in, line);
	LOG(DEBUG) << "Got: " << line;

	// get path by the received key;
	std::string path;
	std::string key;
	JsonReader rdr(line);
	while (rdr.next())
	{
		if (rdr.tag() == "fileKey")
			key = rdr.value()[0];
	}

	if (Downloads.find(key) == Downloads.end())
	{
		LOG(DEBUG) << "fileKey doesn't exist in the Download map";
		return;
	}

	path = Downloads[key];

	if (!FileSystem::File::exists(path))
	{
		LOG(DEBUG) << "Download file doesn't exist :" << path;
		return;
	}

	if (COUNT >= 9) {
        // finished
        //response.getOutputStream() << buildResult("/_file/Download.zip", 500436, 100, 0);
		FileSystem::FileInfo finfo(path);
		LOG(DEBUG) << "Build Url: " << Url(path);
		response.getOutputStream() << buildResult(Url(path), finfo.size(), 100, 0);

        if (COUNT == 10) {
            COUNT = 0;
        }
   }
   else {
        // processing
        response.getOutputStream() << buildResult("", 0, (float)COUNT * 10, 2000);
   }
   COUNT++;
}

IHttpServlet::String GetUrlServlet::buildResult(String url, int size, float percentage, int waiting) {
    String ret = "{\n";
    ret += "    \"fileUrl\": ";
    ret += (url.empty() ? "null" : '\"' + url + '\"');
    ret += ",\n";
    ret += "    \"fileSize\": ";
    ret += std::to_string(size);
    ret += ",\n";
    ret += "    \"percentage\": ";
    ret += std::to_string(percentage);
    ret += ",\n";
    ret += "    \"waitingMillisecond\": ";
    ret += std::to_string(waiting);
    ret += "\n";
    ret += "}";
    return ret;
}

IHttpServlet::String GetUrlServlet::Url(String path)
{
	// directory path must begin with "/"
	String url = "/";

	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '\\')
			url += '/';
		else
			url += path[i];
	}

	return url;
}