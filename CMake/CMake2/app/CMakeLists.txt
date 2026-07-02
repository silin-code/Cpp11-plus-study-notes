# 1. 收集当前目录所有 cpp 文件
file(GLOB SRC_LISTS "*.cpp")

# 2. 创建可执行目标
add_executable(main ${SRC_LISTS})

# 3. 链接静态库 MyMath
# PRIVATE：只自己链接，不继续向下传递
target_link_libraries(main PRIVATE MyMath)

# 4. 设置可执行文件输出路径到构建目录下的 bin 文件夹
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)