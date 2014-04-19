///////////////////////////////////////////////////////////////////////////////
//  IModuleManager.h - provide an interface to manage DLL module's           //
//                     information.                                          //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module provides an interface to manage DLL module's information. Callers 
can load modules, get their information including states.

A DLL module is a individual directory in disks. The directory's name is the 
name of the module. It should contain a file "Module.xml", which defines 
configurations for that module. See "/Doucment/Module.xsd" for its format.
If the module contains a dynamic library file for the current platform, the
library will be loaded. See IModuleObjectFactory.h to see how to implement it.

Main Class:
===========
- IModuleManager : an interface to manage DLL module's information.  

Other Class:
============
- DynamicLibraryStruct : a data structure for dynamic library file.
- ModuleStruct         : a data structure for a DLL module.

Public Interface:
=================
// Get an instance from object factory of MainProgram
IModuleManager* pInstance = someFactory->getModuleManager();
// Get the list of menu items
std::vector<ModuleStruct> vec = pInstance->getModules();
// Load modules
pInstance->loadAll()

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

#include <string>
#include <vector>

// A data struct of a dynamic library file.
struct DynamicLibraryStruct{
    // the path, related to module's directory
    std::string path;

    // the platform, such as "Windows", "Linux x86" and "Linux x64"
    std::string platform;

    // the version
    std::string version;
};

// A data struct of a module
struct ModuleStruct{
    // the name
    std::string name;

    // the display name, displayed to user
    std::string displayName;

    // the description, displayed to user
    std::string description;

    // its library files
    std::vector<DynamicLibraryStruct> libraries;
};

// A class to manage modules. It can load modules and provide info of loaded
// modules.
//
// It shall be thread-safe.
class IModuleManager{
public:
    // Destructor.
    virtual ~IModuleManager() {}

    // Returns info of all loaded modules.
    virtual std::vector<ModuleStruct> getModules() = 0;

    // Load one module by its directory path, related to current working
    // directory. If it is already loaded, it will skip loading. If the module
    // does not support this platform or does not have required dynamic library
    // file, it will stop loading. If errors occur during loading, it will throw
    // exceptions.
    //
    // Once the module contains Module.xml, it will set its state no matter
    // whether loading succeed. So callers can use isModuleLoaded() and
    // getModuleState() to check loading results.
    virtual void load(const std::string& modulePath) = 0;

    // Scan direct sub directories of the current working directory and load
    // them as modules except for directories starting with "_". "MainProgram"
    // module, as a special one, will be loaded first.
    virtual void loadAll() = 0;

    // Returns true if the module has been loaded.
    virtual bool isModuleLoaded(const std::string& moduleName) = 0;

    // Returns the state such as "Running", "Loading Error", "Unsupport
    // Platform", "Running Error", "Stopped".
    virtual std::string getModuleState(const std::string& moduleName) = 0;
};
