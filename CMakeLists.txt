cmake_minimum_required(VERSION 3.19)
project(knn)

set(CMAKE_CXX_STANDARD 17)

add_executable(knn main.cpp knn.cpp csv.cpp)
