cmake_minimum_required(VERSION 3.18)
project(CMake3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MyMath REQUIRED PATHS "${CMAKE_CURRENT_SOURCE_DIR}/../CMake2/build/my_lib")

add_executable(main main.cpp)
target_link_libraries(main PRIVATE MyMath)
