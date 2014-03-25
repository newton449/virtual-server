/*
  Main Program Entry
  */

#include "HttpServer.h"
#include "MainObjectFactoryImpl.h"
#include "MainProgram.h"

// Program entry.
int main(){
	LOG(INFO) << "Starting Virtual Server.";

	MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();

	// Load configuration from file
	el::Configurations conf("./_config/easylogging.conf");
	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);
	// Set logging storage
	factory->setObject("LoggingStorage", &el::Helpers::storage());


	// Load all modules
	ModuleManagerImpl* moduleManager = (ModuleManagerImpl*)factory->getModuleManager();
	moduleManager->loadAll();

	// for shutdown server
	if (!setupInterruptHandler()){
		return EXIT_FAILURE;
	}

	// Create a HttpServer.
	AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
	HttpServer* server = new HttpServer(*mapping, 8080);

	// put the server to factory
	factory->setObject("HttpServer", factory);

	// Start server.
	server->start();
	server->join();

	return 0;
}
