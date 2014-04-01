#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"
#include "../interfaces/IClientManager.h"
#include "ModuleObjectFactoryImpl.h"

void RedirectToHomeServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    response.setStatus(302);
    response.addHeader("Location", "/home/");
    // PENDING In HTTP documents:
    // "Unless the request method was HEAD, the entity of the response SHOULD contain a short hypertext note with a hyperlink to the new URI(s)."
}

void MenuListServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    LOG(TRACE) << "Sending menu list.";
    std::ostream& out = response.getOutputStream();
    out << "{"
        << "  \"menu\":"
        << "    [";
    // get menu list
    IClientManager* manager = ModuleObjectFactoryImpl::getInstance()->getMainObjectFactory()->getClientManager();
    vector<ClientMenuItem> items = manager->getMenuItems();
    for (size_t i = 0; i < items.size(); i++){
        out << "{ \"name\": \"" << items[i].name << "\", \"url\": \"" << items[i].url << "\"";
        // title is optional
        if (!items[i].description.empty()){
            out << ", \"title\": \"" << items[i].description << "\"";
        }
        out << "}";
        if (i != items.size() - 1){
            out << ",";
        }
    }
    out << "]}";
    // such as
    //<< "{"
    //<< "  \"menu\":"
    //<< "    ["
    //<< "      { \"name\": \"Home\", \"url\": \"/home/#\" }, "
    //<< "      { \"name\": \"Clone\", \"url\": \"/installer/#\", \"title\": \"Create a local server in your machine.\" }, "
    //<< "      { \"name\": \"About\", \"url\": \"/home/#about\" } "
    //<< "    ]"
    //<< "}";
}

void ServerInfoServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    LOG(TRACE) << "Sending menu list.";
    std::ostream& out = response.getOutputStream();
    // TODO platform
    out << "{\n"
        << "    \"platformInfo\": \"Windows 8 v6.2 on amd64; en_US\",\n"
        << "    \"items\": [\n";
    // get module list
    IModuleManager* manager = ModuleObjectFactoryImpl::getInstance()->getMainObjectFactory()->getModuleManager();
    vector<ModuleStruct> items = manager->getModules();
    for (size_t i = 0; i < items.size(); i++){
        out << "{ \"name\": \"" << items[i].displayName << "\","
            << "\"description\": \"" << items[i].description << "\", "
            << "\"state\": \"" << manager->getModuleState(items[i].name) << "\"}";
        if (i != items.size() - 1){
            out << ",";
        }
    }
    out << "    ]\n"
        << "}";
    //<< "{\n"
    //    << "    \"platformInfo\": \"Windows 8 v6.2 on amd64; en_US\",\n"
    //    << "    \"items\": [\n"
    //    << "        {\n"
    //    << "            \"name\": \"Main Program\",\n"
    //    << "            \"description\": \"The main server program.\",\n"
    //    << "            \"state\": \"Running\"\n"
    //    << "        },\n"
    //    << "        {\n"
    //    << "            \"name\": \"Home\",\n"
    //    << "            \"description\": \"Provids default HTML pages.\",\n"
    //    << "            \"state\": \"Running\"\n"
    //    << "        },\n"
    //    << "        {\n"
    //    << "            \"name\": \"Installer\",\n"
    //    << "            \"description\": \"Allows others to clone your server.\",\n"
    //    << "            \"state\": \"Running\"\n"
    //    << "        }\n"
    //    << "    ]\n"
    //    << "}";
}