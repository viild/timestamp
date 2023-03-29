#ifndef C_API_H
#define C_API_H

#ifdef __cplusplus
  #define EXPORT_C extern "C"
#else
  #define EXPORT_C
#endif

//============ C++ Only Header =================//
#ifdef __cplusplus  // Enabled only for C++ compilers

#include <iostream>
#include "timestamp.hh"

#endif //-- End of __cplusplus definition //

//============ C-interface for class Runstat ============//

#define MAX_TIMESTAMP_SIZE 64

struct Timestamp;

typedef struct Timestamp Timestamp;
typedef struct Timestamp* timestamp_t;

typedef enum TimestampFormat {
    DAY_MONTH_YEAR,
    MONTH_DAY_YEAR,
    YEAR_MONTH_DAY,
    RAW
} TimestampFormat_t;

typedef enum DateSeparator {
    SLASH,
    BACKSLASH,
    DOT,
    DASH
} DateSeparator_t;

typedef enum TimeFormat {
    TIME_12_H,
    TIME_24_H
} TimeFormat_t;

typedef enum TimeType {
    LOCAL,
    GMT
} TimeType_t;

typedef enum TimeDateAppearance {
    ALL,
    TIME_ONLY,
    DATE_ONLY
} TimeDateAppearance_t;

typedef enum {
  FALSE,
  TRUE
} Bool;

EXPORT_C timestamp_t NewTimestamp();
EXPORT_C timestamp_t NewTimestampSpecific(TimestampFormat_t timestamp_format, DateSeparator_t date_separator,
                                          TimeFormat_t time_format, TimeType_t time_type, TimeDateAppearance_t time_date_appearance,
                                          Bool show_utc_offset, Bool show_seconds, Bool show_milliseconds);
EXPORT_C const char * GetTimestamp(timestamp_t tiemstamp_ptr);
EXPORT_C void FreeTimestamp(timestamp_t timestamp_ptr);

#endif