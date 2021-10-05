cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include_directories(../src/algo)
#include_directories(../src/oop)
#include_directories(../src/patterns)
include_directories(../src/std11)
#include_directories(../src/std14)
#include_directories(../src/system)




#stl library
add_executable(${PROJECT_NAME}_std11
    ${HDR_STD11}
    ${SRC_STD11}
    C++11.cpp
    )
target_link_libraries(${PROJECT_NAME}_std11
    std11
    -lpthread
    )

add_executable(${PROJECT_NAME}_stl
    ${HDR_STD11}
    ${SRC_STD11}
    stl_cpp11.cpp
    )
target_link_libraries(${PROJECT_NAME}_stl
    std11
    -lpthread
    )


#add_executable(${PROJECT_NAME}_multithreading
#    ${skills_headers}
#    ${SRC_ALGO}
#    ${SRC_OOP}
#    ${SRC_PATTERNS}
#    ${SRC_STD11}
#    ${SRC_STD14}
#    ${SRC_SYSTEM}
#    multithreading_cpp11.cpp
#    )
#target_link_libraries(${PROJECT_NAME}_multithreading
#    algo
#    oop
#    patterns
#    std11
#    std14
#    system

#    -lpthread
#    )

##system programming
#add_executable(${PROJECT_NAME}_rwlock
#    ${skills_headers}
#    ${SRC_ALGO}
#    ${SRC_OOP}
#    ${SRC_PATTERNS}
#    ${SRC_STD11}
#    ${SRC_STD14}
#    ${SRC_SYSTEM}
#    rwlock_main.cpp
#    )
#target_link_libraries(${PROJECT_NAME}_rwlock
#    algo
#    oop
#    patterns
#    std11
#    std14
#    system

#    -lpthread
#    )

##patterns usage
#add_executable(${PROJECT_NAME}_pattern_strategy
#    ${skills_headers}
#    ${SRC_ALGO}
#    ${SRC_OOP}
#    ${SRC_PATTERNS}
#    ${SRC_STD11}
#    ${SRC_STD14}
#    ${SRC_SYSTEM}
#    pattern_strategy_main.cpp
#    )
#target_link_libraries(${PROJECT_NAME}_pattern_strategy
#    algo
#    oop
#    patterns
#    std11
#    std14
#    system

#    -lpthread
#    )


#add_executable(${PROJECT_NAME}_pattern_observer
#    ${skills_headers}
#    ${SRC_ALGO}
#    ${SRC_OOP}
#    ${SRC_PATTERNS}
#    ${SRC_STD11}
#    ${SRC_STD14}
#    ${SRC_SYSTEM}
#    pattern_observer_main.cpp
#    )
#target_link_libraries(${PROJECT_NAME}_pattern_observer
#    algo
#    oop
#    patterns
#    std11
#    std14
#    system

#    -lpthread
#    )

#add_executable(${PROJECT_NAME}_pattern_factory
#    ${skills_headers}
#    ${SRC_ALGO}
#    ${SRC_OOP}
#    ${SRC_PATTERNS}
#    ${SRC_STD11}
#    ${SRC_STD14}
#    ${SRC_SYSTEM}
#    pattern_factory_main.cpp
#    )
#target_link_libraries(${PROJECT_NAME}_pattern_factory
#    algo
#    oop
#    patterns
#    std11
#    std14
#    system

#    -lpthread
#    )





