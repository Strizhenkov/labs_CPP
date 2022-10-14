cmake_minimum_required(VERSION 3.23)
project(untitled2)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

# include curl
set(CURL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/curl-7.85.0_7-win64-mingw/include)
set(CURL_LIBRARY "${CMAKE_SOURCE_DIR}/curl-7.85.0_7-win64-mingw/lib/libcurl.dll.a")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(untitled2 main.cpp)
target_link_libraries(untitled2 ${CURL_LIBRARIES} nlohmann_json::nlohmann_json)