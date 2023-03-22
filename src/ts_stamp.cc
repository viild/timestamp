#include "ts_stamp.h"

/**
 *  Format - sets number and fills the rest with 0
 *  @n: total digest in the final number
 *  @value: number that should be set in the the specified format
 */
std::string AuxStamp::Format(const int n, const int value)
{
    std::stringstream string_stream;
    string_stream << std::setw(n) << std::setfill('0') << value;
    return string_stream.str();
}