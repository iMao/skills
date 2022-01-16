cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#include_directories(../src/algo)
#include_directories(../src/oop)
#include_directories(../src/patterns)
include_directories(../src/std11)
#include_directories(../src/std14)
#include_directories(../src/system)




add_executable(${PROJECT_NAME}_std11
    ${HDR_STD11}
    ${SRC_STD11}
    C++11.cpp
    )
target_link_libraries(${PROJECT_NAME}_std11
    std11
    -lpthread
    )


#stl library
add_executable(${PROJECT_NAME}_stl
    ${HDR_STD11}
    ${SRC_STD11}
    stl_cpp11.cpp
    )
target_link_libraries(${PROJECT_NAME}_stl
    std11
    -lpthread
    )

# ------------------features of C++11--------------------------------------------
# feature: alignas(), alignof()
add_executable(alignment features_cpp11_alignment.cpp )

# feature: embedded variable __func__
add_executable(embedded_variable__func__  embedded_variable__func__.cpp )

# feature: user-defined literals
add_executable( user_defined_literals  user_defined_literals.cpp )

# feature: using
add_executable( using  using.cpp )

# feature: constexpr
add_executable(constexpr constexpr.cpp)

# feature: variadic template
add_executable(variadic_template variadic_template.cpp)

# feature: char16_t, char32_t, R"(raw string)", L"wchar_t string", u8"UTF-8 string",
# u"char16_t string", U"char32_t"
add_executable(char16_char32_wchar_t char16_char32_wchar_t.cpp)

# ------------------features of C++14--------------------------------------------
# feature: variable template
add_executable(variable_template variable_template.cpp)

# feature: generic lambda expression
add_executable(generic_lambda generic_lambda.cpp)


# feature: binary literals
add_executable(binary_literals binary_literals.cpp)


# feature: return type deduction
add_executable(return_type_deduction return_type_deduction.cpp)







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





