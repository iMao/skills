cmake_minimum_required(VERSION 2.8)

project(C17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(hdr
./hdr/algo.h
./hdr/oop.h
./hdr/study_stl.h
./hdr/tools.h
)

set(src
./src/algo.cpp
./src/oop.cpp
./src/study_stl.cpp
./src/tools.cpp
)

add_executable(${PROJECT_NAME} ${hdr}  ${src}   "C++17.cpp")




