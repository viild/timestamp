# TimeStamp project
## Description
This projects allows to build timestamp according to a desired format. It provides dynamic and static libraries that can be included in any code that runs on Linux.

Timestamp can be built in different ways, it depends on provided parameters. The basic ones are:

* TimeStamp Format
* Date Separator
* Time Format
* Milliseconds appearance
* UTC offset appearance

## Basic parameters
### TimeStamp format

The project suuports the following TimeStamp formats:

* [DMY] Day Month Year
* [MDY] Month Day Year
* [YMD] Year Month Day
* [DNY_DATE_ONLY] Same as DMY but doesn't show time
* [MDY_DATE_ONLY] Same as MDY but doesn't show time
* [YMD_DATE_ONLY] Same as YMD but doesn't show time 
* [TIME_ONLY] Shows time only, no date is shown
* [RAW] Shows seconds from EPOCH

### Date Separator

The date in the timestamp can be separated with the following characters:

* [DASH] The date is separated with '-'
* [SLASH] The date is separated with '/'
* [BACKSLASH] The date is separated with '\\'
* [DOT] The date is separated with '.'

### Time Format

There are 2 possible time formats. They are:

* [TIME_12_H] 12 hour time format, like 10 PM or 12 AM
* [TIME_24_H] 24 hour time format, like 22:01 or 01:15

### Milliseconds appearance

Show or do not show milliseconds. Milliseconds are shown as 3 digit number.

Example:

10:27:02.275 PM

### UTC offset appearance

If set, the time is shown with some offset from the cuurent UTC.

Example:

20:27:02.278 UTC +0200

## Building the project

This project uses CMake to generate MakeFile for building the code as library. The library can be either dynamically linked library or archive library. These libraries are compiled for Linux OS only.

### Building Release and Debug versions

CMake allows to define the variable "CMAKE_BUILD_TYPE" to build Release or Debug libraries. CMake should be used with the following options:

* -DCMAKE_BUILD_TYPE=Release  -  to build the libraries without debug information
* -DCMAKE_BUILD_TYPE=Debug    -  to build the libraries with the debig information

### Building libraries

To be able to build different types of libraries for the project is is required to define the variable "PROJECT_LIBRARY_TYPE" in the CMake command:

* -DPROJECT_LIBRARY_TYPE=Shared  -  creates Makefile to build dynamically liked library for Linux OS
* -DPROJECT_LIBRARY_TYPE=Static  -  creates Makefile to build an archive for Linux OS

## Usage

The project provides both C++ and C access.

TBD
