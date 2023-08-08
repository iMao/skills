cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_SYSTEM
    rwlock.h
    )

set(SRC_SYSTEM
    rwlock.cpp
    )


add_library(system STATIC
    ${HDR_SYSTEM}
    ${SRC_SYSTEM}
    )
target_link_libraries(system
    -lrt
    )
