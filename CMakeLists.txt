cmake_minimum_required(VERSION 2.8)

project(C17)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -fopenmp -std=c++17 -fPIC -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -fopenmp -std=c++17 -fPIC -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")



set(hdr
./hdr/algo.h
./hdr/oop.h
./hdr/study_stl.h
./hdr/tools.h
./hdr/rwlock.h
)

set(src
./src/algo.cpp
./src/oop.cpp
./src/study_stl.cpp
./src/tools.cpp
./src/rwlock.cpp
)

add_executable(${PROJECT_NAME} ${hdr} ${src} C++17.cpp)

add_executable(${PROJECT_NAME}_std_array ${hdr} ${src} apps/array_main.cpp)


add_executable(${PROJECT_NAME}_rwlock ${hdr} ${src} apps/rwlock_main.cpp)
