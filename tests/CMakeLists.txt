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

foreach(FILE ${TESTS})
    set(NAME)
    get_filename_component(NAME ${FILE} NAME_WE)
    add_executable(
        ${NAME}
        ${SOURCES}
        ${FILE}
        ${PROJECT_SOURCE_DIR}/tests/main.cpp
    )
    target_link_directories(${NAME} gtest_main fff)
    add_test(NAME ${NAME} COMMAND ${NAME})
endforeach()
