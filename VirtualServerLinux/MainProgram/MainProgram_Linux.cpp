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

void MainProgram::setupSignalHandler() {
    struct sigaction old_action;
    struct sigaction action;
    memset(&action, 0, sizeof (action));
    action.sa_handler = &sigintHandler;
    if (0 != sigaction(SIGINT, &action, &old_action)) {
        throw std::runtime_error("Failed to set up singal handler.");
    }
}

std::string MainProgram::getLoggingConfigFilePath() {
    return "./_config/easylogging_Linux.conf";
}

std::string MainProgram::getCurrentPlatform() {
#if __x86_64__ || __ppc64__
    return "Linux x64";
#else
    return "Linux x86";
#endif
}
