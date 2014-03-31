#include "HttpServletsImpl.h"
#include "../interfaces/ILogger.h"

void RedirectToHomeServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    response.setStatus(302);
    response.addHeader("Location", "/home/");
    // PENDING In HTTP documents:
    // "Unless the request method was HEAD, the entity of the response SHOULD contain a short hypertext note with a hyperlink to the new URI(s)."
}

void MenuListServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    // TODO design
    LOG(INFO) << "Module can log!";
    response.getOutputStream()
        << "{"
        << "  \"menu\":"
        << "    ["
        << "      { \"name\": \"Home\", \"url\": \"/home/#\" }, "
        << "      { \"name\": \"Clone\", \"url\": \"/installer/#\", \"title\": \"Create a local server in your machine.\" }, "
        << "      { \"name\": \"About\", \"url\": \"/home/#about\" } "
        << "    ]"
        << "}";
}

void ServerInfoServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    response.getOutputStream()
        << "{\n"
        << "    \"platformInfo\": \"Windows 8 v6.2 on amd64; en_US\",\n"
        << "    \"items\": [\n"
        << "        {\n"
        << "            \"name\": \"Main Program\",\n"
        << "            \"description\": \"The main server program.\",\n"
        << "            \"state\": \"Running\"\n"
        << "        },\n"
        << "        {\n"
        << "            \"name\": \"Home\",\n"
        << "            \"description\": \"Provids default HTML pages.\",\n"
        << "            \"state\": \"Running\"\n"
        << "        },\n"
        << "        {\n"
        << "            \"name\": \"Installer\",\n"
        << "            \"description\": \"Allows others to clone your server.\",\n"
        << "            \"state\": \"Running\"\n"
        << "        }\n"
        << "    ]\n"
        << "}";
}