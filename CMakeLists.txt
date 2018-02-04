cmake_minimum_required (VERSION 2.8)
project (Timestamp)
include(GNUInstallDirs)

set (PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set (PROJECT_INCLUDE_DIR ${PROJECT_ROOT_DIR}/inc)
set (PROJECT_SOURCE_DIR ${PROJECT_ROOT_DIR}/src)

#Define default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

#Define default library type
if(NOT PROJECT_LIBRARY_TYPE)
  set(PROJECT_LIBRARY_TYPE "Shared")
endif(NOT PROJECT_LIBRARY_TYPE)

#Header files to use the library
include_directories(${PROJECT_INCLUDE_DIR})

#Compilator's flags
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -Wall -Werror")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

if(PROJECT_LIBRARY_TYPE STREQUAL "Shared")
add_library(timestamp SHARED
  ${PROJECT_SOURCE_DIR}/ts_date.cc
  ${PROJECT_SOURCE_DIR}/ts_raw.cc
  ${PROJECT_SOURCE_DIR}/ts_stamp.cc
  ${PROJECT_SOURCE_DIR}/ts_time.cc
  ${PROJECT_SOURCE_DIR}/ts_timestamp.cc
)
else()
  add_library(timestamp STATIC
  ${PROJECT_SOURCE_DIR}/ts_date.cc
  ${PROJECT_SOURCE_DIR}/ts_raw.cc
  ${PROJECT_SOURCE_DIR}/ts_stamp.cc
  ${PROJECT_SOURCE_DIR}/ts_time.cc
  ${PROJECT_SOURCE_DIR}/ts_timestamp.cc
)
endif()

#Define library's properties
set_target_properties(timestamp PROPERTIES
  PUBLIC_HEADER ${PROJECT_INCLUDE_DIR}/ts_date.h ${PROJECT_INCLUDE_DIR}/ts_stamp.h ${PROJECT_INCLUDE_DIR}/ts_time.h ${PROJECT_INCLUDE_DIR}/ts_raw.h ${PROJECT_INCLUDE_DIR}/ts_timestamp.h
  ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/lib"
)

configure_file(${PROJECT_ROOT_DIR}/timestamp.pc.in ${PROJECT_ROOT_DIR}/timestamp.pc @ONLY)

target_include_directories(timestamp PRIVATE ${PROJECT_SOURCE_DIR})
target_include_directories(timestamp PUBLIC ${PROJECT_INCLUDE_DIR})

install(TARGETS timestamp
  ARCHIVE DESTINATION "${PROJECT_ROOT_DIR}/lib"
  LIBRARY DESTINATION "${PROJECT_ROOT_DIR}/lib"
  PUBLIC_HEADER DESTINATION ${PROJECT_INCLUDE_DIR}
)

install(FILES ${PROJECT_ROOT_DIR}/timestamp.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
