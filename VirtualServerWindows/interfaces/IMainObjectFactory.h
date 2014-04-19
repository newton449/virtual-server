///////////////////////////////////////////////////////////////////////////////
//  IMainObjectFactory.h - an factory interface to provide objects of        //
//                         MainProgram.                                      //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module contains an factory interface to provide objects of MainProgram. 
For example, callers can get instances of IModuleManager and IClientManager
implemented by MainProgram. Callers can also get objects and set objects 
themselves. It is a way to share objects between DLL modules.

MainProgram will provide an implementation of IMainObjectFactory with some 
implementations of interfaces. When loading a DLL module, it will be passed
to the module's loading function so that the module can retreive objects from
MainProgram.

Callers can set objects with keys. However, if a key already exists, the
factory cannot set new object because it does not know how to delete the old
object. So callers should get old objects by replaceObject() and delete them
manually.

Main Class:
===========
- IMainObjectFactory : an factory interface to provide objects of MainProgram


Public Interface:
=================
// Get an instance when DLL module is loaded
IMainObjectFactory* pFactory = ...;
// Get predefined objects
IModuleManager* pManager = pFactory->getModuleManager();
// Get non-predefined objects
ClassType* pObject = (ClassType*) pFactory->getObject("ObjectKey");
// Use replaceObject() to set object and delete old one
ClassType* newObject = ...;
ClassType* oldObject = (ClassType*) pFactory->replaceObject("ObjectKey", newObject);
if(oldObject != NULL){
    delete oldObject;
}

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

#include <string>
#include <map>
#include "IModuleManager.h"
#include "IClientManager.h"
#include "ILogger.h"

// An object factory, provided by MainProgram for every module to use.
//
// It shall be thread-safe.
class IMainObjectFactory {
public:
    // Destructor.
    virtual ~IMainObjectFactory() {}

    // Returns an object by key. Do not delete the object.
    virtual void* getObject(const std::string& key) = 0;

    // Sets an object with its key. If the key already exists, the old one
    // cannot be deleted because it does not know its type, and a logic_error
    // will be thrown.
    virtual void setObject(const std::string& key, void* object) = 0;

    // Sets an object with its key and returns the old object. The object can be
    // NULL. It is useful to delete old object.
    virtual void* replaceObject(const std::string& key, void* object) = 0;

    // Removes an object by its key and returns the removed object. Note:
    // remember to delete the object.
    virtual void* removeObject(const std::string& key) = 0;

    // Returns an instance of IModuleManager. It can also be get by
    // getObject("IModuleManager").
    virtual IModuleManager* getModuleManager() = 0;

    // Returns an instance of IClientManager. It can also be get by
    // getObject("IClientManager").
    virtual IClientManager* getClientManager() = 0;

    // Returns an property map of configurations. It can also be get by
    // getObject("PropertyMap").
    virtual std::map<std::string, std::string>* getPropertyMap() = 0;
};
