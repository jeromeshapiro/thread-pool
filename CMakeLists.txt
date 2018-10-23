cmake_minimum_required(VERSION 3.10)
add_definitions(-std=c++17)

project (thread_pool)

include_directories(include)
file(GLOB SOURCES src/*.cpp)
