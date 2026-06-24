#pragma once
#include <iostream>

// 旧写法：每个cpp一个副本，地址不同
const int bufferSize = 1024;

// 新写法：全局唯一实例，所有cpp共享同一个地址
inline const int cacheSize = 4 * 1024;

void func();