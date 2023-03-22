#include "ts_date.h"
#include <iostream>

namespace timestamp {

/**
 *  Date - class constructor
 *  @_date_separator: date separator specifier
 *  @_date_format: date format specifier
 *
 *  This constructor creates an object of the Date class. This also sets variables
 *  date_separator and date_format by values given by an user.
 */
Date::Date(const DateSeparator & _date_separator, const DateFormat & _date_format) :
    date_separator(_date_separator), date_format(_date_format)
{}

/**
 *  Get - return date in specific format
 *
 *  This method forms string with current date in format defined by "date_format"
 *  and "date_separator" and then returns it.
 */
const std::string Date::Get() const
{
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);

    int day = local_tm.tm_mday;
    int month = local_tm.tm_mon + 1;
    int year = local_tm.tm_year + 1900;

    std::stringstream string_stream;

    switch (this->date_format) {
        case timestamp::Date::DateFormat::DMY:
            switch (this->date_separator) {
                case timestamp::Date::DateSeparator::DASH:
                    string_stream << AuxStamp::Format(2, day) << "-"
                                  << AuxStamp::Format(2, month) << "-"
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::DOT:
                    string_stream << AuxStamp::Format(2, day) << "."
                                  << AuxStamp::Format(2, month) << "."
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::SLASH:
                    string_stream << AuxStamp::Format(2, day) << "/"
                                  << AuxStamp::Format(2, month) << "/"
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                default:
                    return "";
            }
            ;
            break;
        case timestamp::Date::DateFormat::MDY:
            switch (this->date_separator) {
                case timestamp::Date::DateSeparator::DASH:
                    string_stream << AuxStamp::Format(2, month) << "-"
                                  << AuxStamp::Format(2, day) << "-"
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::DOT:
                    string_stream << AuxStamp::Format(2, month) << "."
                                  << AuxStamp::Format(2, day) << "."
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::SLASH:
                    string_stream << AuxStamp::Format(2, month) << "/"
                                  << AuxStamp::Format(2, day) << "/"
                                  << AuxStamp::Format(4, year);
                    return string_stream.str();
                default:
                    return "";
            }
            ;
            break;
        case timestamp::Date::DateFormat::YMD:
            switch (this->date_separator) {
                case timestamp::Date::DateSeparator::DASH:
                    string_stream << AuxStamp::Format(4, year) << "-"
                                  << AuxStamp::Format(2, day) << "-"
                                  << AuxStamp::Format(2, month);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::DOT:
                    string_stream << AuxStamp::Format(4, year) << "."
                                  << AuxStamp::Format(2, day) << "."
                                  << AuxStamp::Format(2, month);
                    return string_stream.str();
                case timestamp::Date::DateSeparator::SLASH:
                    string_stream << AuxStamp::Format(4, year) << "/"
                                  << AuxStamp::Format(2, day) << "/"
                                  << AuxStamp::Format(2, month);
                    return string_stream.str();
                default:
                    return "";
            }
            ;
            break;
        default:
            return "";
    };
}

} // namespace timestamp
