/*
  Main Program Entry
  */

#include "HttpServer.h"
#include "MainObjectFactoryImpl.h"
#include "MainProgram.h"
#include "XMLDocument.h"
#include "StringUtils.h"

// Program entry.
int main(){

    MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();

    // Load configuration from file
    el::Configurations conf(getLoggingConfigFilePath());
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Set logging storage
    factory->setObject("LoggingStorage", new el::base::type::StoragePointer(el::Helpers::storage()));

    LOG(INFO) << "Starting Virtual Server.";

    // Load config.xml
    PropertyMap* map = factory->getPropertyMap();
    tinyxml2::XMLDocument config;
    config.LoadFile("./_config/config.xml");
    tinyxml2::XMLElement* root = config.FirstChildElement("config");
    tinyxml2::XMLElement* properties = root->FirstChildElement("properties");
    tinyxml2::XMLElement* prop = properties->FirstChildElement();
    while (prop != NULL){
        (*map)[prop->Name()] = prop->GetText();
        prop = prop->NextSiblingElement();
    }

    // TODO set system property
    (*map)["sys.currentPlatform"] = "Windows";

    // Mapping static resources in config.xml
    AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
    tinyxml2::XMLElement* resources = root->FirstChildElement("staticResources");
    if (resources != NULL){
        tinyxml2::XMLElement* res = resources->FirstChildElement();
        while (res != NULL){
            const char* dir = res->FirstChildElement("directory")->GetText();
            tinyxml2::XMLElement* contextElem = res->FirstChildElement("contextPath");
            const char* context = contextElem->GetText();
            mapping->addResourcesMapping(context==NULL ? "" : context, dir);
            res = res->NextSiblingElement();
        }
    }

    // Load all modules
    ModuleManagerImpl* moduleManager = (ModuleManagerImpl*)factory->getModuleManager();
    moduleManager->loadAll();

    // for shutdown server
    if (!setupInterruptHandler()){
        return EXIT_FAILURE;
    }

    // Create a HttpServer.
    int port = StringUtils::parseInt((*map)["main.httpServerPort"]);
    int threadCount = StringUtils::parseInt((*map)["main.httpThreadMinCount"]);
    HttpServer* server = new HttpServer(*mapping, port, threadCount);

    // put the server to factory
    factory->setObject("HttpServer", factory);

    // Start server.
    server->start();
    server->join();

    return 0;
}
