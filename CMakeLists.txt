cmake_minimum_required(VERSION 3.28)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED on)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

option(RLOG_BUILD_TESTS "Build tests" off)

project(
  rlog
  VERSION 0.1.0
  LANGUAGES C)

add_library(rlog src/rlog.c)
target_include_directories(rlog PUBLIC inc/)

if(RLOG_BUILD_TESTS)

  add_executable(rlog_tests tests/tests.c)
  target_link_libraries(rlog_tests PRIVATE rlog)

endif()
