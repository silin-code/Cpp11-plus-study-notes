#1设置最低CMake版本
cmake_minimum_required(VERSION 3.18)

#2设置项目名称和版本（CPack 会从 project() 自动取版本号）
project(TestMyMath
    VERSION 1.0.0
    LANGUAGES CXX
)

#3添加目录层级
add_subdirectory(my_lib)

add_subdirectory(app)

#4配置打包参数（注意：要先设置 CPACK_* 变量，再 include(CPack)）
set(CPACK_PACKAGE_NAME "MyApp")
set(CPACK_PACKAGE_VENDOR "silin")          # 厂商名，不能填版本号
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION}) # 版本号，1.0.0
set(CPACK_GENERATOR "TGZ")

#5开启打包功能
include(CPack)
