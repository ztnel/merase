cmake_minimum_required(VERSION 3.16.3)
project(merase LANGUAGES C VERSION "1.0.0" DESCRIPTION "C logger for micro embedded systems")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

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
endif()