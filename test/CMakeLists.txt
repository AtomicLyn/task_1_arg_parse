cmake_minimum_required(VERSION 3.8)

project(args_parse_test_app LANGUAGES CXX)

add_executable(unit_test_args_parse main.cpp)

target_link_libraries(unit_test_args_parse
    PRIVATE
        args_parse
        Catch2::Catch2WithMain
)

catch_discover_tests(unit_test_args_parse)