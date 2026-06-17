#include <iostream>
#include <bitset>


// struct Bad {
//     int a = 10;
//     int b = a * 2; // 未定义行为！因为成员初始化顺序是a然后b，但这里依赖于a的初始化
// };
// 错误：初始化顺序和声明顺序不匹配
// Employee e{"张三", 15000.0, 1001}; // id=15000, salary=1001，逻辑错误

// // C++17 结构化绑定
// auto [name, id, salary] = e1;
// std::cout << name << "的工号是" << id << "\n";
// // C++20 支持
// Employee e5{.id = 1003, .salary = 20000.0}; 
// // name="Unknown", id=1003, salary=20000.0

// // 嵌套聚合初始化
// struct Inner {
//     int a;
//     int b;
// };

// struct Outer {
//     Inner i;
//     int c;
// };

// Outer o{.i = {.a = 1, .b = 2}, .c = 3};
// // 聚合类
// struct Point {
//     int x;
//     int y;
// };

// // 聚合初始化
// Point p1 = {1, 2}; // C++98支持
// Point p2{3, 4};    // C++11支持的统一初始化语法
// int main() {
//     // 十进制大数字：每三位分隔（国际通用）
//     int million = 1'000'000; // 1000000
//     long long gdp = 123'456'789'123'456LL;

//     // 十六进制：每四位分隔（对应一个字节）
//     long hex_value = 0xDEAD'BEEF; // 0xDEADBEEF
//     uint32_t ip_address = 0xC0'A8'01'01; // 192.168.1.1

//     // 二进制：每四位或八位分隔
//     unsigned long long big_binary = 0b1010'1010'1010'1010; // 0xAAAA

//     // 浮点数：整数部分和小数部分都可以分隔
//     double pi = 3.141'592'653'589'793;

//     std::cout << "一百万: " << million << "\n";
//     std::cout << "十六进制值: 0x" << std::hex << hex_value << std::dec << "\n";
//     std::cout << "π: " << pi << "\n";
//     return 0;
// }
// #include <iostream>
// #include <bitset>

// int main() {
//     // C++11 写法：需要心算十六进制对应的二进制位
// const uint8_t GPIO_DIR_OUTPUT = 0x55; // 谁能立刻看出哪些位是输出？

// // C++14 写法：一目了然
// const uint8_t GPIO_DIR_OUTPUT = 0b01010101; // 偶数位输出，奇数位输入
//     // 四种进制字面量对比（都表示十进制的42）
//     int d = 42;          // 十进制
//     int o = 052;         // 八进制（前缀0）
//     int x = 0x2a;        // 十六进制（前缀0x/0X）
//     int b = 0b101010;    // 二进制（C++14新增，前缀0b/0B）
//     int c = 0;
//     std::cout << d << "\n" << o << "\n" << x << "\n" << b << "\n"; // 全部输出42

//     const int FLAG_A = 0b0001; // 1
//     const int FLAG_B = 0b0010; // 2
//     const int FLAG_C = 0b0100; // 4
//     const int FLAG_D = 0b1000; // 8

//     int flags = FLAG_A | FLAG_C; // 0b0101
//     std::cout << "标志位: " << std::bitset<4>(flags) << "\n"; // 输出0101

//     if (flags & FLAG_A) {
//         std::cout << "FLAG_A 被设置\n";
//     }
//     return 0;
// }