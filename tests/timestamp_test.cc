#include "timestamp_test.hh"

#ifdef SEPARATE_TEST_BUILD
int main(int argc, char * argv[])
{
    TimestampUt timestamp_test;
    return timestamp_test.run();
}
#endif

TimestampUt::TimestampUt()
{}

const std::string TimestampUt::returnFileName() const
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
const bool TimestampUt::verifyCompilance(const std::string match_string, const std::string pattern) const
{
    return std::regex_match(match_string, std::regex(pattern));
}

/**
 *  enumToString - returns a time format as string
 *  @value: format to return
 *
 *  This function returns a time format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimestampUt::enumToString(const timestamp::Time::TimeFormat value) const
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
 *  enumToString - returns a timestamp format as string
 *  @value: format to return
 *
 *  This function returns a timestamp format as string in case of
 *  the format is valid. Otherwise, empty string is returned.
 */
const std::string TimestampUt::enumToString(const Timestamp::TimestampFormat value) const
{
    switch (value) {
        case Timestamp::TimestampFormat::DMY:
            return "Format is Day Month Year";
        case Timestamp::TimestampFormat::MDY:
            return "Format is Month Day Year";
        case Timestamp::TimestampFormat::YMD:
            return "Format is Year Month Day";
        case Timestamp::TimestampFormat::DMY_DATE_ONLY:
            return "Day Month Year date only";
        case Timestamp::TimestampFormat::MDY_DATE_ONLY:
            return "Month Day Year date only";
        case Timestamp::TimestampFormat::YMD_DATE_ONLY:
            return "Year Month Day date only";
        case Timestamp::TimestampFormat::RAW:
            return "RAW";
        case Timestamp::TimestampFormat::TIME_ONLY:
            return "Time only";
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
const std::string TimestampUt::enumToString(const timestamp::Date::DateSeparator value) const
{
    switch (value) {
        case timestamp::Date::DateSeparator::SLASH:
            return "SLASH";
        case timestamp::Date::DateSeparator::DASH:
            return "DASH";
        case timestamp::Date::DateSeparator::DOT:
            return "DOT";
        case timestamp::Date::DateSeparator::BACKSLASH:
            return "BACKSLASH";
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
const int TimestampUt::generateKey(property_set_t set) const
{
    int key = 0;
    switch(set.timestamp_format) {
        case Timestamp::TimestampFormat::DMY:
            key |= 1;
            break;
        case Timestamp::TimestampFormat::MDY:
            key |= (1 << 1);
            break;
        case Timestamp::TimestampFormat::YMD:
            key |= (1 << 2);
            break;
        case Timestamp::TimestampFormat::DMY_DATE_ONLY:
            key |= (1 << 3);
            break;
        case Timestamp::TimestampFormat::MDY_DATE_ONLY:
            key |= (1 << 4);
            break;
        case Timestamp::TimestampFormat::YMD_DATE_ONLY:
            key |= (1 << 5);
            break;
        case Timestamp::TimestampFormat::TIME_ONLY:
            key |= (1 << 6);
            break;
        case Timestamp::TimestampFormat::RAW:
            key |= (1 << 7);
            break;
    }

    switch(set.time_format) {
        case timestamp::Time::TimeFormat::TIME_12_H:
            key |= (1 << 8);
            break;
        case timestamp::Time::TimeFormat::TIME_24_H:
            key |= (1 << 9);
            break;
    }

    switch(set.date_separator) {
        case timestamp::Date::DateSeparator::DASH:
            key |= (1 << 10);
            break;
        case timestamp::Date::DateSeparator::SLASH:
            key |= (1 << 11);
            break;
        case timestamp::Date::DateSeparator::DOT:
            key |= (1 << 12);
            break;
        case timestamp::Date::DateSeparator::BACKSLASH:
            key |= (1 << 13);
            break;
    }

    if(set.show_msec)
        key |= (1 << 14);
    if(set.show_offset)
            key |= (1 << 15);

    return key;
}

/**
 *  run - main function in this test module
 *
 *  This function defines all possible time sets, inserts patterns using unique key,
 *  gets result of "get" method of all the Time objects and check the result's correctness.
 */
const int TimestampUt::run()
{
    bool result = true;
    std::string get_result;
    /* Define all possible sets for the class Time */
    Timestamp::TimestampFormat timestamp_dmy = Timestamp::TimestampFormat::DMY;
    Timestamp::TimestampFormat timestamp_mdy = Timestamp::TimestampFormat::MDY;
    Timestamp::TimestampFormat timestamp_ymd = Timestamp::TimestampFormat::YMD;
    Timestamp::TimestampFormat timestamp_dmy_date_only = Timestamp::TimestampFormat::DMY_DATE_ONLY;
    Timestamp::TimestampFormat timestamp_mdy_date_only = Timestamp::TimestampFormat::MDY_DATE_ONLY;
    Timestamp::TimestampFormat timestamp_ymd_date_only = Timestamp::TimestampFormat::YMD_DATE_ONLY;
    Timestamp::TimestampFormat timestamp_raw = Timestamp::TimestampFormat::RAW;
    Timestamp::TimestampFormat timestamp_time_only = Timestamp::TimestampFormat::TIME_ONLY;

    timestamp::Time::TimeFormat t_format_12_h = timestamp::Time::TimeFormat::TIME_12_H;
    timestamp::Time::TimeFormat t_format_24_h = timestamp::Time::TimeFormat::TIME_24_H;

    timestamp::Date::DateSeparator d_separator_dash = timestamp::Date::DateSeparator::DASH;
    timestamp::Date::DateSeparator d_separator_slash = timestamp::Date::DateSeparator::SLASH;
    timestamp::Date::DateSeparator d_separator_dot = timestamp::Date::DateSeparator::DOT;
    timestamp::Date::DateSeparator d_separator_backslash = timestamp::Date::DateSeparator::BACKSLASH;

    property_set_t timestamp_set[kMaxDateSets] =

         /* d_separator_dash */

        {{timestamp_dmy,            d_separator_dash, t_format_12_h, false, false},
         {timestamp_mdy,            d_separator_dash, t_format_12_h, false, false},
         {timestamp_ymd,            d_separator_dash, t_format_12_h, false, false},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_12_h, false, false},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_12_h, false, false},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_12_h, false, false},
         {timestamp_raw,            d_separator_dash, t_format_12_h, false, false},
         {timestamp_time_only,      d_separator_dash, t_format_12_h, false, false},
         {timestamp_dmy,            d_separator_dash, t_format_12_h, false, true},
         {timestamp_mdy,            d_separator_dash, t_format_12_h, false, true},
         {timestamp_ymd,            d_separator_dash, t_format_12_h, false, true},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_12_h, false, true},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_12_h, false, true},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_12_h, false, true},
         {timestamp_raw,            d_separator_dash, t_format_12_h, false, true},
         {timestamp_time_only,      d_separator_dash, t_format_12_h, false, true},
         {timestamp_dmy,            d_separator_dash, t_format_12_h, true, false},
         {timestamp_mdy,            d_separator_dash, t_format_12_h, true, false},
         {timestamp_ymd,            d_separator_dash, t_format_12_h, true, false},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_12_h, true, false},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_12_h, true, false},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_12_h, true, false},
         {timestamp_raw,            d_separator_dash, t_format_12_h, true, false},
         {timestamp_time_only,      d_separator_dash, t_format_12_h, true, false},
         {timestamp_dmy,            d_separator_dash, t_format_12_h, true, true},
         {timestamp_mdy,            d_separator_dash, t_format_12_h, true, true},
         {timestamp_ymd,            d_separator_dash, t_format_12_h, true, true},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_12_h, true, true},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_12_h, true, true},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_12_h, true, true},
         {timestamp_raw,            d_separator_dash, t_format_12_h, true, true},
         {timestamp_time_only,      d_separator_dash, t_format_12_h, true, true},

         {timestamp_dmy,            d_separator_dash, t_format_24_h, false, false},
         {timestamp_mdy,            d_separator_dash, t_format_24_h, false, false},
         {timestamp_ymd,            d_separator_dash, t_format_24_h, false, false},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_24_h, false, false},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_24_h, false, false},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_24_h, false, false},
         {timestamp_raw,            d_separator_dash, t_format_24_h, false, false},
         {timestamp_time_only,      d_separator_dash, t_format_24_h, false, false},
         {timestamp_dmy,            d_separator_dash, t_format_24_h, false, true},
         {timestamp_mdy,            d_separator_dash, t_format_24_h, false, true},
         {timestamp_ymd,            d_separator_dash, t_format_24_h, false, true},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_24_h, false, true},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_24_h, false, true},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_24_h, false, true},
         {timestamp_raw,            d_separator_dash, t_format_24_h, false, true},
         {timestamp_time_only,      d_separator_dash, t_format_24_h, false, true},
         {timestamp_dmy,            d_separator_dash, t_format_24_h, true, false},
         {timestamp_mdy,            d_separator_dash, t_format_24_h, true, false},
         {timestamp_ymd,            d_separator_dash, t_format_24_h, true, false},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_24_h, true, false},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_24_h, true, false},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_24_h, true, false},
         {timestamp_raw,            d_separator_dash, t_format_24_h, true, false},
         {timestamp_time_only,      d_separator_dash, t_format_24_h, true, false},
         {timestamp_dmy,            d_separator_dash, t_format_24_h, true, true},
         {timestamp_mdy,            d_separator_dash, t_format_24_h, true, true},
         {timestamp_ymd,            d_separator_dash, t_format_24_h, true, true},
         {timestamp_dmy_date_only,  d_separator_dash, t_format_24_h, true, true},
         {timestamp_mdy_date_only,  d_separator_dash, t_format_24_h, true, true},
         {timestamp_ymd_date_only,  d_separator_dash, t_format_24_h, true, true},
         {timestamp_raw,            d_separator_dash, t_format_24_h, true, true},
         {timestamp_time_only,      d_separator_dash, t_format_24_h, true, true},

         /* d_separator_slash */

         {timestamp_dmy,            d_separator_slash, t_format_12_h, false, false},
         {timestamp_mdy,            d_separator_slash, t_format_12_h, false, false},
         {timestamp_ymd,            d_separator_slash, t_format_12_h, false, false},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_12_h, false, false},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_12_h, false, false},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_12_h, false, false},
         {timestamp_raw,            d_separator_slash, t_format_12_h, false, false},
         {timestamp_time_only,      d_separator_slash, t_format_12_h, false, false},
         {timestamp_dmy,            d_separator_slash, t_format_12_h, false, true},
         {timestamp_mdy,            d_separator_slash, t_format_12_h, false, true},
         {timestamp_ymd,            d_separator_slash, t_format_12_h, false, true},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_12_h, false, true},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_12_h, false, true},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_12_h, false, true},
         {timestamp_raw,            d_separator_slash, t_format_12_h, false, true},
         {timestamp_time_only,      d_separator_slash, t_format_12_h, false, true},
         {timestamp_dmy,            d_separator_slash, t_format_12_h, true, false},
         {timestamp_mdy,            d_separator_slash, t_format_12_h, true, false},
         {timestamp_ymd,            d_separator_slash, t_format_12_h, true, false},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_12_h, true, false},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_12_h, true, false},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_12_h, true, false},
         {timestamp_raw,            d_separator_slash, t_format_12_h, true, false},
         {timestamp_time_only,      d_separator_slash, t_format_12_h, true, false},
         {timestamp_dmy,            d_separator_slash, t_format_12_h, true, true},
         {timestamp_mdy,            d_separator_slash, t_format_12_h, true, true},
         {timestamp_ymd,            d_separator_slash, t_format_12_h, true, true},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_12_h, true, true},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_12_h, true, true},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_12_h, true, true},
         {timestamp_raw,            d_separator_slash, t_format_12_h, true, true},
         {timestamp_time_only,      d_separator_slash, t_format_12_h, true, true},

         {timestamp_dmy,            d_separator_slash, t_format_24_h, false, false},
         {timestamp_mdy,            d_separator_slash, t_format_24_h, false, false},
         {timestamp_ymd,            d_separator_slash, t_format_24_h, false, false},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_24_h, false, false},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_24_h, false, false},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_24_h, false, false},
         {timestamp_raw,            d_separator_slash, t_format_24_h, false, false},
         {timestamp_time_only,      d_separator_slash, t_format_24_h, false, false},
         {timestamp_dmy,            d_separator_slash, t_format_24_h, false, true},
         {timestamp_mdy,            d_separator_slash, t_format_24_h, false, true},
         {timestamp_ymd,            d_separator_slash, t_format_24_h, false, true},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_24_h, false, true},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_24_h, false, true},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_24_h, false, true},
         {timestamp_raw,            d_separator_slash, t_format_24_h, false, true},
         {timestamp_time_only,      d_separator_slash, t_format_24_h, false, true},
         {timestamp_dmy,            d_separator_slash, t_format_24_h, true, false},
         {timestamp_mdy,            d_separator_slash, t_format_24_h, true, false},
         {timestamp_ymd,            d_separator_slash, t_format_24_h, true, false},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_24_h, true, false},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_24_h, true, false},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_24_h, true, false},
         {timestamp_raw,            d_separator_slash, t_format_24_h, true, false},
         {timestamp_time_only,      d_separator_slash, t_format_24_h, true, false},
         {timestamp_dmy,            d_separator_slash, t_format_24_h, true, true},
         {timestamp_mdy,            d_separator_slash, t_format_24_h, true, true},
         {timestamp_ymd,            d_separator_slash, t_format_24_h, true, true},
         {timestamp_dmy_date_only,  d_separator_slash, t_format_24_h, true, true},
         {timestamp_mdy_date_only,  d_separator_slash, t_format_24_h, true, true},
         {timestamp_ymd_date_only,  d_separator_slash, t_format_24_h, true, true},
         {timestamp_raw,            d_separator_slash, t_format_24_h, true, true},
         {timestamp_time_only,      d_separator_slash, t_format_24_h, true, true},


         /* d_separator_dot */

         {timestamp_dmy,            d_separator_dot, t_format_12_h, false, false},
         {timestamp_mdy,            d_separator_dot, t_format_12_h, false, false},
         {timestamp_ymd,            d_separator_dot, t_format_12_h, false, false},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_12_h, false, false},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_12_h, false, false},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_12_h, false, false},
         {timestamp_raw,            d_separator_dot, t_format_12_h, false, false},
         {timestamp_time_only,      d_separator_dot, t_format_12_h, false, false},
         {timestamp_dmy,            d_separator_dot, t_format_12_h, false, true},
         {timestamp_mdy,            d_separator_dot, t_format_12_h, false, true},
         {timestamp_ymd,            d_separator_dot, t_format_12_h, false, true},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_12_h, false, true},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_12_h, false, true},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_12_h, false, true},
         {timestamp_raw,            d_separator_dot, t_format_12_h, false, true},
         {timestamp_time_only,      d_separator_dot, t_format_12_h, false, true},
         {timestamp_dmy,            d_separator_dot, t_format_12_h, true, false},
         {timestamp_mdy,            d_separator_dot, t_format_12_h, true, false},
         {timestamp_ymd,            d_separator_dot, t_format_12_h, true, false},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_12_h, true, false},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_12_h, true, false},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_12_h, true, false},
         {timestamp_raw,            d_separator_dot, t_format_12_h, true, false},
         {timestamp_time_only,      d_separator_dot, t_format_12_h, true, false},
         {timestamp_dmy,            d_separator_dot, t_format_12_h, true, true},
         {timestamp_mdy,            d_separator_dot, t_format_12_h, true, true},
         {timestamp_ymd,            d_separator_dot, t_format_12_h, true, true},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_12_h, true, true},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_12_h, true, true},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_12_h, true, true},
         {timestamp_raw,            d_separator_dot, t_format_12_h, true, true},
         {timestamp_time_only,      d_separator_dot, t_format_12_h, true, true},

         {timestamp_dmy,            d_separator_dot, t_format_24_h, false, false},
         {timestamp_mdy,            d_separator_dot, t_format_24_h, false, false},
         {timestamp_ymd,            d_separator_dot, t_format_24_h, false, false},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_24_h, false, false},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_24_h, false, false},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_24_h, false, false},
         {timestamp_raw,            d_separator_dot, t_format_24_h, false, false},
         {timestamp_time_only,      d_separator_dot, t_format_24_h, false, false},
         {timestamp_dmy,            d_separator_dot, t_format_24_h, false, true},
         {timestamp_mdy,            d_separator_dot, t_format_24_h, false, true},
         {timestamp_ymd,            d_separator_dot, t_format_24_h, false, true},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_24_h, false, true},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_24_h, false, true},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_24_h, false, true},
         {timestamp_raw,            d_separator_dot, t_format_24_h, false, true},
         {timestamp_time_only,      d_separator_dot, t_format_24_h, false, true},
         {timestamp_dmy,            d_separator_dot, t_format_24_h, true, false},
         {timestamp_mdy,            d_separator_dot, t_format_24_h, true, false},
         {timestamp_ymd,            d_separator_dot, t_format_24_h, true, false},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_24_h, true, false},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_24_h, true, false},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_24_h, true, false},
         {timestamp_raw,            d_separator_dot, t_format_24_h, true, false},
         {timestamp_time_only,      d_separator_dot, t_format_24_h, true, false},
         {timestamp_dmy,            d_separator_dot, t_format_24_h, true, true},
         {timestamp_mdy,            d_separator_dot, t_format_24_h, true, true},
         {timestamp_ymd,            d_separator_dot, t_format_24_h, true, true},
         {timestamp_dmy_date_only,  d_separator_dot, t_format_24_h, true, true},
         {timestamp_mdy_date_only,  d_separator_dot, t_format_24_h, true, true},
         {timestamp_ymd_date_only,  d_separator_dot, t_format_24_h, true, true},
         {timestamp_raw,            d_separator_dot, t_format_24_h, true, true},
         {timestamp_time_only,      d_separator_dot, t_format_24_h, true, true},
         
           
         /* d_separator_backslash */

         {timestamp_dmy,            d_separator_backslash, t_format_12_h, false, false},
         {timestamp_mdy,            d_separator_backslash, t_format_12_h, false, false},
         {timestamp_ymd,            d_separator_backslash, t_format_12_h, false, false},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_12_h, false, false},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_12_h, false, false},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_12_h, false, false},
         {timestamp_raw,            d_separator_backslash, t_format_12_h, false, false},
         {timestamp_time_only,      d_separator_backslash, t_format_12_h, false, false},
         {timestamp_dmy,            d_separator_backslash, t_format_12_h, false, true},
         {timestamp_mdy,            d_separator_backslash, t_format_12_h, false, true},
         {timestamp_ymd,            d_separator_backslash, t_format_12_h, false, true},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_12_h, false, true},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_12_h, false, true},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_12_h, false, true},
         {timestamp_raw,            d_separator_backslash, t_format_12_h, false, true},
         {timestamp_time_only,      d_separator_backslash, t_format_12_h, false, true},
         {timestamp_dmy,            d_separator_backslash, t_format_12_h, true, false},
         {timestamp_mdy,            d_separator_backslash, t_format_12_h, true, false},
         {timestamp_ymd,            d_separator_backslash, t_format_12_h, true, false},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_12_h, true, false},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_12_h, true, false},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_12_h, true, false},
         {timestamp_raw,            d_separator_backslash, t_format_12_h, true, false},
         {timestamp_time_only,      d_separator_backslash, t_format_12_h, true, false},
         {timestamp_dmy,            d_separator_backslash, t_format_12_h, true, true},
         {timestamp_mdy,            d_separator_backslash, t_format_12_h, true, true},
         {timestamp_ymd,            d_separator_backslash, t_format_12_h, true, true},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_12_h, true, true},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_12_h, true, true},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_12_h, true, true},
         {timestamp_raw,            d_separator_backslash, t_format_12_h, true, true},
         {timestamp_time_only,      d_separator_backslash, t_format_12_h, true, true},

         {timestamp_dmy,            d_separator_backslash, t_format_24_h, false, false},
         {timestamp_mdy,            d_separator_backslash, t_format_24_h, false, false},
         {timestamp_ymd,            d_separator_backslash, t_format_24_h, false, false},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_24_h, false, false},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_24_h, false, false},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_24_h, false, false},
         {timestamp_raw,            d_separator_backslash, t_format_24_h, false, false},
         {timestamp_time_only,      d_separator_backslash, t_format_24_h, false, false},
         {timestamp_dmy,            d_separator_backslash, t_format_24_h, false, true},
         {timestamp_mdy,            d_separator_backslash, t_format_24_h, false, true},
         {timestamp_ymd,            d_separator_backslash, t_format_24_h, false, true},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_24_h, false, true},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_24_h, false, true},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_24_h, false, true},
         {timestamp_raw,            d_separator_backslash, t_format_24_h, false, true},
         {timestamp_time_only,      d_separator_backslash, t_format_24_h, false, true},
         {timestamp_dmy,            d_separator_backslash, t_format_24_h, true, false},
         {timestamp_mdy,            d_separator_backslash, t_format_24_h, true, false},
         {timestamp_ymd,            d_separator_backslash, t_format_24_h, true, false},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_24_h, true, false},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_24_h, true, false},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_24_h, true, false},
         {timestamp_raw,            d_separator_backslash, t_format_24_h, true, false},
         {timestamp_time_only,      d_separator_backslash, t_format_24_h, true, false},
         {timestamp_dmy,            d_separator_backslash, t_format_24_h, true, true},
         {timestamp_mdy,            d_separator_backslash, t_format_24_h, true, true},
         {timestamp_ymd,            d_separator_backslash, t_format_24_h, true, true},
         {timestamp_dmy_date_only,  d_separator_backslash, t_format_24_h, true, true},
         {timestamp_mdy_date_only,  d_separator_backslash, t_format_24_h, true, true},
         {timestamp_ymd_date_only,  d_separator_backslash, t_format_24_h, true, true},
         {timestamp_raw,            d_separator_backslash, t_format_24_h, true, true},
         {timestamp_time_only,      d_separator_backslash, t_format_24_h, true, true}};


    /* Fill the map in with patterns */
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[0]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[1]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[2]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[3]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[4]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[5]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[6]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[7]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[8]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[9]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[10]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[11]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[12]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[13]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[14]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[15]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[16]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[17]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[18]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[19]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[20]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[21]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[22]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[23]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[24]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[25]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[26]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[27]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[28]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[29]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[30]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[31]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
//
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[32]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[33]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[34]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[35]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[36]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[37]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[38]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[39]), "(\\d{2}):(\\d{2}):(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[40]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[41]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[42]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[43]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[44]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[45]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[46]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[47]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[48]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[49]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[50]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[51]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[52]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[53]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[54]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[55]), "(\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[56]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[57]), "(\\d{2})-(\\d{2})-(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[58]), "(\\d{4})-(\\d{2})-(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[59]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[60]), "(\\d{2})-(\\d{2})-(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[61]), "(\\d{4})-(\\d{2})-(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[62]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[63]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
// ---------------------------------------------------------------------------------------------------------------------------
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[64]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[65]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[66]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[67]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[68]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[69]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[70]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[71]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[72]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[73]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[74]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[75]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[76]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[77]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[78]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[79]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[80]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[81]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[82]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[83]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[84]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[85]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[86]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[87]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[88]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[89]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[90]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[91]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[92]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[93]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[94]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[95]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
//
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[96]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[97]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[98]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[99]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[100]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[101]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[102]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[103]), "(\\d{2}):(\\d{2}):(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[104]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[105]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[106]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[107]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[108]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[109]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[110]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[111]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[112]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[113]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[114]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[115]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[116]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[117]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[118]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[119]), "(\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[120]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[121]), "(\\d{2})/(\\d{2})/(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[122]), "(\\d{4})/(\\d{2})/(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[123]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[124]), "(\\d{2})/(\\d{2})/(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[125]), "(\\d{4})/(\\d{2})/(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[126]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[127]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
//------------------------------------------------------------------------------------------------------------------------------
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[128]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[129]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[130]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[131]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[132]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[133]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[134]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[135]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[136]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[137]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[138]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[139]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[140]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[141]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[142]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[143]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[144]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[145]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[146]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[147]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[148]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[149]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[150]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[151]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[152]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[153]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[154]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[155]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[156]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[157]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[158]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[159]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
//
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[160]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[161]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[162]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[163]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[164]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[165]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[166]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[167]), "(\\d{2}):(\\d{2}):(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[168]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[169]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[170]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[171]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[172]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[173]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[174]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[175]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[176]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[177]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[178]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[179]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[180]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[181]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[182]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[183]), "(\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[184]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[185]), "(\\d{2}).(\\d{2}).(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[186]), "(\\d{4}).(\\d{2}).(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[187]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[188]), "(\\d{2}).(\\d{2}).(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[189]), "(\\d{4}).(\\d{2}).(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[190]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[191]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));

//------------------------------------------------------------------------------------------------------------------------------
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[192]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[193]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[194]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[195]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[196]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[197]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[198]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[199]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[200]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[201]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[202]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[203]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[204]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[205]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[206]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[207]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM)"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[208]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[209]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[210]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[211]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[212]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[213]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[214]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[215]), "(\\d{2}):(\\d{2}):(\\d{2}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[216]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[217]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[218]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[219]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[220]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[221]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[222]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[223]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) (AM|PM) UTC [+|-](\\d{2})(\\d{2})"));
//
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[224]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[225]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[226]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[227]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[228]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[229]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[230]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[231]), "(\\d{2}):(\\d{2}):(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[232]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[233]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[234]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[235]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[236]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[237]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[238]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[239]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[240]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[241]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[242]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[243]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[244]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[245]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[246]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[247]), "(\\d{2}):(\\d{2}):(\\d{2}) UTC [+|-](\\d{2})(\\d{2})"));

    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[248]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[249]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[250]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2}) (\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[251]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[252]), "(\\d{2})\\\\(\\d{2})\\\\(\\d{4})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[253]), "(\\d{4})\\\\(\\d{2})\\\\(\\d{2})"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[254]), "(\\d+)"));
    match_map.insert(std::pair<int, std::string>(generateKey(timestamp_set[255]), "(\\d{2}):(\\d{2}):(\\d{2}).(\\d{3}) UTC [+|-](\\d{2})(\\d{2})"));


    /* Create the class object, get result and compare with pattern */
    /* Constructor 1 */
    for (int i = 0; i < kMaxDateSets; i++) {
        if (!timestamp_set[i].show_offset && !timestamp_set[i].show_msec &&
            timestamp_set[i].date_separator == timestamp::Date::DateSeparator::SLASH
            && timestamp_set[i].time_format == timestamp::Time::TimeFormat::TIME_24_H) {

            Timestamp timestamp_obj(timestamp_set[i].timestamp_format);
            get_result = timestamp_obj.Get();
            it = match_map.find(generateKey(timestamp_set[i]));
            if (it != match_map.end()) {
                /* Just match regex, matching values is to complex action */
                bool local_result = verifyCompilance(get_result, it->second);
                result = result && local_result;

                std::string set_string = enumToString(timestamp_set[i].timestamp_format);
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].date_separator));
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].time_format));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds disabled"));

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
    }

    /* Constructor 2 */
    for (int i = 0; i < kMaxDateSets; i++) {
        if (!timestamp_set[i].show_offset && !timestamp_set[i].show_msec
            && timestamp_set[i].time_format == timestamp::Time::TimeFormat::TIME_24_H) {

            Timestamp timestamp_obj(timestamp_set[i].timestamp_format,
                                    timestamp_set[i].date_separator);
            get_result = timestamp_obj.Get();
            it = match_map.find(generateKey(timestamp_set[i]));
            if (it != match_map.end()) {
                /* Just match regex, matching values is to complex action */
                bool local_result = verifyCompilance(get_result, it->second);
                result = result && local_result;

                std::string set_string = enumToString(timestamp_set[i].timestamp_format);
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].date_separator));
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].time_format));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds disabled"));

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
    }

    /* Constructor 3 */
    for (int i = 0; i < kMaxDateSets; i++) {
        if (!timestamp_set[i].show_offset && !timestamp_set[i].show_msec
            && timestamp_set[i].date_separator == timestamp::Date::DateSeparator::SLASH) {

            Timestamp timestamp_obj(timestamp_set[i].timestamp_format,
                                    timestamp_set[i].time_format);
            get_result = timestamp_obj.Get();
            it = match_map.find(generateKey(timestamp_set[i]));
            if (it != match_map.end()) {
                /* Just match regex, matching values is to complex action */
                bool local_result = verifyCompilance(get_result, it->second);
                result = result && local_result;

                std::string set_string = enumToString(timestamp_set[i].timestamp_format);
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].date_separator));
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].time_format));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds disabled"));

                if (!local_result) {
                    unexpectedResult(3, TYPE, set_string, get_result);
                } else {
                    expectedResult(3, TYPE, set_string, get_result);
                }
            } else {
                result = result && false;
                errorMessage(3, TYPE, "No pattern");
            }
        }
    }

    /* Constructor 4 */
    for (int i = 0; i < kMaxDateSets; i++) {
        if (timestamp_set[i].date_separator == timestamp::Date::DateSeparator::SLASH) {
            Timestamp timestamp_obj(timestamp_set[i].timestamp_format, timestamp_set[i].time_format,
                                    timestamp_set[i].show_offset, timestamp_set[i].show_msec);
            get_result = timestamp_obj.Get();
            it = match_map.find(generateKey(timestamp_set[i]));
            if (it != match_map.end()) {
                /* Just match regex, matching values is to complex action */
                bool local_result = verifyCompilance(get_result, it->second);
                result = result && local_result;

                std::string set_string = enumToString(timestamp_set[i].timestamp_format);
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].date_separator));
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].time_format));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds disabled"));

                if (!local_result) {
                    unexpectedResult(4, TYPE, set_string, get_result);
                } else {
                    expectedResult(4, TYPE, set_string, get_result);
                }
            } else {
                result = result && false;
                errorMessage(4, TYPE, "No pattern");
            }
        }
    }


    /* Constructor 5 */
    for (int i = 0; i < kMaxDateSets; i++) {
        if (!timestamp_set[i].show_offset && !timestamp_set[i].show_msec) {
            Timestamp timestamp_obj(timestamp_set[i].timestamp_format, timestamp_set[i].date_separator,
                                    timestamp_set[i].time_format);
            get_result = timestamp_obj.Get();
            it = match_map.find(generateKey(timestamp_set[i]));
            if (it != match_map.end()) {
                /* Just match regex, matching values is to complex action */
                bool local_result = verifyCompilance(get_result, it->second);
                result = result && local_result;

                std::string set_string = enumToString(timestamp_set[i].timestamp_format);
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].date_separator));
                set_string.append(", ");
                set_string.append(enumToString(timestamp_set[i].time_format));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
                set_string.append(", ");
                set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds enabled"));

                if (!local_result) {
                    unexpectedResult(5, TYPE, set_string, get_result);
                } else {
                    expectedResult(5, TYPE, set_string, get_result);
                }
            } else {
                result = result && false;
                errorMessage(5, TYPE, "No pattern");
            }
        }
    }

    /* Constructor 6 */
    for (int i = 0; i < kMaxDateSets; i++) {
        Timestamp timestamp_obj(timestamp_set[i].timestamp_format, timestamp_set[i].date_separator,
                                timestamp_set[i].time_format, timestamp_set[i].show_offset,
                                timestamp_set[i].show_msec);
        get_result = timestamp_obj.Get();
        it = match_map.find(generateKey(timestamp_set[i]));
        if (it != match_map.end()) {
            /* Just match regex, matching values is to complex action */
            bool local_result = verifyCompilance(get_result, it->second);
            result = result && local_result;

            std::string set_string = enumToString(timestamp_set[i].timestamp_format);
            set_string.append(", ");
            set_string.append(enumToString(timestamp_set[i].date_separator));
            set_string.append(", ");
            set_string.append(enumToString(timestamp_set[i].time_format));
            set_string.append(", ");
            set_string.append((timestamp_set[i].show_offset ? "Offset enabled" : "Offset disabled"));
            set_string.append(", ");
            set_string.append((timestamp_set[i].show_msec ? "Milliseconds enabled" : "Milliseconds disabled"));

            if (!local_result) {
                unexpectedResult(6, TYPE, set_string, get_result);
            } else {
                expectedResult(6, TYPE, set_string, get_result);
            }
        } else {
            result = result && false;
            errorMessage(6, TYPE, "No pattern");
        }
    }

    return !result;
}
