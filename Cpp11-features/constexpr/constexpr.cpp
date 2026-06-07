#include<iostream>
#include<vector>
#include<array>
#include<string>
#include<algorithm>
using namespace std;


// consteval int square(int n) {
//     return n * n;
// }

// constexpr int compute_value() {
//     return 42;
// }

// constinit int global = compute_value(); // 正确
// constinit int squared_value = square(5); // 正确

// // 确保复杂对象在编译期初始化
// class ComplexInit {
//     int value;
// public:
//     constexpr ComplexInit(int v) : value(v) {}
// };

// constinit ComplexInit obj{42}; // 全局对象确保编译期初始化

// int main() {
//     // constinit int local = 10; // 错误：只能用于静态存储期变量
//     squared_value = 30; // 可以修改
//     return 0;
// }

// constexpr int square(int x) {
//     return x * x;
// }

// int main() {
//     // 场景1：编译时求值
//     constexpr int const_val = square(10); // 必须在编译时计算
//     int array[const_val];

//     // 场景2：运行时求值
//     int runtime_input = 5;
//     int runtime_val = square(runtime_input); // 运行时调用

//     return 0;
// }

// // 将square改为consteval修饰
// consteval int square_consteval(int x) {
//     return x * x;
// }

// int main() {
//     constexpr int const_val = square_consteval(10); // 正确
//     int runtime_input = 5;
//     int runtime_val = square_consteval(runtime_input); // 报错：必须编译期求值
// }
// // constexpr虚函数示例
// class Base {
// public:
//     virtual constexpr int value() const { return 1; }
// };

// class Derived : public Base {
// public:
//     constexpr int value() const override { return 2; }
// };

// constexpr int get_value(const Base& b) {
//     return b.value(); // 编译期多态调用
// }

// int main() {
//     constexpr int ret1 = get_value(Base()); // 1
//     constexpr int ret2 = get_value(Derived()); // 2
//     return 0;
// }

// constexpr int safe_divide(int a, int b) {
//     try {
//         if (b == 0)
//             throw "Division by zero";
//         else
//             return a / b;
//     }
//     catch (...) {
//         return 0; // 编译期异常处理
//     }
// }

// int main()
// {
//     constexpr int val1 = safe_divide(10, 2); // 5
//     // constexpr int val2 = safe_divide(10, 0); // 报错：抛出异常不是常量表达式
//     return 0;
// }

// // 编译报错：vector的析构函数在编译期无法释放内存
// // constexpr std::vector<int> create_vector() {
// //     std::vector<int> v{1, 2, 3};
// //     v.push_back(4);
// //     return v;
// // }

// constexpr auto sort_example() {
//     std::array<int, 5> arr{5, 3, 4, 1, 2};
//     std::sort(arr.begin(), arr.end()); // 编译期排序
//     return arr;
// }

// int main()
// {
//     // constexpr auto vec = create_vector(); // 编译失败
//     constexpr auto sorted = sort_example(); // {1,2,3,4,5}
//     constexpr auto it2 = find(sorted.begin(), sorted.end(), 4);
//     static_assert(*it2 == 4, "编译期查找");

//     return 0;
// }

// constexpr int dynamic_memory_example() {
//     int* p = new int{42}; // 编译期分配
//     int value = *p;
//     delete p; // 必须显式释放
//     return value;
// }

// int main()
// {
//     constexpr int v = dynamic_memory_example(); // 42
//     return 0;
// }

// int main()
// {
//     // constexpr lambda示例
//     constexpr int n = 10;
//     int y = 0;
//     constexpr auto square = [n](int x) constexpr { return x * x * n; };
//     constexpr int result = square(n); // 编译期计算：250

//     return 0;
// }

// template <typename T>
// auto get_value(T t) {
//     if constexpr (std::is_pointer_v<T>) {
//         return *t; // 仅当T为指针类型时实例化
//     } else {
//         return t; // 非指针类型时实例化
//     }
// }

// // 使用示例
// int x = 42;
// auto v1 = get_value(x); // 返回x本身
// auto v2 = get_value(&x); // 解引用返回42
// struct Point {
//     constexpr Point(double x, double y): x(x), y(y) {}
//     double x, y;
// };

// constexpr Point midpoint(Point a, Point b) {
//     return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
// }

// constexpr std::array<int, 5> createArray() {
//     std::array<int, 5> arr{};
//     for (size_t i = 0; i < arr.size(); ++i) {
//         arr[i] = i * i;
//     }
//     return arr;
// }

// constexpr int fibonacci(int n) {
//     return (n <= 1) ? n : (fibonacci(n - 1) + fibonacci(n - 2));
// }

// int main()
// {
//     Point p1 = midpoint({1.1, 1.1}, {2.2, 2.2}); // 运行时
//     constexpr Point p2 = midpoint({1.1, 1.1}, {2.2, 2.2}); // 编译期

//     constexpr std::array<int, 5> a1 = createArray(); // 编译期生成数组

//     constexpr int fibArray[] = {
//         fibonacci(0), fibonacci(1), fibonacci(2), fibonacci(3),
//         fibonacci(4), fibonacci(5), fibonacci(6), fibonacci(7)
//     };

//     return 0;
// }


// // C++14允许的constexpr函数示例
// constexpr int factorial(int n) {
//     int res = 1; // 允许局部变量
//     for (int i = 2; i <= n; ++i) { // 允许循环
//         res *= i;
//     }
//     return res; // 单一return
// }

// constexpr size_t stringLength(const char* str) {
//     size_t len = 0;
//     while (str[len] != '\0')
//         ++len;
//     return len;
// }

// constexpr size_t len = stringLength("Hello"); // 编译期计算：5

// class Date
// {
// public:
//     constexpr Date(int year, int month, int day)
//     : _year(year)
//     , _month(month)
//     , _day(day)
//     {
//         // cout << "构造函数" << endl; // 错误：不能有IO操作
//     }

//     constexpr int GetYear() const
//     {
//         return _year;
//     }

// private:
//     int _year;
//     int _month;
//     int _day;
// };

// template<typename T>
// constexpr T Func(T t)
// {
//     return t;
// }

// int main()
// {
//     int x = 2025;
//     // constexpr Date d0(x, 9, 8); // 报错：x是运行时变量
//     constexpr Date d1(2025, 9, 8); // 编译期构造对象
//     constexpr int y = d1.GetYear(); // 编译期调用成员函数

//     Date d2(2025, 8, 11); // 运行时构造对象
//     int z = d2.GetYear(); // 运行时调用

//     string ret1 = Func("111111"); // 普通函数（constexpr被忽略）
//     constexpr int ret2 = Func(10); // 编译期调用

//     return 0;
// }
// #include<iostream>
// using namespace std;

// constexpr int size()
// {
//     return 10;
// }

// constexpr int func(int x)
// {
//     return 10 + x;
// }

// constexpr int factorial(int n)
// {
//     return n <= 1 ? 1 : n * factorial(n - 1);
// }

// // 错误：包含局部变量和IO操作
// constexpr int fxx(int x)
// {
//     int i = x;
//     i++;
//     cout << i << endl;
//     return 10 + x;
// }

// int main()
// {
//     // 编译时N1被直接替换为10，constexpr函数默认是inline
//     constexpr int N1 = size();
//     int arr1[N1];

//     // 传常量表达式时，func在编译期计算
//     constexpr int N2 = func(10);
//     int arr2[N2];

//     // 传运行时变量时，func在运行时计算
//     int i = 10;
//     // constexpr int N3 = func(i); // 报错：i是运行时变量
//     int N4 = func(i); // 不报错：运行时调用

//     constexpr int fact5 = factorial(5); // 编译时计算出120

//     //constexpr int N5 = fxx(10); // 报错：fxx不符合constexpr要求

//     return 0;
// }


// // // const可以运行时初始化
// // int x = 10;
// // const int y = x; // 正确：运行时初始化

// // constexpr必须编译时初始化
// // constexpr int z = x; // 错误：x是运行时变量

// // int size()
// // {
// //     int n = 10;
// //     return n;
// // }

// // int main()
// // {
// //     const int a = 1; // a是常量表达式
// //     const int b = a + 1; // b是常量表达式
// //     int c = 1; // c不是常量表达式
// //     const int d = c; // d不是常量表达式
// //     const int e = size(); // e不是常量表达式

// //     // 常量表达式可以做数组大小（VS不支持变长数组）
// //     int arr[a];

// //     constexpr int aa = 1;
// //     constexpr int bb = aa + 1;
// //     // constexpr int cc = c; // 报错：c不是常量表达式
// //     // constexpr int cc = size(); // 报错：size()不是常量表达式

// //     // constexpr修饰指针是顶层const
// //     // constexpr int* p1 = &d; // 报错：权限放大
// //     const int* p2 = &d;
// //     constexpr const int* p3 = &d; // constexpr修饰p3本身，const修饰*p3

// //     return 0;
// // }