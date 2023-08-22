cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HDR_PATTERNS
        pattern_factory.h
        pattern_observer.h
        pattern_strategy.h
        )

set(SRC_PATTERNS
        pattern_factory.cpp
        pattern_observer.cpp
        pattern_strategy.cpp
        )


add_library(patterns STATIC
        ${HDR_PATTERNS}
        ${SRC_PATTERNS}
        )
target_link_libraries(patterns -lrt)
