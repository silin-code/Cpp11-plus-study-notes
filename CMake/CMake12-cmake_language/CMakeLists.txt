cmake_minimum_required(VERSION 3.18)

project(CaCheScopDemo)

set(OS "MAC" CACHE STRING "OS name" FORCE)
message("OS : ${OS}")
message("OS : $CACHE{OS}")