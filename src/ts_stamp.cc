#include "ts_stamp.h"

namespace timestamp {

/**
 *  Stamp - class constructor
 *
 *  This constructor initializes empty pattern.
 */
Stamp::Stamp() : pattern("") {};

/**
 *  GetPattern - return current pattern
 *
 *  This method returns value of "pattern" variable defined in the class.
 */
const std::string Stamp::GetPattern() const
{
    return this->pattern;
}

/**
 *  SetPattern - save new pattern
 *  @pattern: pattern string to save
 *
 *  This method saves new pattern in "pattern" variable defined in the class.
 */
void Stamp::SetPattern(const std::string & pattern)
{
    this->pattern = pattern;
}

/**
 *  GetValue - form string using different arguments
 *  @fmt: format used to form the string
 *
 *  This method forms the string using various arguments. It returns empty string if
 *  "fmt" is empty.
 */
const std::string Stamp::GetValue(const char * fmt, ...) const
{
    char result[kMaxValueSize];
    if (!strcmp(fmt, ""))
        return "";

    va_list args;
    va_start(args, fmt);
    vsprintf(result, fmt, args);
    va_end(args);

    return result;
}

/**
 *  Stamp - class destructor
 *
 *  This destructor does nothing but is necessary because there is virtual function.
 */
Stamp::~Stamp() {}

} // namespace timestamp
