# 1. 收集当前目录所有 cpp 文件
file(GLOB SRC_LISTS "*.cpp")

# 2. 创建可执行目标
add_executable(main ${SRC_LISTS})

# 3. 链接动态库 MyMath
# PRIVATE：只自己链接，不继续向下传递
target_link_libraries(main PRIVATE MyMath)

# 4. 设置可执行文件输出路径到构建目录下的 bin 文件夹
set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    # 运行时动态链接器搜索路径，否则 main 运行时找不到 libMyMath.so
    BUILD_RPATH ${CMAKE_BINARY_DIR}/lib
)

#5打印库文件相对main的相对路径
file(RELATIVE_PATH LIB_REL_PATH "${CMAKE_CURRENT_BINARY_DIR}" "${CMAKE_BINARY_DIR}/lib")
add_custom_command(
    TARGET main POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "动态库输出路径 相对main: ${LIB_REL_PATH}"
)

#6安装main
install(TARGETS main)