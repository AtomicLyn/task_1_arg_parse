cmake_minimum_required(VERSION 3.28)

project(ArgParser)

add_library(args_parse STATIC 
	Arg.cpp
	ArgParser.cpp
	ArgParser.hpp
	ArgumentType.hpp
	BoolArg.cpp
	BoolArg.hpp
	EmptyArg.cpp
	EmptyArg.hpp
	IntArg.cpp
	IntArg.hpp
	MultiBoolArg.cpp
	MultiBoolArg.hpp
	MultiIntArg.cpp
	MultiIntArg.hpp
	MultiStringArg.cpp
	MultiStringArg.hpp
	StringArg.cpp
	StringArg.hpp
	ParseResult.hpp
	Helpers.hpp
)

target_include_directories(args_parse PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(args_parse_demo main.cpp)

target_link_libraries(args_parse_demo PRIVATE args_parse)

target_compile_features(args_parse PUBLIC cxx_std_17)