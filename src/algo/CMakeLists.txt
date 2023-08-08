cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_ALGO
    algo.h
    )

set(SRC_ALGO
    algo.cpp
    )


add_library(algo STATIC
    ${HDR_ALGO}
    ${SRC_ALGO}
    )
target_link_libraries(algo
    -lrt
    )
