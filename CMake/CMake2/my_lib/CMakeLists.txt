#1通配收集所有源文件
file(GLOB SRC_LISTS "src/*.cpp")

#2创建静态库目录
add_library(MyMath STATIC ${SRC_LISTS})

#3设置头文件搜索路径
#PUBLIC自己编译用，下游使用者也会自动获取该路径
target_include_directories(MyMath
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)

#4修改静态库输出路径到构建目录下的lib文件夹
set_target_properties(MyMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)