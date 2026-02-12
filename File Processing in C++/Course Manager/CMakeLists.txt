cmake_minimum_required(VERSION 3.12)
project(FileOrg_Assign3_20170288)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(FileOrg_Assign3_20170288 main.cpp Course.cpp Course.h prIndex.h)