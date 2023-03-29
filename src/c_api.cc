#include "c_api.h"
#include <cstring>

timestamp_t NewTimestamp()
{
    try {
        return reinterpret_cast<timestamp_t>(Timestamp::TimestampBuilder().BuildPointer());
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampSpecific(TimestampFormat timestamp_format, DateSeparator date_separator,
                                          TimeFormat time_format, TimeType time_type, TimeDateAppearance time_date_appearance,
                                          Bool show_utc_offset, Bool show_seconds, Bool show_milliseconds)
{

    Timestamp::TimestampFormat timestamp_format_cpp;
    Timestamp::DateSeparator date_separator_cpp;
    Timestamp::TimeFormat time_format_cpp;
    Timestamp::TimeType time_type_cpp;
    Timestamp::TimeDateAppearance time_date_appearance_cpp;

    switch (timestamp_format) {
        case DAY_MONTH_YEAR: {
            timestamp_format_cpp = Timestamp::TimestampFormat::DAY_MONTH_YEAR;
            break;
        }
        case MONTH_DAY_YEAR: {
            timestamp_format_cpp = Timestamp::TimestampFormat::MONTH_DAY_YEAR;
            break;
        }
        case YEAR_MONTH_DAY: {
            timestamp_format_cpp = Timestamp::TimestampFormat::YEAR_MONTH_DAY;
            break;
        }
        case RAW: {
            timestamp_format_cpp = Timestamp::TimestampFormat::RAW;
            break;
        }
        default:
            return NULL;
    }

    switch (date_separator) {
        case SLASH: {
            date_separator_cpp = Timestamp::DateSeparator::SLASH;
            break;
        }
        case BACKSLASH: {
            date_separator_cpp = Timestamp::DateSeparator::BACKSLASH;
            break;
        }
        case DOT: {
            date_separator_cpp = Timestamp::DateSeparator::DOT;
            break;
        }
        case DASH: {
            date_separator_cpp = Timestamp::DateSeparator::DASH;
            break;
        }
        default:
            return NULL;
    }

    switch (time_format) {
        case TIME_12_H: {
            time_format_cpp = Timestamp::TimeFormat::TIME_12_H;
            break;
        }
        case TIME_24_H: {
            time_format_cpp = Timestamp::TimeFormat::TIME_24_H;
            break;
        }
        default:
            return NULL;
    }

    switch (time_type) {
        case LOCAL: {
            time_type_cpp = Timestamp::TimeType::LOCAL;
            break;
        }
        case GMT: {
            time_type_cpp = Timestamp::TimeType::GMT;
            break;
        }
        default:
            return NULL;
    }

    switch (time_date_appearance) {
        case ALL: {
            time_date_appearance_cpp = Timestamp::TimeDateAppearance::ALL;
            break;
        }
        case TIME_ONLY: {
            time_date_appearance_cpp = Timestamp::TimeDateAppearance::TIME_ONLY;
            break;
        }
        case DATE_ONLY: {
            time_date_appearance_cpp = Timestamp::TimeDateAppearance::DATE_ONLY;
            break;
        }
        default:
            return NULL;
    }

    Timestamp::TimestampBuilder timestamp_builder = Timestamp::TimestampBuilder().SetTimestampFormat(timestamp_format_cpp).
                SetDateSeparator(date_separator_cpp). SetTimeFormat(time_format_cpp).SetTimeType(time_type_cpp).
                SetTimeDateAppearance(time_date_appearance_cpp);

    if (show_utc_offset == TRUE)
        timestamp_builder.AddUtcOffset();
    
    if (show_seconds == TRUE)
        timestamp_builder.AddSeconds();

    if (show_milliseconds == TRUE)
        timestamp_builder.AddMilliseconds();

    try {
        return reinterpret_cast<timestamp_t>(timestamp_builder.BuildPointer());
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