project(design)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{GMOCK_HOME}/include $ENV{GMOCK_HOME}/gtest/include $ENV{JSONCPP_HOME}/include $ENV{CURL_HOME}/include)
link_directories($ENV{GMOCK_HOME}/mybuild $ENV{GMOCK_HOME}/gtest/mybuild $ENV{JSONCPP_HOME}/libs $ENV{CURL_HOME}/build/lib)
add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

set(sources 
   main.cpp 
   CurlHttpTest.cpp CurlHttp.cpp
   AddressExtractorTest.cpp AddressExtractor.cpp
   PlaceDescriptionServiceTest.cpp PlaceDescriptionService.cpp)
add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)
target_link_libraries(test json_linux-gcc)
target_link_libraries(test curl)

