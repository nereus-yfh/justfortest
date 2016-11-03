
cmake_minimum_required (VERSION 2.8.11)

project (fiber)

set (CMAKE_VERBOSE_MAKEFILE off)

set (CMAKE_FILES_DIRECTORY ${CMAKE_BINARY_DIR})

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/output) 

set (PROJECT_SOURCE_DIR ${CMAKE_BINARY_DIR}/..)

set (CMAKE_CXX_COMPILER /usr/bin/g++) 

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DDEBUG")
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -g -O3")

include_directories (${PROJECT_SOURCE_DIR}/include)

link_libraries (pthread boost_system)

set (EXAMPLE_SRC_DIR ${PROJECT_SOURCE_DIR}/asio_test)

#add_executable (http_server ${EXAMPLE_SRC_DIR}/http_server.cpp)
add_executable (echo_server ${EXAMPLE_SRC_DIR}/async_echo.cpp)

#set (TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/test)

#add_executable (test_server ${TEST_SRC_DIR}/test_server.cpp )
#add_executable (test_client ${TEST_SRC_DIR}/test_client.cpp)



