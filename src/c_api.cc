#include "c_api.h"
#include <cstring>

std::unique_ptr < Timestamp > timestamp_obj;

void NewTimestamp()
{
    if (timestamp_obj)
        return;
    timestamp_obj = std::unique_ptr < Timestamp >
                (new Timestamp(Timestamp::TimestampFormat::DMY));
}

const char *  Get()
{
    static char result[256];

    memset(result, 0, 256);

    if (timestamp_obj) {
        strncpy(result, timestamp_obj->Get().c_str(), 256);
        return result;
    }

    return "";
}