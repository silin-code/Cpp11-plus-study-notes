#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <map>
using namespace std;


// typedef写法
typedef int (*ArrayPtr)[5];

// using写法
using ArrayPtr = int (*)[5];

// typedef map<string, int> CountMap;
// typedef map<string, string> DictMap;
// typedef int DateType;
// typedef void (*Callback)(int);

// using 兼容typedef的用法
// using CountMap = map<string, int>;
// using DictMap = map<string, string>;
// using STDateType = int;
// using Callback = void (*)(int);

// // using支持带模板参数的类型重定义（typedef不支持）
// template<class Val>
// using Map = map<string, Val>;

// template<class Val>
// using MapIter = typename map<string, Val>::iterator;

// int main()
// {
//     Map<int> countMap;
//     Map<string> dictMap;

//     MapIter<int> cit = countMap.begin();
//     MapIter<string> dit = dictMap.begin();

//     return 0;
// }
// // 完美转发函数调用的返回值
// template <typename Func, typename... Args>
// decltype(auto) invoke(Func&& func, Args&&... args) {
//     return std::forward<Func>(func)(std::forward<Args>(args)...);
// }

// // 使用示例
// int& getRef(int& x) { return x; }
// int getVal(int x) { return x; }

// int main() {
//     int x = 10;
//     decltype(auto) ref = invoke(getRef, x); // int&
//     decltype(auto) val = invoke(getVal, 10); // int
//     return 0;
// }
// int main()
// {
//     int i = 0;
//     int& ri = i;
//     const int ci = 42; // 顶层const
//     int* const p1 = &i; // 顶层const
//     const int* p2 = &ci; // 底层const

//     auto j = ri;          // j类型为int（忽略引用）
//     decltype(auto) j1 = ri; // j1类型为int&（保留引用）
//     ++j1;

//     auto r1 = ci;         // r1类型为int（忽略顶层const）
//     decltype(auto) rr1 = ci; // rr1类型为const int（保留顶层const）
//     // rr1++; // 报错

//     auto r2 = p1;         // r2类型为int*（忽略顶层const）
//     decltype(auto) rr2 = p1; // rr2类型为int* const（保留顶层const）
//     // rr2++; // 报错

//     auto r3 = p2;         // r3类型为const int*（保留底层const）
//     decltype(auto) rr3 = p2; // rr3类型为const int*（保留底层const）
//     // (*rr3)++; // 报错

//     return 0;
// }

// template <typename Iter>
// auto Func(Iter it1,Iter it2) -> decltype(*it1)
// {
//     auto& x= *it1;
//     ++it1;
//     while(it1!=it2)
//     {
//         x+=*it1;
//         ++it1;
//     }
//     return x;
// }

// int main()
// {
//     int i = 0;
//     const int ci = 0;
//     const int& rci = ci;

//     decltype(i) m = 1;    // m的类型是int
//     decltype(ci) x = 1;   // x的类型是const int（保留顶层const）
//     // x++; // 报错：const变量不可修改
//     decltype(rci) y = x;  // y的类型是const int&（保留引用）
//     // decltype(rci) z; // 报错：引用必须初始化

//     int* p1 = &i;
//     decltype(p1) p2 = nullptr; // p2的类型是int*

//     // 三个特殊推导规则
//     decltype(*p1) r1 = i; // int&（解引用表达式推导出引用）
//     decltype(i) r2; // r2的类型是int
//     decltype((i)) r3 = i; // int&（括号括起来的左值表达式推导出引用）

//     return 0;
// }

// C++14 auto返回类型
// template <typename T, typename U>
// auto add(T t, U u) {
//     return t + u;
// }

// // 需要尾置返回类型的场景：精确控制返回值为引用
// template <typename T>
// auto getRef(T& t) -> T& {
//     return t;
// }

// auto getComplexType() -> std::map<std::string, std::vector<int>>{
//     return {{"Alice", {1, 2, 3}}, {"Bob", {4, 5, 6}}};
// }

// template<typename T,typename U>
// auto add(T t,U u) -> decltype(t + u) {
//     return t + u;
// }

// auto lambda = [](int x) { return x * 2; };

// std::tuple<int, double, std::string> getInfo() {
//     return {1, 3.14, "hello"};
// }

// int main() {
//     // 结构化绑定解包tuple
//     auto [id, score, name] = getInfo();

//     // 解包pair
//     std::pair<int, std::string> p = {10, "Alice"};
//     auto [key, value] = p;

//     // 解包结构体
//     struct Point { int x; int y; };
//     Point pt = {1, 2};
//     auto [x, y] = pt;

//     return 0;
// }

// vector<int> vec = {1,2,3,4,5};

// // 拷贝元素，修改不会影响原容器
// for (auto x : vec) {
//     x *= 2;
// }

// // 引用元素，修改会影响原容器
// for (auto& x : vec) {
//     x *= 2;
// }

// // const引用，只读访问，避免拷贝
// for (const auto& x : vec) {
//     cout << x << endl;
// }

// auto x = {1,2,3}; // std::initializer_list<int>
// auto y{1};        // C++17及以后：int；C++11/C++14：std::initializer_list<int>
// // auto z = {1, 2.0}; // 错误：元素类型不一致

// auto lambda = [](int x) { return x * 2; }; // lambda的类型是唯一的匿名类型

// int arr[5] = {1,2,3,4,5};
// auto a1 = arr;  // int*（数组退化为指针）
// auto& a2 = arr; // int(&)[5]（显式声明引用，保留数组类型）

// // 可以用a2获取数组大小
// cout << sizeof(a2) / sizeof(int) << endl; // 输出5

// void func(int& x) { cout << "void func(int& x)" << endl; }
// void func(int&& x) { cout << "void func(int&& x)" << endl; }
// void func(const int& x) { cout << "void func(const int& x)" << endl; }
// void func(const int&& x) { cout << "void func(const int&& x)" << endl; }

// int main()
// {
//     int x = 10;
//     const int cx = 20;

//     auto& rx1 = x;       // int&
//     auto& rx2 = cx;      // const int&
//     func(rx1); // 输出void func(int& x)
//     func(rx2); // 输出void func(const int& x)

//     const auto& rx3 = x; // const int&
//     const auto& rx4 = cx; // const int&
//     func(rx3); // 输出void func(const int& x)
//     func(rx4); // 输出void func(const int& x)

//     // 万能引用
//     auto&& rx5 = x;      // int&（左值推导为左值引用）
//     auto&& rx6 = cx;     // const int&（const左值推导为const左值引用）
//     func(rx5); // 输出void func(int& x)
//     func(rx6); // 输出void func(const int& x)

//     auto&& rx7 = move(x); // int&&（右值推导为右值引用）
//     auto&& rx8 = move(cx); // const int&&（const右值推导为const右值引用）
//     func(forward<int>(rx7)); // 输出void func(int&& x)
//     func(forward<const int>(rx8)); // 输出void func(const int&& x)

//     return 0;
// }

// int main()
// {
//     int i = 0;
//     int& ri = i;
//     const int ci = 42; // 顶层const
//     int* const p1 = &i; // 顶层const
//     const int* p2 = &ci; // 底层const
//     const int& ri1 = ci; // 底层const
//     const int& ri2 = i; // 底层const

//     auto j = ri;  // j类型为int（忽略引用）
//     j++;

//     auto k = i; // k类型为int
//     k++;

//     auto r1 = ci; // r1类型为int（忽略顶层const）
//     r1++;

//     auto r2 = p1; // r2类型为int*（忽略顶层const）
//     r2++;

//     auto r3 = p2; // r3类型为const int*（保留底层const）
//     // (*r3)++; // 报错：不能修改底层const指向的对象

//     auto r4 = ri1; // r4类型为int（ri1是ci的别名，ci的顶层const被忽略）
//     r4++;

//     auto r5 = ri2; // r5类型为int
//     r5++;

//     // 显式声明引用或const
//     const auto r7 = ci; // r7类型为const int
//     auto& r8 = ri1;     // r8类型为const int&
//     auto& r9 = ri2;     // r9类型为const int&
//     auto& r10 = ci;     // r10类型为const int&
//     auto& r11 = ri;     // r11类型为int&

//     // r7++; // 报错：const变量不可修改
//     // r8++; // 报错：const引用不可修改
//     r11++; // 正确：非const引用可以修改

//     return 0;
// }
// // #include <iostream>

// // class String {
// // public:
// //     // 返回const引用，防止用户修改内部字符
// //     const char& operator[](size_t index) const {
// //         return _data[index];
// //     }

// // private:
// //     char* _data;
// // };

// // class Counter {
// // public:
// //     Counter() : _count(0) {}

// //     void increment() const {
// //         _count++; // 正确：mutable成员可以在const函数中修改
// //     }

// //     int getCount() const {
// //         return _count;
// //     }

// // private:
// //     mutable int _count; // 可变成员
// // };

// // class Array {
// // public:
// //     int& operator[](size_t index) {
// //         return _data[index];
// //     }

// //     // const版本：返回const引用，防止通过const对象修改元素
// //     const int& operator[](size_t index) const {
// //         return _data[index];
// //     }

// // private:
// //     int _data[10];
// // };

// // class Person {
// // public:
// //     Person(std::string name, int age) : _name(name), _age(age) {}

// //     // const成员函数：this指针类型为const Person*
// //     std::string getName() const {
// //         // _age = 20; // 错误：不能修改非mutable成员变量
// //         return _name;
// //     }

// //     // 非const成员函数：this指针类型为Person*
// //     void setAge(int age) {
// //         _age = age;
// //     }

// // private:
// //     std::string _name;
// //     int _age;
// // };

// // int main() {
// //     Person p1("Alice", 18);
// //     const Person p2("Bob", 20);

// //     p1.getName(); // 正确：非const对象可以调用const成员函数
// //     p1.setAge(19); // 正确

// //     p2.getName(); // 正确：const对象只能调用const成员函数
// //     // p2.setAge(21); // 错误：const对象不能调用非const成员函数
// //     return 0;
// // }

// // // // 错误：这两个函数是重复定义，顶层const在传值时被忽略
// // // void func(int x) {}
// // // void func(const int x) {}

// // // // 正确：这是两个不同的函数，底层const不被忽略
// // // void func(int* p) {}       // 不能接受const int*参数（权限放大）
// // // void func(const int* p) {} // 可以接受int*和const int*参数（权限缩小）

// // // // 引用参数同理
// // // void func(int& x) {}       // 不能接受const int&参数
// // // void func(const int& x) {} // 可以接受int&和const int&参数
// // // int main()
// // // {
// // //     int i = 0;
// // //     int* const p1 = &i; // 顶层const：p1本身不可修改，但*p1可以修改
// // //     const int ci = 42;  // 顶层const：ci本身不可修改
// // //     const int* p2 = &ci; // 底层const：*p2不可修改，但p2可以指向其他对象
// // //     const int& r = ci;   // 引用的const永远是底层const

// // //     return 0;
// // // }