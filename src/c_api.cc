#include "c_api.h"
#include <cstring>

timestamp_t NewTimestamp()
{
    try {
        return reinterpret_cast<timestamp_t>(new Timestamp(Timestamp::TimestampFormat::DMY));
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampSpecific(TimestampFormat timestamp_format, DateSeparator date_separator,
                                          TimeFormat time_format, Bool show_offset, Bool show_msec)
{
    Timestamp::TimestampFormat timestamp_format_cpp;
    timestamp::Date::DateSeparator date_separator_cpp;
    timestamp::Time::TimeFormat time_format_cpp;
    bool show_offset_cpp;
    bool show_msec_cpp;

    switch (timestamp_format) {
        case DMY: {
            timestamp_format_cpp = Timestamp::TimestampFormat::DMY;
            break;
        }
        case MDY: {
            timestamp_format_cpp = Timestamp::TimestampFormat::MDY;
            break;
        }
        case YMD: {
            timestamp_format_cpp = Timestamp::TimestampFormat::YMD;
            break;
        }
        default:
            return NULL;
    }

    switch (date_separator) {
        case SLASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::SLASH;
            break;
        }
        case BACKSLASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::BACKSLASH;
            break;
        }
        case DOT: {
            date_separator_cpp = timestamp::Date::DateSeparator::DOT;
            break;
        }
        case DASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::DASH;
            break;
        }
        default:
            return NULL;
    }

    switch (time_format) {
        case TIME_12_H_FORMAT: {
            time_format_cpp = timestamp::Time::TimeFormat::TIME_12_H;
            break;
        }
        case TIME_24_H_FORMAT: {
            time_format_cpp = timestamp::Time::TimeFormat::TIME_24_H;
            break;
        }
        default:
            return NULL;
    }

    switch (show_offset) {
        case FALSE: {
            show_offset_cpp = false;
            break;
        }
        case TRUE: {
            show_offset_cpp = true;
            break;
        }
        default:
            return NULL;
    }

    switch (show_msec) {
        case FALSE: {
            show_msec_cpp = false;
            break;
        }
        case TRUE: {
            show_msec_cpp = true;
            break;
        }
        default:
            return NULL;
    }

    try {
        return reinterpret_cast<timestamp_t>(new Timestamp(timestamp_format_cpp,
                    date_separator_cpp, time_format_cpp, show_offset_cpp, show_msec_cpp));
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampDateOnly(TimestampFormat timestamp_format, DateSeparator date_separator)
{
    Timestamp::TimestampFormat timestamp_format_cpp;
    timestamp::Date::DateSeparator date_separator_cpp;

    switch (timestamp_format) {
        case DMY: {
            timestamp_format_cpp = Timestamp::TimestampFormat::DMY_DATE_ONLY;
            break;
        }
        case MDY: {
            timestamp_format_cpp = Timestamp::TimestampFormat::MDY_DATE_ONLY;
            break;
        }
        case YMD: {
            timestamp_format_cpp = Timestamp::TimestampFormat::YMD_DATE_ONLY;
            break;
        }
        default:
            return NULL;
    }

    switch (date_separator) {
        case SLASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::SLASH;
            break;
        }
        case BACKSLASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::BACKSLASH;
            break;
        }
        case DOT: {
            date_separator_cpp = timestamp::Date::DateSeparator::DOT;
            break;
        }
        case DASH: {
            date_separator_cpp = timestamp::Date::DateSeparator::DASH;
            break;
        }
        default:
            return NULL;
    }

    try {
        return reinterpret_cast<timestamp_t>(new Timestamp(timestamp_format_cpp, date_separator_cpp));
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampTimeOnly(TimeFormat time_format, Bool show_offset, Bool show_msec)
{
    timestamp::Time::TimeFormat time_format_cpp;
    bool show_offset_cpp;
    bool show_msec_cpp;

    switch (time_format) {
        case TIME_12_H_FORMAT: {
            time_format_cpp = timestamp::Time::TimeFormat::TIME_12_H;
            break;
        }
        case TIME_24_H_FORMAT: {
            time_format_cpp = timestamp::Time::TimeFormat::TIME_24_H;
            break;
        }
        default:
            return NULL;
    }

    switch (show_offset) {
        case FALSE: {
            show_offset_cpp = false;
            break;
        }
        case TRUE: {
            show_offset_cpp = true;
            break;
        }
        default:
            return NULL;
    }

    switch (show_msec) {
        case FALSE: {
            show_msec_cpp = false;
            break;
        }
        case TRUE: {
            show_msec_cpp = true;
            break;
        }
        default:
            return NULL;
    }

    try {
        return reinterpret_cast<timestamp_t>(new Timestamp(Timestamp::TimestampFormat::TIME_ONLY,
                                time_format_cpp, show_offset_cpp, show_msec_cpp));
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampRaw()
{
    try {
        return reinterpret_cast<timestamp_t>(new Timestamp(Timestamp::TimestampFormat::RAW));
    } catch (...) {
        return NULL;
    }
}

void FreeTimestamp(timestamp_t timestamp_ptr)
{
    try {
        delete reinterpret_cast<Timestamp*>(timestamp_ptr);
    } catch (...) {
        exit(127);
    }
}

const char * GetTimestamp(timestamp_t timestamp_ptr)
{
    static char result[MAX_TIMESTAMP_SIZE];

    if (!timestamp_ptr)
        return "";

    try {
        memset(result, 0, MAX_TIMESTAMP_SIZE);
        strncpy(result, reinterpret_cast<Timestamp*>(timestamp_ptr)->Get().c_str(), MAX_TIMESTAMP_SIZE-1);
        result[MAX_TIMESTAMP_SIZE-1] = 0;
        return result;
    } catch (...) {
        return "";
    }
}