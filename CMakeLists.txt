cmake_minimum_required(VERSION 2.9)
project(lturtle)

find_package(SFML 2 REQUIRED COMPONENTS graphics system)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
enable_testing()

FILE(GLOB_RECURSE SOURCES "src/exception/*" "src/lexer/*" "src/parser/*" "src/semantics/*")
FILE(GLOB_RECURSE HEADERS "include/*")
include_directories("include/exception" "include/lexer" "include/parser" "include/semantics")

set(DEFAULT_FLAGS "-Wall -pedantic -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEFAULT_FLAGS} -O0 -g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${DEFAULT_FLAGS} -Werror -O3")

add_library(lturtle_core STATIC ${SOURCES} ${HEADERS})
add_executable(lturtle src/main/main.cpp)
add_executable(lexer_tests src/tests/test_lexer.cpp)
add_executable(parser_tests src/tests/test_parser.cpp)
add_executable(semantics_tests src/tests/test_semantics.cpp)

target_link_libraries(lturtle lturtle_core ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
target_link_libraries(lexer_tests lturtle_core ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(parser_tests lturtle_core ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
target_link_libraries(semantics_tests lturtle_core ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
