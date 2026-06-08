#include <iostream>
#include <tuple>
#include <utility>
#include <string>

// 返回多个值：姓名、年龄、分数
std::tuple<std::string, int, double> getStudentInfo(int id) {
    if (id == 1) {
        return {"Alice", 18, 95.5};
    } else {
        return {"Bob", 20, 88.0};
    }
}

int main() {
    auto [name, age, score] = getStudentInfo(1);
    // 使用name、age、score
    return 0;
}

// // C++17折叠表达式遍历
// template<typename... Args>
// void print_tuple(const std::tuple<Args...>& t) {
//     std::apply([](const auto&... args) {
//         ((std::cout << args << " "), ...);
//     }, t);
//     std::cout << std::endl;
// }

// int main() {
//     auto t = std::make_tuple(1, 3.14, "hello", true);
//     print_tuple(t); // 输出：1 3.14 hello 1
//     return 0;
// }

// int main() {
//     auto t1 = std::make_tuple(1, 2, 3);
//     auto t2 = std::make_tuple(1, 2, 4);
//     auto t3 = std::make_tuple(1, 3, 0);

//     std::cout << (t1 < t2) << std::endl; // 输出1（true）
//     std::cout << (t1 < t3) << std::endl; // 输出1（true）
//     std::cout << (t2 == t3) << std::endl; // 输出0（false）

//     return 0;
// }

// int main() {
//     auto t1 = std::make_tuple(1, 2);
//     auto t2 = std::make_tuple(3.14, "hello");
//     auto t3 = std::make_tuple(true);

//     auto t4 = std::tuple_cat(t1, t2, t3);
//     // t4的类型是std::tuple<int, int, double, const char*, bool>

//     return 0;
// }

// int main() {
//     std::tuple<int, double, std::string> t1(10, 3.14, "hello");

//     int x;
//     double y;
//     std::string z;

//     // 1. 使用std::tie解包
//     std::tie(x, y, z) = t1;
//     std::cout << x << ", " << y << ", " << z << std::endl;

//     // 2. C++17结构化绑定（推荐）
//     auto [a, b, c] = t1;
//     std::cout << a << ", " << b << ", " << c << std::endl;

//     return 0;
// }

// int main() {
//     std::tuple<int, double, std::string> t1(10, 3.14, "hello");

//     // 通过索引访问
//     std::cout << std::get<0>(t1) << std::endl; // 输出10
//     std::cout << std::get<1>(t1) << std::endl; // 输出3.14
//     std::cout << std::get<2>(t1) << std::endl << std::endl; // 输出"hello"

//     // 修改元素
//     std::get<0>(t1) = 100; // 修改第一个元素

//     // C++14起可以通过类型访问（类型必须唯一）
//     std::cout << std::get<int>(t1) << std::endl; // 输出100
//     std::cout << std::get<double>(t1) << std::endl; // 输出3.14

//     return 0;
// }
// int main() {
//     // 1. 直接构造，显式指定类型
//     std::tuple<int, double, std::string> t1(10, 3.14, "hello");

//     // 2. 使用make_tuple自动推导类型
//     auto t2 = std::make_tuple(20, 2.718, "world");

//     // 3. C++17起可以使用类模板参数推导
//     std::tuple t3(30, 1.618, "cpp"); // 自动推导为tuple<int, double, const char*>

//     return 0;
// }

// constexpr auto x = 10;
// static_assert(x > 5, "x must be greater than 5"); // 错误：x是运行时变量
// // 计算阶乘，检查输入是否为非负数
// template<unsigned int N>
// struct Factorial {
//     static_assert(N >= 0, "N must be non-negative");
//     static constexpr unsigned int value = N * Factorial<N - 1>::value;
// };

// template<>
// struct Factorial<0> {
//     static constexpr unsigned int value = 1;
// };

// int main() {
//     // Factorial<-1>::value; // 编译错误：N must be non-negative
//     return 0;
// }

// // 检查T是否是可复制构造且可移动构造的类型
// template<typename T>
// void func(T t) {
//     static_assert(std::is_copy_constructible_v<T>, "T must be copy constructible");
//     static_assert(std::is_move_constructible_v<T>, "T must be move constructible");
//     static_assert(!std::is_pointer_v<T>, "T must not be a pointer type");
// }

// // 检查类是否有特定的成员函数
// template<typename T>
// class MyClass {
//     static_assert(std::is_member_function_pointer_v<decltype(&T::toString)>,
//                   "T must have a toString() member function");
// };

// // 1. 类型检查
// template<typename T>
// void process(T value) {
//     static_assert(std::is_integral<T>::value, "T must be an integral type");
//     // 函数实现...
// }

// // 2. 编译时常量验证
// constexpr int buffer_size = 1024;
// static_assert(buffer_size > 0, "Buffer size must be positive");
// static_assert(buffer_size % 4 == 0, "Buffer size must be divisible by 4");

// // 3. 平台或架构检查
// static_assert(sizeof(void*) == 8, "This code requires 64-bit platform");

// // 4. 类型大小验证
// static_assert(sizeof(int) == 4, "int must be 4 bytes");

// enum class FileAccess : uint8_t {
//     Read = 1 << 0,
//     Write = 1 << 1,
//     Execute = 1 << 2
// };

// // 重载|运算符
// constexpr FileAccess operator|(FileAccess a, FileAccess b) {
//     return static_cast<FileAccess>(
//         static_cast<std::underlying_type_t<FileAccess>>(a) |
//         static_cast<std::underlying_type_t<FileAccess>>(b)
//     );
// }

// // 重载&运算符
// constexpr bool operator&(FileAccess a, FileAccess b) {
//     return (static_cast<std::underlying_type_t<FileAccess>>(a) &
//             static_cast<std::underlying_type_t<FileAccess>>(b)) != 0;
// }

// int main() {
//     FileAccess access = FileAccess::Read | FileAccess::Write;
//     if (access & FileAccess::Read) {
//         // 有读权限
//     }
//     return 0;
// }


// enum class Direction { Left, Right, Up, Down };
// void move(Direction dir) {
//     switch (dir) {
//         using enum Direction; // 引入所有枚举值
//         case Left:  /* ... */ break;
//         case Right: /* ... */ break;
//         case Up:    /* ... */ break;
//         case Down:  /* ... */ break;
//     }
// }
// // enum class Color { Red, Green, Blue };
// enum class TrafficLight { Red, Yellow, Green }; // 正确：作用域隔离，无重定义

// // 指定底层类型
// enum class SmallEnum : uint8_t { Value1, Value2 }; // 8位存储
// enum class BigEnum : uint32_t { Value1, Value2 }; // 32位存储

// int main() {
//     Color c1 = Color::Red; // 正确：必须通过枚举名访问
//     // Color c2 = Red; // 错误：不能直接使用枚举值
//     // int i = Color::Red; // 错误：不能隐式转换为int
//     int j = static_cast<int>(Color::Red); // 正确：显式转换

//     // C++20支持：引入枚举值到当前作用域
//     using enum Color;
//     Color c = Red; // 现在可以直接使用

//     return 0;
// }

// // 传统枚举的问题示例
// enum Color { Red, Green, Blue };
// enum TrafficLight { Red, Yellow, Green }; // 错误：Red和Green重定义，作用域污染

// int main() {
//     Color c = Red;
//     int i = c; // 隐式转换为int，可能导致意外
//     if (c == 0) { // 可以和整数直接比较，语义模糊
//         // ...
//     }
//     return 0;
// }