#ifndef MDATA_H_
#define MDATA_H_

/* platform_data.h
   For : data structure for storing user customized platform and module sets.
*/

#include <string>
#include <vector>
#include <map>

struct m_data
{
	std::string name;
	std::string des;
	std::vector<std::string> pfs;
};

#endif