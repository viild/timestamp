# TimeStamp project
## Description
This projects allows to build timestamp according to a desired format. It provides dynamic and static libraries that can be included in any code that runs on Linux.

Timestamp can be built in different ways, it depends on provided parameters. The basic ones are:

* TimeStamp Format
* Date Separator
* Time Format
* Time Type
* Time Date Appearance
* Milliseconds appearance
* UTC offset appearance
* Seconds appearance

## Basic parameters
### TimeStamp format

The project suuports the following TimeStamp formats:

* [DAY_MONTH_YEAR] Day Month Year
* [MONTH_DAY_YEAR] Month Day Year
* [YEAR_MONTH_DAY] Year Month Day
* [RAW] Shows seconds from EPOCH

### Date Separator

The date in the timestamp can be separated with the following characters:

* [DASH] The date is separated with '-'
* [SLASH] The date is separated with '/'
* [BACKSLASH] The date is separated with '\\'
* [DOT] The date is separated with '.'

### Time Format

There are 2 possible time formats:

* [TIME_12_H] 12 hour time format, like 10 PM or 12 AM
* [TIME_24_H] 24 hour time format, like 22:01 or 01:15

### Time Type

There are 2 possible time types:

* [LOCAL] Shows local time where the project is used
* [GMT] Shows GMT time

### Time Date Appearance

There are 2 possible time formats. They are:

* [ALL] Shows both Date and Time
* [TIME_ONLY] Shows Time only
* [DATE_ONLY] Shows Date only

### Milliseconds appearance

Show or do not show milliseconds. Milliseconds are shown as 3 digit number.

Example:

10:27:02.**275** PM

### UTC offset appearance

If set, the time is shown with some offset from the current UTC.

Example:

30/03/2023 12:35 AM UTC +0200

### Seconds appearance

If set, seconds are added to the time.

Example:

12:35:**19** AM

## Configuring the project

This project uses CMake to generate MakeFile for building the code as library. The library can be either dynamically linked library or archive library. These libraries are compiled for Linux OS only.

Run "cmake ." command in the root directory. Additional flags can be used to configure the project. By default, the project is configured with Release build type and Shared library type.

### Configuring Release and Debug versions

CMake allows to define the variable "CMAKE_BUILD_TYPE" to build Release or Debug libraries. CMake should be used with the following options:

* -DCMAKE_BUILD_TYPE=Release  -  to build the libraries without debug information
* -DCMAKE_BUILD_TYPE=Debug    -  to build the libraries with the debig information

### Configuring libraries

To be able to build different types of libraries for the project is is required to define the variable "PROJECT_LIBRARY_TYPE" in the CMake command:

* -DPROJECT_LIBRARY_TYPE=Shared  -  creates Makefile to build dynamically liked library for Linux OS
* -DPROJECT_LIBRARY_TYPE=Static  -  creates Makefile to build an archive for Linux OS

## Building the project

The project uses automatically generated Makefile file. Firstly generate the file with CMake command.

Run "make" command to build the library and place the files localy.

Run "make install" command to build the library and install the files. The headers are placed at "/usr/local/include/wlc/timestamp/", the libraries are placed at "/usr/local/lib/wlc/".

## Usage

The project provides both C++ and C access.

### C++

The project introduces single class Timestamp with additional class TimestampBuilder to setup desired format of the timestamp. 

The parameters required for the class Timestamp listed above.

Example:

Code:

```
#include <stdio.h>
#include <wlc/timestamp/timestamp.hh>

int main()
{
        Timestamp timestamp = Timestamp::TimestampBuilder().Build();
        Timestamp timestamp_2 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::YEAR_MONTH_DAY).AddSeconds().Build();
        Timestamp * timestamp_3 = Timestamp::TimestampBuilder().AddSeconds().AddMilliseconds().AddUtcOffset().BuildPointer();
        printf("Current Date and Time %s\n", timestamp.Get().c_str());
        printf("Current Date and Time %s\n", timestamp_2.Get().c_str());
        printf("Current Date and Time %s\n", timestamp_3->Get().c_str());
        delete timestamp_3;
}
```

Output:

```
Current Date and Time 30/03/2023 01:00
Current Date and Time 2023/03/30 01:00:32
Current Date and Time 30/03/2023 01:00:32.070 UTC +0200
```

### C

The project provides C API to work with the Timestamp class in C code. The header file "c_api.h" should be included to get access to the C-related procedures. No more header files should be included in an application.

In order to use Timestamp functionality one of the following procedures should be called to get the pointer:

```
timestamp_t NewTimestamp();
timestamp_t NewTimestampSpecific(TimestampFormat_t timestamp_format, DateSeparator_t date_separator,
                                 TimeFormat_t time_format, TimeType_t time_type, TimeDateAppearance_t time_date_appearance,
                                 Bool show_utc_offset, Bool show_seconds, Bool show_milliseconds);
```

The parameters for these procedures should be used from specially designed enumerations for the C code:

```
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
```

C pointers are not cleared automatically. In order to correctly clear the pointer, use the procedure FreeTimestamp(timestamp_t timestamp_ptr). It deletes Timestamp object in the library using "delete" keyword.

In order to print timestamp where it is necessary, use the procedure "GetTimestamp(timestamp_t tiemstamp_ptr)" where the only argument is the timestamp pointer. It returns C string limited with 64 characters including NULL at the end.
