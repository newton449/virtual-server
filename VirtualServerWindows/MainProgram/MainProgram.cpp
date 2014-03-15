/*
  Main Program Entry
  */

#include "HttpServer.h"
#include "MainObjectFactoryImpl.h"

int main(){
	MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();

	// Load configuration from file
	el::Configurations conf("./_config/easylogging.conf");
	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);
	// Set logging storage
	factory->setObject("LoggingStorage", &el::Helpers::storage());

	LOG(INFO) << "Starting server.";

	// Load all modules
	ModuleManagerImpl* moduleManager = (ModuleManagerImpl*)factory->getModuleManager();
	moduleManager->loadAll();

	// Create a HttpServer.
	AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
	HttpServer* server = new HttpServer(*mapping, 8080);
	server->start();
	server->join();

	return 0;
}
