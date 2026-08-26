#1设置最低CMake版本
cmake_minimum_required(VERSION 3.18)

#2设置项目名称
project(TestMyMath)

#3添加目录层级
add_subdirectory(my_lib)

add_subdirectory(app)