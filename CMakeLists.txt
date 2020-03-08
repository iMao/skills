cmake_minimum_required(VERSION 3.5)

project(skills)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3  -fPIC -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3  -std=c++17 -fPIC -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Werror -pedantic")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lgomp")

set(HDR_LIST
    src/algo/algo.h
    src/oop/oop.h
    src/CPP11/stl/study_stl.h
    src/CPP11/multithreading/tools.h
    src/CPP14/features.h
    src/system/rwlock.h
    src/patterns/pattern_factory.h
    src/patterns/pattern_observer.h
    src/patterns/pattern_strategy.h
)


set(SRC
    src/algo/algo.cpp
    src/oop/oop.cpp
    src/CPP11/stl/study_stl.cpp
    src/CPP11/multithreading/tools.cpp
    src/CPP14/features.cpp
    src/system/rwlock.cpp
)

set(PATTERNS
    src/patterns/pattern_strategy.cpp
    src/patterns/pattern_observer.cpp
    src/patterns/pattern_factory.cpp
    )


include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libs)

#headers
add_custom_target(${PROJECT_NAME}_headers SOURCES ${HDR_LIST} )

#stl library
add_executable(${PROJECT_NAME} ${HDR_LIST} ${SRC} aps/C++17.cpp)
add_executable(${PROJECT_NAME}_stl ${HDR_LIST} ${SRC} aps/stl_cpp11.cpp)
add_executable(${PROJECT_NAME}_multithreading ${HDR_LIST} ${SRC} aps/multithreading_cpp11.cpp)

#system programming
add_executable(${PROJECT_NAME}_rwlock ${HDR_LIST} ${SRC} aps/rwlock_main.cpp)

#patterns usage
add_executable(${PROJECT_NAME}_pattern_strategy ${HDR_LIST}  ${PATTERNS} aps/pattern_strategy_main.cpp)
add_executable(${PROJECT_NAME}_pattern_observer ${HDR_LIST} ${PATTERNS} aps/pattern_observer_main.cpp)
add_executable(${PROJECT_NAME}_pattern_factory ${HDR_LIST} ${PATTERNS} aps/pattern_factory_main.cpp)




