cmake_minimum_required(VERSION 3.18)

project(ForeachDemo)

# #1items
# foreach(X "1" "2;3;4" "abc")
#     message(STATUS "X1: ${X}")
# endforeach()

# #2 range stop
# foreach(X RANGE 10)
#     message(STATUS "X2: ${X}")
# endforeach(X RANGE 10)

# #3range start stop step
# foreach(X RANGE 10 20 3)
#     message(STATUS "X3: ${X}")
# endforeach(X RANGE 10 20 3)

# #4 range items
# foreach(X IN ITEMS "1" "2;3;4" "abc")
#     message(STATUS "X4: ${X}")
# endforeach(X IN ITEMS "1" "2;3;4" "abc")

#5 range Lists
set(L1 "1")
set(L2 "2;4;5")
set(L3 "3")
foreach(X IN LISTS L1 L2 L3)
    message(STATUS "X5: ${X}")
endforeach(X IN LISTS L1 L2 L3)
