//////////////////////////////////////////////////////////////////////////////
//
// *** Functions to convert between Unicode UTF-8 and Unicode UTF-16 ***
//                      using ATL CStringA/W classes
//
// By Giovanni Dicanio 
//
// Last update: 2015, March 18th
//
//
// FILE: UnicodeConvAtl.h
//
// DESCRIPTION: 
// 
// Header file for the conversion functions.
//
// These functions use the ::MultiByteToWideChar() and ::WideCharToMultiByte()
// Win32 APIs to convert between Unicode UTF-8 and UTF-16.
//
// UTF-16 strings are stored in instances of CStringW.
// UTF-8 strings are stored in instances of CStringA.
//
// On error, the conversion functions use AtlThrow() to signal the
// error condition.
//
//
//
// Useful Web References:
// ----------------------
//
// WideCharToMultiByte() Function
// http://msdn.microsoft.com/en-us/library/dd374130.aspx
//
// MultiByteToWideChar() Function
// http://msdn.microsoft.com/en-us/library/dd319072.aspx
//
// AtlThrow()
// http://msdn.microsoft.com/en-us/library/z325eyx0.aspx
//
//
// Initially developed on Visual Studio 2008 SP1.
// Next ported to Visual Studio 2010 SP1.
//
//////////////////////////////////////////////////////////////////////////////


#pragma once

#include <atldef.h>         // For AtlThrow()
#include <atlstr.h>         // For CString

namespace win32
{


//----------------------------------------------------------------------------
// FUNCTION: Utf8ToUtf16
// DESC:     Converts Unicode UTF-8 text to Unicode UTF-16 (Windows default).
//----------------------------------------------------------------------------
CStringW Utf8ToUtf16(const CStringA& utf8);

//----------------------------------------------------------------------------
// FUNCTION: Utf16ToUtf8
// DESC:     Converts Unicode UTF-16 (Windows default) text to Unicode UTF-8.
//----------------------------------------------------------------------------
CStringA Utf16ToUtf8(const CStringW& utf16);


} // namespace win32

