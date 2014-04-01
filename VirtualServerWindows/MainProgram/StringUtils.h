#ifndef STRINGUTILS_H
#define STRINGUTILS_H

/////////////////////////////////////////////////////////////////////
//  StringUtils.h - provides opreations for handling strings.      //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2012                                 //
//  Platform:      Windows 8                                       //
//  Application:   CSE687 Pr2, Spring 2013                         //
//  Author:        Sheng Wang                                      //
/////////////////////////////////////////////////////////////////////

/*
Module Operations:
==================
This module provides opreations for handling strings. It can check
whether a string starts with an alphabet or "_", can check whether an
array constains the specific string, can turn a string to lower case,
can split a string into some substrings according to a seperator, and
so on.

Public Interface:
=================
// We need a string.
String token=...
// Chech string's beginning
bool b=StringUtils::isBeginWithAlphabet(token);
// Check string's existing.
b=StringUtils::isStringInArray(token);
// To lower case.
String lower=StringUtils::toLowerCase(token);
// Split the string.
std::vector<String> results=StringUtils::split(token, seperator);
// Fix file name
String fixedFileName=StringUtils::fixFilePath(token);

Build Process:
==============
Required files (all)
- StringUtils.h, StringUtils.cpp

Build commands
- devenv Test_StringUtils.vcxproj /rebuild debug

Maintenance History:
====================
ver 1.0 : 3/14/2013
- first release

*/

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

typedef std::string String;

/////////////////////////////////////////////////////////////////////
// A class which provides some utility methods for handling strings.
class StringUtils
{
    // Handle special file name. Return true if it is special.
    static bool handleSpecialName(String& fileName)
    {
        if (fileName.empty())
        {
            fileName = "";
        }
        else if (fileName == "." || fileName == "..")
        {
            fileName = fileName + "\\";
        }
        else
        {
            return false;
        }
        return true;
    }

    // Remove useless ".\" and "..\" in the file name.
    static void removeCurrentAndParentDirectoryTokens(String& ret)
    {
        std::vector<String> tokens = split(ret, "\\", true);
        int i = 0;
        while (i < (int)tokens.size())
        {
            if (tokens[i] == ".")
            {
                // Remove it
                tokens.erase(tokens.begin() + i);
            }
            else if (tokens[i] == ".." && i != 0 && tokens[i - 1] != "..")
            {
                if (tokens[i - 1].find(":") == String::npos)
                {
                    // Remove the current and the previous.
                    tokens.erase(tokens.begin() + i);
                    i--;
                    tokens.erase(tokens.begin() + i);
                }
                else
                {
                    // Remove the current only.
                    tokens.erase(tokens.begin() + i);
                }
            }
            else
            {
                i++;
            }
        }
        // Merge results.
        ret = "";
        for (auto token : tokens)
        {
            if (!token.empty())
            {
                ret = ret + token + "\\";
            }
        }
    }

public:
    // Return true if the first char of the token is a-z, A-Z or '_'.
    static bool isBeginWithAlphabet(const String& token)
    {
        char c = token[0];
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95)
        {
            return true;
        }
        return false;
    }


    // Return whether the strArray contains the str.
    static bool isStringInArray(const String& str,
        const String strArray[], const size_t& arraySize)
    {
        for (size_t i = 0; i < arraySize; i++)
        {
            if (str == strArray[i])
            {
                return true;
            }
        }
        return false;
    }

    // Return the lower case version of the string.
    static String toLowerCase(const String& str)
    {
        // PENDING couldn't solve utf-8 ro ansi strings.
        String ret = str;
        std::transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
        return ret;
    }

    /// <summary>
    /// Splits the string s on the given delimiter(s) and
    /// returns a list of tokens without the delimiter(s)
    /// </summary>
    /// <param name=s>The string being split</param>
    /// <param name=match>The delimiter(s) for splitting</param>
    /// <param name=removeEmpty>Removes empty tokens from the list</param>
    /// <param name=fullMatch>
    /// True if the whole match string is a match, false
    /// if any character in the match string is a match
    /// </param>
    /// <returns>A list of tokens</returns>
    static std::vector<String> split(const String& s,
        const String& match,
        bool removeEmpty = false,
        bool fullMatch = false)
    {
        typedef String::size_type(String::*find_t)(const String& delim,
            String::size_type offset) const;

        std::vector<String> result;                 // return container for tokens
        String::size_type start = 0,           // starting position for searches
            skip = 1;            // positions to skip after a match
        find_t pfind = &String::find_first_of; // search algorithm for matches
        if (fullMatch)
        {
            // use the whole match string as a key
            // instead of individual characters
            // skip might be 0. see search loop comments
            skip = match.length();
            pfind = &String::find;
        }
        while (start != String::npos)
        {
            // get a complete range [start..end)
            String::size_type end = (s.*pfind)(match, start);
            // null strings always match in string::find, but
            // a skip of 0 causes infinite loops. pretend that
            // no tokens were found and extract the whole string
            if (skip == 0) end = String::npos;
            String token = s.substr(start, end - start);
            if (!(removeEmpty && token.empty()))
            {
                // extract the token and add it to the result list
                result.push_back(token);
            }
            // start the next range
            if ((start = end) != String::npos) start += skip;
        }
        return result;
    }

    // Remove the file name extension of the str and return the result.
    // If the str has no extension, return it directly.
    static String removeFileNameExtension(const String& str)
    {
        size_t pos = str.find_last_of(".");
        if (pos == String::npos)
        {
            return str;
        }
        return str.substr(0, pos);
    }

    // Replace all tokens in the string.
    static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if (from.empty())
            return;
        size_t start_pos = 0;
        while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    // Return true if the fullString ends with the ending.
    static bool hasEnding(std::string const &fullString, std::string const &ending)
    {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
        }
        else {
            return false;
        }
    }
    
    // In Windows, it converts '/' to '\', converts "\\" to "\", remvoes ".\" and
    // merges "..\" and its parentdir. In Linux, it did nothing.
    static String fixFilePath(const String& fileName)
    {
        // TODO do something in Linux
#ifdef WIN32
        String ret = fileName;
        if (handleSpecialName(ret))
        {
            return ret;
        }
        replaceAll(ret, "/", "\\");
        while (ret.find("\\\\") != String::npos)
        {
            replaceAll(ret, "\\\\", "\\");
        }
        // Delete ".\" and merges "..\" and its parentdir.
        removeCurrentAndParentDirectoryTokens(ret);
        // Add "\" at ending if it is a directory.
        bool isEndWithBackslash = fileName[fileName.size() - 1] == '\\' || hasEnding(fileName, "\\.") || hasEnding(fileName, "\\..");
        if ((!ret.empty()) && !isEndWithBackslash)
        {
            ret = ret.substr(0, ret.length() - 1);
        }
        // Add "\" at beginning if it begins with it
        if (fileName[0] == '\\')
        {
            ret = "\\" + ret;
        }
        if (ret.empty())
        {
            return ".\\";
        }
        // If it is like "C:", let it be "C:\"
        if (ret[ret.length() - 1] == ':')
        {
            ret = ret + '\\';
        }
        return ret;
#else
        return fileName;
#endif
    }

    // Similar to fixFilePath(), but it will append a '\\' to the directory path.
    static String fixDirectoryPath(const String& fileName){
        String ret = fixFilePath(fileName);
        if (ret.empty()){
            return ret;
        }
#ifdef WIN32
        if (ret[ret.length() - 1] != '\\'){
            ret += '\\';
        }
#else
        if (ret[ret.length() - 1] != '/'){
            ret += '/';
        }
#endif
        return ret;
    }

    // Returns true if str starts with token.
    static bool startWith(const String& str, const String& token){
        size_t len = token.length();
        if (len > str.length()){
            return false;
        }
        for (size_t i = 0; i < len; i++){
            if (str.at(i) != token.at(i)){
                return false;
            }
        }
        return true;
    }

    static int parseInt(const String& str){
        std::stringstream ss(str);
        int x;
        ss >> x;
        return x;
    }

    static float parseFloat(const String& str){
        std::stringstream ss(str);
        float x;
        ss >> x;
        return x;
    }

    // If the argument is null, return an empty string.
    static inline String NullToEmpty(const char* str){
        if (str == NULL){
            return "";
        }
        else{
            return str;
        }
    }
};

#endif