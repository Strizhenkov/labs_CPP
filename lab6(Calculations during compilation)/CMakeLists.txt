cmake_minimum_required(VERSION 3.20)
project(lab6.2)

add_subdirectory(lib)
add_subdirectory(testing)
set(CMAKE_CXX_STANDARD 14)

add_executable(lab6.2 main.cpp lib/polynomial.h)
target_include_directories(lab6.2 PUBLIC lib)
target_include_directories(testing PUBLIC lib)