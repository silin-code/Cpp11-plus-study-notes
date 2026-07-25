#include <variant>
#include <list>
#include <set>
#include <vector>
#include <algorithm>

// overloaded辅助类
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

template<class K, size_t Len = 8>
class HashTable {
    // 每个桶要么是链表，要么是红黑树set
    using Value = std::variant<std::list<K>, std::set<K>>;
public:
    HashTable() : _tables(10) {}

    void Insert(const K& key) {
        size_t hashi = key % _tables.size();

        // 链表插入逻辑：小于8插入，大于8转红黑树
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

        // 红黑树插入逻辑
        auto setInsert = [&key](std::set<K>& s) {
            s.insert(key);
            };

        // visit自动匹配当前类型执行对应逻辑
        std::visit(overloaded{ listInsert, setInsert }, _tables[hashi]);
    }

    bool Find(const K& key) {
        size_t hashi = key % _tables.size();
        auto listFind = [&key](std::list<K>& lt) -> bool {
            return std::find(lt.begin(), lt.end(), key) != lt.end();
            };
        auto setFind = [&key](std::set<K>& s) -> bool {
            return s.count(key);
            };
        return std::visit(overloaded{ listFind, setFind }, _tables[hashi]);
    }

private:
    std::vector<Value> _tables;
};
//#include <variant>
//#include <string>
//#include <iostream>
//#include <variant>
//#include <vector>
//#include <string>
//
//// overloaded辅助类：合并多个lambda为一个重载的访问者
//template<class... Ts>
//struct overloaded : Ts... { using Ts::operator()...; };
//// C++17需要显式推导指引，C++20可省略
//template<class... Ts>
//overloaded(Ts...) -> overloaded<Ts...>;
//
//using value_t = std::variant<int, double, std::string>;
//
//int main() {
//    std::vector<value_t> vec = { 10, 1.5, "hello" };
//
//    for (auto& v : vec) {
//        // 方式1：重载lambda访问，每个类型对应一个处理分支
//        std::visit(overloaded{
//            [](int arg) { std::cout << "int: " << arg << '\n'; },
//            [](double arg) { std::cout << "double: " << arg << '\n'; },
//            [](const std::string& arg) { std::cout << "string: " << arg << '\n'; }
//            }, v);
//
//        // 方式2：配合if constexpr泛型lambda处理
//        std::visit([](auto&& arg) {
//            using T = std::decay_t<decltype(arg)>;
//            if constexpr (std::is_same_v<T, int>) {
//                std::cout << "int with value " << arg << '\n';
//            }
//            else if constexpr (std::is_same_v<T, double>) {
//                std::cout << "double with value " << arg << '\n';
//            }
//            else if constexpr (std::is_same_v<T, std::string>) {
//                std::cout << "string with value " << arg << '\n';
//            }
//            }, v);
//    }
//    return 0;
//}
//
////int main() {
////    std::variant<int, double, std::string> v = "hello";
////
////    if (auto pval = std::get_if<int>(&v)) {
////        std::cout << "int value: " << *pval << std::endl;
////    }
////    else if (auto pval = std::get_if<double>(&v)) {
////        std::cout << "double value: " << *pval << std::endl;
////    }
////    else if (auto pval = std::get_if<std::string>(&v)) {
////        std::cout << "string value: " << *pval << std::endl;
////    }
//
//    //std::variant<int, double> v = 42;
//
//    //try {
//    //    std::cout << std::get<int>(v) << std::endl;    // 按类型访问，正确
//    //    std::cout << std::get<0>(v) << std::endl;      // 按索引访问，正确
//    //    std::cout << std::get<double>(v) << std::endl; // 类型不匹配，抛异常
//    //}
//    //catch (const std::bad_variant_access& e) {
//    //    std::cout << "Error: " << e.what() << std::endl;
//    //}
//
//
//    //// 定义：可以存储int、double、std::string三种类型
//    //std::variant<int, double, std::string> v;
//
//    //// 赋值：自动切换类型，自动管理生命周期
//    //v = 42;          // 当前存储int
//    //v = 3.14;        // 自动析构int，构造double
//    //v = "hello";     // 自动析构double，构造string
//
//    //// index()：获取当前类型的索引（从0开始，对应模板参数顺序）
//    //std::cout << "Current index: " << v.index() << std::endl; // 输出2
//    //return 0;
////}
////#include<iostream>
////#include<optional>
////#include<string>
////#include<vector>
////#include<map>
////
////std::map<std::string, int> indexMap = { {"张庄",1},{"王村",2},{"李家村",3} };
////
////// 返回optional：找到返回下标，没找到返回空
////std::optional<int> findIndex(const std::string& str) {
////    auto it = indexMap.find(str);
////    if (it != indexMap.end()) {
////        return it->second;
////    }
////    return std::nullopt;
////}
////
////int main() {
////    if (auto index = findIndex("王村"); index.has_value()) {
////        std::cout << "编号: " << *index << std::endl;
////    }
////
////    std::vector<std::string> v = { "张庄", "李庄", "王家坪" };
////
////    std::optional<std::string> safeAccess(int i) {
////        if (i < v.size()) {
////            return v[i];
////        }
////        return std::nullopt; // 越界返回空，而不是空字符串（空字符串可能是正常值）
////    }
//    //std::string x;
//    //std::cin >> x;
//    //std::optional<int> index = findIndex(x);
//    //// 强制调用者处理空的情况，避免遗漏检查
//    //if (index) {
//    //    std::cout << x << "对应的编号为:" << *index << std::endl;
//    //}
//    //else {
//    //    std::cout << x << "是非法顶点" << std::endl;
//    //}
//    //return 0;
////}
//
////void test_basic()
////{
////	//1创建对象
////	std::optional<int> maybeInt;//初始为空
////	std::optional<std::string> maybeStr = "Hello";//初始有值
////	std::optional<double> empty = std::nullopt;//初始为空
////
////	//2判断是否有值
////	if (maybeInt.has_value())
////	{
////		std::cout << "has value" << std::endl;
////	}
////
////	//更简洁的隐式bool转换
////	if (maybeStr)
////	{
////		std::cout << "has value" << std::endl;
////	}
////
////	//3取值方式
////	//安全取值，无抛异常
////	try {
////		int value = maybeInt.value(); //如果没有值会抛异常
////	}catch(const std::bad_optional_access& e){
////		std::cout << e.what() << std::endl;
////	}
////
////	maybeInt = 1;
////	// 不安全但快速：必须确保有值
////	int val1 = *maybeInt;
////	// 带默认值：无值返回默认
////	int val2 = maybeInt.value_or(2);
////
////	// 4. 修改与重置
////	maybeInt = 42;       // 赋新值
////	maybeInt = std::nullopt; // 设为空
////	maybeInt.reset();    // 等价设为空
////}
//
//
////#include<iostream>
////#include <string>
////#include <set>
////#include <map>
////
////std::map<std::string,int> indexMap;
////
////// 查找字符串下标，找不到返回-1
////int findIndex(const std::string& str) {
////    auto it = indexMap.find(str);
////    if (it != indexMap.end()) return it->second;
////    return -1; // 特殊值表示找不到
////}
////
////bool findIndex(const std::string& str, int& outIndex) {
////    auto it = indexMap.find(str);
////    if (it == indexMap.end()) return false;
////    outIndex = it->second;
////    return true;
////}
////
////int findIndex(const std::string& str) {
////    auto it = indexMap.find(str);
////    if (it == indexMap.end()) throw std::runtime_error("not found");
////    return it->second;
////}
////
////int main()
////{
////
////}