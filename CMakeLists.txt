project(design)
cmake_minimum_required(VERSION 2.6)

include_directories(~/gmock-1.6.0/include ~/gmock-1.6.0/gtest/include ~/jsoncpp-src-0.5.0/include ~/curl-7.27.0/include)
link_directories(~/gmock-1.6.0/mybuild ~/gmock-1.6.0/gtest/mybuild ~/jsoncpp-src-0.5.0/libs/linux-gcc-4.6 ~/curl-7.27.0/build/lib)
add_definitions(-std=c++0x)

set(sources 
   main.cpp 
   CurlHttpTest.cpp CurlHttp.cpp
   stringutilTest.cpp 
   AddressExtractorTest.cpp AddressExtractor.cpp
   PlaceDescriptionServiceTest.cpp PlaceDescriptionService.cpp)
add_executable(test ${sources})
target_link_libraries(test pthread)
target_link_libraries(test gmock)
target_link_libraries(test gtest)
target_link_libraries(test rt)
target_link_libraries(test json_linux-gcc-4.6)
target_link_libraries(test curl)

