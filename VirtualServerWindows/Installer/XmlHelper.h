#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "XmlReader.h"

class XmlHelper
{
public:
	void static updateMap(std::string xml, std::map<std::string, std::string> &map);
};