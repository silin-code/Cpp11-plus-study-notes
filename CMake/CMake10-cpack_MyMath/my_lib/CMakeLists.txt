#1收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

#2添加构建目标
add_library(MyMath SHARED ${SRC_LISTS})

#3设置库的使用要求，也就是下游消费者必须包含的头文件搜索路径
target_include_directories(MyMath PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include>"
)

#4设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    OUTPUT_NAME MyMath
    VERSION 1.0.0
    SOVERSION 20
    COMPILE_OPTIONS "-fPIC"
)

#5安装库文件
install(TARGETS MyMath)

#6安装头文件（DESTINATION 必须写在 FILES_MATCHING/PATTERN 之前）
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
