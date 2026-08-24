#1收集源代码
file(GLOB SRC_LISTS "src/*.cpp")

#2添加构建目标
add_library(MyMath STATIC ${SRC_LISTS})

#3设置库的使用要求，也就是下游消费者必须包含的头文件搜索路径
target_include_directories(MyMath INTERFACE 
    "$<INSTALL_INTERFACE:include:${CMAKE_INSTALL_INCLUDEDIR}>" #/usr/local/include
)

#4设置库的默认输出路径
set_target_properties(MyMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

#5安装静态库
include(GNUInstallDirs)
install(TARGETS MyMath
    EXPORT MyMathTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR} #lib
)

#6安装头文件
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} /math #/usr/local/include/math/math.h
    FILES_MATCHING PATHTERN "*.h"
)

#7安装导出目标集合 到 构建树
export(EXPORT MyMathTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/MyMathTargets.cmake
)

#8安装导出目标集合 到 安装树
install(EXPORT MyMathTargets
    FILE MyMathTargets.cmake
    NAMESPACE MyMath:: #MyMath::MyMath
    DESTINATION ${CMAKE_INSTALL_LOIBDIR}/cmake/MyMath # /usr/local/lib/cmake/MyMathTargets.cmake
)

#9生成find_package需要的配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_DOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
    INSTALL_DESTINATION "lib/cmake/MyMath"
)

#10安装配置文件到1cmake标准的安装路径
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
    DESTINATION "lib/cmake/MyMath"
)