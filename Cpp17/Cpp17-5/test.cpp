#include <cstdlib>
#include <iostream>
#include <stdexcept>

// 终止程序的函数
[[noreturn]] void fatal_error(const std::string& message) {
    std::cerr << "Fatal error: " << message << std::endl;
    std::exit(EXIT_FAILURE);
    // 不需要return语句
}

// 永远抛异常的函数
[[noreturn]] void throw_runtime_error(const char* message) {
    throw std::runtime_error(message);
}