#include <any>
#include <list>
#include <set>
#include <vector>
#include <algorithm>
#include <cassert>

template<class K, size_t Len = 8>
class HashTable {
public:
    HashTable() : _tables(10, std::list<K>()) {}

    void Insert(const K& key) {
        size_t hashi = key % _tables.size();

        auto listInsert = [this, &key, hashi](std::list<K>& lt) {
            if (lt.size() < Len) {
                lt.push_back(key);
            }
            else {
                std::set<K> s(lt.begin(), lt.end());
                s.insert(key);
                _tables[hashi] = std::move(s);
            }
            };

        auto setInsert = [&key](std::set<K>& s) {
            s.insert(key);
            };

        // 手动尝试类型转换，判断当前存储的类型
        if (auto* ptr = std::any_cast<std::list<K>>(&_tables[hashi])) {
            listInsert(*ptr);
        }
        else if (auto* ptr = std::any_cast<std::set<K>>(&_tables[hashi])) {
            setInsert(*ptr);
        }
        else {
            assert(false);
        }
    }

    bool Find(const K& key) {
        size_t hashi = key % _tables.size();
        if (!_tables[hashi].has_value()) return false;

        auto listFind = [&key](std::list<K>& lt) -> bool {
            return std::find(lt.begin(), lt.end(), key) != lt.end();
            };
        auto setFind = [&key](std::set<K>& s) -> bool {
            return s.count(key);
            };

        if (auto* ptr = std::any_cast<std::list<K>>(&_tables[hashi])) {
            return listFind(*ptr);
        }
        else if (auto* ptr = std::any_cast<std::set<K>>(&_tables[hashi])) {
            return setFind(*ptr);
        }
        else {
            assert(false);
            return false;
        }
    }

private:
    std::vector<std::any> _tables;
};
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