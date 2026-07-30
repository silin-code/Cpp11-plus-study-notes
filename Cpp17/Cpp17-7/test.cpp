#include <iostream>
#include <chrono>
#include <string>
#include <string_view>

void error_example3() {
    std::string str = "Hello";
    std::string_view sv = str;

    str[0] = 'h'; // 未扩容，视图仍然有效
    std::cout << sv << std::endl;

    // 触发扩容，str重新分配内存，原内存释放，sv变为悬垂
    str = "New value 111111111111111111111111";
    std::cout << sv << std::endl; // 未定义行为
}

void error_example2() {
    char buffer[] = { 'T', 'e', 's', 't', '.', 't', 'x', 't' }; // 无\0结尾
    std::string_view sv(buffer, 4); // 正确，指定长度

    // 错误：传给期望\0结尾的C接口，会越界读取
    FILE* fout = fopen(sv.data(), "w");
}

std::string_view get_view() {
    std::string temp = "Temporary string";
    return temp; // 严重错误！temp函数结束时销毁，返回的视图指向已释放内存
}

void error_example1() {
    std::string_view sv = get_view();
    std::cout << sv << std::endl; // 未定义行为，悬垂引用
}

void process_string(const std::string& s) {}
void process_string_view(std::string_view sv) {}

int main() {
    const int N = 100'0000;
    std::string long_str = "This is a very long string...";

    // 测试std::string参数
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        process_string(long_str);     // 无额外开销
        process_string("literal");    // 创建临时string，有分配
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // 测试std::string_view参数
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        process_string_view(long_str); // 隐式转换，零开销
        process_string_view("literal");// 无临时对象
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
    std::cout << "std::string: " << duration1.count() << "ms\n";
    std::cout << "std::string_view: " << duration2.count() << "ms\n";
    return 0;
}
//#include <string_view>
//#include <vector>
//
//// 提取分隔符前的子串，零拷贝返回
//std::string_view extract_str(std::string_view input, char delimiter) {
//    size_t pos = input.find(delimiter);
//    return input.substr(0, pos);
//}
//
//// 按分隔符拆分字符串，返回视图数组，全程零拷贝
//std::vector<std::string_view> split(std::string_view str, char delimiter) {
//    std::vector<std::string_view> result;
//    size_t start = 0;
//    size_t end = str.find(delimiter);
//
//    while (end != std::string_view::npos) {
//        result.push_back(str.substr(start, end - start));
//        start = end + 1;
//        end = str.find(delimiter, start);
//    }
//    result.push_back(str.substr(start));
//    return result;
//}
//#include <string_view>
//#include <string>
//
//// 替代 const std::string&，接受任意字符串类型，零拷贝
//void process_string(std::string_view sv) {
//    // 只读处理sv，和使用string几乎一样
//}
//
//int main() {
//    process_string("C-string");     // 无临时对象，零拷贝
//    std::string s("std::string");
//    process_string(s);              // 隐式转换，零开销
//    return 0;
//}
//#include <iostream>
//#include <string>
//#include <string_view>
//
//int main()
//{
//    // 1. 从C风格字符串构造
//    std::string_view sv1("Hello, world!");
//
//    // 2. 从std::string隐式转换构造
//    std::string str = "C++17 string_view";
//    std::string_view sv2(str);
//
//    // 3. 从部分字符串构造（指针+长度）
//    std::string_view sv3(str.c_str() + 6, 6); // 取从第6位开始的6个字符
//
//    // 4. 字面量后缀 sv（C++17）
//    using namespace std::literals;
//    std::string_view sv4 = "Literal"sv;
//
//    return 0;
//}

//// 传统写法：传入字面量会构造临时string，有内存分配
//void process_string(const std::string& s) {
//    // 只读处理
//}
//
//int main() {
//    process_string("hello world"); // 构造临时string，产生拷贝和分配
//    return 0;
//}
//#include <any>
//#include <list>
//#include <set>
//#include <vector>
//#include <algorithm>
//#include <cassert>
//
//template<class K, size_t Len = 8>
//class HashTable {
//public:
//    HashTable() : _tables(10, std::list<K>()) {}
//
//    void Insert(const K& key) {
//        size_t hashi = key % _tables.size();
//
//        auto listInsert = [this, &key, hashi](std::list<K>& lt) {
//            if (lt.size() < Len) {
//                lt.push_back(key);
//            }
//            else {
//                std::set<K> s(lt.begin(), lt.end());
//                s.insert(key);
//                _tables[hashi] = std::move(s);
//            }
//            };
//
//        auto setInsert = [&key](std::set<K>& s) {
//            s.insert(key);
//            };
//
//        // 手动尝试类型转换，判断当前存储的类型
//        if (auto* ptr = std::any_cast<std::list<K>>(&_tables[hashi])) {
//            listInsert(*ptr);
//        }
//        else if (auto* ptr = std::any_cast<std::set<K>>(&_tables[hashi])) {
//            setInsert(*ptr);
//        }
//        else {
//            assert(false);
//        }
//    }
//
//    bool Find(const K& key) {
//        size_t hashi = key % _tables.size();
//        if (!_tables[hashi].has_value()) return false;
//
//        auto listFind = [&key](std::list<K>& lt) -> bool {
//            return std::find(lt.begin(), lt.end(), key) != lt.end();
//            };
//        auto setFind = [&key](std::set<K>& s) -> bool {
//            return s.count(key);
//            };
//
//        if (auto* ptr = std::any_cast<std::list<K>>(&_tables[hashi])) {
//            return listFind(*ptr);
//        }
//        else if (auto* ptr = std::any_cast<std::set<K>>(&_tables[hashi])) {
//            return setFind(*ptr);
//        }
//        else {
//            assert(false);
//            return false;
//        }
//    }
//
//private:
//    std::vector<std::any> _tables;
//};
//#include <any>
//#include <string>
//#include <vector>
//#include <iostream>
//#include <cassert>
//
//static void printConfig(const std::vector<std::any>& configs) {
//    for (const auto& item : configs) {
//        if (item.type() == typeid(int)) {
//            std::cout << "整数配置: " << std::any_cast<int>(item) << '\n';
//        }
//        else if (item.type() == typeid(double)) {
//            std::cout << "浮点配置: " << std::any_cast<double>(item) << '\n';
//        }
//        else if (item.type() == typeid(std::string)) {
//            std::cout << "字符串配置: " << std::any_cast<const std::string&>(item) << '\n';
//        }
//        else {
//            assert(false && "未知配置类型");
//        }
//    }
//}
//#include <any>
//#include <string>
//#include <iostream>
//
//// 简化版底层结构
//class any {
//private:
//    const std::type_info* type_; // 类型信息
//    union {
//        std::byte small_buffer_[sizeof(void*) * 3]; // 小对象缓冲区
//        void* heap_ptr_; // 大对象堆指针
//    } storage_;
//    // 操作函数指针：拷贝、析构等
//    void (*destroy_)(void*);
//    void* (*clone_)(const void*);
//};
//
//int main() {
//    std::any a = std::string("Hello");
//
//    // 方式1：值拷贝，类型不匹配抛 std::bad_any_cast 异常
//    try {
//        std::string s = std::any_cast<std::string>(a); // 正确
//        std::cout << "Value: " << s << '\n';
//        // double d = std::any_cast<double>(a); // 错误，抛出异常
//    }
//    catch (const std::bad_any_cast& e) {
//        std::cout << "Cast failed: " << e.what() << '\n';
//    }
//
//    // 方式2：引用形式，避免拷贝，可修改内部值
//    std::string& s_ref = std::any_cast<std::string&>(a);
//    s_ref[0] = 'h';
//    std::cout << std::any_cast<const std::string&>(a) << '\n'; // 输出 hello
//
//    // 方式3：指针形式，传入any的指针，不匹配返回nullptr，不抛异常
//    if (auto* p = std::any_cast<int>(&a)) {
//        std::cout << "int value: " << *p << '\n';
//    }
//    else {
//        std::cout << "Not an int" << '\n';
//    }
//    return 0;
//}
//#include<any>
//#include<string>
//#include<iostream>
//
//int main()
//{
//	//1构造和赋值
//    std::any a1 = 42;                  // 存储int
//    std::any a2 = 3.14;                // 存储double
//    std::any a3 = std::string("Hello"); // 存储std::string
//    std::any a4;                        // 空状态
//
//    a4 = std::make_pair(std::string("key"), std::string("value"));
//
//    // 2. 原地构造，避免临时对象拷贝
//    a3.emplace<std::string>("World");
//
//    // 3. 状态与类型检查
//    if (a3.has_value()) {
//        std::cout << "a3 has value" << std::endl;
//        const std::type_info& ti = a1.type();
//        std::cout << "a1 type: " << ti.name() << std::endl;
//    }
//
//    // 4. 重置为空
//    a1.reset();
//}