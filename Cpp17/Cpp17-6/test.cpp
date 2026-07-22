#include<iostream>
#include<optional>
#include<string>
#include<vector>
#include<map>

std::map<std::string, int> indexMap = { {"张庄",1},{"王村",2},{"李家村",3} };

// 返回optional：找到返回下标，没找到返回空
std::optional<int> findIndex(const std::string& str) {
    auto it = indexMap.find(str);
    if (it != indexMap.end()) {
        return it->second;
    }
    return std::nullopt;
}

int main() {
    if (auto index = findIndex("王村"); index.has_value()) {
        std::cout << "编号: " << *index << std::endl;
    }

    std::vector<std::string> v = { "张庄", "李庄", "王家坪" };

    std::optional<std::string> safeAccess(int i) {
        if (i < v.size()) {
            return v[i];
        }
        return std::nullopt; // 越界返回空，而不是空字符串（空字符串可能是正常值）
    }
    //std::string x;
    //std::cin >> x;
    //std::optional<int> index = findIndex(x);
    //// 强制调用者处理空的情况，避免遗漏检查
    //if (index) {
    //    std::cout << x << "对应的编号为:" << *index << std::endl;
    //}
    //else {
    //    std::cout << x << "是非法顶点" << std::endl;
    //}
    //return 0;
}

//void test_basic()
//{
//	//1创建对象
//	std::optional<int> maybeInt;//初始为空
//	std::optional<std::string> maybeStr = "Hello";//初始有值
//	std::optional<double> empty = std::nullopt;//初始为空
//
//	//2判断是否有值
//	if (maybeInt.has_value())
//	{
//		std::cout << "has value" << std::endl;
//	}
//
//	//更简洁的隐式bool转换
//	if (maybeStr)
//	{
//		std::cout << "has value" << std::endl;
//	}
//
//	//3取值方式
//	//安全取值，无抛异常
//	try {
//		int value = maybeInt.value(); //如果没有值会抛异常
//	}catch(const std::bad_optional_access& e){
//		std::cout << e.what() << std::endl;
//	}
//
//	maybeInt = 1;
//	// 不安全但快速：必须确保有值
//	int val1 = *maybeInt;
//	// 带默认值：无值返回默认
//	int val2 = maybeInt.value_or(2);
//
//	// 4. 修改与重置
//	maybeInt = 42;       // 赋新值
//	maybeInt = std::nullopt; // 设为空
//	maybeInt.reset();    // 等价设为空
//}


//#include<iostream>
//#include <string>
//#include <set>
//#include <map>
//
//std::map<std::string,int> indexMap;
//
//// 查找字符串下标，找不到返回-1
//int findIndex(const std::string& str) {
//    auto it = indexMap.find(str);
//    if (it != indexMap.end()) return it->second;
//    return -1; // 特殊值表示找不到
//}
//
//bool findIndex(const std::string& str, int& outIndex) {
//    auto it = indexMap.find(str);
//    if (it == indexMap.end()) return false;
//    outIndex = it->second;
//    return true;
//}
//
//int findIndex(const std::string& str) {
//    auto it = indexMap.find(str);
//    if (it == indexMap.end()) throw std::runtime_error("not found");
//    return it->second;
//}
//
//int main()
//{
//
//}