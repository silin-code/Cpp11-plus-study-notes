#1指定最低CMake版本
cmake_minimum_required(VERSION 3.18)

#2设置项目名称
project(helloWorld
    VERSION 1.1.0
    LANGUAGES CXX
)

#3添加可执行文件构建目标
add_executable(main main.cpp)