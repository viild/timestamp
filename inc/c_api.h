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

EXPORT_C timestamp_t NewTimestamp();
EXPORT_C const char * GetTimestamp(timestamp_t tiemstamp_ptr);
EXPORT_C void FreeTimestamp(timestamp_t timestamp_ptr);

#endif