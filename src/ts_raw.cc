#include "ts_raw.h"

namespace timestamp {

/**
 *  Get - return raw stamp
 *
 *  This method returns long integer as string. The long integer is
 *  result of using of function "time".
 */
const std::string Raw::Get() const
{
    std::stringstream stamp;
    stamp << time(0);
    return stamp.str();
}

} // namespace timestamp
