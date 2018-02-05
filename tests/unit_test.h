#ifndef UNIT_TEST_H_
#define UNIT_TEST_H_

#include <map>
#include <iostream>
#include <regex>
#include <string>
#include <cstdlib>
#include <cstring>
#include <fstream>

class UnitTest {
protected:
    UnitTest();
    ~UnitTest();
    std::map<int, std::string> match_map;
    std::map<int, std::string>::iterator it;
    const bool isAmPm(const char * match) const;
    const int unexpectedResult(const int number, const std::string type, const std::string set,
                               const std::string result);
    const int errorMessage(const int number, const std::string type,
                           const std::string message);
    const int expectedResult(const int number, const std::string type, const std::string set,
                             const std::string result);
};

#endif /* UNIT_TEST_H_ */
