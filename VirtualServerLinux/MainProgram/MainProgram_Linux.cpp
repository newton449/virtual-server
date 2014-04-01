#include "../../VirtualServerWindows/MainProgram/MainProgram.h"

bool MainProgram::setupInterruptHandler(){
    // TODO
    return true;
}

std::string MainProgram::getLoggingConfigFilePath(){
    return "./_config/easylogging_Linux.conf";
}

std::string MainProgram::getCurrentPlatform(){
#if __x86_64__ || __ppc64__
  return "Linux x64";
#else
  return "Linux x32";
#endif
}
