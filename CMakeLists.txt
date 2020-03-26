cmake_minimum_required(VERSION 3.14)
project(mango
        VERSION 1.0.0
        DESCRIPTION "a simple KVS built using argula"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_executable(mango base_kvs.hpp)
set_target_properties(mango PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(arugula)
