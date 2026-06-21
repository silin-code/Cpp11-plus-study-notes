// 编译期字节单位转换
constexpr unsigned long long operator "" _KB(unsigned long long x) {
    return x * 1024;
}

constexpr unsigned long long operator "" _MB(unsigned long long x) {
    return x * 1024_KB;
}

constexpr unsigned long long operator "" _GB(unsigned long long x) {
    return x * 1024_MB;
}

int main() {
    // 编译期计算：1GB = 1073741824字节
    constexpr auto buffer_size = 1_GB;
    static_assert(buffer_size == 1073741824ULL);
    return 0;
}

// #include <iostream>
// #include <string>
// #include <thread>
// #include <string_view>
// #include <chrono>

// // 自定义字面量后缀：必须以下划线开头
// // 1. 字符串字面量后缀
// std::string operator "" _s(const char* str, size_t len) {
//     return std::string(str, len);
// }

// std::string_view operator "" _sv(const char* str, size_t len) {
//     return std::string_view(str, len);
// }

// // 2. 浮点数字面量后缀：公里转米
// constexpr long double operator "" _km(unsigned long long x) {
//     return x * 1000.0L;
// }

// // 3. 浮点数字面量后缀：弧度转角度
// constexpr long double operator "" _pi(long double x) {
//     return x * 3.14159265358979323846L;
// }

// int main() {
//     // 使用自定义后缀
//     auto str = "hello"_s; // std::string
//     auto sv = "world"_sv; // std::string_view
//     auto distance = 5_km; // 5000.0L
//     auto angle = 2.0_pi;  // 6.283185307...

//     // C++14 标准库后缀（需要引入命名空间）
//     using namespace std::literals;
    
//     // 字符串字面量
//     auto std_str = "hello"s;   // std::string
//     auto std_sv = "world"sv;   // std::string_view（C++17）
    
//     // 时间字面量
//     auto hours = 24h;          // std::chrono::hours
//     auto minutes = 30min;      // std::chrono::minutes
//     auto seconds = 10s;        // std::chrono::seconds
//     auto ms = 100ms;           // std::chrono::milliseconds

//     // 使用时间字面量
//     std::this_thread::sleep_for(500ms); // 比 std::chrono::milliseconds(500) 简洁得多

//     return 0;
// }
// #include <iostream>
// #include <shared_mutex>
// #include <mutex>
// #include <thread>
// #include <vector>
// #include <chrono>
// #include <syncstream> // C++20 同步输出，保证多线程输出不乱序

// // 定义别名，方便后续切换互斥锁类型
// using MutexType = std::shared_timed_mutex;

// class ThreadSafeCounter {
// private:
//     // mutable：允许在const成员函数中修改mutex
//     mutable MutexType mutex_;
//     unsigned int value_ = 0;

// public:
//     ThreadSafeCounter() = default;

//     // 读操作：使用共享锁（shared_lock）
//     unsigned int get() const {
//         std::shared_lock<MutexType> lock(mutex_);
//         return value_;
//     }

//     // 写操作：使用独占锁（unique_lock）
//     void increment() {
//         std::unique_lock<MutexType> lock(mutex_);
//         ++value_;
//     }

//     // 尝试获取独占锁（非阻塞）
//     bool try_increment() {
//         std::unique_lock<MutexType> lock(mutex_, std::try_to_lock);
//         if (lock.owns_lock()) {
//             ++value_;
//             return true;
//         }
//         return false;
//     }

//     // 一段时间内尝试获取独占锁（带超时）
//     bool try_increment_for(int milliseconds) {
//         std::unique_lock<MutexType> lock(
//             mutex_, std::chrono::milliseconds(milliseconds));
//         return lock.owns_lock() ? (++value_, true) : false;
//     }
// };

// int main() {
//     ThreadSafeCounter counter;
//     const int N = 10;

//     // 写线程：每100ms递增一次
//     auto writer = [&counter]() {
//         for (int i = 0; i < N/2; ++i) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(100));
//             counter.increment();
//             std::osyncstream(std::cout) 
//                 << "写线程 " << std::this_thread::get_id() 
//                 << "：计数器值 = " << counter.get() << "\n";
//         }
//     };

//     // 读线程：每50ms读取一次
//     auto reader = [&counter]() {
//         for (int i = 0; i < N; ++i) {
//             std::this_thread::sleep_for(std::chrono::milliseconds(50));
//             std::osyncstream(std::cout) 
//                 << "读线程 " << std::this_thread::get_id() 
//                 << "：读取到值 = " << counter.get() << "\n";
//         }
//     };

//     // 启动线程：1个写线程 + 3个读线程
//     std::vector<std::thread> threads;
//     threads.emplace_back(writer);
//     for (int i = 0; i < 3; ++i) {
//         threads.emplace_back(reader);
//     }

//     // 等待所有线程结束
//     for (auto& t : threads) {
//         t.join();
//     }

//     std::cout << "最终计数器值：" << counter.get() << "\n";
//     return 0;
// }