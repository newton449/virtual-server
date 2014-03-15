#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"

void ModulesListServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	response.getOutputStream()
		<< "       {\n"
		<< "         \"versions\": [\n"
		<< "         \"Windows\",\n"
		<< "         \"Linux x86\",\n"
		<< "         \"Linux x64\"\n"
		<< "         ],\n"
		<< "         \"modules\": [\n"
		<< "         {\n"
		<< "         \"name\": \"Main Program\",\n"
		<< "         \"description\": \"The main server program.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"name\": \"Installer\",\n"
		<< "         \"description\": \"Allows others to clone your server.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": false\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": false\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"name\": \"File Manager\",\n"
		<< "         \"description\": \"Supports uploading and downloading files.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": false\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": false\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         }";
}


void CheckDependenciesServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	response.getOutputStream()
		<< "       {\n"
		<< "         \"versions\": [\n"
		<< "         \"Windows\",\n"
		<< "         \"Linux x86\",\n"
		<< "         \"Linux x64\"\n"
		<< "         ],\n"
		<< "         \"modules\": [\n"
		<< "         {\n"
		<< "         \"name\": \"Main Program\",\n"
		<< "         \"description\": \"The main server program.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": true\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"name\": \"Installer\",\n"
		<< "         \"description\": \"Allows others to clone your server.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"name\": \"File Manager\",\n"
		<< "         \"description\": \"Supports uploading and downloading files.\",\n"
		<< "         \"versionStates\": [\n"
		<< "         {\n"
		<< "         \"enabled\": true,\n"
		<< "         \"selected\": true\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": false\n"
		<< "         },\n"
		<< "         {\n"
		<< "         \"enabled\": false,\n"
		<< "         \"selected\": false\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         }\n"
		<< "         ]\n"
		<< "         }";
}


void CreateServerServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	response.getOutputStream() << "{\n"
		<< "    \"fileKey\": \"VirtualServer-all\"\n"
		<< "}";
}


int GetUrlServlet::COUNT = 0;

void GetUrlServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
	if (COUNT >= 9) {
		// finished
		response.getOutputStream() << buildResult("/_file/VirtualServer-all.zip", 500436, 100, 0);
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