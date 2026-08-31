cmake_minimum_required(VERSION 3.18)

project(FunctionDemo)

#形参两个
function(print_args first second)
    message("ARCG = ${ARGC}")#实参个数
    message("ARGV = ${ARGV}")#实参列表;分隔开字符串
    message("ARGV0 = ${ARGV0}")#第一个参数
    message("ARGV1 = ${ARGV1}")#第二个参数
    message("ARGN = ${ARGN}")#剩余的实参列表
endfunction()

print_args(A B C D E)

#实现一个加法函数 演示如何传递结果到外层作用域
function(sum A B)
    math(EXPR RESULT "${A}+${B}")
    set(LOCAL_SUM ${RESULT}) #局部变量
    set(OUT_PUT ${RESULT} PARENT_SCOPE)#f父级作用域
    set(CACHE_SUM ${RESULT} CACHE STRING "sum")#缓存变量
endfunction(sum A B)

sum(3 5)
message(STATUS "LOCAL_SUM = ${LOCAL_SUM}")
message(STATUS "OUTPUT_SUM = ${OUT_PUT}")
message(STATUS "CACHE_SUM = $CACHE{CACHE_SUM}")
