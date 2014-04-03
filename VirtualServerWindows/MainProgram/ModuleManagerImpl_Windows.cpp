#include "ModuleManagerImpl.h"
#include "MainObjectFactoryImpl.h"
#include <locale>
#include <codecvt>
#include <string>

IModuleObjectFactory* ModuleManagerImpl::loadDllAndGetModuleFactory(string path){
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wpath = converter.from_bytes(path);

    // call SetErrorMode() twice to achieve the same effect.
    UINT oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
    SetErrorMode(oldErrorMode | SEM_FAILCRITICALERRORS);
    
    HINSTANCE hGetProcIDDLL = LoadLibrary(wpath.c_str());

    if (!hGetProcIDDLL) {
        LOG(ERROR) << "Could not load the dynamic library \"" << path << "\"";
        return NULL;
    }

    // Restore previous error mode.
    SetErrorMode(oldErrorMode);

    loadModuleAndReturnFactory func = (loadModuleAndReturnFactory)GetProcAddress(hGetProcIDDLL, "loadModuleAndReturnFactory");
    if (!func) {
        LOG(ERROR) << "Could not locate the function in the dynamic library \"" << path << "\"";
        return NULL;
    }

    return func(MainObjectFactoryImpl::getInstance());
}
