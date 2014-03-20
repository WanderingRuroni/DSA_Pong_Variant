/**
 * Convenience typedefs.
 *
 * @author Peter B. Tummillo
 */

#ifndef TYPES_H
#define TYPES_H


// Turn off compiler warnings about disabled exceptions
#pragma warning( disable : 4530 )


#include <string>
#include <vector>


// Primitive types
typedef unsigned char      BYTE;
typedef short              INT16;
typedef unsigned short     UINT16;
typedef unsigned int       UINT;
typedef unsigned long      DWORD;
typedef long long          INT64;
typedef unsigned long long UINT64;
typedef wchar_t            WCHAR;

// String types
typedef std::string  string;
typedef std::wstring wstring;

// List types
typedef std::vector<string> StringList;


#endif // TYPES_H
