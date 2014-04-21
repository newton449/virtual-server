#include "../../VirtualServerWindows/Home/HttpServletsImpl.h"
#include <sys/utsname.h>

std::string ServerInfoServlet::getSystemInfo() {
    struct utsname buf;

    int iRet = uname(&buf);
    if (iRet != 0) {
        return "Unknown Linux";
    }

    std::string ret;
    ret += buf.sysname;
    ret += " ";
    ret += buf.nodename;
    ret += " ";
    ret += buf.release;
    ret += " ";
    ret += buf.version;
    ret += " ";
    ret += buf.machine;
    return ret;
}