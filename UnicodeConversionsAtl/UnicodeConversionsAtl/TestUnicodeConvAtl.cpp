//////////////////////////////////////////////////////////////////////////////
//
// FILE: Test.cpp
// DESC: Some test cases for the string conversion helpers.
//
// By Giovanni Dicanio
//
//////////////////////////////////////////////////////////////////////////////


#include "UnicodeConvAtl.h" // Conversion helpers header
#include <exception>        // For std::exception
#include <iostream>         // For console output



//----------------------------------------------------------------------------
// Verify that the given condition is satisfied.
// If not, throws an exception (std::runtime_error) with an error message
//----------------------------------------------------------------------------
inline void Verify(const bool condition, const char* const message)
{
    if (!condition)
    {
        throw std::runtime_error(message);
    }
}



//----------------------------------------------------------------------------
// Test cases for the UTF-8 string conversion helpers.
//----------------------------------------------------------------------------
void Test()
{
    // Namespace in which I enclosed the conversion functions
    using namespace win32;


    //
    // Print Test Title
    //
    std::cout << "*** UTF-8 <-> UTF-16 Conversion Tests -- by Giovanni Dicanio ***\n\n";



    //
    // Test for empty strings
    //
    std::cout << "Testing empty string conversions...";
    Verify(Utf16ToUtf8(L"").IsEmpty(), 
        "An empty UTF-16 string should be converted to an empty UTF-8 string.");
    Verify(Utf8ToUtf16("").IsEmpty(),
        "An empty UTF-8 string should be converted to an empty UTF-16 string.");
    std::cout << "OK.\n";


    //
    // Simple test
    // Unicode Character 'LATIN SMALL LETTER A WITH GRAVE' (U+00E0)
    // http://www.fileformat.info/info/unicode/char/00E0/index.htm
    //

    std::cout << "Testing conversion from UTF-16 to UTF-8 and back to UTF-16...";
    const CStringW initialUtf16 = L"Latin small letter 'a' with grave: \x00E0";
    const CStringA utf8 = Utf16ToUtf8(initialUtf16);
    const CStringW finalUtf16 = Utf8ToUtf16(utf8);
    Verify(finalUtf16 == initialUtf16, 
        "Converting from UTF-16 to UTF-8 and back to UTF-16\n"
        "should result in the same initial string.");
    std::cout << "OK.\n";


    //
    // Test with conversion error
    //
    try
    {
        std::cout << "Attempting conversion with invalid UTF-8 char...";

        const CStringA invalidUtf8 = "\xC0";
        const CStringW errorUtf16 = Utf8ToUtf16(invalidUtf8);
    }
    catch (const CAtlException& e)
    {
        Verify(static_cast<HRESULT>(e) 
            == HRESULT_FROM_WIN32(ERROR_NO_UNICODE_TRANSLATION), 
            "Attempting to convert invalid UTF-8 strings should throw\n"
            "a CAtlException with error code set to\n"
            "ERROR_NO_UNICODE_TRANSLATION."
            );

        // Exception successfully thrown and caught, with proper error code
        std::cout << "OK.\n";
    }


    std::cout << '\n';
}



//----------------------------------------------------------------------------
// Console application entry-point.
//----------------------------------------------------------------------------
int main()
{
    static const int kExitOk = 0;
    static const int kExitError = 1;

    try
    {
        // Run test cases
        Test();

        // All right
        std::cout << "\nAll test cases passed successfully.\n";
        return kExitOk;
    }
    catch (const std::exception& ex)
    {
        std::cout << "\n\n*** ERROR: " << ex.what() << '\n';

        // Something went wrong
        return kExitError;
    }
}

