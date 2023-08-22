cmake_minimum_required(VERSION 3.5)

project(skills)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3  -fPIC -pthread")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3  -std=c++11 -fPIC -pthread")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -pedantic")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libs)


add_subdirectory(apps)
add_subdirectory(src)












