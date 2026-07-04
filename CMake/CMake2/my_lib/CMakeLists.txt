file(GLOB SRC_LISTS "src/*.cpp")
add_library(MyMath STATIC ${SRC_LISTS})

# 设置头文件路径：构建时和安装后均可见
target_include_directories(MyMath PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

set_target_properties(MyMath PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

include(GNUInstallDirs)

# 1. 安装库文件，并关联到导出集 MyMathTargets
install(TARGETS MyMath
    EXPORT MyMathTargets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# 2. 安装头文件到 include/math 目录下
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/math
    FILES_MATCHING PATTERN "*.h"
)

# 3. 导出目标到构建树（仅当前构建目录可用）
export(EXPORT MyMathTargets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/MyMathTargets.cmake
)

# 4. 安装导出目标到系统目录
install(EXPORT MyMathTargets
    FILE MyMathTargets.cmake
    NAMESPACE MyMath::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyMath
)

# 5. 生成 Config 配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
    INSTALL_DESTINATION "lib/cmake/MyMath"
)

# 6. 安装 Config 文件
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
    DESTINATION "lib/cmake/MyMath"
)