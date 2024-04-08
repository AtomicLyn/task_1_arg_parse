cmake_minimum_required(VERSION 3.28)

project(ArgParser)

add_library(args_parse STATIC 
	Args.cpp
	Args.hpp
	ArgParser.cpp
	ArgParser.hpp
	ArgumentType.hpp
	ParseResult.hpp
	Helpers.hpp
	Validators.hpp
)

target_include_directories(args_parse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(args_parse_demo main.cpp)

target_link_libraries(args_parse_demo PRIVATE args_parse)

target_compile_features(args_parse PUBLIC cxx_std_17)