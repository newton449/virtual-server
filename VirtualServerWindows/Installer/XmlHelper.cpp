#include "XmlHelper.h"

void XmlHelper::updateMap(std::string xml, std::map<std::string, std::string> &map)
{
	// clear the map
	map.clear();

	std::vector<std::string> meta;

	XmlReader rdr(xml);
	while (rdr.next())
	{
		if (rdr.tag() == "dynamicLibrary")
			meta.push_back(rdr.body());
	}

	while (meta.size())
	{
		std::string str = meta.back();
		meta.pop_back();

		XmlReader rdr(str);
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
}