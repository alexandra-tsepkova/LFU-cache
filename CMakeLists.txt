cmake_minimum_required(VERSION 3.16)
project(lfu_cache)

set(CMAKE_CXX_STANDARD 17)

add_executable(lfu_cache main.cpp lfu_cache.h)