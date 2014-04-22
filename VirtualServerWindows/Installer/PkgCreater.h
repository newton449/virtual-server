#include "pf_data.h"
#include "FileMng.h"
#include <iostream>

class PkgCreater
{
public:
	PkgCreater(std::string from, std::string to, std::string pkgName);
	~PkgCreater();
	bool createPkg(std::vector<m_data> meta);
	std::string pkgZipper();

private:
	std::map<std::string, std::string> _typemap;
	std::map<std::string, int> _cnt;
	std::string _from;
	std::string _to;
	std::string _pkgName;
	
	bool IsLib(std::string str);
	void updateMap(std::string xml);
	void updateCnt(m_data m);
	
	
};