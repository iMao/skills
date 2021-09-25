cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_STD11
    study_stl.h
    tools.h
    )

set(SRC_STD11
    study_stl.cpp
    tools.cpp
    )


add_library(std11
    ${HDR_STD11}
    ${SRC_STD11}
    )
target_link_libraries(std11

    )
