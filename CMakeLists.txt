cmake_minimum_required(VERSION 3.13)
project(db406645_jb385150)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O2 -Wshadow")

include_directories("/usr/local/boost_1_71_0")

add_executable(main main.cpp fibo.cc)
add_executable(example fibo_example.cc fibo.cc)
