#include "unit_test.h"

UnitTest::UnitTest()
{}

UnitTest::~UnitTest()
{}

/**
 *  isAmPm - check that a string equals AM or PM
 *  @match: string to compare
 *
 *  This function returns true if a string equals "AM" or "PM".
 *  Otherwise, false is returned.
 */
const bool UnitTest::isAmPm(const char * match) const
{
    if (!strcmp(match, "AM") || !strcmp(match, "PM"))
        return true;
    return false;
}

const int UnitTest::unexpectedResult(const int number, const std::string type,
                                     const std::string set, const std::string result)
{
    try {

#ifndef SEPARATE_TEST_BUILD
        std::ofstream file;
        file.open("all_unit_tests.log", std::ios::app);
        file << "[" << type << "] Constructor number " << number << ": Unexpected result for set ("
            << set << ") - " << result << std::endl;
        file.close();
#else
        std::cout << "[" << type << "] Constructor number " << number
        << ": Unexpected result for set (" << set << ") - " << result << std::endl;
#endif
    } catch (...) {
        return -1;
    }
    return 0;
}

const int UnitTest::expectedResult(const int number, const std::string type, const std::string set,
                                   const std::string result)
{
    try {
#ifndef SEPARATE_TEST_BUILD
        std::ofstream file;
        file.open("all_unit_tests.log", std::ios::app);
        file << "[" << type << "] Constructor number " << number
            << ": Match OK and all values are valid for set (" << set << ") - " << result
            << std::endl;
        file.close();
#else
        std::cout << "[" << type << "] Constructor number " << number
        << ": Match OK and all values are valid for set (" << set << ") - " << result << std::endl;
#endif
    } catch (...) {
        return -1;
    }
    return 0;
}

const int UnitTest::errorMessage(const int number, const std::string type,
                                 const std::string message)
{
    try {
#ifndef SEPARATE_TEST_BUILD
        std::ofstream file;
        file.open("all_unit_tests.log", std::ios::app);
        file << "[" << type << "] Constructor number " << number << ": [ERROR] " << message
            << std::endl;
        file.close();
#else
        std::cout << "[" << type << "] Constructor number " << number << ": [ERROR] " << message
        << std::endl;
#endif

    } catch (...) {
        return -1;
    }
    return 0;
}
