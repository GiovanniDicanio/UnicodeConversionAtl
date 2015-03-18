//////////////////////////////////////////////////////////////////////////////
//
// *** Functions to convert between Unicode UTF-8 and Unicode UTF-16 ***
//                      using ATL CStringA/W classes
//
// By Giovanni Dicanio 
//
//
// FILE: UnicodeConvAtl.cpp
//
// DESCRIPTION: 
// 
// Implementation of the conversion functions.
//
//////////////////////////////////////////////////////////////////////////////


#include "UnicodeConvAtl.h"     // Module header
#include <Windows.h>            // For Windows Platform SDK


namespace win32
{


//----------------------------------------------------------------------------
// FUNCTION: Utf8ToUtf16
// DESC:     Converts Unicode UTF-8 text to Unicode UTF-16 (Windows default).
//----------------------------------------------------------------------------
CStringW Utf8ToUtf16(const CStringA& utf8)
{
    // Special case of empty input string
    if (utf8.IsEmpty())
    {
        // Return empty string
        return CStringW();
    }


    // "Code page" value used with MultiByteToWideChar() for UTF-8 conversion 
    const UINT codePageUtf8 = CP_UTF8;

    // Safely fails if an invalid UTF-8 character is encountered
    const DWORD flags = MB_ERR_INVALID_CHARS;

    // Get the length, in WCHARs, of the resulting UTF-16 string
    const int utf16Length = ::MultiByteToWideChar(
            codePageUtf8,       // source string is in UTF-8
            flags,              // conversion flags
            utf8.GetString(),   // source UTF-8 string
            utf8.GetLength(),   // length of source UTF-8 string, in chars
            nullptr,            // unused - no conversion done in this step
            0);                 // request size of destination buffer, in WCHARs           
    if (utf16Length == 0)
    {
        // Conversion error
        AtlThrowLastWin32();
    }


    // Allocate destination buffer to store the resulting UTF-16 string
    CStringW utf16;
    WCHAR* const utf16Buffer = utf16.GetBuffer(utf16Length);
    ATLASSERT(utf16Buffer != nullptr);


    // Do the conversion from UTF-8 to UTF-16
    int result = ::MultiByteToWideChar(
            codePageUtf8,       // source string is in UTF-8
            flags,              // conversion flags
            utf8.GetString(),   // source UTF-8 string
            utf8.GetLength(),   // length of source UTF-8 string, in chars
            utf16Buffer,        // pointer to destination buffer
            utf16Length);       // size of destination buffer, in WCHARs           
    if (result == 0)
    {
        // Conversion error
        AtlThrowLastWin32();
    }

    // Don't forget to release internal CString buffer 
    // before returning the string to the caller
    utf16.ReleaseBufferSetLength(utf16Length);

    // Return resulting UTF-16 string
    return utf16;
}



//----------------------------------------------------------------------------
// FUNCTION: Utf16ToUtf8
// DESC:     Converts Unicode UTF-16 (Windows default) text to Unicode UTF-8.
//----------------------------------------------------------------------------
CStringA Utf16ToUtf8(const CStringW& utf16)
{
    // Special case of empty input string
    if (utf16.IsEmpty())
    {
        // Return empty string
        return CStringA();
    }


    // "Code page" value used with WideCharToMultiByte() for UTF-8 conversion 
    const UINT codePageUtf8 = CP_UTF8;

    // Safely fails if an invalid UTF-16 character is encountered
    const DWORD flags = WC_ERR_INVALID_CHARS;

    // Get the length, in chars, of the resulting UTF-8 string
    const int utf8Length = ::WideCharToMultiByte(
            codePageUtf8,       // convert to UTF-8
            flags,              // conversion flags
            utf16.GetString(),  // source UTF-16 string
            utf16.GetLength(),  // length of source UTF-16 string, in WCHARs
            nullptr,            // unused - no conversion required in this step
            0,                  // request size of destination buffer, in chars
            nullptr, nullptr);  // unused
    if (utf8Length == 0)
    {
        // Conversion error
        AtlThrowLastWin32();
    }


    // Allocate destination buffer to store the resulting UTF-8 string
    CStringA utf8;
    char* const utf8Buffer = utf8.GetBuffer(utf8Length);
    ATLASSERT(utf8Buffer != nullptr);


    // Do the conversion from UTF-16 to UTF-8
    int result = ::WideCharToMultiByte(
            codePageUtf8,       // convert to UTF-8
            flags,              // conversion flags
            utf16.GetString(),  // source UTF-16 string
            utf16.GetLength(),  // length of source UTF-16 string, in WCHARs
            utf8Buffer,         // pointer to destination buffer
            utf8Length,         // size of destination buffer, in chars
            nullptr, nullptr);  // unused
    if (result == 0)
    {
        // Conversion error
        AtlThrowLastWin32();
    }


    // Don't forget to release internal CString buffer 
    // before returning the string to the caller
    utf8.ReleaseBufferSetLength(utf8Length);

    // Return resulting UTF-8 string
    return utf8;
}



} // namespace win32


//////////////////////////////////////////////////////////////////////////////

