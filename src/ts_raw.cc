#include "ts_raw.h"

namespace timestamp {

/**
 *  Raw - class constructor
 *
 *  This constructor creates an object of the Raw class. This also invokes constructor
 *  of the Stamp class. In brackets, it prepares pattern and throws the exception if
 *  error occurred.
 */
Raw::Raw() : Stamp()
{
    PairIntString rv;
    rv = BuildPattern();
    if (rv.first != 0)
        throw rv.first;
}

/**
 *  BuildPattern - form pattern of the class Date
 *
 *  This method forms the pattern string based on pre-defined value "%d". Once the string
 *  is formed, it is saved in the Stamp class by using "SetPattern" method.
 */
const PairIntString Raw::BuildPattern()
{
    try {
        std::string local_pattern = "%d";
        SetPattern(local_pattern);
    } catch (...) {
        return std::make_pair(1, "Cannot create pattern");
    }

    return std::make_pair(0, "No error");
}

/**
 *  Get - return raw stamp
 *
 *  This method returns long integer as string. The long integer is
 *  result of using of function "time".
 */
const std::string Raw::Get() const
{
    return GetValue(GetPattern().c_str(), time(0));
}

} // namespace timestamp
