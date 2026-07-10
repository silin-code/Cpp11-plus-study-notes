#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template<typename T>
void formatPrint(const T& val) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << "\"" << val << "\"";
    }
    else if constexpr (std::is_integral_v<T>) {
        std::cout << "[int]" << val;
    }
    else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "[float]" << val;
    }
    else {
        std::cout << val;
    }
}

template<typename... Args>
void smartPrint(Args&&... args) {
    auto printElem = [](const auto& val) {
        formatPrint(val);
        std::cout << " ";
        };
    (..., printElem(args));
    std::cout << std::endl;
}

int main() {
    smartPrint(123, std::string("test"), 3.14, "hello");
    // 输出：[int]123 "test" [float]3.14 hello
    return 0;
}

//template<typename... Args>
//void print(Args&&... args) {
//    (std::cout << ... << args) << '\n';
//    // 展开：(((std::cout << arg1) << arg2) << arg3) << '\n'
//}
//
//int main() {
//    print(1, "hello", 3.14); // 输出1hello3.14
//    return 0;
//}
//// 批量打印参数，带空格分隔
//template<typename... Args>
//void print_with_separator(Args&&... args) {
//    auto print_elem = [](const auto& x)
//        {
//            std::cout << x << " ";
//        };
//    (..., print_elem(args));// 一元左折叠逗号
//    // 展开：((print_elem(arg1), print_elem(arg2)), print_elem(arg3))
//    std::cout << std::endl;
//
//}
//
//// 批量向vector插入元素
//template<typename T, typename... Args>
//void push_back_vec(std::vector<T>& v, Args&&... args) {
//    (v.push_back(std::forward<Args>(args)), ...);
//}
//
//int main() {
//    print_with_separator(1, "hello", 3.14); // 输出1 hello 3.14
//
//    std::vector<int> v;
//    push_back_vec(v, 1, 2, 3, 4);
//    for (int i : v) std::cout << i << ' '; // 输出1 2 3 4
//    return 0;
//}

//// 二元左折叠：字符串拼接，初始值为"%%"
//template<typename... Strings>
//std::string concat_left(Strings... strs)
//{
//	return (std::string("%%") + ... + strs);
//	// 展开：((("%%" + str1) + str2) + str3)
//}
//
//// 二元右折叠：字符串拼接，初始值为"%%"
//template<typename... Strings>
//std::string concat_right(Strings... strs) {
//	return (strs + ... + std::string("%%"));
//	// 展开：str1 + (str2 + (str3 + "%%"))
//}
//
//int main() {
//	std::cout << concat_left("x", "y", "z") << "\n"; // 输出%%xyz
//	std::cout << concat_right("x", "y", "z") << "\n"; // 输出xyz%%
//	return 0;
//}

//// 一元左折叠：逻辑与，判断所有参数是否全为true
//template<typename... Args>
//bool all(Args... args)
//{
//	return (... && args);
//	// 展开：(((arg1 && arg2) && arg3) && arg4)
//}
//// 一元右折叠：求和
//template<typename... Args>
//auto sum(Args... args)
//{
//	return (args + ...);
//	// 展开：arg1 + (arg2 + (arg3 + arg4))
//}
//
//int main()
//{
//	std::cout << all(true, true, false, false) << std::endl;
//	std::cout << sum(1, 2, 3, 4) << std::endl;
//}

////C++11/14写法：递归模版
//template<class T>
//T sum(T t)
//{
//	return t;
//}
//
//template<class T,class... Args>
//T sum(T first, Args... args)
//{
//	return first + sum(args...);
//}


//template<typename T>
//void process(T value) {
//    if constexpr (std::is_same_v<T, int>) {
//        std::cout << "Processing int: " << value * 2 << std::endl;
//    }
//    else if constexpr (std::is_same_v<T, std::string>) {
//        std::cout << "Processing string: " << value.length() << " chars" << std::endl;
//    }
//    else {
//        // 不支持的类型，编译期直接报错
//        static_assert(std::is_same_v<T, int> || std::is_same_v<T, std::string>,
//            "Unsupported type");
//    }
//}
//
//int main() {
//    process(100);
//    process(std::string("test"));
//    process(std::vector<int>{1, 2});
//    // process(3.14); // 编译错误：触发static_assert
//    return 0;
//}

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