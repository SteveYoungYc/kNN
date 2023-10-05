cmake_minimum_required(VERSION 3.26)
project(chen)

set(CMAKE_CXX_STANDARD 17)

add_executable(chen main.cpp
        knn.cpp
        csv.cpp)
