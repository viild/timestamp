cmake_minimum_required (VERSION 2.8)
project (Tests)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set (TIMESTAMP_DIR ${CMAKE_CURRENT_LIST_DIR}/../)
set (TEST_PROJECT_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set (TEST_PROJECT_INCLUDE_DIR ${TEST_PROJECT_ROOT_DIR})
set (TEST_PROJECT_SOURCE_DIR ${TEST_PROJECT_ROOT_DIR})
set (TEST_OUTPUT_BINS ${TEST_PROJECT_ROOT_DIR}/bins)

set(TEST_SRCS
  ${TEST_PROJECT_SOURCE_DIR}/main.cpp
  ${TIMESTAMP_DIR}/src/ts_date.cc
  ${TIMESTAMP_DIR}/src/ts_time.cc
  ${TIMESTAMP_DIR}/src/ts_raw.cc
  ${TIMESTAMP_DIR}/src/ts_stamp.cc
  ${TIMESTAMP_DIR}/src/ts_timestamp.cc
  ${TEST_PROJECT_SOURCE_DIR}/timestamp_test.cc
  ${TEST_PROJECT_SOURCE_DIR}/raw_test.cc
  ${TEST_PROJECT_SOURCE_DIR}/time_test.cc
  ${TEST_PROJECT_SOURCE_DIR}/date_test.cc
  ${TEST_PROJECT_SOURCE_DIR}/unit_test.cc
)

set(TIME_UT_SRCS
  ${TEST_PROJECT_SOURCE_DIR}/time_test.cc
  ${TIMESTAMP_DIR}/src/ts_time.cc
  ${TIMESTAMP_DIR}/src/ts_stamp.cc
  ${TEST_PROJECT_SOURCE_DIR}/unit_test.cc
)

set(DATE_UT_SRCS
  ${TEST_PROJECT_SOURCE_DIR}/date_test.cc
  ${TIMESTAMP_DIR}/src/ts_date.cc
  ${TIMESTAMP_DIR}/src/ts_stamp.cc
  ${TEST_PROJECT_SOURCE_DIR}/unit_test.cc
)

set(RAW_UT_SRCS
  ${TEST_PROJECT_SOURCE_DIR}/raw_test.cc
  ${TIMESTAMP_DIR}/src/ts_raw.cc
  ${TIMESTAMP_DIR}/src/ts_stamp.cc
  ${TEST_PROJECT_SOURCE_DIR}/unit_test.cc
)

set(TIMESTAMP_UT_SRCS
  ${TEST_PROJECT_SOURCE_DIR}/timestamp_test.cc
  ${TIMESTAMP_DIR}/src/ts_raw.cc
  ${TIMESTAMP_DIR}/src/ts_timestamp.cc
  ${TIMESTAMP_DIR}/src/ts_time.cc
  ${TIMESTAMP_DIR}/src/ts_date.cc
  ${TIMESTAMP_DIR}/src/ts_stamp.cc
  ${TEST_PROJECT_SOURCE_DIR}/unit_test.cc
)

include_directories(${TEST_PROJECT_INCLUDE_DIR})
include_directories(${TIMESTAMP_DIR}/inc)

#Test of Time class
add_executable(time_test ${TIME_UT_SRCS})
set_target_properties(time_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TEST_OUTPUT_BINS}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TEST_OUTPUT_BINS}
  COMPILE_FLAGS "-std=c++11 -DSEPARATE_TEST_BUILD"
)

#Test of Date class
add_executable(date_test ${DATE_UT_SRCS})
set_target_properties(date_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TEST_OUTPUT_BINS}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TEST_OUTPUT_BINS}
  COMPILE_FLAGS "-std=c++11 -DSEPARATE_TEST_BUILD"
)

#Test of Raw class
add_executable(raw_test ${RAW_UT_SRCS})
set_target_properties(raw_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TEST_OUTPUT_BINS}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TEST_OUTPUT_BINS}
  COMPILE_FLAGS "-std=c++11 -DSEPARATE_TEST_BUILD"
)

#Test of Timestamp class
add_executable(timestamp_test ${TIMESTAMP_UT_SRCS})
set_target_properties(timestamp_test PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TEST_OUTPUT_BINS}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TEST_OUTPUT_BINS}
  COMPILE_FLAGS "-std=c++11 -DSEPARATE_TEST_BUILD"
)

add_executable(all_unit_tests ${TEST_SRCS})
set_target_properties(all_unit_tests PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${TEST_OUTPUT_BINS}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${TEST_OUTPUT_BINS}
  COMPILE_FLAGS "-std=c++11"
)
