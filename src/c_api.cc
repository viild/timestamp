#include "c_api.h"
#include <cstring>

timestamp_t NewTimestamp()
{
    return reinterpret_cast<timestamp_t>(new Timestamp(Timestamp::TimestampFormat::DMY));
}

void FreeTimestamp(timestamp_t timestamp_ptr)
{
    delete reinterpret_cast<Timestamp*>(timestamp_ptr);
}

const char * GetTimestamp(timestamp_t timestamp_ptr)
{
    static char result[MAX_TIMESTAMP_SIZE];

    if (!timestamp_ptr)
        return "";

    memset(result, 0, MAX_TIMESTAMP_SIZE);
    strncpy(result, reinterpret_cast<Timestamp*>(timestamp_ptr)->Get().c_str(), MAX_TIMESTAMP_SIZE-1);
    result[MAX_TIMESTAMP_SIZE-1] = 0;
    return result;
}