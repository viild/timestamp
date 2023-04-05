#include "c_api.h"
#include <cstring>

EXPORT_C timestamp_t NewTimestamp()
{
    try {
        return reinterpret_cast<timestamp_t>(Timestamp::TimestampBuilder().BuildPointer());
    } catch (...) {
        return NULL;
    }
}

EXPORT_C timestamp_t NewTimestampSpecific(TimestampFormat_t timestamp_format, DateSeparator_t date_separator,
                                          TimeFormat_t time_format, TimeType_t time_type, TimeDateAppearance_t time_date_appearance,
                                          MonthAsTextType_t month_as_text_type, DayAsTextType_t day_as_text_type, char * pattern,
                                          Bool show_utc_offset, Bool show_seconds, Bool show_milliseconds)
{

    Timestamp::TimestampFormat timestamp_format_cpp;
    Timestamp::DateSeparator date_separator_cpp;
    Timestamp::TimeFormat time_format_cpp;
    Timestamp::TimeType time_type_cpp;
    Timestamp::TimeDateAppearance time_date_appearance_cpp;
    Timestamp::MonthAsTextType month_as_text_type_cpp;
    Timestamp::DayAsTextType day_as_text_type_cpp;

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
        case CUSTOM: {
            timestamp_format_cpp = Timestamp::TimestampFormat::CUSTOM;
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

    switch (month_as_text_type) {
        case M_FULL: {
            month_as_text_type_cpp = Timestamp::MonthAsTextType::FULL;
            break;
        }
        case M_SHORT: {
            month_as_text_type_cpp = Timestamp::MonthAsTextType::SHORT;
            break;
        }
        case M_NONE: {
            month_as_text_type_cpp = Timestamp::MonthAsTextType::NONE;
            break;
        }
        default:
            return NULL;
    }

    switch (day_as_text_type) {
        case D_FULL:  {
            day_as_text_type_cpp = Timestamp::DayAsTextType::FULL;
            break;
        }
        case D_SHORT: {
            day_as_text_type_cpp = Timestamp::DayAsTextType::SHORT;
            break;
        }
        default:
            return NULL;
    }

    Timestamp::TimestampBuilder timestamp_builder = Timestamp::TimestampBuilder().
                                                    SetTimestampFormat(timestamp_format_cpp).
                                                    SetDateSeparator(date_separator_cpp).
                                                    SetTimeFormat(time_format_cpp).
                                                    SetTimeType(time_type_cpp).
                                                    SetTimeDateAppearance(time_date_appearance_cpp).
                                                    SetMonthAsTextType(month_as_text_type_cpp).
                                                    SetDayAsTextType(day_as_text_type_cpp);

    if (pattern)
        timestamp_builder.SetPattern(pattern);

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

EXPORT_C void FreeTimestamp(timestamp_t timestamp_ptr)
{
    try {
        delete reinterpret_cast<Timestamp*>(timestamp_ptr);
    } catch (...) {
        exit(127);
    }
}

EXPORT_C const char * GetTimestamp(timestamp_t timestamp_ptr)
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