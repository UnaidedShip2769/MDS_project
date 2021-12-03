cmake_minimum_required(VERSION 3.20)
project(MDS_project)

set(CMAKE_CXX_STANDARD 23)

add_executable(MDS_project main.cpp Shingling.cpp LSH.hpp)
