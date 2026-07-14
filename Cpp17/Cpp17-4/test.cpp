#include <iostream>

// 兼容不同版本的filesystem库
#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#error "需要 filesystem 支持"
#endif

int main() {
    std::cout << "Optional support: " << HAS_OPTIONAL << std::endl;
#if HAS_OPTIONAL
    std::optional<int> opt = 42;
    std::cout << "Optional value: " << *opt << std::endl;
#else
    std::cout << "Optional not available" << std::endl;
#endif
    return 0;
}
//// 检查标准库头文件（尖括号形式）
//#if __has_include(<optional>)
//#include <optional>
//#define HAS_OPTIONAL 1
//#else
//#define HAS_OPTIONAL 0
//#endif
//
//// 检查自定义头文件（双引号形式）
//#if __has_include("my_header.h")
//#include "my_header.h"
//#define HAS_MY_HEADER 1
//#else
//#define HAS_MY_HEADER 0
//#endif
//
//#include<iostream>
//#include<vector>
//#include <string>
//#include <tuple>
//#include <array>
//#include <utility>
//#include <typeinfo>
//
//// 旧写法
//namespace A {
//    namespace B {
//        namespace C {
//            void foo() {
//                std::cout << "Old nested namespace style" << std::endl;
//            }
//        }
//    }
//}
//
//// 新写法
//namespace A::B::C {
//    void bar() {
//        std::cout << "New nested namespace style" << std::endl;
//    }
//}
//
//// 部分嵌套
//namespace A::B {
//    void qux() {
//        std::cout << "Partially nested namespace" << std::endl;
//    }
//}
//
//int main() {
//    A::B::C::foo();
//    A::B::C::bar();
//    A::B::qux();
//    return 0;
//}

//// C++17 写法：简洁直观
//namespace A::B::C {
//    void bar() {
//        std::cout << "New nested namespace style" << std::endl;
//    }
//}
//
//namespace A::B {
//    void qux() {
//        std::cout << "Partially nested namespace" << std::endl;
//    }
//}

//template<auto Value>
//void printValue() {
//    std::cout << "Type: " << typeid(Value).name() << std::endl;
//    std::cout << "---" << std::endl;
//}
//
//// 编译期值列表：可变参数auto非类型模板
//template<auto... Values>
//struct ValueList {
//    ValueList() {
//        ((std::cout << Values << ' '), ...); // 逗号折叠表达式打印
//        std::cout << std::endl;
//    }
//};
//
//const char arr[] = "hello";
//
//int main() {
//    printValue<42>();       // 推导为int
//    printValue<'A'>();      // 推导为char
//    printValue<true>();     // 推导为bool
//    printValue<nullptr>();  // 推导为std::nullptr_t
//    printValue<arr>();      // 推导为const char*
//
//    // C++20才支持，C++17编译报错
//     //printValue<3.14>(); 
//     //printValue<Point{10,20}>();
//
//    ValueList<1, 'a', true> vl; // 输出1 a 1
//    return 0;
//}
//template<auto Value>
//void printValue() {
//    std::cout << "Value: " << Value << std::endl;
//    std::cout << "Type: " << typeid(Value).name() << std::endl;
//}

//// C++14 写法：必须显式指定非类型参数的类型
//template<int Value>
//void printValue() {
//    std::cout << Value << std::endl;
//}
//
//template<char Value>
//void printCharValue() {
//    std::cout << Value << std::endl;
//}


//int main() {
//    // array同时推导类型和长度
//    std::array a = { 1, 2, 3 }; // 推导为 std::array<int, 3>
//
//    // pair推导两个元素的类型
//    std::pair p(1, 2.0); // 推导为 std::pair<int, double>
//
//    // tuple推导多个元素的类型
//    std::tuple t(1, 2.0, std::string("three")); // 推导为 std::tuple<int, double, const char*>
//    return 0;
//}

//int main() {
//    std::vector<int> v1 = { 1, 2, 3 };
//
//    // 1. 初始化列表推导：元素类型为int
//    std::vector v2 = { 4, 5, 6 };
//
//    // 2. 字符串字面量推导：元素类型为const char*
//    std::vector v3{ "hello", "world" };
//
//    // 3. 填充构造推导：两个参数均为int，推导vector<int>
//    std::vector v4(10, 1);
//
//    // 4. 迭代器范围推导：根据迭代器指向的元素类型推导
//    std::vector v5(v1.begin(), v1.end());
//
//    // 5. 空构造报错：无参数无法推导模板类型
//    // std::vector v6; // 编译错误
//
//    return 0;
//}

//int main()
//{
//	//// C++14 写法：必须显式指定模板参数
//	//std::vector<int> v1 = { 1, 2, 3 };
//	//std::pair<int, double> p(1, 2.0);
//	//std::tuple<int, double, const char*> t(1, 2.0, "three");
//
//	// C++17 写法：编译器自动推导模板参数
//	std::vector v2 = { 4, 5, 6 }; // 推导为 std::vector<int>
//	std::pair p(1, 2.0);        // 推导为 std::pair<int, double>
//	std::tuple t(1, 2.0, "three"); // 推导为 std::tuple<int, double, const char*>
//}