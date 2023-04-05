# TimeStamp project
## Description

The class Timestamp provides possibility to print timestamp in desired format. The project provides dynamic and static libraries that can be included in C and C++ code on Linux OS. The project is written on C++ but can be used in C code with C API.

There are 2 ways to use the project:

* Use pre-defined types with different options
* Build custom timestamp based on pattern rules

## Types and options
### TimeStamp format

The project suuports the following TimeStamp formats:

* [DAY_MONTH_YEAR] Date will be printed in the order "Day, Month, Year"
* [MONTH_DAY_YEAR] Date will be printed in the order "Month, Day, Year"
* [YEAR_MONTH_DAY] Date will be printed in the order "Year, Month, Day"
* [RAW] Timestamp is printed as integer value as seconds since EPOCH
* [CUSTOM] Timestamp will depend on the provided pattern

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

* [LOCAL] Returns local time where the project is used
* [GMT] Returns GMT time

### Time Date Appearance

There are 2 possible time formats. They are:

* [ALL] Shows both Date and Time
* [TIME_ONLY] Shows Time only
* [DATE_ONLY] Shows Date only

### Month As Text Type

By default month is printed as 2 digit number but can be printed as text in different formats:

* [FULL/M_FULL]  Month is printed in full
* [SHORT/M_SHORT] Month is printed in short
* [NONE/M_NONE] Prints 2 digit number by default

The prefix "M_" is for C API code.

### Day As Text Type

This parameter is only used in CUSTOM timestamp. Pre-defined timestamps do not provide week day.

* [FULL/D_FULL] Day is printed in full
* [SHORT/D_SHORT] Day is printed in full

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
/* Custom TimeStamp in 12H time format and show full day of the week */
Timestamp timestamp = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).
                                                    SetPattern("E dd-MM-yyyy HH:mm a").
                                                    SetTimeFormat(Timestamp::TimeFormat::TIME_12_H).
                                                    SetDayAsTextType(Timestamp::DayAsTextType::FULL).
                                                    Build();
std::cout << "Custom TimeStamp in 12H time format and day of the week = " << timestamp.Get().c_str() << std::endl;

/* Custom TimeStamp in 24H time format, current week, seconds and milliseconds */
/* TODO: format either should be followed by some specifier or text should be somehow separated */
Timestamp timestamp2 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).
                                                        SetPattern("Week w dd-MM-yyyy HH:mm:ss.SSS").
                                                        SetTimeFormat(Timestamp::TimeFormat::TIME_24_H).
                                                        Build();
std::cout << "Custom TimeStamp in 24H time format, current week, seconds and milliseconds = " << timestamp2.Get().c_str() << std::endl;

/* Default custom TimeStamp */
Timestamp timestamp3 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::CUSTOM).Build();
std::cout << "Default custom TimeStamp = " << timestamp3.Get().c_str() << std::endl;


/* Pre-defined Year Month Day format, with seconds, milliseconds and offset */
Timestamp timestamp4 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::YEAR_MONTH_DAY).
                                                        AddSeconds().
                                                        AddMilliseconds().
                                                        AddUtcOffset().
                                                        Build();
std::cout << "Pre-defined Year Month Day format, with seconds, milliseconds and offset = " << timestamp4.Get().c_str() << std::endl;

/* Month Day Year, Date only with Dash separator */
Timestamp timestamp5 = Timestamp::TimestampBuilder().SetTimestampFormat(Timestamp::TimestampFormat::MONTH_DAY_YEAR).
                                                        SetTimeDateAppearance(Timestamp::TimeDateAppearance::DATE_ONLY).
                                                        SetDateSeparator(Timestamp::DateSeparator::DASH).
                                                        Build();
std::cout << "Month Day Year, Date only with Dash separator = " << timestamp5.Get().c_str() << std::endl;

/* Default timestamp */
Timestamp timestamp6 = Timestamp::TimestampBuilder().Build();
std::cout << "Default timestamp = " << timestamp6.Get().c_str() << std::endl;
```

Output:

```
Custom TimeStamp in 12H time format and day of the week = Wednesday 05-04-2023 09:03 PM
Custom TimeStamp in 24H time format, current week, seconds and milliseconds = Week 14 05-04-2023 21:03:17.409
Default custom TimeStamp = 05-04-2023 21:03:17
Pre-defined Year Month Day format, with seconds, milliseconds and offset = 2023/04/05 21:03:17.410 UTC +0200
Month Day Year, Date only with Dash separator = 04-05-2023
Default timestamp = 05/04/2023 21:03
```

### C

The project provides C API to work with the Timestamp class in C code. The header file "c_api.h" should be included to get access to the C-related procedures. No more header files should be included in an application.

In order to use Timestamp functionality one of the following procedures should be called to get the pointer:

Example:

Code:

```
/* Custom TimeStamp in 12H time format and show full day of the week */
timestamp_t timestamp = NewTimestampSpecific(CUSTOM, SLASH, TIME_12_H, LOCAL,
                                                ALL, M_NONE, D_FULL, "E dd-MM-yyyy HH:mm a",
                                                FALSE, FALSE, FALSE);
printf("Custom TimeStamp in 12H time format and day of the week = %s\n", GetTimestamp(timestamp));
FreeTimestamp(timestamp);

/* Custom TimeStamp in 24H time format, current week, seconds and milliseconds */
/* TODO: format either should be followed by some specifier or text should be somehow separated */
timestamp_t timestamp2 = NewTimestampSpecific(CUSTOM, SLASH, TIME_24_H, LOCAL,
                                                ALL, M_NONE, D_FULL, "Week w dd-MM-yyyy HH:mm:ss.SSS",
                                                FALSE, FALSE, FALSE);
printf("Custom TimeStamp in 24H time format, current week, seconds and milliseconds = %s\n", GetTimestamp(timestamp2));
FreeTimestamp(timestamp2);

/* Default custom TimeStamp */
timestamp_t timestamp3 = NewTimestampSpecific(CUSTOM, SLASH, TIME_24_H, LOCAL,
                                                ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                FALSE, FALSE, FALSE);
printf("Default custom TimeStamp = %s\n", GetTimestamp(timestamp3));
FreeTimestamp(timestamp3);


/* Pre-defined Year Month Day format, with seconds, milliseconds and offset */
timestamp_t timestamp4 = NewTimestampSpecific(YEAR_MONTH_DAY, SLASH, TIME_24_H, LOCAL,
                                                ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                TRUE, TRUE, TRUE);
printf("Pre-defined Year Month Day format, with seconds, milliseconds and offset = %s\n", GetTimestamp(timestamp4));
FreeTimestamp(timestamp4);

/* Month Day Year, Date only with Dash separator */
timestamp_t timestamp5 = NewTimestampSpecific(MONTH_DAY_YEAR, DASH, TIME_24_H, LOCAL,
                                                DATE_ONLY, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                FALSE, FALSE, FALSE);
printf("Month Day Year, Date only with Dash separator = %s\n", GetTimestamp(timestamp5));
FreeTimestamp(timestamp5);

/* Default timestamp */
timestamp_t timestamp6 = NewTimestampSpecific(DAY_MONTH_YEAR, SLASH, TIME_24_H, LOCAL,
                                                ALL, M_NONE, D_FULL, "dd-MM-yyyy HH:mm:ss",
                                                FALSE, FALSE, FALSE);
printf("Default timestamp = %s\n", GetTimestamp(timestamp6));
FreeTimestamp(timestamp6);
```

Output:

```
Custom TimeStamp in 12H time format and day of the week = Wednesday 05-04-2023 09:06 PM
Custom TimeStamp in 24H time format, current week, seconds and milliseconds = Week 14 05-04-2023 21:06:11.121
Default custom TimeStamp = 05-04-2023 21:06:11
Pre-defined Year Month Day format, with seconds, milliseconds and offset = 2023/04/05 21:06:11.121 UTC +0200
Month Day Year, Date only with Dash separator = 04-05-2023
Default timestamp = 05/04/2023 21:06
```

The parameters for these procedures should be used from specially designed enumerations for the C code:

```
typedef enum TimestampFormat {
    DAY_MONTH_YEAR,
    MONTH_DAY_YEAR,
    YEAR_MONTH_DAY,
    RAW,
    CUSTOM
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

typedef enum MonthAsTextType {
    M_FULL,
    M_SHORT,
    M_NONE
} MonthAsTextType_t;

typedef enum DayAsTextType {
    D_FULL,
    D_SHORT
} DayAsTextType_t;

typedef enum {
    FALSE,
    TRUE
} Bool;
```

C pointers are not cleared automatically. In order to correctly clear the pointer, use the procedure FreeTimestamp(timestamp_t timestamp_ptr). It deletes Timestamp object in the library using "delete" keyword.

In order to print timestamp where it is necessary, use the procedure "GetTimestamp(timestamp_t tiemstamp_ptr)" where the only argument is the timestamp pointer. It returns C string limited with 64 characters including NULL at the end.

## Know issues

Static library doesn't work with C code.
