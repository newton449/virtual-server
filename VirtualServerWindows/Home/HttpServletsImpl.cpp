#include <fstream>
#include <string.h>
#include <stdexcept>
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
    char buf[100];
    std::istream& in = request.getInputStream();
    in.get(buf, 100, '\n');
    LOG(DEBUG) << "Got: " << buf;
    in.get(buf, 100, '\n');
    LOG(DEBUG) << "Got: " << buf;
    std::ostream& out = response.getOutputStream();
    // TODO platform
    out << "{\n"
#ifdef WIN32
        << "    \"platformInfo\": \"Windows 8 v6.2 on amd64; en_US\",\n"
#else
        << "    \"platformInfo\": \"Linux debian 3.2.0 on amd64; en_US\",\n"
#endif
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

void UploadingServlet::doMethod(IHttpServletRequest& request, IHttpServletResponse& response){
    UploadingHandler handler;
    handler.handleRequestBody(request);
}

std::string UploadingHandler::getTempDirectory(){
    return tempDirectory;
}

void UploadingHandler::setTempDirectory(std::string dir){
    tempDirectory = dir;
}

void UploadingHandler::handleRequestBody(IHttpServletRequest& request){
    std::string boundary = getBoundary(request);
    boundary += '\r';
    // get first boundary
    istream& in = request.getInputStream();
    char line[1000];
    in.getline(line, 1000);
    if (strcmp(line, boundary.c_str()) != 0){
        throw std::runtime_error("Failed to parse request: expect boundary.");
    }
    while (true){
        // parse header
        std::map<std::string, std::string> headers = parseHeaders(in);
        std::string disposition = headers["Content-Disposition"];
        std::map<std::string, std::string> dispositionMap = parseDisposition(disposition);

        // parse content
        if (dispositionMap.find("filename") == dispositionMap.end()){
            // parse normal data
            std::string value;
            bool skipR = false;
            bool firstLoop = true;
            while (true){
                in.get(line, 1000, '\n');
                if (strcmp(line, boundary.c_str()) == 0){
                    // reach boundary, end.
                    in.get(); // for \n
                    break;
                }
                else if (!in){
                    throw std::runtime_error("Failed to parse field value: unexpected eof.");
                }
                else{
                    if (skipR){
                        value += '\r';
                        skipR = false;
                    }
                    if (firstLoop){
                        firstLoop = false;
                    }
                    else{
                        value += '\n';
                    }
                    if (line[in.gcount() - 1] == '\r'){
                        skipR = true;
                        line[in.gcount() - 1] = '\0';
                        value += line;
                    }
                    else{
                        value += line;
                    }
                    in.get();
                }
            }

            // save data
            fieldMap[dispositionMap["name"]] = value;
        }
        else{
            // parse file data
            ofstream fout("temp.bin", ofstream::out | ofstream::binary);
            bool skipR = false;
            bool firstLoop = true;
            while (true){
                in.get(line, 1000, '\n');
                if (line == (boundary.substr(0, boundary.length() - 1) + "--\r")){
                    // reach boundary, end.
                    in.get(); // for \n
                    fout.close();
                    return;
                }
                else if (!in){
                    throw std::runtime_error("Failed to parse field value: unexpected eof.");
                }
                else{
                    if (skipR){
                        fout.put('\r');
                        skipR = false;
                    }
                    if (firstLoop){
                        firstLoop = false;
                    }
                    else{
                        fout.put('\n');
                    }
                    if (line[in.gcount() - 1] == '\r'){
                        skipR = true;
                        fout.write(line, in.gcount() - 1);
                    }
                    else{
                        fout.write(line, in.gcount());
                    }
                    in.get(); // for \n
                }
            }
        }
    }
}

std::string UploadingHandler::getBoundary(IHttpServletRequest& request){
    // parse Content-Type to get boundary
    std::string headerValue = request.getHeader("Content-Type");
    size_t semicolonPos = headerValue.find_first_of(';');
    if (semicolonPos == std::string::npos){
        throw std::runtime_error("Failed to parse request: not a valid header for uploading.");
    }
    size_t equalSignPos = headerValue.find_first_of('=', semicolonPos);
    if (equalSignPos == std::string::npos){
        throw std::runtime_error("Failed to parse request: not a valid header for uploading.");
    }
    std::string shortType = headerValue.substr(0, semicolonPos);
    std::string boundaryName = headerValue.substr(semicolonPos + 1, equalSignPos - semicolonPos - 1);
    std::string boundary = "--" + headerValue.substr(equalSignPos + 1);
    if (shortType != "multipart/form-data"){
        throw std::runtime_error("Failed to parse request: not a valid header for uploading.");
    }
    if (boundaryName != "boundary" && boundaryName != " boundary"){
        throw std::runtime_error("Failed to parse request: not a valid header for uploading.");
    }
    return boundary;

}

std::map<std::string, std::string> UploadingHandler::parseHeaders(istream& in){
    std::map<std::string, std::string> ret;
    char line[1000];
    in.getline(line, 1000);
    while (in.gcount() > 0 && line[0] != '\r'){
        std::string str = line;
        int length = str.length();
        int pos = str.find_first_of(':');
        if (pos >= length - 1){
            throw std::runtime_error("Failed to parse header: no comma");
        }
        std::string name = str.substr(0, pos);
        std::string value = str[pos + 1] == ' ' ? str.substr(pos + 2, length - pos - 2) : str.substr(pos + 1, length - pos - 1);
        if ((!value.empty()) && value[value.length() - 1] == '\r'){
            value = value.substr(0, value.length() - 1);
        }
        ret[name] = value;
        in.getline(line, 1000);
    }
    return ret;
}

std::map<std::string, std::string> UploadingHandler::parseDisposition(std::string headerValue){
    std::map<std::string, std::string> ret;
    // check "form-data"
    size_t pos = headerValue.find(';');
    std::string type = headerValue.substr(0, pos);
    if (type != "form-data"){
        throw std::runtime_error("Failed to parse header: expect \"form-data\"");
    }

    // 
    while (true){
        size_t next = headerValue.find(';', pos + 1);
        if (next != std::string::npos){
            std::string field = headerValue.substr(pos + 1, next - pos - 1);
            size_t sepa = field.find_first_of('=');
            ret[field.substr(1, sepa - 1)] = field.substr(sepa + 2, field.length() - sepa - 3);
            pos = next;
        }
        else{
            std::string field = headerValue.substr(pos + 1);
            size_t sepa = field.find_first_of('=');
            ret[field.substr(1, sepa - 1)] = field.substr(sepa + 2, field.length() - sepa - 3);
            break;
        }
    }
    return ret;
}
