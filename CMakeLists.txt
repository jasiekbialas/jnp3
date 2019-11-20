cmake_minimum_required(VERSION 3.13)
project(db406645_jb385150)


set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -std=c++17 -Wshadow")

include_directories("/usr/local/boost_1_71_0")

add_executable(db406645_jb385150
        fibo.cc
        fibo.h main.cpp)

