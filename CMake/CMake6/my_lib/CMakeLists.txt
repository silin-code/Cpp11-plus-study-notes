#1收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

#2添加构建目标
add_library(MyMath SHARED ${SRC_LISTS})

#3设置库的使用要求，也就是下游消费者必须包含的头文件搜索路径
target_include_directories(MyMath 
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include #/usr/local/include
)

#4设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

#5开启位置无关代码（生成 SHARED 库时 CMake 默认已加 -fPIC，这里显式声明）
set_target_properties(MyMath PROPERTIES POSITION_INDEPENDENT_CODE ON)

