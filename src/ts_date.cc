#include "ts_date.h"
#include <iostream>

namespace timestamp {

/**
 *  Date - class constructor
 *  @_date_separator: date separator specifier
 *  @_date_format: date format specifier
 *
 *  This constructor creates an object of the Date class. This also invokes constructor
 *  of the Stamp class and sets variables date_separator and date_format by values
 *  given by an user. In brackets, it prepares pattern and throws the exception if
 *  error occurred.
 */
Date::Date(const DateSeparator & _date_separator, const DateFormat & _date_format) :
    Stamp(), date_separator(_date_separator), date_format(_date_format)
{
    PairIntString rv;
    rv = BuildPattern();
    if (rv.first)
        throw rv.first;
}

/**
 *  Get - return date in specific format
 *
 *  This method forms string with current date in format defined by "date_format"
 *  and returns it.
 */
const std::string Date::Get() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);

    int day = local_tm.tm_mday;
    int month = local_tm.tm_mon + 1;
    int year = local_tm.tm_year + 1900;

    switch (this->date_format) {
        case timestamp::Date::DateFormat::DMY:
            return GetValue(GetPattern().c_str(), day, month, year);
        case timestamp::Date::DateFormat::MDY:
            return GetValue(GetPattern().c_str(), month, day, year);
        case timestamp::Date::DateFormat::YMD:
            return GetValue(GetPattern().c_str(), year, month, day);
        default : return "";
    }
}

/**
 *  BuildPattern - form pattern of the class Date
 *
 *  This method forms the pattern string based on user-defined date separator
 *  and date format. Once the string is formed, it is saved in the Stamp class
 *  by using "SetPattern" method.
 */
const PairIntString Date::BuildPattern()
{
    char separator;

    /* Get separator */
    switch (this->date_separator) {
        case timestamp::Date::DateSeparator::DASH:
            separator = '-';
            break;
        case timestamp::Date::DateSeparator::DOT:
            separator = '.';
            break;
        case timestamp::Date::DateSeparator::SLASH:
            separator = '/';
            break;
    }

    std::string local_pattern;
    /* Build pattern based on the format */
    switch (this->date_format) {
        case timestamp::Date::DateFormat::MDY:
        case timestamp::Date::DateFormat::DMY:
            local_pattern  = "%02d";
            local_pattern += separator;
            local_pattern += "%02d";
            local_pattern += separator;
            local_pattern += "%04d";
            break;
        case timestamp::Date::DateFormat::YMD:
            local_pattern  = "%04d";
            local_pattern += separator;
            local_pattern += "%02d";
            local_pattern += separator;
            local_pattern += "%02d";
            break;
    }

    try {
        SetPattern(local_pattern);
    } catch (...) {
        return std::make_pair(1, "Set pattern error");
    }
    return std::make_pair(0, "No error");
}

} // namespace timestamp
