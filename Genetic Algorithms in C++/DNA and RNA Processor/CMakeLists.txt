cmake_minimum_required(VERSION 3.12)
project(ass4)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(ass4
        include/CodonsTable.h
        include/DNA.h
        include/Protein.h
        include/RNA.h
        include/Sequence.h
        src/CodonsTable.cpp
        src/DNA.cpp
        src/Protein.cpp
        src/RNA.cpp
        src/Sequence.cpp
        main.cpp)
