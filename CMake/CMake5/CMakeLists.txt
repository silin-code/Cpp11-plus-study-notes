cmake_minimum_required(VERSION 3.18)

project(TestMyMath)

add_executable(main main.cpp)

#4查找MyMath数学库
find_package(MyMath CONFIG REQUIRED)

#5声明依赖
target_link_libraries(main PRIVATE MyMath::MyMath)