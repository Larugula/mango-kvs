cmake_minimum_required(VERSION 3.14)
project(mango
        VERSION 1.0.0
        DESCRIPTION "a simple KVS built using argula"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(mango_kvs INTERFACE)
add_executable(tester tester.cpp transform.cpp)
target_link_libraries(tester mango_kvs)

add_subdirectory(arugula)
