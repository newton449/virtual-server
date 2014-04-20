#pragma once

#include "../interfaces/IHttpServlet.h"
#include <string>
#include <map>
#include <vector>
#include "PkgCreater.h"

static std::map<std::string, std::string> Downloads;

class ModulesListServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
	
private:
	m_data loadMdInfo(std::string path, std::string file, std::map<std::string, std::string> &map);
	void checkPf(m_data &m, std::map<std::string, std::string> &map);
	std::string createRsp(std::vector<m_data> mdls, std::map<std::string, std::string> &map);
};

class CheckDependenciesServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
};

class CreateServerServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);

private:
	void parseMList(std::vector<m_data> &mdls, std::string request);
	void updateMap(std::map<int, std::string> &map, std::vector<std::string> list);
	void updateMList(std::vector<m_data> &mdls, std::map<int, std::string> &map, std::vector<std::string> vs);
	void updateMInfo(m_data &m, std::map<int, std::string> &map, std::vector<std::string> rs);
	std::string rmBlank(std::string s);
};

class GetUrlServlet : public IHttpServlet{
public:
	// Do the HTTP method.
	void doMethod(IHttpServletRequest& request, IHttpServletResponse& response);
private:
	static int COUNT;

	String buildResult(String url, int size, float percentage, int waiting);
	
};
