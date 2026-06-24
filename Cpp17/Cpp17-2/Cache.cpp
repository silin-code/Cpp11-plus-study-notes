#include "Cache.hpp"
void func() {
    std::cout << &bufferSize << std::endl; // 地址1
    std::cout << &cacheSize << std::endl;  // 全局唯一地址
}