cmake_minimum_required(VERSION 3.27)
project(artistSearch_main_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(artistSearch_main_2
        artists.cpp
        artists.h
        hashtable.cpp
        hashtable.h
        main.cpp)
