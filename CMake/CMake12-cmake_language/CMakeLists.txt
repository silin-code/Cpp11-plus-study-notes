cmake_minimum_required(VERSION 3.18)

project(ListDemo)

#1创建列表
set(SRCS "main.cpp;utils.cpp;main.cpp")

#2添加元素
list(APPEND SRCS "network.cpp")
message(STATUS "add: ${SRCS}")

#移除元素
list(REMOVE_ITEM SRCS "main.cpp")
message(STATUS "remove: ${SRCS}")

#排序
list(SORT SRCS)
message(STATUS "sort: ${SRCS}")

#遍历列表
foreach(file ${SRCS})
    message(STATUS "file: ${file}")
endforeach()

#求长度
list(LENGTH SRCS LEN)
message(STATUS "len(SRCS): ${LEN}")