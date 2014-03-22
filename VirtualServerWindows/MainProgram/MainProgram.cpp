/*
  Main Program Entry
  */

#include "HttpServer.h"
#include "MainObjectFactoryImpl.h"

#include <windows.h> 
#include <stdio.h> 

HttpServer* server = NULL;

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		LOG(INFO) << "The user wants to close server.";
		// shutdown server
		if (server != NULL){
			server->stop();
		}
		return(TRUE);

		// CTRL-CLOSE: confirm that the user wants to exit. 
	//case CTRL_CLOSE_EVENT:
	//	// shutdown server
	//	if (server != NULL){
	//		server->stop();
	//	}
	//	return(TRUE);

	//	// Pass other signals to the next handler. 
	//case CTRL_BREAK_EVENT:
	//	Beep(900, 200);
	//	printf("Ctrl-Break event\n\n");
	//	return FALSE;

	//case CTRL_LOGOFF_EVENT:
	//	Beep(1000, 200);
	//	printf("Ctrl-Logoff event\n\n");
	//	return FALSE;

	//case CTRL_SHUTDOWN_EVENT:
	//	Beep(750, 500);
	//	printf("Ctrl-Shutdown event\n\n");
	//	return FALSE;

	default:
		return FALSE;
	}
}

int main(int argc, char* argv[]){
	MainObjectFactoryImpl* factory = MainObjectFactoryImpl::getInstance();

	// Load configuration from file
#ifdef WIN32
	el::Configurations conf("./_config/easylogging_Windows.conf");
#else
	el::Configurations conf("./_config/easylogging_Linux.conf");
#endif
	// Reconfigure single logger
	el::Loggers::reconfigureLogger("default", conf);
	// Set logging storage
	factory->setObject("LoggingStorage", &el::Helpers::storage());

	LOG(INFO) << "Starting server.";

	// Load all modules
	ModuleManagerImpl* moduleManager = (ModuleManagerImpl*)factory->getModuleManager();
	moduleManager->loadAll();

	// for shutdown server
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)){
		printf("\nERROR: Could not set control handler");
		return 1;
	}

	// Create a HttpServer.
	AggregateHttpServletMapping* mapping = factory->getAggregateHttpServletMapping();
	server = new HttpServer(*mapping, 8080);
	server->start();
	server->join();

	return 0;
}
