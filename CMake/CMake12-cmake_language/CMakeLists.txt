cmake_minimum_required(VERSION 3.18)

project(whilehDemo)

#初始化变量
set(i 1)

#当i <= 5时,就输出i的值
while(i LESS_EQUAL 5)
    message(STATUS "i= ${i}")
    math(EXPR i "${i}+1") #i++
endwhile()
