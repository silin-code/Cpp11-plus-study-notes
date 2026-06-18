#include <iostream>
#include <utility>
#include <vector>

// 函数签名
template<class T, class U = T>
T exchange(T& obj, U&& new_value);

int main() {
    // 1. 基础用法：替换基本类型
    int x = 10;
    int old_x = std::exchange(x, 20);
    std::cout << "old_x: " << old_x << ", new_x: " << x << "\n"; // 10, 20

    // 2. 替换容器
    std::vector<int> v1 = {1, 2, 3};
    std::vector<int> old_v = std::exchange(v1, {4, 5, 6});
    std::cout << "old_v size: " << old_v.size() << ", new_v size: " << v1.size() << "\n"; // 3, 3

    // 3. 课件经典示例：简洁实现斐波那契数列
    std::cout << "斐波那契数列: ";
    for (int a{0}, b{1}; a < 100; a = std::exchange(b, a + b)) {
        std::cout << a << ", ";
    }
    std::cout << "...\n";

    // 4. 替换类成员变量
    class Stream {
        int flags_ = 0;
    public:
        int flags() const { return flags_; }
        int flags(int newf) { return std::exchange(flags_, newf); }
    };

    Stream s;
    std::cout << "初始flags: " << s.flags() << "\n"; // 0
    std::cout << "旧flags: " << s.flags(12) << "\n"; // 0
    std::cout << "新flags: " << s.flags() << "\n"; // 12

    return 0;
}