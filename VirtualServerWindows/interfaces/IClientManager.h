///////////////////////////////////////////////////////////////////////////////
//  IClientManager.h - provide an interface to manage client's information.  //
//  ver 0.9                                                                  //
//  Language:      Visual C++ 2013 & gcc 4.7.2                               //
//  Platform:      Windows 8       & Linux Debian 3.2 x86_x64                //
//  Application:   CSE775 Final Project, Spring 2014                         //
//  Author:        Sheng Wang, Qiuyong Yang, Bei Li                          //
///////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module provides an interface "IClientManager" to manage client's
information. It stores a list of menu items which are showed in client's pages
for navigation. Callers can add an menu item to the list, and retreive the
whole list.

MainProgram will provide an implementation of IClientManager with loaded menu
items from configuration files so that other modules can retreive the menu
list.

Main Class:
===========
- IClientManager : an interface to manage client's information

Other Class:
============
- ClientMenuItem : a data structure for client's information.

Public Interface:
=================
// Get an instance from object factory of MainProgram
IClientManager* pInstance = someFactory->getClientManager();
// Get the list of menu items
vector<ClientMenuItem> vec = pInstance->getMenuItems();

Maintenance History:
====================
ver 0.9 : 4/18/2013
- first commented

*/
#pragma once

#include <string>
#include <vector>

// A data struct to store a menu item. It will be used by user to navigate
// between client pages.
struct ClientMenuItem{
    // the name, showed in the body of "a" tag. No HTML.
    std::string name;

    // the description, showed in "title" attribute of "a" tag. No HTML.
    std::string description;

    // the URL, used in "href" attribute of "a" tag. It may contain "#".
    std::string url;

    // the number to decide order of items. The smaller, the fronter.
    float orderNumber;
};

// An interface to manage data for clients. Callers can add menu items or
// retreive a list of whole menu items.
//
// It shall be thread-safe.
class IClientManager{
public:
    // Destructor.
    virtual ~IClientManager() {}

    // Adds a menu item. The item will be put in the list with the right order
    // decided by its orderNumber. No duplication will be checked.
    virtual void addMenuItem(ClientMenuItem item) = 0;

    // Returns a list of all menu items. The items are already in their order
    // decided by their orderNumbers. They are returned "by value" so that it
    // is safe to change it without affecting original ones.
    virtual std::vector<ClientMenuItem> getMenuItems() = 0;
};
