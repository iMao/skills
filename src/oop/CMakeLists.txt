cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_OOP
    oop.h
    )

set(SRC_OOP
    oop.cpp
    )


add_library(oop STATIC
    ${HDR_OOP}
    ${SRC_OOP}
    )
target_link_libraries(oop
    -lrt
    )
