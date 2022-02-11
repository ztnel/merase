cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(
  merase
  LANGUAGES C CXX
  VERSION "1.0.0"
  DESCRIPTION "C logger for micro embedded systems"
)

# cmake build guard
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 11)

# Detect if the project is being build within a project or standalone.
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(STANDALONE true)
else()
  set(STANDALONE false)
endif()

if (NOT ${STANDALONE})
    set(MERASE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)
endif()

option(CMAKE_BUILD_TYPE "Specify cmake build type [ Release | Debug ]" ON)

set(MERASE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/merase.c)
set(MERASE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(merase-static STATIC ${MERASE_SRC})
target_include_directories(merase-static PRIVATE ${MERASE_INCLUDE})
target_compile_options(merase-static PRIVATE -fstack-protector-all -Wextra -Wshadow -Wconversion -Wformat -Wundef -fno-common -O3 -g3)

if(CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "Building with debug option")
  message(STATUS "Configuring code coverage")
  list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
  include(cmake/CodeCoverage.cmake)
  append_coverage_compiler_flags()
  set(COVERAGE_EXCLUDES "${PROJECT_SOURCE_DIR}/tests/*" "${PROJECT_SOURCE_DIR}/main.c" "${PROJECT_SOURCE_DIR}/build/*")
  setup_target_for_coverage_gcovr_xml(
    NAME cov
    EXECUTABLE GTEST_COLOR=1 ctest -V
  )  
  message(STATUS "Fetching unittest dependancies")
  # setup gtest and fff
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
  )
  FetchContent_Declare(
    fff
    GIT_REPOSITORY https://github.com/meekrosoft/fff
    GIT_TAG v1.1 
  )
  FetchContent_MakeAvailable(googletest)
  FetchContent_GetProperties(fff)
  # remove gtest confliction
  if(NOT fff_POPULATED)
    FetchContent_Populate(fff)
    file(REMOVE_RECURSE ${fff_SOURCE_DIR}/gtest)
  endif()
  enable_testing()
  add_subdirectory(tests)
endif()