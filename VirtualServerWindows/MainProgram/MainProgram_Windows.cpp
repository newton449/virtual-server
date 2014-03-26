#include "HttpServer.h"
#include "MainProgram.h"
#include <stdio.h> 
#include "../interfaces/ILogger.h"
#include "MainObjectFactoryImpl.h"
#include <windows.h> 

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	HttpServer* server;
	switch (fdwCtrlType)
	{
		// Handle the CTRL-C signal. 
	case CTRL_C_EVENT:
		LOG(INFO) << "The user wants to close server.";
		// shutdown server
		server = (HttpServer*)MainObjectFactoryImpl::getInstance()->getObject("HttpServer");
		if (server != NULL){
			server->stop();
		}
		else{
			LOG(WARNING) << "Failed to get server instance from factory.";
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

bool setupInterruptHandler(){
	if (!SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE)){
		LOG(ERROR) << "Could not set control handler";
		return false;
	}
	return true;
}

std::string getLoggingConfigFilePath(){
    return "./_config/easylogging_Windows.conf";
}