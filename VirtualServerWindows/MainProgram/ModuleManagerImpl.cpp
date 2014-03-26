#include "ModuleManagerImpl.h"
#include "MainObjectFactoryImpl.h"
#include "../interfaces/IClientManager.h"
#include <iostream>

vector<ModuleStruct> ModuleManagerImpl::getModules() {
    //TODO design
    return modules;
}

void ModuleManagerImpl::load(string modulePath) {
    LOG(INFO) << "Loading module: " << modulePath;
    // TODO check whether it has been loaded

    // TODO Load its XML configuration file.

    // TODO Register module namd and supported platforms.
    // TODO Register dynamic libraries.
    ModuleStruct module;
    module.displayName = "Home";
    module.description = "Description for Home";
    DynamicLibraryStruct libStr;
    libStr.path = "Home.dll";
    libStr.platform = "Windows";
    libStr.version = "0.1";
    module.libraries.push_back(libStr);
    libStr.path = "Home_x86.so";
    libStr.platform = "Linux x86";
    libStr.version = "0.1";
    module.libraries.push_back(libStr);
    this->addModule(module);

    // TODO Load the dynamic of the current platform.
#ifdef WIN32
    IModuleObjectFactory* moduleFactory = loadDllAndGetModuleFactory("./Home/Home.dll"); // load from dll
#else
    IModuleObjectFactory* moduleFactory = loadDllAndGetModuleFactory("./Home/Home_x64.so"); // load from dll
#endif
    if (moduleFactory == NULL) {
        exit(1);
    }
    this->addModuleObjectFactory("Home", moduleFactory);

    // TODO Register client's menu items.
    MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();
    ClientManagerImpl* clientManager = (ClientManagerImpl*) factory->getClientManager();
    ClientMenuItem item;
    item.name = "Home";
    item.description = "Description for Home";
    item.orderNumber = 0;
    item.url = "/home/";
    clientManager->addMenuItem(item); // from XML
    item.name = "Clone";
    item.description = "Clone the server to your machine.";
    item.orderNumber = 80;
    item.url = "/installer/";
    clientManager->addMenuItem(item);
    item.name = "About";
    item.description = "About this website";
    item.orderNumber = 100;
    item.url = "/home/#about";
    clientManager->addMenuItem(item); // from XML

    // TODO Register servlets.
    AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
    IServletFactory* servletFactory = moduleFactory->getServletFactory();
    mapping->addServletMapping("/", servletFactory, "RedirectToHomeServlet");
    mapping->addServletMapping("/home/menu_list", servletFactory, "MenuListServlet"); // from XML

    // TODO Register static resources.
    mapping->addResourcesMapping("/home", "./Home/web/");
    mapping->addResourcesMapping("", "./_web/");

    LOG(INFO) << "Finished loading module: " << modulePath;

    // TODO Load the dynamic of the current platform.
#ifdef WIN32
    moduleFactory = loadDllAndGetModuleFactory("./Installer/Installer.dll"); // load from dll
#else
    moduleFactory = loadDllAndGetModuleFactory("./Installer/Installer_x64.so"); // load from dll
#endif
    if (moduleFactory == NULL) {
        exit(1);
    }
    this->addModuleObjectFactory("Installer", moduleFactory);

    // TODO Register servlets.
    servletFactory = moduleFactory->getServletFactory();
    mapping->addServletMapping("/installer/modules_list", servletFactory, "ModulesListServlet");
    mapping->addServletMapping("/installer/check_dependencies", servletFactory, "CheckDependenciesServlet");
    mapping->addServletMapping("/installer/create_server", servletFactory, "CreateServerServlet");
    mapping->addServletMapping("/installer/get_url", servletFactory, "GetUrlServlet");

    // TODO Register static resources.
    mapping->addResourcesMapping("/installer", "./Installer/web/");
}

void ModuleManagerImpl::loadAll() {
    LOG(DEBUG) << "Loading all modules.";
    // TODO design
    load("Home");
}

void ModuleManagerImpl::addModule(ModuleStruct module) {
    // TODO design
    modules.push_back(module);
}

void ModuleManagerImpl::addModuleObjectFactory(string moduleName, IModuleObjectFactory* moduleFactory) {
    // TODO design
    factoryMap[moduleName] = moduleFactory;
}
