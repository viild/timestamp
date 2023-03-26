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
#include "timestamp.h"

#endif //-- End of __cplusplus definition //

//============ C-interface for class Runstat ============//

#define MAX_TIMESTAMP_SIZE 64

struct Timestamp;

typedef struct Timestamp Timestamp;
typedef struct Timestamp* timestamp_t;

typedef enum {
  DMY,
  MDY,
  YMD
} TimestampFormat;

typedef enum {
  SLASH,
  BACKSLASH,
  DOT,
  DASH
} DateSeparator;

typedef enum {
  TIME_12_H_FORMAT,
  TIME_24_H_FORMAT
} TimeFormat;

typedef enum {
  FALSE,
  TRUE
} Bool;

EXPORT_C timestamp_t NewTimestamp();
EXPORT_C timestamp_t NewTimestampSpecific(TimestampFormat timestamp_format, DateSeparator date_separator,
                                          TimeFormat time_format, Bool show_offset, Bool show_msec);
EXPORT_C timestamp_t NewTimestampDateOnly(TimestampFormat timestamp_format, DateSeparator date_separator);
EXPORT_C timestamp_t NewTimestampTimeOnly(TimeFormat time_format, Bool show_offset, Bool show_msec);
EXPORT_C timestamp_t NewTimestampRaw();
EXPORT_C const char * GetTimestamp(timestamp_t tiemstamp_ptr);
EXPORT_C void FreeTimestamp(timestamp_t timestamp_ptr);

#endif