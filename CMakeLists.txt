cmake_minimum_required(VERSION 3.27)
project(artistSearch_main_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(artistSearch_main_2
        resources/images/code.png
        resources/images/image.jpg
        resources/images/NOTES.md
        resources/MARKDOWN.md
        artists.cpp
        artists.h
        main.cpp
        README.md)
