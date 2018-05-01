cmake_minimum_required(VERSION 2.9)
project(lturtle)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
enable_testing()

FILE(GLOB_RECURSE SOURCES "src/exception/*" "src/lexer/*" "src/parser/*")
FILE(GLOB_RECURSE HEADERS "include/*")
include_directories("include/exception" "include/lexer" "include/parser")

set(DEFAULT_FLAGS "-Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEFAULT_FLAGS} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${DEFAULT_FLAGS} -Werror -O3")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} src/main/main.cpp)
add_executable(lexer_tests ${SOURCES} ${HEADERS} src/tests/test_lexer.cpp)

target_link_libraries(lexer_tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
