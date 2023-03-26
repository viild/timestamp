#include "date_test.hh"

#ifdef SEPARATE_TEST_BUILD
int main(int argc, char * argv[])
{
    DateUt date_test;
    return date_test.run();
}
#endif

DateUt::DateUt()
{}

const std::string DateUt::returnFileName() const
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
const bool DateUt::verifyCompilance(const std::string match_string, const std::string pattern,
                                    property_set_t set) const
{
    std::regex re(pattern);
    std::smatch match;
    bool result = std::regex_match(match_string, re);
    if (std::regex_search(match_string, match, re) && match.size() > 1) {
        int day = -1;
        int month = -1;
        int year = -1;
        switch(set.date_format) {
            case timestamp::Date::DateFormat::DMY:
                day = atoi(match.str(1).c_str());
                month = atoi(match.str(2).c_str());
                year = atoi(match.str(3).c_str());
                break;
            case timestamp::Date::DateFormat::MDY:
                month = atoi(match.str(1).c_str());
                day = atoi(match.str(2).c_str());
                year = atoi(match.str(3).c_str());
                break;
            case timestamp::Date::DateFormat::YMD:
                year = atoi(match.str(1).c_str());
                month = atoi(match.str(2).c_str());
                day = atoi(match.str(3).c_str());
                break;
        }

        result = result && (day >= 1 && day <= 31) && (month >= 1 && month <= 12)
                        && (year >= 1 && year <= 9999);
    } else {
        return false;
    }
    return result;
}

/**
 *  enumToString - returns a date format as string
 *  @value: format to return
 *
 *  This function returns a date format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string DateUt::enumToString(const timestamp::Date::DateFormat value) const
{
    switch (value) {
        case timestamp::Date::DateFormat::DMY:
            return "Format is Day Month Year";
        case timestamp::Date::DateFormat::MDY:
            return "Format is Month Day Year";
        case timestamp::Date::DateFormat::YMD:
            return "Format is Year Month Day";
        default:
            return "";
    }
}

/**
 *  enumToString - returns a date separator as string
 *  @value: format to return
 *
 *  This function returns a date separator as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string DateUt::enumToString(const timestamp::Date::DateSeparator value) const
{
    switch (value) {
        case timestamp::Date::DateSeparator::BACKSLASH:
            return "BACKSLASH";
        case timestamp::Date::DateSeparator::SLASH:
            return "SLASH";
        case timestamp::Date::DateSeparator::DASH:
            return "DASH";
        case timestamp::Date::DateSeparator::DOT:
            return "DOT";
        default:
            return "";
    }
}

/**
 *  generateKey - generate unique key
 *  @set: set to use
 *
 *  This function generates unique key using set of a class properties.
 *  In order to guarantee uniqueness of the key, certain bits are set
 *  if a certain condition is met.
 */
const int DateUt::generateKey(property_set_t set) const
{
    int key = 0;
    switch(set.date_format) {
        case timestamp::Date::DateFormat::DMY:
            key |= 1;
            break;
        case timestamp::Date::DateFormat::MDY:
            key |= (1 << 1);
            break;
        case timestamp::Date::DateFormat::YMD:
            key |= (1 << 2);
            break;
    }
    switch(set.date_separator) {
        case timestamp::Date::DateSeparator::DASH:
            key |= (1 << 3);
            break;
        case timestamp::Date::DateSeparator::SLASH:
            key |= (1 << 4);
            break;
        case timestamp::Date::DateSeparator::DOT:
            key |= (1 << 5);
            break;
        case timestamp::Date::DateSeparator::BACKSLASH:
            key |= (1 << 6);
            break;
    }

    return key;
}

/**
 *  run - main function in this test module
 *
 *  This function defines all possible time sets, inserts patterns using unique key,
 *  gets result of "get" method of all the Time objects and check the result's correctness.
 */
const int DateUt::run()
{
    bool result = true;
    std::string get_result;
    /* Define all possible sets for the class Time */
    timestamp::Date::DateFormat d_format_dmy = timestamp::Date::DateFormat::DMY;
    timestamp::Date::DateFormat d_format_mdy = timestamp::Date::DateFormat::MDY;
    timestamp::Date::DateFormat d_format_ymd = timestamp::Date::DateFormat::YMD;

    timestamp::Date::DateSeparator d_separator_dash = timestamp::Date::DateSeparator::DASH;
    timestamp::Date::DateSeparator d_separator_slash = timestamp::Date::DateSeparator::SLASH;
    timestamp::Date::DateSeparator d_separator_dot = timestamp::Date::DateSeparator::DOT;
    timestamp::Date::DateSeparator d_separator_backslash = timestamp::Date::DateSeparator::BACKSLASH;

    property_set_t date_set[kMaxDateSets] = {{d_format_dmy, d_separator_dash},
                                             {d_format_dmy, d_separator_slash},
                                             {d_format_dmy, d_separator_dot},
                                             {d_format_dmy, d_separator_backslash},
                                             {d_format_mdy, d_separator_dash},
                                             {d_format_mdy, d_separator_slash},
                                             {d_format_mdy, d_separator_dot},
                                             {d_format_mdy, d_separator_backslash},
                                             {d_format_ymd, d_separator_dash},
                                             {d_format_ymd, d_separator_slash},
                                             {d_format_ymd, d_separator_dot},
                                             {d_format_ymd, d_separator_backslash}};


    /* Fill the map in with patterns */
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[0]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[1]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[2]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[3]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));

    match_map.insert(std::pair<int, std::string>(generateKey(date_set[4]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[5]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[6]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[7]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));

    match_map.insert(std::pair<int, std::string>(generateKey(date_set[8]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[9]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[10]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(date_set[11]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));

    /* Create the class object, get result and compare with pattern */
    for (int i = 0; i < kMaxDateSets; i++) {
        timestamp::Date date_obj(date_set[i].date_separator, date_set[i].date_format);
        get_result = date_obj.Get();
        it = match_map.find(generateKey(date_set[i]));
        if (it != match_map.end()) {
            bool local_result = verifyCompilance(get_result, it->second, date_set[i]);
            result = result && local_result;

            std::string set_string = enumToString(date_set[i].date_format);
            set_string.append(", ");
            set_string.append(enumToString(date_set[i].date_separator));

            if (!local_result) {
                unexpectedResult(1, TYPE, set_string, get_result);
            } else {
                expectedResult(1, TYPE, set_string, get_result);
            }
        } else {
            result = result && false;
            errorMessage(1, TYPE, "No pattern");
        }
    }

    return !result;
}
