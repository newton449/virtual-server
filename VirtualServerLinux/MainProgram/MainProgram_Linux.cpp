#include "../../VirtualServerWindows/MainProgram/MainProgram.h"
#include <signal.h>
#include "../../VirtualServerWindows/MainProgram/HttpServer.h"

void sigintHandler(int sig) { // can be called asynchronously
    LOG(INFO) << "The user wants to close server.";
    // shutdown server
    HttpServer* server = (HttpServer*) MainObjectFactoryImpl::getInstance()->getObject("HttpServer");
    if (server != NULL) {
        server->stop();
    } else {
        LOG(WARNING) << "Failed to get server instance from factory.";
    }
}

bool MainProgram::setupInterruptHandler() {
    struct sigaction old_action;
    struct sigaction action;
    memset(&action, 0, sizeof (action));
    action.sa_handler = &sigintHandler;
    sigaction(SIGINT, &action, &old_action);
    return true;
}

std::string MainProgram::getLoggingConfigFilePath() {
    return "./_config/easylogging_Linux.conf";
}

std::string MainProgram::getCurrentPlatform() {
#if __x86_64__ || __ppc64__
    return "Linux x64";
#else
    return "Linux x32";
#endif
}
