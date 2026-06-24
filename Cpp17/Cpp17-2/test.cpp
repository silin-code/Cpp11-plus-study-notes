#include <iostream>

class Buffer {
public:
    Buffer(size_t size) : size_(size), data_(new char[size]) {}
    // ... 析构、拷贝/移动构造等
private:
    size_t size_;
    char* data_;
};

// 工厂函数：零拷贝返回
Buffer createDefaultBuffer() {
    return Buffer(1024); // 强制URVO，无移动、无拷贝
}

int main() {
    Buffer buf = createDefaultBuffer(); // 直接在buf上构造
}
//struct NonMoveable {
//    NonMoveable() = default;
//    NonMoveable(const NonMoveable&) = delete;
//    NonMoveable(NonMoveable&&) = delete;
//};
//
//NonMoveable make() {
//    return NonMoveable(); // C++17 合法：URVO强制保证，不需要移动构造
//}
//
//int main() {
//    NonMoveable nm = make(); // C++17 合法
//}
//struct Noisy {
//    Noisy() { std::cout << "constructed at " << this << '\n'; }
//    Noisy(const Noisy&) { std::cout << "copy-constructed\n"; }
//    Noisy(Noisy&&) { std::cout << "move-constructed\n"; }
//    ~Noisy() { std::cout << "destructed at " << this << '\n'; }
//};
//
//Noisy f() {
//    Noisy v = Noisy(); // C++17 强制URVO，直接构造v，无拷贝
//    return v;          // NRVO，编译器可选优化（主流编译器都会做）
//}
//
//void g(Noisy arg) {
//    std::cout << "&arg = " << &arg << '\n';
//}
//
//int main() {
//    Noisy v = f(); // C++17 强制URVO，直接在v的地址上构造
//    std::cout << "&v = " << &v << '\n';
//
//    g(f()); // 临时对象直接构造在arg的地址上
//    return 0;
//}
//#include <iostream>
//#include <vector>
//#include <string>
//#include <map>
//#include "Cache.hpp"
//
//struct NonMoveable {
//    NonMoveable() = default;
//    NonMoveable(const NonMoveable&) = delete; // 禁止拷贝
//    NonMoveable(NonMoveable&&) = delete;      // 禁止移动
//};
//
//NonMoveable make() {
//    return NonMoveable(); // C++14 编译错误！
//    // 语法逻辑上需要调用移动构造，但它被删除了
//}
//
//int main() {
//    NonMoveable nm = make(); // C++14 同样编译错误
//}

////C++17
//class Widgt {
//public:
//	inline static std::string name = "张三";
//	static const int version = 1;
//};

////C++17之前
//class Widgt {
//public:
//	static std::string name;
//	static const int version = 1;
//};
//
//std::string Widgt::name = "张三";

//// Test.cpp
//#include "Cache.hpp"
//int main() {
//    std::cout << &bufferSize << std::endl; // 地址2（和上面不同）
//    std::cout << &cacheSize << std::endl;  // 和上面地址完全相同
//    func();
//    return 0;
//}
//
//// 修饰全局变量
//inline const int cacheSize = 4 * 1024;
//
//// 修饰类静态成员变量
//class Widget {
//public:
//    inline static std::string name = "张三";
//};