cmake_minimum_required(VERSION 3.8)

project(ArgParser)

add_library(scan_dir STATIC 
	Directory.hpp
	Directory.cpp
)

target_include_directories(scan_dir PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(scan_dir_demo main.cpp)

target_link_libraries(scan_dir_demo PRIVATE scan_dir args_parse)

target_compile_features(scan_dir PUBLIC cxx_std_17)