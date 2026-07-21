#include <map>

int main()
{
	std::map<int, int> m = { {1, 10}, {2, 20} };
	auto it = m.begin();

	int value = it++->second;
	// C++17前：未定义行为，it++和it->second的求值顺序不确定
	// C++17后：明确先求值it->second（取到10），再执行it++（it指向下一个元素）
	// 最终value=10，it指向第二个元素，行为安全确定
}

//#include <iostream>
//
//void process(int a, int b) {
//    std::cout << "a = " << a << ", b = " << b << std::endl;
//}
//
//int main() {
//    int x = 0;
//    process(x++, x++); // C++17前：未指定行为！可能输出(0,1)或(1,0)
//
//    int i = 0;
//    i = i++; // C++17前：未定义行为！结果不可预测
//    std::cout << i;
//    return 0;
//}
//// 函数参数故意不使用（比如回调函数的固定签名）
//void callback([[maybe_unused]] int unusedParam) {
//    [[maybe_unused]] int reservedVar = 10; // 预留变量，暂时不用
//    // 业务逻辑不使用参数
//}
//
//// 条件编译下的调试函数
//[[maybe_unused]] void debugOnlyFunc() {
//    // 仅Debug模式启用
//}
//#include <iostream>
//
//void checkValue(int x) {
//    switch (x) {
//    case 1:
//        std::cout << "Case 1" << std::endl;
//        [[fallthrough]]; // 故意贯穿，编译器不告警
//    case 2:
//        std::cout << "Case 2" << std::endl;
//        break;
//    default:
//        std::cout << "Default case" << std::endl;
//    }
//}
//
//// 标记返回值不能忽略：典型的错误码函数
//[[nodiscard]] int computeErrorCode() {
//    return -1;
//}
//
//// C++20 支持添加自定义提示原因
//// [[nodiscard("Please check the error code.")]]
//
//int main() {
//    computeErrorCode(); // 编译器警告：忽略了nodiscard函数的返回值
//    int code = computeErrorCode(); // 正确，无警告
//    return 0;
//}
//// 标记函数弃用
//[[deprecated]]
//void old_function();
//
//// 带自定义提示
//[[deprecated("Use new_function() instead, which is safer and faster.")]]
//void legacy_function();
//
//// 也可以标记类型、变量、枚举
//[[deprecated]] typedef char* CString;
//struct [[deprecated]] OldStruct {};
//[[deprecated]] int obsolete_variable;
//#include <cstdlib>
//#include <iostream>
//#include <stdexcept>
//
//// 终止程序的函数
//[[noreturn]] void fatal_error(const std::string& message) {
//    std::cerr << "Fatal error: " << message << std::endl;
//    std::exit(EXIT_FAILURE);
//    // 不需要return语句
//}
//
//// 永远抛异常的函数
//[[noreturn]] void throw_runtime_error(const char* message) {
//    throw std::runtime_error(message);
//}