cmake_minimum_required(VERSION 3.10)
add_definitions(-std=c++17)

project (thread_pool VERSION 0.1.0 LANGUAGES CXX)

add_library(thread_pool
        src/runner.cpp
        src/thread_pool.cpp)

target_include_directories(thread_pool PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src)
