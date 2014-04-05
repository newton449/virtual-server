#include "ModuleManagerImpl.h"
#include "MainObjectFactoryImpl.h"
#include "../interfaces/IClientManager.h"
#include "FileSystem.h"
#include "XMLDocument.h"
#include "StringUtils.h"
#include <iostream>

ModuleManagerImpl::ModuleManagerImpl(){
    factory = MainObjectFactoryImpl::getInstance();
}

vector<ModuleStruct> ModuleManagerImpl::getModules() {
    return modules;
}

void ModuleManagerImpl::load(string moduleName) {
    LOG(INFO) << "Loading module: " << moduleName;
    // check whether it has been loaded
    if (isModuleLoaded(moduleName)){
        LOG(WARNING) << "The module has been loaded: " << moduleName;
        return;
    }
    // Load its XML configuration file.
    std::string configPath = moduleName + FILE_SEPARATOR + "Module.xml";
    if (!FileSystem::File::exists(configPath)){
        LOG(WARNING) << "Cannot find Module.xml for module \"" << moduleName << "\"";
        return;
    }
    tinyxml2::XMLDocument doc;
    doc.LoadFile(configPath.c_str());
    if (doc.Error()){
        throw InvalidFormatException("Failed to parse XML file: " + configPath);
    }
    tinyxml2::XMLElement* root = doc.FirstChildElement("module");
    CHECK_NODE(root, "module");

    ModuleStruct module;
    module.name = moduleName;
    tinyxml2::XMLElement* elem = NULL;
    // Register module name.
    loadBasicInfo(moduleName, root, module);

    // Register properties
    loadProperties(moduleName, root);

    // Register supported platforms and dynamic libraries.
    IModuleObjectFactory* moduleFactory = NULL;
    if (!loadLibrariesInfo(moduleName, root, module, moduleFactory)){
        this->addModule(module);
        return;
    }
    this->addModule(module);

    try{
        DefaultHttpServletMapping* mapping = factory->getHttpServletMapping();

        // Register servlets. Only when it has a module factory.
        if (moduleFactory != NULL){
            loadServletsInfo(moduleName, root, moduleFactory, mapping);
        }

        // Register static resources.
        loadStaticResourcesInfo(moduleName, root, moduleFactory, mapping);

        // Register client's menu items. We do it at last, because if error occurs, users will not see these.
        loadMenuInfo(moduleName, root);
    }
    catch (std::exception& ex){
        this->setModuleState(moduleName, "Loading Error");
        throw ex;
    }

    this->setModuleState(moduleName, "Running");
    LOG(INFO) << "Finished loading module: " << moduleName;
}

void ModuleManagerImpl::loadAll() {
    LOG(DEBUG) << "Loading all modules.";
    // load primaryKeys
    primaryKeys = (std::unordered_set<std::string>*) factory->getObject("primaryKeys");

    // Load Module.xml for MainProgram first.
    load("MainProgram");
    // Get subdirectory list of working directory.
    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(".");
    for (auto& dir : dirs){
        char firstChar = dir[0];
        if (firstChar != '.' && firstChar != '_' && dir != "MainProgram"){
            load(dir);
        }
    }
    LOG(DEBUG) << "Finished loading all modules.";
}

bool ModuleManagerImpl::isModuleLoaded(string moduleName){
    unordered_map<string, string>::iterator it = stateMap.find(moduleName);
    return it != stateMap.end();
}

string ModuleManagerImpl::getModuleState(string moduleName){
    unordered_map<string, string>::iterator it = stateMap.find(moduleName);
    if (it != stateMap.end()){
        return it->second;
    }
    return "";
}

void ModuleManagerImpl::setModuleState(string moduleName, string state){
    stateMap[moduleName] = state;
}

void ModuleManagerImpl::addModule(ModuleStruct module) {
    modules.push_back(module);
}

void ModuleManagerImpl::addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory) {
    unordered_map<string, IModuleObjectFactory*>::iterator it = factoryMap.find(moduleName);
    if (it != factoryMap.end()){
        // not allow, because we don't know how to delete old object
        // If we delete it directly, its destructor will not be called.
        throw std::logic_error("A moduleFactory of the module \"" + moduleName + "\" has been set.");
    }
    factoryMap[moduleName] = moduleFactory;
}

void ModuleManagerImpl::loadBasicInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, ModuleStruct& module){
    tinyxml2::XMLElement* elem = NULL;
    // Register module name.
    elem = root->FirstChildElement("displayName");
    CHECK_NODE(elem, "displayName");
    module.displayName = StringUtils::NullToEmpty(elem->GetText());
    CHECK_EMPTY(module.displayName, "displayName");
    elem = root->FirstChildElement("description");
    CHECK_NODE(elem, "description");
    module.description = StringUtils::NullToEmpty(elem->GetText());
    CHECK_EMPTY(module.description, "description");
}

void ModuleManagerImpl::loadProperties(const std::string& moduleName, tinyxml2::XMLElement*& root){
    PropertyMap* map = factory->getPropertyMap();
    // parse <properties>
    tinyxml2::XMLElement* properties = root->FirstChildElement("properties");
    if (properties != NULL){
        // parse elem such as <MainProgram.httpServerPort>8080</MainProgram.httpServerPort>
        // it should not over
        tinyxml2::XMLElement* prop = properties->FirstChildElement();
        while (prop != NULL){
            // cannot override properties in primaryKeys
            std::string key = prop->Name();
            if (primaryKeys->find(key) == primaryKeys->end()){
                (*map)[key] = StringUtils::NullToEmpty(prop->GetText());
            }
            prop = prop->NextSiblingElement();
        }
    }
}

bool ModuleManagerImpl::loadLibrariesInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, ModuleStruct& module, IModuleObjectFactory*& moduleFactory){
    tinyxml2::XMLElement* elem = NULL;
    std::string currentPlatform = (*factory->getPropertyMap())["system.currentPlatform"];
    std::string currentLibraryPath;
    DynamicLibraryStruct libStr;
    elem = root->FirstChildElement("dynamicLibraries");
    if (elem == NULL){
        LOG(DEBUG) << "The module does not have dynamic libraries: " << moduleName;
        return true;
    }
    else{
        // parse <dynamicLibrary>
        tinyxml2::XMLElement* lib = elem->FirstChildElement();
        while (lib != NULL){
            EXPECT_NODE(lib, "dynamicLibrary");
            // parse <path>
            elem = lib->FirstChildElement("path");
            CHECK_NODE(elem, "path");
            libStr.path = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(libStr.path, "path");
            // parse <platform>
            elem = lib->FirstChildElement("platform");
            CHECK_NODE(elem, "platform");
            libStr.platform = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(libStr.platform, "platform");
            // parse version. It is optional.
            elem = lib->FirstChildElement("version");
            if (elem != NULL){
                libStr.version = StringUtils::NullToEmpty(elem->GetText());
            }
            module.libraries.push_back(libStr);
            lib = lib->NextSiblingElement();
            // save current platform's library file
            if (libStr.platform == currentPlatform){
                currentLibraryPath = moduleName + FILE_SEPARATOR + libStr.path;
            }
        }
        if (currentLibraryPath.empty()){
            LOG(INFO) << "No specific library file of \"" << moduleName << "\" for the current platform \"" << currentPlatform << "\". Stop loading.";
            this->setModuleState(moduleName, "Unsupport Platform");
            return false;
        }

        if (!FileSystem::File::exists(currentLibraryPath)){
            LOG(INFO) << "The library file \"" << currentLibraryPath << "\" does not exist, so this platform is not supported.";
            this->setModuleState(moduleName, "Unsupport Platform");
            return false;
        }

        // Load the dynamic of the current platform except for MainProgram.
        if (moduleName != "MainProgram"){
            try{
                moduleFactory = loadDllAndGetModuleFactory(currentLibraryPath); // load from dll
            }
            catch (std::exception& ex){
                LOG(ERROR) << "Got exception when load library file: " << ex.what();
                return false;
            }
            if (moduleFactory == NULL) {
                LOG(ERROR) << "Falied to load library: " << currentLibraryPath;
                this->setModuleState(moduleName, "Loading Error");
                return false;
            }
            this->addModuleObjectFactory(moduleName, moduleFactory);
            return true;
        }
        else{
            return true;
        }
    }
}

void ModuleManagerImpl::loadServletsInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, IModuleObjectFactory*& moduleFactory, DefaultHttpServletMapping*& mapping){
    tinyxml2::XMLElement* elem = NULL;
    IServletFactory* servletFactory = moduleFactory->getServletFactory();
    tinyxml2::XMLElement* servlets = root->FirstChildElement("servlets");
    if (servlets != NULL){
        tinyxml2::XMLElement* servlet = servlets->FirstChildElement();
        while (servlet != NULL){
            EXPECT_NODE(servlet, "servlet");
            // parse <url>
            elem = servlet->FirstChildElement("url");
            CHECK_NODE(elem, "url");
            std::string url = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(url, "url");
            // parse <name>
            elem = servlet->FirstChildElement("name");
            CHECK_NODE(elem, "name");
            std::string name = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(name, "name");
            mapping->addServletMapping(url, servletFactory, name);
            // go to next element
            servlet = servlet->NextSiblingElement();
        }
    }
}
void ModuleManagerImpl::loadStaticResourcesInfo(const std::string& moduleName, tinyxml2::XMLElement*& root, IModuleObjectFactory*& moduleFactory, DefaultHttpServletMapping*& mapping){
    tinyxml2::XMLElement* elem = NULL;
    elem = root->FirstChildElement("staticResources");
    if (elem != NULL){
        tinyxml2::XMLElement* res = elem->FirstChildElement();
        while (res != NULL){
            EXPECT_NODE(res, "staticResource");
            // parse <directory>
            elem = res->FirstChildElement("directory");
            CHECK_NODE(elem, "directory");
            std::string dir = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(dir, "directory");
            // the path is related to module's directory. So add module name.
            dir = moduleName + FILE_SEPARATOR + dir;
            dir = StringUtils::fixDirectoryPath(dir);
            // parse <contextPath>
            elem = res->FirstChildElement("contextPath");
            CHECK_NODE(elem, "contextPath");
            std::string context = StringUtils::NullToEmpty(elem->GetText());
            if ((!context.empty()) && context[0] != '/'){
                throw InvalidFormatException("A context path should start with '/' or be empty.");
            }
            // context path cannot be a single "/"
            if (context == "/"){
                context = "";
            }
            mapping->addResourcesMapping(context, dir);
            res = res->NextSiblingElement();
        }
    }
}
void ModuleManagerImpl::loadMenuInfo(const std::string& moduleName, tinyxml2::XMLElement*& root){
    tinyxml2::XMLElement* elem = NULL;
    ClientManagerImpl* clientManager = (ClientManagerImpl*)factory->getClientManager();
    ClientMenuItem item;
    // parse <clientMenu>
    tinyxml2::XMLElement* menu = root->FirstChildElement("clientMenu");
    if (menu != NULL){
        // parse <item>
        tinyxml2::XMLElement* itemElem = menu->FirstChildElement();
        while (itemElem != NULL){
            EXPECT_NODE(itemElem, "item");
            // parse <name>
            elem = itemElem->FirstChildElement("name");
            CHECK_NODE(elem, "name");
            item.name = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(item.name, "name");
            // parse <description>. It is optional.
            elem = itemElem->FirstChildElement("description");
            if (elem != NULL){
                item.description = StringUtils::NullToEmpty(elem->GetText());
            }
            // parse <url>
            elem = itemElem->FirstChildElement("url");
            CHECK_NODE(elem, "url");
            item.url = StringUtils::NullToEmpty(elem->GetText());
            CHECK_EMPTY(item.url, "url");
            // parse <orderNumber>
            elem = itemElem->FirstChildElement("orderNumber");
            CHECK_NODE(elem, "orderNumber");
            item.orderNumber = StringUtils::parseFloat(StringUtils::NullToEmpty(elem->GetText()));
            // add the item
            clientManager->addMenuItem(item);
            // go to next item
            itemElem = itemElem->NextSiblingElement();
        }
    }

}
