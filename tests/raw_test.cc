#include "raw_test.hh"

#ifdef SEPARATE_TEST_BUILD
int main(int argc, char * argv[])
{
    RawUt raw_test;
    return raw_test.run();
}
#endif

RawUt::RawUt()
{}

const std::string RawUt::returnFileName() const
{
    return __FILE__;
}

/**
 *  verifyCompilance - check that match_string matches "pattern" regex and all values are valid
 *  @match_string: string with a time in any format
 *  @pattern: pattern for regex
 *  @set: set to calculate valid values
 *
 *  This function checks that match_string matches the pattern and all the obtained values
 *  are valid. If they are valid, the function will return true. If one of the conditions
 *  wasn't met, it will return false.
 */
const bool RawUt::verifyCompilance(const std::string match_string, const std::string pattern) const
{
    return std::regex_match(match_string, std::regex(pattern));
}

/**
 *  run - main function in this test module
 *
 *  This function defines all possible time sets, inserts patterns using unique key,
 *  gets result of "get" method of all the Time objects and check the result's correctness.
 */
const int RawUt::run()
{
    bool result = true;
    std::string get_result;
    timestamp::Raw raw_obj;
    get_result = raw_obj.Get();
    result = verifyCompilance(get_result, "(\\d+)");

    std::string set_string = "";

    if (!result) {
        unexpectedResult(1, TYPE, set_string, get_result);
    } else {
        expectedResult(1, TYPE, set_string, get_result);
    }

    return !result;
}
