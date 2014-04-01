/*
  Main Program Entry
  */

#include "HttpServer.h"
#include "MainProgram.h"
#include "MainObjectFactoryImpl.h"
#include "MainProgram.h"
#include "XMLDocument.h"
#include "StringUtils.h"
#include <unordered_set>

MainProgram::MainProgram(){

}


void MainProgram::launch(){

    factory = MainObjectFactoryImpl::getInstance();
    
    setupLoggers();

    LOG(INFO) << "Starting Virtual Server.";

    try{

        setupConfigs();

        setupModules();

        // for shutdown server
        if (!setupInterruptHandler()){
            LOG(WARNING) << "Failed to set up interrupt hander. Ignored it.";
        }

        runHttpServer();
    }
    catch (std::exception& ex){
        LOG(ERROR) << "Failed to start the server: " << ex.what();
    }
}

void MainProgram::setupLoggers(){
    // Load configuration from file
    el::Configurations conf(getLoggingConfigFilePath());
    // Reconfigure single logger
    el::Loggers::reconfigureLogger("default", conf);
    // Set logging storage so that modules can get it.
    factory->setObject("LoggingStorage", new el::base::type::StoragePointer(el::Helpers::storage()));
}


void MainProgram::setupConfigs(){
    PropertyMap* map = factory->getPropertyMap();
    // Set system property.
    (*map)["system.currentPlatform"] = getCurrentPlatform();

    // properties in config.xml cannot be overrided by Module.xml
    // so we use primaryKeys to keep those keys
    std::unordered_set<std::string>* primaryKeys = new std::unordered_set<std::string>();

    // Load config.xml
    LOG(DEBUG) << "Loading config.xml.";
    tinyxml2::XMLDocument config;
    config.LoadFile(StringUtils::fixFilePath("./_config/config.xml").c_str());
    if (config.Error()){
        throw InvalidFormatException("Failed to parse config.xml");
    }
    // parse <config>
    tinyxml2::XMLElement* root = config.FirstChildElement("config");
    CHECK_NODE(root, "config");
    // parse <properties>
    tinyxml2::XMLElement* properties = root->FirstChildElement("properties");
    if (properties != NULL){
        // parse elem such as <main.httpServerPort>8080</main.httpServerPort>
        tinyxml2::XMLElement* prop = properties->FirstChildElement();
        while (prop != NULL){
            (*map)[prop->Name()] = StringUtils::NullToEmpty(prop->GetText());
            primaryKeys->insert(prop->Name());
            prop = prop->NextSiblingElement();
        }
    }
    factory->setObject("primaryKeys", primaryKeys);

    LOG(DEBUG) << "Finished loading config.xml.";
}

void MainProgram::setupModules(){
    // Load all modules
    ModuleManagerImpl* moduleManager = (ModuleManagerImpl*)factory->getModuleManager();
    moduleManager->loadAll();
}

void MainProgram::runHttpServer(){
    PropertyMap* map = factory->getPropertyMap();
    AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
    // Create a HttpServer.
    int port = StringUtils::parseInt((*map)["MainProgram.httpServerPort"]);
    int threadCount = StringUtils::parseInt((*map)["MainProgram.httpThreadMinCount"]);
    HttpServer* server = new HttpServer(*mapping, port, threadCount);

    // put the server to factory
    factory->setObject("HttpServer", server);

    // Start server.
    server->start();
    server->join();
}


// Program entry.
int main(){
    MainProgram program;
    program.launch();
}
