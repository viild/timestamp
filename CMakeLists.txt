cmake_minimum_required (VERSION 2.8.12)
project (Timestamp)
include(GNUInstallDirs)

set (TS_PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set (TS_PROJECT_INCLUDE_DIR ${TS_PROJECT_ROOT_DIR}/inc)
set (TS_PROJECT_SOURCE_DIR ${TS_PROJECT_ROOT_DIR}/src)
set (TS_PROJECT_OUTPUT_LIBRARY /usr/local/lib/wlc)
set (TS_PROJECT_OUTPUT_PUBLIC_HEADER /usr/local/include/wlc/timestamp)

enable_testing()

#Define default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

#Define default library type
if(NOT PROJECT_LIBRARY_TYPE)
  set(PROJECT_LIBRARY_TYPE "Shared")
endif(NOT PROJECT_LIBRARY_TYPE)

#Header files to use the library
include_directories(${TS_PROJECT_INCLUDE_DIR})

#Compilator's flags
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#Test block
include(${TS_PROJECT_ROOT_DIR}/tests/CMakeLists.txt)

set(TESTS_DIR ${TS_PROJECT_ROOT_DIR}/tests/bins)
macro(add_unit_test target target_test)
    set(UNIT_TEST_TARGETS ${UNIT_TEST_TARGETS} ${target_test} PARENT_SCOPE)
    add_test(target ${CMAKE_CURRENT_BINARY_DIR}/target_test)
endmacro(add_unit_test)

add_test(NAME timestamp_test COMMAND ${TESTS_DIR}/timestamp_test)

#Define default library name
if(NOT LIBRARY_NAME)
  set(LIBRARY_NAME "timestamp")
endif(NOT LIBRARY_NAME)

#Define type of the library
if(PROJECT_LIBRARY_TYPE STREQUAL "Shared")
add_library(${LIBRARY_NAME} SHARED
  ${TS_PROJECT_SOURCE_DIR}/c_api.cc
  ${TS_PROJECT_SOURCE_DIR}/timestamp.cc
)
else()
  add_library(${LIBRARY_NAME} STATIC
  ${TS_PROJECT_SOURCE_DIR}/c_api.cc
  ${TS_PROJECT_SOURCE_DIR}/timestamp.cc
)
endif()

set(TS_HEADERS
 ${TS_PROJECT_INCLUDE_DIR}/c_api.h
 ${TS_PROJECT_INCLUDE_DIR}/timestamp.hh
)

#Test block added here as well in order to run the tests
#correctly during the build
add_custom_target(all_tests ALL
                   DEPENDS ${UNIT_TEST_TARGETS}
)
add_custom_command(TARGET all_tests
                   COMMENT "Run tests"
                   POST_BUILD COMMAND ctest ARGS --output-on-failure
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

#Define library's properties
set_target_properties(timestamp PROPERTIES
  PUBLIC_HEADER "${TS_HEADERS}"
  ARCHIVE_OUTPUT_DIRECTORY "${TS_PROJECT_ROOT_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${TS_PROJECT_ROOT_DIR}/lib"
)

configure_file(${TS_PROJECT_ROOT_DIR}/timestamp.pc.in ${TS_PROJECT_ROOT_DIR}/timestamp.pc @ONLY)

target_include_directories(timestamp PRIVATE ${TS_PROJECT_SOURCE_DIR})
target_include_directories(timestamp PRIVATE ${TS_PROJECT_INCLUDE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  if(PROJECT_LIBRARY_TYPE STREQUAL "Shared")
    add_custom_command(TARGET ${LIBRARY_NAME} POST_BUILD
      COMMAND "/usr/bin/strip" -S -g -d --strip-debug
      "${TS_PROJECT_ROOT_DIR}/lib/lib${LIBRARY_NAME}.so"
      COMMENT "Strip debug symbols done on final binary.")
  else()
    add_custom_command(TARGET timestamp POST_BUILD
      COMMAND "/usr/bin/strip" -S -g -d --strip-debug
      "${TS_PROJECT_ROOT_DIR}/lib/lib${LIBRARY_NAME}.a"
      COMMENT "Strip debug symbols done on final binary.")
  endif()
endif()

install(TARGETS timestamp
  ARCHIVE DESTINATION "${TS_PROJECT_OUTPUT_LIBRARY}"
  LIBRARY DESTINATION "${TS_PROJECT_OUTPUT_LIBRARY}"
  PUBLIC_HEADER DESTINATION ${TS_PROJECT_OUTPUT_PUBLIC_HEADER}
)

install(FILES ${TS_PROJECT_ROOT_DIR}/timestamp.pc
  DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)