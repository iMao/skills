cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_STD14
    features.h
    )

set(SRC_STD14
    features.cpp
    )


add_library(std14 STATIC
    ${HDR_STD14}
    ${SRC_STD14}
    )
target_link_libraries(std14
    -lrt
    )
