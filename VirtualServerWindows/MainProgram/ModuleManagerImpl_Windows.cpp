#include "ModuleManagerImpl.h"
#include "MainObjectFactoryImpl.h"
#include <locale>
#include <codecvt>
#include <string>

IModuleObjectFactory* ModuleManagerImpl::loadDllAndGetModuleFactory(string path){
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wpath = converter.from_bytes(path);

	HINSTANCE hGetProcIDDLL = LoadLibrary(wpath.c_str());

	if (!hGetProcIDDLL) {
		std::cout << "could not load the dynamic library" << std::endl;
		return NULL;
	}

	loadModuleAndReturnFactory func = (loadModuleAndReturnFactory)GetProcAddress(hGetProcIDDLL, "loadModuleAndReturnFactory");
	if (!func) {
		std::cout << "could not locate the function" << std::endl;
		return NULL;
	}

	return func(MainObjectFactoryImpl::getInstance());
}