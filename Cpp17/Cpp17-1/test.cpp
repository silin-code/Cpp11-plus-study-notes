#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <tuple>

std::map<std::string, int> scores = { {"Alice", 95}, {"Bob", 88} };

int main()
{
    // 插入并判断是否成功
    if (auto [it, inserted] = scores.insert({ "Charlie", 90 }); inserted) {
        std::cout << "Inserted " << it->first << " with score " << it->second << std::endl;
    }
    else {
        std::cout << it->first << " already exists, score is " << it->second << std::endl;
    }
}

//// 除法函数：返回(是否成功, 结果, 错误信息)
//std::tuple<bool, int, std::string> divide(int a, int b) {
//    if (b == 0) {
//        return { false, 0, "Division by zero" };
//    }
//    return { true, a / b, "" };
//}
//
//int main() {
//    // 一次性解包并判断结果
//    if (auto [success, result, error] = divide(10, 2); success) {
//        std::cout << "Result: " << result << std::endl;
//    }
//    else {
//        std::cout << "Error: " << error << std::endl;
//    }
//    return 0;
//}

//int checkValue(int v) {
//    return v % 2;
//}
//
//int main()
//{
//    // status变量仅在switch块内可见
//    switch (auto status = checkValue(42); status) {
//    case 0:
//        std::cout << "Status is zero" << std::endl;
//        break;
//    case 1:
//        std::cout << "Status is one" << std::endl;
//        break;
//    default:
//        std::cout << "Unknown status: " << status << std::endl;
//    }
//}
//std::map<std::string, int> scores = { {"Alice", 95}, {"Bob", 88} };
//
//int main()
//{
//	if (auto it = scores.find("Alice"); it != scores.end())
//	{
//		std::cout << "Found Alice, age: " << it->second << std::endl;
//	}
//	else 
//	{
//		std::cout << "Alice not found" << std::endl;
//	}
//
//	// 这里无法访问it变量，编译错误
//	//std::cout << it->second << std::endl;
//}

//int main() {
//    // C++11/14 写法：it变量污染外层作用域
//    auto it = scores.find("Alice");
//    if (it != scores.end()) {
//        std::cout << "Alice's score: " << it->second << std::endl;
//    }
//    // it变量在这里仍然存在，可能被误用
//}


//int main()
//{
//	// C++17 写法：直接解包键值对
//	std::map<std::string, int> scores = { {"Alice", 95}, {"Bob", 88} };
//	for (const auto& [name, score] : scores) {
//		std::cout << name << ": " << score << std::endl;
//	}
//}
// 
//struct Point {
//	double x;
//	double y;
//	void print()
//	{
//		std::cout << x <<" " << y;
//	}
//};
//
//int main()
//{
//	Point p = { 1,2 };
//	auto&& [x, y] = p;
//}


//int main()
//{
//	std::tuple<int, double, std::string> t(1, 2.3, "hello");
//	auto [a, b, c] = t;
//	auto& [a2, b2, c2] = t;
//	auto&& [a3, b3, c3] = std::move(t);
//
//	//auto& [a5, b5] = std::make_pair(1, 2);
//	auto&& [a5, b5] = std::make_pair(1, 2);
//	std::cout << a5  << " " << &b5;
//}
//int main()
//{
//
//	int arr[2] = { 1, 2 };
//	auto [x, y] = arr; // x=1, y=2（值拷贝）
//	std::cout << x << " " << y << std::endl;
//
//	// 引用绑定：修改xx会影响原数组
//	auto& [xx, yy] = arr;
//	xx++;
//	std::cout << arr[0] << std::endl; // 输出2
//}
//// 1. 拷贝初始化（最常用）
//auto [var1, var2, ..., varN] = expression;
//
//// 2. 直接初始化
//auto [var1, var2, ..., varN](expression);
//
//// 3. 列表初始化
//auto [var1, var2, ..., varN] {expression};
//
//// 引用绑定模式
//auto& [var1, var2, ..., varN] = expression;        // 左值引用
//auto&& [var1, var2, ..., varN] = expression;       // 万能引用（可绑定左值/右值）
//const auto& [var1, var2, ..., varN] = expression;  // const左值引用

//// C++11/14 遍历map：必须通过临时entry对象访问键值
//std::map<std::string, int> scores = { {"Alice", 95}, {"Bob", 88} };
//
//
//// C++11/14 多值返回：必须通过std::get按索引取值，极易出错
//std::tuple<int, double, std::string> getPerson() {
//    return { 25, 1.75, "Alice" };
//}
//
//int main() {
//    auto person = getPerson();
//    int age = std::get<0>(person);    // 索引0对应年龄
//    double height = std::get<1>(person); // 索引1对应身高
//    std::string name = std::get<2>(person); // 索引2对应姓名
//    for (auto& entry : scores) {
//        std::cout << entry.first << ": " << entry.second << std::endl;
//    }
//    return 0;
//}