#ifndef UTILITIES_H
#define UTILITIES_H
/////////////////////////////////////////////////////////////////////
// Utilities.h -  Provides useful resources                        //
// ver 1.0                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides basic utilities.  In this version only a type
   conversion function is provided.

*/
//
/*
   Build Process:
   ==============
   Required Files:
     Utilities.h, Utilities.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_UTILITIES Utilities.cpp

   Maintenance History:
   ====================
   ver 1.0 : 23 Apr 12
   - first release

   Planned Changes:
   ================
   - 
*/
#include <string>
#include <sstream>

template <typename T>
std::string ToString(const T& t)
{
  std::ostringstream out;
  out << t;
  return out.str();
}
#endif
