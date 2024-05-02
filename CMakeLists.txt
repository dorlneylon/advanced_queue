cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++ CACHE PATH "" FORCE)

project(MyProjectName)

add_subdirectory(Catch2)
# target_link_directories(Catch2 PUBLIC Catch2::Catch2WithMain)

set(TEST_SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests")

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${TEST_SOURCES_DIR}/*.cc"
)

set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CTEST_EXECUTABLE_NAME "MyTests")

add_executable(${CTEST_EXECUTABLE_NAME}
    "${SOURCE_DIR}/main.cc"
    ${TEST_SOURCES}
)

target_link_libraries(${CTEST_EXECUTABLE_NAME}
    PRIVATE
        Catch2::Catch2WithMain
)

include(CTest)
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
    "${TEST_SOURCES_DIR}/*.cc"
)
foreach(SOURCE_FILE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${SOURCE_FILE} NAME_WE)
    string(REPLACE ".cc" "" TEST_NAME ${TEST_NAME})
    add_test(NAME ${CTEST_EXECUTABLE_NAME}_${TEST_NAME} COMMAND ${CTEST_EXECUTABLE_NAME})
endforeach()

# set_property(TEST ${CTEST_EXECUTABLE_NAME} PROPERTY TIMEOUT 10)

# Cleanup
set(CTEST_EXECUTABLE_NAME)
set(TEST_SOURCES)
set(TEST_SOURCES_DIR)
set(SOURCE_DIR)
