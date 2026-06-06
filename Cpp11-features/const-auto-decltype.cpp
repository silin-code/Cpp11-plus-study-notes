#include<iostream>
using namespace std;

void func(int& x) { cout << "void func(int& x)" << endl; }
void func(int&& x) { cout << "void func(int&& x)" << endl; }
void func(const int& x) { cout << "void func(const int& x)" << endl; }
void func(const int&& x) { cout << "void func(const int&& x)" << endl; }

int main()
{
    int x = 10;
    const int cx = 20;

    auto& rx1 = x;       // int&
    auto& rx2 = cx;      // const int&
    func(rx1); // 输出void func(int& x)
    func(rx2); // 输出void func(const int& x)

    const auto& rx3 = x; // const int&
    const auto& rx4 = cx; // const int&
    func(rx3); // 输出void func(const int& x)
    func(rx4); // 输出void func(const int& x)

    // 万能引用
    auto&& rx5 = x;      // int&（左值推导为左值引用）
    auto&& rx6 = cx;     // const int&（const左值推导为const左值引用）
    func(rx5); // 输出void func(int& x)
    func(rx6); // 输出void func(const int& x)

    auto&& rx7 = move(x); // int&&（右值推导为右值引用）
    auto&& rx8 = move(cx); // const int&&（const右值推导为const右值引用）
    func(forward<int>(rx7)); // 输出void func(int&& x)
    func(forward<const int>(rx8)); // 输出void func(const int&& x)

    return 0;
}

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