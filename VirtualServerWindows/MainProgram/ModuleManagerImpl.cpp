#include "ModuleManagerImpl.h"
#include "MainObjectFactoryImpl.h"
#include "../interfaces/IClientManager.h"
#include "FileSystem.h"
#include "XMLDocument.h"
#include "StringUtils.h"
#include <iostream>

vector<ModuleStruct> ModuleManagerImpl::getModules() {
    //TODO design
    return modules;
}

void ModuleManagerImpl::load(string moduleName) {
    LOG(INFO) << "Loading module: " << moduleName;
    // check whether it has been loaded
    if (isModuleLoaded(moduleName)){
        LOG(WARNING) << "The module has been loaded: " << moduleName;
    }
    // TODO Load its XML configuration file.
    std::string configPath = moduleName + FILE_SEPARATOR + "Module.xml";
    tinyxml2::XMLDocument doc; 
    doc.LoadFile(configPath.c_str());
    tinyxml2::XMLElement* root = doc.FirstChildElement("module");

    ModuleStruct module;
    // TODO Register module namd and supported platforms.
    module.displayName = root->FirstChildElement("displayName")->GetText();
    module.description = root->FirstChildElement("description")->GetText();
    // TODO Register dynamic libraries.
    std::string currentPlatform = (*MainObjectFactoryImpl::getInstance()->getPropertyMap())["sys.currentPlatform"];
    std::string currentLibraryPath;
    DynamicLibraryStruct libStr;
    tinyxml2::XMLElement* libs = root->FirstChildElement("dynamicLibraries");
    tinyxml2::XMLElement* lib = libs->FirstChildElement("dynamicLibrary");
    while (lib != NULL){
        const char* path = lib->FirstChildElement("path")->GetText();
        const char* platform = lib->FirstChildElement("platform")->GetText();
        const char* version = lib->FirstChildElement("version")->GetText();
        libStr.path = path;
        libStr.platform = platform;
        libStr.version = version;
        module.libraries.push_back(libStr);
        lib = lib->NextSiblingElement();
        // save current platform's library file
        if (platform == currentPlatform){
            currentLibraryPath = moduleName + FILE_SEPARATOR + path;
        }
    }
    this->addModule(module);

    if (currentLibraryPath.empty()){
        LOG(INFO) << "No property file for current platform.";
        return;
    }

    // TODO Load the dynamic of the current platform.
    IModuleObjectFactory* moduleFactory = loadDllAndGetModuleFactory(currentLibraryPath); // load from dll
    if (moduleFactory == NULL) {
        LOG(WARNING) << "Falied to load library: " << currentLibraryPath;
        return;
    }
    this->addModuleObjectFactory(moduleName, moduleFactory);

    // TODO Register client's menu items.
    MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();
    ClientManagerImpl* clientManager = (ClientManagerImpl*)factory->getClientManager();
    ClientMenuItem item;
    tinyxml2::XMLElement* menu = root->FirstChildElement("clientMenu");
    if (menu != NULL){
        tinyxml2::XMLElement* elem = menu->FirstChildElement("item");
        while (elem != NULL){
            item.name = elem->FirstChildElement("name")->GetText();
            tinyxml2::XMLElement* des = elem->FirstChildElement("description");
            if (des != NULL){
                item.description = des->GetText();
            }
            item.url = elem->FirstChildElement("url")->GetText();
            item.orderNumber = StringUtils::parseFloat(elem->FirstChildElement("orderNumber")->GetText());
            clientManager->addMenuItem(item);
            elem = elem->NextSiblingElement();
        }
    }

    // TODO Register servlets.
    AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
    IServletFactory* servletFactory = moduleFactory->getServletFactory();
    tinyxml2::XMLElement* servlets = root->FirstChildElement("servlets");
    tinyxml2::XMLElement* servlet = servlets->FirstChildElement("servlet");
    while (servlet != NULL){
        mapping->addServletMapping(servlet->FirstChildElement("url")->GetText(), servletFactory, servlet->FirstChildElement("name")->GetText());
        servlet = servlet->NextSiblingElement();
    }

    // TODO Register static resources.
    tinyxml2::XMLElement* resources = root->FirstChildElement("staticResources");
    if (resources != NULL){
        tinyxml2::XMLElement* res = resources->FirstChildElement();
        while (res != NULL){
            const char* dir = res->FirstChildElement("directory")->GetText();
            tinyxml2::XMLElement* contextElem = res->FirstChildElement("contextPath");
            const char* context = contextElem->GetText();
            mapping->addResourcesMapping(context == NULL ? "" : context, moduleName + dir);
            res = res->NextSiblingElement();
        }
    }

    LOG(INFO) << "Finished loading module: " << moduleName;
}

void ModuleManagerImpl::loadAll() {
    LOG(DEBUG) << "Loading all modules.";
    // TODO design
    load("Home");

    load("Installer");
}

bool ModuleManagerImpl::isModuleLoaded(string moduleName){
    // TODO 
    return false;
}

void ModuleManagerImpl::addModule(ModuleStruct module) {
    // TODO design
    modules.push_back(module);
}

void ModuleManagerImpl::addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory) {
    // TODO design
    factoryMap[moduleName] = moduleFactory;
}
