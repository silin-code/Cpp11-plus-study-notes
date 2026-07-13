#include<iostream>
#include<vector>
#include <string>
#include <tuple>
#include <array>
#include <utility>


int main() {
    // array同时推导类型和长度
    std::array a = { 1, 2, 3 }; // 推导为 std::array<int, 3>

    // pair推导两个元素的类型
    std::pair p(1, 2.0); // 推导为 std::pair<int, double>

    // tuple推导多个元素的类型
    std::tuple t(1, 2.0, std::string("three")); // 推导为 std::tuple<int, double, const char*>
    return 0;
}

//int main() {
//    std::vector<int> v1 = { 1, 2, 3 };
//
//    // 1. 初始化列表推导：元素类型为int
//    std::vector v2 = { 4, 5, 6 };
//
//    // 2. 字符串字面量推导：元素类型为const char*
//    std::vector v3{ "hello", "world" };
//
//    // 3. 填充构造推导：两个参数均为int，推导vector<int>
//    std::vector v4(10, 1);
//
//    // 4. 迭代器范围推导：根据迭代器指向的元素类型推导
//    std::vector v5(v1.begin(), v1.end());
//
//    // 5. 空构造报错：无参数无法推导模板类型
//    // std::vector v6; // 编译错误
//
//    return 0;
//}

//int main()
//{
//	//// C++14 写法：必须显式指定模板参数
//	//std::vector<int> v1 = { 1, 2, 3 };
//	//std::pair<int, double> p(1, 2.0);
//	//std::tuple<int, double, const char*> t(1, 2.0, "three");
//
//	// C++17 写法：编译器自动推导模板参数
//	std::vector v2 = { 4, 5, 6 }; // 推导为 std::vector<int>
//	std::pair p(1, 2.0);        // 推导为 std::pair<int, double>
//	std::tuple t(1, 2.0, "three"); // 推导为 std::tuple<int, double, const char*>
//}