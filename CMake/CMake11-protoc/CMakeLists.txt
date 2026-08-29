cmake_minimum_required(VERSION 3.18)

project(ProtocExample
    LANGUAGES CXX
)

#设置C++标准
set(CMAKE_CXX_STANDARD 11)

#1查找protobuf库，要求版本>=3.0
find_package(Protobuf 3.0 REQUIRED)

#2收集proto项目描述文件
file(GLOB PROTO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/proto/*.proto)

#3创建protoc的生成文件的目录
set(PB_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/pb)
file(MAKE_DIRECTORY ${PB_OUT_DIR})

#4初始化生成的源代码文件集合,用于生成我们的静态库·,用main使用
set(GEN_SRCS "") # *.pb.cc
set(GEN_HEADS "")# *.pb.h

#5为每一个proto文件生成对应的.cc和.h文件
foreach(PROTO ${PROTO_FILES})
    #5.1获取不带扩展名的文件名
    get_filename_component(BASE_NAME ${PROTO} NAME_WE) #person

    #5.2添加生成的c++文件到源代码集合
    list(APPEND GEN_SRCS ${PB_OUT_DIR}/${BASE_NAME}.pb.cc)
    list(APPEND GEN_HEADS ${PB_OUT_DIR}/${BASE_NAME}.pb.h)

    #5.3为每一个proto文件生成C++文件
    add_custom_command(
        OUTPUT "${PB_OUT_DIR}/${BASE_NAME}.pb.cc" "${PB_OUT_DIR}/${BASE_NAME}.pb.h"
        COMMAND protoc
        ARGS --cpp_out=${PB_OUT_DIR} -I ${CMAKE_CURRENT_SOURCE_DIR}/proto ${PROTO}
        DEPENDS ${PROTO}
        COMMENT "从*.proto生成对应的C++代码"
        VERBATIM
    )
endforeach()

#6添加触发生成pb文件的目标
add_custom_target(generate_protobuf DEPENDS ${GEN_SRCS} ${GEN_HEADS})

#7吧protoc生成的C++文件编译成静态库
add_library(MyProto STATIC ${GEN_SRCS})
add_dependencies(MyProto generate_protobuf)
#main.cpp 需要 #include "person.pb.h"，这里要暴露生成目录为头文件搜索路径
target_include_directories(MyProto PUBLIC
    ${PB_OUT_DIR}
)
target_link_libraries(MyProto PUBLIC protobuf::libprotobuf)

#8添加可执行程序
add_executable(main main.cpp)

#9添加依赖关系
target_link_libraries(main PRIVATE MyProto)