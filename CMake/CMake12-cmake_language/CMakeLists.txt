cmake_minimum_required(VERSION 3.18)

project(IfBasicExprDemo)

# 1命名常量真
if("ON")
    message("1: true")
else()
    message("1: false")
endif()

# 2常量名假
if("NOT")
    message("2: true")
else()
    message("2: false")
endif()

# 3数字真
if("1")
    message("3: true")
else()
    message("3: false")
endif()

# 4数字假
if("0")
    message("4: true")
else()
    message("4: false")
endif()

# 5不能转换成数字的字符串
if("123A")
    message("5: true")
else()
    message("5: false")
endif()

# 6变量真
set(OS "linux")

if(OS)
    message("6: true")
else()
    message("6: false")
endif()

# 7变量假
set(OS "OFF")

if(OS)
    message("7: true")
else()
    message("7: false")
endif()

# 8字符串字面量
if("abc")
    message("8: true")
else()
    message("8: false")
endif()

# 9字符串字面量-常量
if("on")
    message("9: true")
else()
    message("9: false")
endif()

# 10环境变量
set(ENV{OS} "linux")
message("OS: $ENV{OS}")

if($ENV{OS})
    message("10: true")
else()
    message("10: false")
endif()

# 11变量和7对应
set(OS "ON")

if(${OS})
    message("11: true")
else()
    message("11: false")
endif()

# 12NOT
if(NOT "on")
    message("12: true")
else()
    message("12: false")
endif()

#13AND
if("ON" AND "OFF")
    message("13: true")
else()
    message("13: false")
endif()

#14OR
if("ON" OR "OFF")
    message("14: true")
else()
    message("14: false")
endif()

#15COMMAND
if(COMMAND ls)
    message("15: true")
else()
    message("15: false")
endif()

#16TARGET
add_library(MyMath INTERFACE IMPORTED)

if(TARGET MyMath)
    message("16: true")
else()
    message("16: false")
endif()

#17DEFIND 普通变量定义
set(NAME "silin")
if(DEFINED NAME)
    message("17 :true")
else()
    message("17: false")
endif()

#18DEFIND 缓存变量定义
set(AGE "18" CACHE STRING "age")
if(DEFINED NAME)
    message("18 :true")
else()
    message("18: false")
endif()

#19DEFIND 环境变量定义
if(DEFINED ENV{_})
    message("19 :true")
else()
    message("19: false")
endif()

#20file 文件存在性检测
if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
    message("20: true")
else()
    message("20: false")
endif()

#21数字比较
if("20" LESS "30")
    message("21: true")
else()
    message("21: false")
endif()

#22字符串比较
if("abc" STRLESS "acb")
    message("22: true")
else()
    message("22: false")
endif()

#23版本号比较
set(VERSION "1.2.3")
if(VERSION VERSION_LESS "1.3.0") 
    message("23: true")
else()
    message("23: false")
endif()

