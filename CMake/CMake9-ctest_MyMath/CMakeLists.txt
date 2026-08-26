cmake_minimum_required(VERSION 3.18)
project(TestMyMath
    LANGUAGES CXX
)

#1开启测试功能
include(CTest)

#2添加测试执行文件
add_executable(main main.cpp)

#3查找MyMAth库
find_package(MyMath CONFIG REQUIRED)

#4链接MyMath库
target_link_libraries(main PRIVATE MyMath::MyMath)

#5添加测试Case到CTest
add_test(
    NAME TestMyMath
    COMMAND main
)