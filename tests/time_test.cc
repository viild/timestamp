#include "time_test.h"

#ifdef SEPARATE_TEST_BUILD
int main(int argc, char * argv[])
{
    TimeUt time_test;
    return time_test.run();
}
#endif

TimeUt::TimeUt()
{}

const std::string TimeUt::returnFileName() const
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
const bool TimeUt::verifyCompilance(const std::string match_string, const std::string pattern,
                                    property_set_t set) const
{
    std::regex re(pattern);
    std::smatch match;
    bool result = std::regex_match(match_string, re);
    if (std::regex_search(match_string, match, re) && match.size() > 1) {
        int h = atoi(match.str(1).c_str());
        int m = atoi(match.str(2).c_str());
        int s = atoi(match.str(3).c_str());
        int msec = 0;
        int offset_hour = 0;
        int offset_min = 0;
        int time_pattern = 0;
        std::string am_pm_string = "AM";

        switch (set.time_format) {
            case timestamp::Time::TimeFormat::TIME_12_H:
                time_pattern = 12;
                if (set.msec && !set.offset) {
                    msec = atoi(match.str(4).c_str());
                    am_pm_string = match.str(5);
                } else if (!set.msec && set.offset) {
                    am_pm_string = match.str(4);
                    offset_hour = atoi(match.str(5).c_str());
                    offset_min = atoi(match.str(6).c_str());
                } else if (set.msec && set.offset) {
                    am_pm_string = match.str(5);
                    msec = atoi(match.str(4).c_str());
                    offset_hour = atoi(match.str(6).c_str());
                    offset_min = atoi(match.str(7).c_str());
                }
                break;
            case timestamp::Time::TimeFormat::TIME_24_H:
                time_pattern = 24;
                if (set.msec && !set.offset) {
                    msec = atoi(match.str(4).c_str());
                } else if (!set.msec && set.offset) {
                    offset_hour = atoi(match.str(4).c_str());
                    offset_min = atoi(match.str(5).c_str());
                } else if (set.msec && set.offset) {
                    msec = atoi(match.str(4).c_str());
                    offset_hour = atoi(match.str(5).c_str());
                    offset_min = atoi(match.str(6).c_str());
                }
                break;
            default:
                return false;
        }

        result = result && isAmPm(am_pm_string.c_str()) && (msec >= 0 && msec <= 999)
            && (offset_hour >= 0 && offset_hour <= 14) && (offset_min >= 0 && offset_min <= 59)
            && (h >= 0 && h <= time_pattern) && (m >= 0 && m <= 59) && (s >= 0 && s <= 59);
    } else {
        return false;
    }
    return result;
}

/**
 *  enumToString - returns a time format as string
 *  @value: format to return
 *
 *  This function returns a time format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimeUt::enumToString(const timestamp::Time::TimeFormat value) const
{
    switch (value) {
        case timestamp::Time::TimeFormat::TIME_12_H:
            return "Time in 12H format";
        case timestamp::Time::TimeFormat::TIME_24_H:
            return "Time in 24H format";
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
const int TimeUt::generateKey(property_set_t set) const
{
    int key = 0;
    switch(set.time_format) {
        case timestamp::Time::TimeFormat::TIME_12_H:
            key |= 1;
            break;
        case timestamp::Time::TimeFormat::TIME_24_H:
            key |= (1 << 1);
            break;
    }
    if (set.msec == true)
        key |= (1 << 2);
    if (set.offset == true)
        key |= (1 << 3);
    return key;
}

/**
 *  run - main function in this test module
 *
 *  This function defines all possible time sets, inserts patterns using unique key,
 *  gets result of "get" method of all the Time objects and check the result's correctness.
 */
const int TimeUt::run()
{
    bool result = true;
    std::string get_result;
    /* Define all possible sets for the class Time */
    timestamp::Time::TimeFormat t_format_12_h = timestamp::Time::TimeFormat::TIME_12_H;
    timestamp::Time::TimeFormat t_format_24_h = timestamp::Time::TimeFormat::TIME_24_H;
    property_set_t time_set[kMaxDateSets] = { { t_format_12_h, false, false }, /* these bool values are default */
                                               { t_format_12_h, false, true },
                                               { t_format_12_h, true, false },
                                               { t_format_12_h, true, true },
                                               { t_format_24_h, false, false }, /* these bool values are default */
                                               { t_format_24_h, false, true },
                                               { t_format_24_h, true, false },
                                               { t_format_24_h, true, true }};


    /* Fill the map in with patterns */
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[0]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[1]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[2]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[3]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[4]), "(\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[5]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[6]), "(\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(time_set[7]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));

    /* Check first constructor */
    int time_c1_1_key = generateKey(time_set[0]);
    int time_c1_2_key = generateKey(time_set[4]);
    timestamp::Time time_c1_1(t_format_12_h);
    timestamp::Time time_c1_2(t_format_24_h);

    get_result = time_c1_1.Get();
    it = match_map.find(time_c1_1_key);
    if (it != match_map.end()) {
        bool local_result = verifyCompilance(get_result, it->second, time_set[0]);
        result = result && local_result;
        std::string set_string = enumToString(time_set[0].time_format);
        set_string.append(", ");
        set_string.append(time_set[0].offset ? "Offset enabled" : "Offset disabled");
        set_string.append(", ");
        set_string.append(time_set[0].msec ? "Milliseconds enabled" : "Milliseconds disabled");
        if (!local_result) {
            unexpectedResult(1, TYPE, set_string, get_result);
        } else {
            expectedResult(1, TYPE, set_string, get_result);
        }
    } else {
        errorMessage(1, TYPE, "No pattern");
    }

    get_result = time_c1_2.Get();
    it = match_map.find(time_c1_2_key);
    if (it != match_map.end()) {
        bool local_result = verifyCompilance(get_result, it->second, time_set[4]);
        result = result && local_result;
        std::string set_string = enumToString(time_set[4].time_format);
        set_string.append(", ");
        set_string.append(time_set[4].offset ? "Offset enabled" : "Offset disabled");
        set_string.append(", ");
        set_string.append(time_set[4].msec ? "Milliseconds enabled" : "Milliseconds disabled");
        if (!local_result) {
            unexpectedResult(1, TYPE, set_string, get_result);
        } else {
            expectedResult(1, TYPE, set_string, get_result);
        }
    } else {
        errorMessage(1, TYPE, "No pattern");
    }

    /* Create the class object, get result and compare with pattern */
    for (int i = 0; i < kMaxDateSets; i++) {

        timestamp::Time time_obj(time_set[i].time_format, time_set[i].offset, time_set[i].msec);
        get_result = time_obj.Get();
        it = match_map.find(generateKey(time_set[i]));
        if (it != match_map.end()) {
            bool local_result = verifyCompilance(get_result, it->second, time_set[i]);
            result = result && local_result;
            std::string set_string = enumToString(time_set[i].time_format);
            set_string.append(", ");
            set_string.append(time_set[i].offset ? "Offset enabled" : "Offset disabled");
            set_string.append(", ");
            set_string.append(time_set[i].msec ? "Milliseconds enabled" : "Milliseconds disabled");
            if (!local_result) {
                unexpectedResult(2, TYPE, set_string, get_result);
            } else {
                expectedResult(2, TYPE, set_string, get_result);
            }
        } else {
            result = result && false;
            errorMessage(2, TYPE, "No pattern");
        }
    }

        return !result;
}
