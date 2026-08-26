cmake_minimum_required(VERSION 3.18)

project(JsoncppDemo
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11)

#查找jsoncpp,使用Config模式
find_package(jsoncpp CONFIG REQUIRED)

#添加构建目标、
add_executable(main main.cpp)

#链接jsoncpp
target_link_libraries(main PRIVATE JsonCpp::JsonCpp)