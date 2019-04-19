cmake_minimum_required(VERSION 3.13)
project(LibCurlWrapper)

set(CMAKE_CXX_STANDARD 14)

set(CURL_LIBRARY "-lcurl")

find_package(CURL REQUIRED)

add_executable(LibCurlWrapper main.cpp WebRequest.cpp WebRequest.h)

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(LibCurlWrapper ${CURL_LIBRARIES})