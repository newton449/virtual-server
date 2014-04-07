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
#include "FileSystem.h"

MainProgram::MainProgram(){

}


void MainProgram::launch(){
    // Get an instance of main factory.
    try{
        factory = MainObjectFactoryImpl::getInstance();

        // Create configuration files if they do not exist. 
        checkConfigs();

        // Set up loggers. Then we can use LOG(XXX).
        setupLoggers();

        LOG(INFO) << "Starting Virtual Server.";
    }
    catch (std::exception& ex){
        std::cerr << "Failed to start the server: " << ex.what();
        return;
    }

    try{
        // Load config.xml.
        setupConfigs();

        // Load all modules. It will scan directories in the working directory to find Module.xml.
        setupModules();

        // for shutdown server and abort.
        setupSignalHandler();
    }
    catch (std::exception& ex){
        LOG(ERROR) << "Failed to start the server: " << ex.what();
        return;
    }

    try{
        // Running HTTP server. It will join the HTTP server thread.
        runHttpServer();
    }
    catch (std::exception& ex){
        LOG(ERROR) << "Got exception when running HTTP server: " << ex.what();
        return;
    }
}

void MainProgram::checkConfigs(){
    std::string configPath = StringUtils::fixFilePath("_config/config.xml");
    std::string logfilePath = getLoggingConfigFilePath();

    // Check the directory
    if (!FileSystem::Directory::exists("_config")){
        if (!FileSystem::Directory::create("_config")){
            throw runtime_error("Failed to create dicretory .\\_config\\");
        }
        if (!FileSystem::File::copy(StringUtils::fixFilePath("MainProgram/_config/config.xml"), configPath)){
            throw runtime_error("Failed to create file " + configPath);
        }
        if (!FileSystem::File::copy(StringUtils::fixFilePath(std::string("MainProgram") + FILE_SEPARATOR + logfilePath), logfilePath)){
            throw runtime_error("Failed to create file " + logfilePath);
        }
    }
    else{
        // check individual files
        if (!FileSystem::File::exists(configPath)){
            if (!FileSystem::File::copy(StringUtils::fixFilePath("MainProgram/_config/config.xml"), configPath)){
                throw runtime_error("Failed to create file " + configPath);
            }
        }
        if (!FileSystem::File::exists(logfilePath)){
            if (!FileSystem::File::copy(StringUtils::fixFilePath(std::string("MainProgram") + FILE_SEPARATOR + logfilePath), logfilePath)){
                throw runtime_error("Failed to create file " + logfilePath);
            }
        }
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
    DefaultHttpServletMapping* mapping = factory->getHttpServletMapping();
    // Create a HttpServer.
    int port = StringUtils::parseInt((*map)["MainProgram.httpServerPort"]);
    int threadCount = StringUtils::parseInt((*map)["MainProgram.httpThreadMinCount"]);

    HttpServer* server = new HttpServer(*mapping, port, threadCount);

    // put the server to factory
    factory->setObject("HttpServer", server);

    // Start server.
    server->start();
    server->join();

    // clear
    delete server;
}


// Program entry.
int main(){
    MainProgram program;
    program.launch();
}
