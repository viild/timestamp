#include "ts_date.hh"
#include <iostream>
#include <stdexcept>

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
 *  FormatToChar - returns separator as char
 */
const std::string Date::SeparatorToChar() const
{
    switch (this->date_separator) {
        case Date::DateSeparator::DASH:
            return "-";
        case Date::DateSeparator::SLASH:
            return "/";
        case Date::DateSeparator::BACKSLASH:
            return "\\";
        case Date::DateSeparator::DOT:
            return ".";
        default:
            throw std::invalid_argument( "Date separator is invalid" );
    }
}

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
    std::string order[3];

    switch (this->date_format) {
        case Date::DateFormat::DMY: {
            order[0] = AuxStamp::Format(2, day);
            order[1] = AuxStamp::Format(2, month);
            order[2] = AuxStamp::Format(4, year);
            break;
        }
        case Date::DateFormat::MDY: {
            order[0] = AuxStamp::Format(2, month);
            order[1] = AuxStamp::Format(2, day);
            order[2] = AuxStamp::Format(4, year);
            break;
        }
        case Date::DateFormat::YMD: {
            order[0] = AuxStamp::Format(4, year);
            order[1] = AuxStamp::Format(2, month);
            order[2] = AuxStamp::Format(2, day);
            break;
        }
        default:
            throw std::invalid_argument( "Date format is not invalid" );
    }

    string_stream << order[0] << Date::SeparatorToChar()
                  << order[1] << Date::SeparatorToChar()
                  << order[2];
    return string_stream.str();
}

} // namespace timestamp
