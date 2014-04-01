#include "AggregateHttpServletMapping.h"
#include "HttpServletsImpl.h"
#include "Logger.h"

IHttpServlet* AggregateHttpServletMapping::createServlet(const string& url){
    LOG(TRACE) << "Creating a servlet for url :" << url;

    // try to find a specific servlet
    unordered_map<string, pair<IServletFactory*, string> >::iterator iter = servletMap.find(url);
    if (iter != servletMap.end()){
        LOG(TRACE) << "Found servlet mapping: " << iter->second.second;
        return iter->second.first->createInstance(iter->second.second);
    }

    // get context path from url
    string contextPath;
    size_t pos = url.find('/', 1);
    if (pos < url.length()){
        contextPath = url.substr(0, pos);
    }

    // try to find resource mapping
    unordered_map<string, string>::iterator it = resourceMap.find(contextPath);
    if (it != resourceMap.end()){
        LOG(TRACE) << "Found static resource mapping: " << it->second;
        return new StaticResourcesServlet(contextPath, it->second);
    }

    // try to find resource mapping for empty contextPath. The url may does not have context path.
    unordered_map<string, string>::iterator it2 = resourceMap.find("");
    if (it2 != resourceMap.end()){
        LOG(TRACE) << "Found static resource mapping for empty context path.";
        return new StaticResourcesServlet("", it2->second);
    }


    // nothing found
    LOG(DEBUG) << "Failed to find a servlet. Returning NULL.";
    return NULL;
}

void AggregateHttpServletMapping::addServletMapping(const string& url, IServletFactory* servletFactory,
    const string& servletName){
    pair<IServletFactory*, string> pair;
    pair.first = servletFactory;
    pair.second = servletName;
    servletMap[url] = pair;
    LOG(TRACE) << "Added servlet mapping: " << url << " -> " << servletName;
}

void AggregateHttpServletMapping::addResourcesMapping(const string& contextPath, const string& directory){
    resourceMap[contextPath] = directory;
    LOG(TRACE) << "Added static resources mapping: " << (contextPath.empty() ? "[]" : contextPath) << " -> " << directory;
}