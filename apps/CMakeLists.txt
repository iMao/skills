cmake_minimum_required(VERSION 3.5)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include_directories(../src/algo)
include_directories(../src/oop)
include_directories(../src/std11)
include_directories(../src/system)
include_directories(../src/patterns)



#-----------------------tests OOP---------------------------------------------------------------------------------------
add_executable(tests_oop ${HDR_OOP} tests_oop.cpp)
target_link_libraries(tests_oop oop)

#-----------------------tests algorithms--------------------------------------------------------------------------------
add_executable(tests_algo ${HDR_ALGO} tests_algo.cpp)
target_link_libraries(tests_algo algo)


#-----------------------tests system features---------------------------------------------------------------------------
add_executable(tests_system_features ${HDR_SYSTEM} tests_system_features.cpp)
target_link_libraries(tests_system_features system)

##system programming
add_executable(${PROJECT_NAME}_rwlock
        ${skills_headers}
        ${SRC_ALGO}
        ${SRC_OOP}
        ${SRC_PATTERNS}
        ${SRC_STD11}
        ${SRC_STD14}
        ${SRC_SYSTEM}
        rwlock_main.cpp
        )
target_link_libraries(${PROJECT_NAME}_rwlock
        algo
        oop
        patterns
        std11
        system
        -lpthread
        )




#-----------------------tests OOP patterns------------------------------------------------------------------------------
add_executable(tests_oop_patterns ${HDR_PATTERNS} tests_oop_patterns.cpp)
target_link_libraries(tests_oop_patterns patterns)

#patterns usage
add_executable(${PROJECT_NAME}_pattern_strategy
        ${skills_headers}
        ${SRC_ALGO}
        ${SRC_OOP}
        ${SRC_PATTERNS}
        ${SRC_STD11}
        ${SRC_SYSTEM}
        pattern_strategy_main.cpp
        )
target_link_libraries(${PROJECT_NAME}_pattern_strategy
        algo
        oop
        patterns
        std11
        system

        -lpthread
        )


add_executable(${PROJECT_NAME}_pattern_observer
        ${skills_headers}
        ${SRC_ALGO}
        ${SRC_OOP}
        ${SRC_PATTERNS}
        ${SRC_STD11}
        ${SRC_SYSTEM}
        pattern_observer_main.cpp
        )
target_link_libraries(${PROJECT_NAME}_pattern_observer
        algo
        oop
        patterns
        std11
        system

        -lpthread
        )

add_executable(${PROJECT_NAME}_pattern_factory
        ${skills_headers}
        ${SRC_ALGO}
        ${SRC_OOP}
        ${SRC_PATTERNS}
        ${SRC_STD11}
        ${SRC_SYSTEM}
        pattern_factory_main.cpp
        )
target_link_libraries(${PROJECT_NAME}_pattern_factory
        algo
        oop
        patterns
        std11
        system

        -lpthread
        )







# ------------------features of C++11--------------------------------------------

#parallel programming and features C++11
add_executable(${PROJECT_NAME}_parallel_std11 ${HDR_STD11} parallel_C++11.cpp)
target_link_libraries(${PROJECT_NAME}_parallel_std11 std11 -lpthread)

#stl library features C++11
add_executable(${PROJECT_NAME}_stl_std11 ${HDR_STD11} stl_cpp11.cpp)
target_link_libraries(${PROJECT_NAME}_stl_std11 std11 -lpthread)

# feature: alignas(), alignof()
add_executable(alignment features_cpp11_alignment.cpp)

# feature: embedded variable __func__
add_executable(embedded_variable__func__ embedded_variable__func__.cpp)

# feature: user-defined literals
add_executable(user_defined_literals user_defined_literals.cpp)

# feature: using
add_executable(using using.cpp)

# feature: constexpr
add_executable(constexpr constexpr.cpp)

# feature: variadic template
add_executable(variadic_template variadic_template.cpp)

# feature: char16_t, char32_t, R"(raw string)", L"wchar_t string", u8"UTF-8 string",
# u"char16_t string", U"char32_t"
add_executable(char16_char32_wchar_t char16_char32_wchar_t.cpp)

# vector of packaged_task objects
add_executable(packaged_task packaged_task.cpp)
target_link_libraries(packaged_task -lpthread)

#atomic mailbox example
add_executable(atomic_mailbox atomic_mailbox.cpp)
target_link_libraries(atomic_mailbox -lpthread)


# ------------------features of C++14--------------------------------------------
# feature: variable template
add_executable(variable_template variable_template.cpp)

# feature: generic lambda expression
add_executable(generic_lambda generic_lambda.cpp)

# feature: binary literals
add_executable(binary_literals binary_literals.cpp)

# feature: return type deduction
add_executable(return_type_deduction return_type_deduction.cpp)

# feature: aggregate initialization
add_executable(aggregate_initialization aggregate_initialization.cpp)

# feature: std::exchange<>(a,b)
add_executable(exchange exchange.cpp)

# feature: std::quoted()
add_executable(quoted quoted.cpp)

# feature: std::integer_sequence
add_executable(integer_sequence integer_sequence.cpp)

# feature: std::make_unique()
add_executable(make_unique make_unique.cpp)

#feature: std::shared_timed_mutex
add_executable(shared_timed_mutex shared_timed_mutex.cpp)
target_link_libraries(shared_timed_mutex -lpthread)

#------------------features of C++17------------------------------------
# feature std::variant<A,B,C>
add_executable(variant variant.cpp)

# feature std::any
add_executable(any any.cpp)

# feature std::optional
add_executable(optional optional.cpp)

# feature std::constexpr if()
add_executable(constexpr_if constexpr_if.cpp)

# feature nested namespaces mao::dsp::math{}
add_executable(nested_namespaces nested_namespaces.cpp)

# feature std::string_view
add_executable(string_view string_view.cpp)

# feature initializers for if() and switch()
add_executable(initializers_if_switch initializers_if_switch.cpp)

# feature inline variables
add_executable(inline_variables inline_variables.cpp inline_vars.h inline_vars.cpp)

# feature class template argument deduction CTAD
add_executable(class_template_argument_deduction class_template_argument_deduction.cpp)

# feature template parameters auto
add_executable(template_parameters_auto template_parameters_auto.cpp)

# feature structured binding const auto&[a,b] = std::tuple<int, char>(p,q)
add_executable(structured_binding structured_binding.cpp)

# feature noexcept
add_executable(noexcept noexcept.cpp)

# feature parallel algorithms
#add_executable(parallel_algorithms parallel_algorithms.cpp)
#target_link_libraries(parallel_algorithms -ltbb)









