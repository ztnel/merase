message(STATUS "Beginning test configuration")
add_library(fff INTERFACE)
target_include_directories(
    fff
    INTERFACE
    ${PROJECT_SOURCE_DIR}/build/_deps/fff-src
)

include_directories(${PROJECT_SOURCE_DIR}/include)
set(SOURCES
    ${PROJECT_SOURCE_DIR}/src/merase.c
)

set(TESTS
    ${PROJECT_SOURCE_DIR}/tests/test_merase.cpp
)

foreach(file ${TESTS})
  set(name)
  get_filename_component(name ${file} NAME_WE)
  add_executable(
    ${name}
    ${SOURCES}
    ${file}
    ${PROJECT_SOURCE_DIR}/tests/main.cpp)
  target_link_libraries(${name} gtest_main fff) 
  add_test(NAME ${name} COMMAND ${name})
endforeach()