cmake_minimum_required(VERSION 3.16.3)
project(merase-example)

message(STATUS "Building Merase Example")
if(NOT LOG_LEVEL)
    set(LOG_LEVEL 0)
endif()
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_BINARY_DIR}/merase)
include_directories(${MERASE_INCLUDE})
add_executable(merase-ex main.c)
target_compile_definitions(merase-ex PRIVATE LOG_LEVEL=${LOG_LEVEL})
target_link_libraries(merase-ex merase-static)