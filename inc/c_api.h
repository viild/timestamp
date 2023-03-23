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

EXPORT_C void    NewTimestamp();
EXPORT_C const char *  Get();

#endif