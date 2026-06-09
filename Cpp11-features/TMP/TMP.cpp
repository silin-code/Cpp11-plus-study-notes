
// // 定义一个要求T是整形的概念
// template< class T >
// concept Integral = std::is_integral_v<T>;

// // 模板参数后直接使用
// template<Integral T>
// void f1(T x)
// {
//     std::cout << "有 concepts 约束" << std::endl;
// }
// template<typename... Args>
// void print(Args&&... args) {
//     (std::cout << ... << args) << '\n';
//     // 等价于 (((std::cout << arg1) << arg2) << ...) << argN;
// }

// // 使用示例
//print(1, " ", 3.14, " ", "hello"); // 输出：1 3.14 hello
// template <typename T>
// auto process(T value) {
//     if constexpr (std::is_integral_v<T>) {
//         return value * 2;
//     } else if constexpr (std::is_floating_point_v<T>) {
//         return value / 2;
//     } else {
//         return value;
//     }
// }

// // // C++11写法
// // std::is_integral<int>::value;
// // std::remove_const<const int>::type;

// // // C++17写法（推荐）
// // std::is_integral_v<int>;
// // std::remove_const_t<const int>;

// // #include <type_traits>
// // #include <iostream>
// // template<typename T>
// // constexpr T pi = T(3.1415926535897932385);

// // template< class T >
// // constexpr bool is_integral_v = std::is_integral<T>::value;

// // int main() {
// //     float f = pi<float>; // 单精度π
// //     double x = pi<double>; // 双精度π

// //     std::cout.precision(6);
// //     std::cout << "float π: " << f << std::endl;
// //     std::cout.precision(10);
// //     std::cout << "double π: " << x << std::endl;

// //     return 0;
// // }

// // // 传统模板元编程阶乘
// // template <unsigned int N>
// // struct Factorial {
// //     static const unsigned int value = N * Factorial<N - 1>::value;
// // };

// // template <>
// // struct Factorial<0> {
// //     static const unsigned int value = 1;
// // };

// // // constexpr函数阶乘（C++11起）
// // constexpr int factorial(int n) {
// //     return n <= 1 ? 1 : n * factorial(n - 1);
// // }

// // constexpr int x = factorial(5); // 120

// // // 对于整数类型启用此重载
// // template<typename T>
// // typename std::enable_if_t<std::is_integral_v<T>, T>
// // add_one(T t) {
// //     return t + 1;
// // }

// // // 对于浮点类型启用此重载
// // template<typename T>
// // typename std::enable_if_t<std::is_floating_point_v<T>, T>
// // add_one(T t) {
// //     return t + 2.0;
// // }

// // // 模板参数的检查
// // template<typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
// // void process_integer(T value) {
// //     // 只接受整数类型
// // }

// // int main() {
// //     std::cout << add_one(5) << "\n"; // 调用整数版本，输出6
// //     std::cout << add_one(3.14) << "\n"; // 调用浮点版本，输出4.14
// //     process_integer(1);
// //     return 0;
// }
// // 版本1：仅适用于可递增的类型
// // template<typename T>
// // auto foo(T x) -> decltype(++x, void()) {
// //     std::cout << "foo(T): " << x << " (can be incremented)\n";
// // }

// // // 版本2：回退版本
// // void foo(...) {
// //     std::cout << "foo(...): fallback (cannot increment)\n";
// // }

// // int main() {
// //     foo(42); // 调用版本1（int支持++x）
// //     foo(std::string("1111")); // 调用版本2（string不支持++x）
// // }
// // #pragma once
// // #include<assert.h>
// // namespace my
// // {
// //     // 迭代器类别标签
// //     struct input_iterator_tag {};
// //     struct output_iterator_tag {};
// //     struct forward_iterator_tag: public input_iterator_tag {};
// //     struct bidirectional_iterator_tag: public forward_iterator_tag {};
// //     struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// //     // 迭代器特性萃取模板
// //     template <class Iterator>
// //     struct iterator_traits {
// //         typedef typename Iterator::iterator_category iterator_category;
// //         typedef typename Iterator::value_type value_type;
// //         typedef typename Iterator::difference_type difference_type;
// //         typedef typename Iterator::pointer pointer;
// //         typedef typename Iterator::reference reference;
// //     };

// //     // 针对原生指针的特化版本
// //     template <class T>
// //     struct iterator_traits<T*> {
// //         typedef random_access_iterator_tag iterator_category;
// //         typedef T value_type;
// //         typedef ptrdiff_t difference_type;
// //         typedef T* pointer;
// //         typedef T& reference;
// //     };

// //     // 输入迭代器版本：逐个计数
// //     template <class InputIterator>
// //     inline iterator_traits<InputIterator>::difference_type
// //     __distance(InputIterator first, InputIterator last, input_iterator_tag) {
// //         typename iterator_traits<InputIterator>::difference_type n = 0;
// //         while (first != last) {
// //             ++first; ++n;
// //         }
// //         return n;
// //     }

// //     // 随机访问迭代器版本：直接相减
// //     template <class RandomAccessIterator>
// //     inline iterator_traits<RandomAccessIterator>::difference_type
// //     __distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag) {
// //         return last - first;
// //     }

// //     // 统一接口：根据迭代器类别自动选择最优实现
// //     template <class InputIterator>
// //     inline typename iterator_traits<InputIterator>::difference_type
// //     distance(InputIterator first, InputIterator last) {
// //         typedef typename iterator_traits<InputIterator>::iterator_category category;
// //         return __distance(first, last, category());
// //     }

// //     // vector的迭代器构造函数
// //     template<class T>
// //     class vector
// //     {
// //     public:
// //         typedef T* iterator;

// //         template <class InputIterator>
// //         vector(InputIterator first, InputIterator last)
// //         {
// //             // 根据迭代器类型自动选择最优的resize方式
// //             resize(bit::distance(first, last));
// //             while (first != last)
// //             {
// //                 // push_back(*first);
// //                 ++first;
// //             }
// //         }

// //         void resize(size_t n) {}
// //     private:
// //         iterator _start = nullptr;
// //         iterator _finish = nullptr;
// //         iterator _end_of_storage = nullptr;
// //     };
// // }

// int main()
// {
//     string s("hello world");
//     my::vector<char> v1(s.begin(), s.end());

//     std::list<int> lt(10000, 1);
//     my::vector<int> v2(lt.begin(), lt.end());

//     return 0;
// }
// // #include <iostream>
// // #include <vector>

// // namespace my
// // {

// //     // 主模版默认不是指针
// //     template <typename T>
// //     struct is_pointer
// //     {
// //         static constexpr bool value = false;
// //     };

// //     // 针对指针类型的偏特化
// //     template <typename T>
// //     struct is_pointer<T *>
// //     {
// //         static constexpr bool value = true;
// //     };

// //     // 主模版：默认类型不同
// //     template <typename T, typename U>
// //     struct is_same
// //     {
// //         static constexpr bool value = false;
// //     };

// //     // 特化版本，当两个类型相同
// //     template <typename T>
// //     struct is_same<T, T>
// //     {
// //         static constexpr bool value = true;
// //     };

// //     // 主模版:默认不改变类型
// //     template <typename T>
// //     struct remov_const
// //     {
// //         using type = T;
// //     };

// //     //针对const T的特化，移除const
// //     template <typename T>
// //     struct remov_const<const T>
// //     {
// //         using type = T;
// //     };

// //     //移除指针
// //     template<typename T>
// //     struct remove_pointer{
// //         using type = T;
// //     };

// //     template<typename T>
// //     struct remove_pointer<T*>{
// //         using type = T;
// //     };

// //     template<typename T>
// //     struct remove_pointer<T* const>{
// //         using type = T;
// //     };
// //     void func()
// //     {
// //         static_assert(is_pointer<int*>::value, "int* is a pointer");
// //         static_assert(is_same<int, int>::value, "int and int should be the same");
// //         static_assert(is_same<remove_pointer<int*>::type, int>::value, "int and int should be the same");
// //         static_assert(is_same<remove_const<const int>::type, int>::value, "int and int should be the same");
// //     }
// // }

// // int main()
// // {
// //     my::func();
// //     return 0;
// // }


// // template <unsigned int N>
// // struct Factorial
// // {
// //     static const unsigned int value = N * Factorial<N - 1>::value;
// // };

// // //终止条件特化
// // template<>
// // struct Factorial<0>
// // {
// //     static const unsigned int value =1;
// // };

// // int main()
// // {
// //     constexpr unsigned int result = Factorial<5>::value;
// //     return 0;
// // }
// // template <typename T>
// // struct MyTemplate {
// //     using type = T; // 类型成员
// //     static const int value = 42; // 静态成员（编译期常量）
// // };