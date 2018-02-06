#include "ts_stamp.h"

namespace timestamp {

/**
 *  PlaceTwoDigits - return string in specified format
 *  @value: value to return in specified format
 *
 *  This method returns the string with decimal value in format
 *  %02d or 00-99.
 */
std::string Stamp::PlaceTwoDigits(const int value)
{
    std::stringstream string_stream;
    string_stream << std::setw(2) << std::setfill('0') << value;
    return string_stream.str();
}

/**
 *  PlaceThreeDigits - return string in specified format
 *  @value: value to return in specified format
 *
 *  This method returns the string with decimal value in format
 *  %03d or 000-999.
 */
std::string Stamp::PlaceThreeDigits(const int value)
{
    std::stringstream string_stream;
    string_stream << std::setw(3) << std::setfill('0') << value;
    return string_stream.str();
}

/**
 *  PlaceFourDigits - return string in specified format
 *  @value: value to return in specified format
 *
 *  This method returns the string with decimal value in format
 *  %04d or 0000-9999.
 */
std::string Stamp::PlaceFourDigits(const int value)
{
    std::stringstream string_stream;
    string_stream << std::setw(4) << std::setfill('0') << value;
    return string_stream.str();
}

} // namespace timestamp
