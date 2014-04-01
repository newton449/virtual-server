#pragma once

#include <string>
#include <stdexcept>
#include "tinyxml2.h"

// check whether a XMLElement "NODE" is null. If it is, throw an InvalidFormatException.
#define CHECK_NODE(NODE, NAME) if(NODE==NULL) throw InvalidFormatException(std::string("Failed to get node: ") + NAME);
// check whether a string "STR" is empty. If it is, throw an InvalidFormatException.
#define CHECK_EMPTY(STR, NAME) if(STR.empty()) throw InvalidFormatException(std::string("The tag cannnot be empty: ") + NAME);
// check whether a XMLElement "NODE" has a expected name. If it is not, throw an InvalidFormatException.
#define EXPECT_NODE(NODE, NAME) if(NODE->Name()!=std::string(NAME)) throw InvalidFormatException(std::string("Expected tag \"")+NAME+"\" but got \""+NODE->Name()+"\"");

// In the ISO C++11 Standard, the noexcept operator is introduced, but support
// for this feature is not yet present in Visual C++.
#ifndef NOEXCEPT
#ifdef WIN32
#define NOEXCEPT throw()
#else
#define NOEXCEPT noexcept(true)
#endif
#endif

// An exception, thrown when XML format is invalid or does not contain expected contents.
class InvalidFormatException : public std::logic_error{
public:
    explicit InvalidFormatException(const std::string& what_arg)
        : std::logic_error(what_arg)
    {}

    virtual ~InvalidFormatException() NOEXCEPT{}
};