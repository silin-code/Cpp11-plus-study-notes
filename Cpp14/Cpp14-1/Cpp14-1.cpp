#include <iostream>
#include <vector>
#include <string>
#include <memory>



// // 错误：推导f(n-1)时f的返回类型还未确定
// // auto factorial(int n) {
// //     if (n == 0) return 1;
// //     else return n * factorial(n-1);
// // }

// // 解决方法：使用尾置返回类型
// auto factorial(int n) -> int {
//     if (n == 0) return 1;
//     else return n * factorial(n-1);
// }

// int x = 1;

// // C++11写法(必须尾置返回类型)
// auto f1_cpp11() -> int { return x; }
// auto f2_cpp11() -> int & { return x; }

// // C++14写法(直接auto推导)
// auto f1() { return x; }
// auto &f2() { return x; }
// auto f3(int x) { return x * 1.5; }

// // 错误：多返回语句类型必须一致
// // auto f4(int x) {
// //     if (x > 0) return 1.0; // double
// //     else return 2;        // int
// // }

// int main() {
//     std::cout << f1() << "\n"; // 1
//     int& ret = f2();
//     ret++;
//     std::cout << x << "\n";    // 2（x被修改了）
//     return 0;
// }

// // C++20 模板Lambda语法
// auto glambda = []<class T>(T a, auto&& b) {
//     return a < b;
// };

// // 可以显式指定模板参数
// glambda<int>(10, 20.5);

// // 配合概念添加类型约束
// auto integral_sum = []<std::integral T>(T a, T b) {
//     return a + b;
// };

// struct __lambda_getMax {
//     template<class T, class U>
//     auto operator()(const T& a, const U& b) const {
//         return a > b ? a : b;
//     }
// };
// auto getMax = __lambda_getMax{};
// int main()
// {
//     // 1基础泛型lambda：返回两个参数的最大值
//     auto getMax = [](const auto &a, const auto &b)
//     {
//         return a > b ? a : b;
//     };
//     std::cout << getMax(10, 20) << std::endl;
//     std::cout << getMax("apple", "banana") << std::endl;

//     // 2万能引用auto&&遵循引用折叠
//     auto func = [](auto &&x, auto &y)
//     {
//         x += 97;
//         y += 97;
//     };

//     int i = 0, j = 1;
//     func(10, i);
//     func(j, i);

//     //3可变参数泛型lambda+完美转发
//     /*
//      * @brief  泛型可变参数 lambda，将传入的参数完美转发至 vector 的 emplace_back，
//      *         直接在 vector 尾部原地构造 std::string 元素，避免额外的拷贝或移动开销。
//      * @param  ts... 可变参数包，支持任意数量、任意类型的实参（以转发引用形式接收），
//      *               实参将被完美转发用于 std::string 的原地构造。
//      * @return void
//      */
//     std::vector<std::string>v;
//     auto emplace_to_v =[&v](auto&&... ts)
//     {
//         v.emplace_back(std::forward<decltype(ts)>(ts)...);
//     };

//     emplace_to_v("hello");
//     emplace_to_v(std::string("world"));

//     //4初始化捕获C++14，lambda最重要的改进
//     auto p =std::make_unique<int>(10);
//     auto lambda =[value=5,ptr=std::move(p),&v](){
//         std::cout << "捕获的值: " << value << "\n";
//         std::cout << "智能指针值: " << *ptr << "\n";
//         std::cout << "vector大小: " << v.size() << "\n";
//     };
//     lambda();
//     return 0;
// }

// #include <iostream>

// // 编译期幂运算
// template<std::size_t Base, std::size_t Exp>
// constexpr std::size_t power = Base * power<Base, Exp - 1>;

// template<std::size_t Base>
// constexpr std::size_t power<Base, 0> = 1;

// // 使用：编译期计算2^10
// constexpr std::size_t two_pow_10 = power<2, 10>; // 1024

// // C++11 写法
// template<class T>
// struct Pi {
//     static constexpr T value = T(3.1415926535897932385L);
// };

// // 使用时必须加::value
// double area = Pi<double>::value * r * r;

// // 变量模版：定义任意精度的π
// template <class T>
// constexpr T pi = T(3.1415926535897932385L);

// // 函数模版使用变量模版
// template <class T>
// T circular_area(T r)
// {
//     return pi<T> * r * r; // 实例化对应类型的pi变量
// }

// // 编译器计算阶乘模版
// template <size_t N>
// constexpr size_t factorial = N * factorial<N - 1>;

// //全特化：递归终止条件
// template<>
// constexpr size_t factorial<0> = 1;

// //类型萃取的变量模版形式（C++14标准库全面采用）
// template<class T>
// constexpr bool is_const_v = std::is_const<T>::value;

// int main()
// {
//     std::cout.precision(10);
//     std::cout << "float π: " << pi<float> << "\n";   // 3.141592741
//     std::cout << "double π: " << pi<double> << "\n"; // 3.141592654
//     std::cout << "半径2.5的圆面积: " << circular_area(2.5) << "\n";
//     std::cout << "5! = " << factorial<5> << "\n";    // 120
//     std::cout << "int是const吗？" << is_const_v<const int> << "\n"; // 1
//     return 0;
// }
