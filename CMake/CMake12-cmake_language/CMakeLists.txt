cmake_minimum_required(VERSION 3.18)

project(MessageDemo)

message("begin CMakeLists.txt")
message(STATUS "begin CMakeLists.txt")

message(STATUS "1" "2" "3")

#message(WARNING "This is Warning")

#message(SEND_ERROR "This is Error")

message(FATAL_ERROR "This is fatal error")

message(STATUS "end CMakeLists.txt")