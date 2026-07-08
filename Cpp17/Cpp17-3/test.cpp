#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
void process(T value) {
    if constexpr (std::is_same_v<T, int>) {
        std::cout << "Processing int: " << value * 2 << std::endl;
    }
    else if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "Processing string: " << value.length() << " chars" << std::endl;
    }
    else {
        // 不支持的类型，编译期直接报错
        static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::string>,
            "Unsupported type");
    }
}

int main() {
    process(100);
    process(std::string("test"));
    process(std::vector<int>{1, 2});
    // process(3.14); // 编译错误：触发static_assert
    return 0;
}

//#include <iostream>
//#include <utility>
//
//// C++17 写法：一个函数搞定可变参数打印
//template<typename T, typename... Args>
//void printArgs(T&& arg, Args&&... args) {
//    std::cout << arg;
//    if constexpr (sizeof...(args) > 0) {
//        std::cout << ", ";
//        printArgs(std::forward<Args>(args)...);
//    }
//    else {
//        std::cout << std::endl;
//    }
//}
//
//int main() {
//    printArgs(1, 2.5, "three", '4');
//    return 0;
//}
//#include <iostream>
//#include <type_traits>
//
//template<typename T>
//void printTypeInfo(const T& value) {
//    if constexpr (std::is_integral_v<T>) {
//        std::cout << value << " is an integral type" << std::endl;
//    }
//    else if constexpr (std::is_floating_point_v<T>) {
//        std::cout << value << " is a floating point type" << std::endl;
//    }
//    else if constexpr (std::is_pointer_v<T>) {
//        std::cout << "Pointer to " << *value << std::endl;
//    }
//    else {
//        std::cout << value << " is some other type" << std::endl;
//    }
//}
//
//int main() {
//    printTypeInfo(42);        // 整型分支编译
//    printTypeInfo(3.14);      // 浮点分支编译
//    int x = 10;
//    printTypeInfo(&x);        // 指针分支编译
//    printTypeInfo("hello");   // 其他类型分支编译
//    return 0;
//}
//#include <iostream>
//
//// C++14 写法：SFINAE + 模板重载
//template<typename T>
//typename std::enable_if<std::is_integral_v<T>, void>::type
//printTypeInfo(const T& value) {
//    std::cout << value << " is an integral type" << std::endl;
//}
//
//template<typename T>
//typename std::enable_if<std::is_floating_point_v<T>, void>::type
//printTypeInfo(const T& value) {
//    std::cout << value << " is a floating point type" << std::endl;
//}
//
//int main()
//{
//
//}