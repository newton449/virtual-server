///////////////////////////////////////////////////////////////////////////////
//  IHttpServletMapping.h - an interfaces to to create servlets according to //
//                          URLs.                                            //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module provides an interfaces to to create servlets according to URLs. The
underlying implementation shall create an instance of IHttpServlet for every
URL asked. The caller should delete the servlet instance. 

The typicall usages are to create an implementation of IHttpServletMapping, and
provide it to a http server object. Then the http server object can get servlet
instances by this IHttpServletMapping.

Main Class:
===========
- IHttpServletMapping: An interface to create servlets according to URLs. 

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

#include <string>
#include "IHttpServlet.h"

// An interface to create servlets according to URLs. 
//
// This interface shall be thread-safe.
class IHttpServletMapping{
public:
	// Destructor
	virtual ~IHttpServletMapping() {}

	// Returns an IHttpServlet according to the url. The caller should delete
    // the instance. If no servlet can handle this URL, returns null.
	virtual IHttpServlet* createServlet(const std::string& url) = 0;
};
