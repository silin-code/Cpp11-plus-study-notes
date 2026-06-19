#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <array>
#include <tuple>
#include <sstream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>

void log(const std::string& message) {
    std::cout << "[INFO] " << std::quoted(message) << "\n";
}

int main() {
    log("User logged in"); // [INFO] "User logged in"
    log("Message with\nnewline"); // [INFO] "Message with\nnewline"
    return 0;
}

struct Config {
    std::string username;
    std::string password;
    std::string server;
    int port;
};

std::string serialize_config(const Config& config) {
    std::ostringstream oss;
    oss << "username=" << std::quoted(config.username) << "\n"
        << "password=" << std::quoted(config.password) << "\n"
        << "server=" << std::quoted(config.server) << "\n"
        << "port=" << config.port << "\n";
    return oss.str();
}

Config deserialize_config(const std::string& str) {
    Config config;
    std::istringstream iss(str);
    std::string key, value;
    while (std::getline(iss, key, '=')) {
        std::getline(iss, value);
        std::istringstream value_ss(value);
        if (key == "username") value_ss >> std::quoted(config.username);
        else if (key == "password") value_ss >> std::quoted(config.password);
        else if (key == "server") value_ss >> std::quoted(config.server);
        else if (key == "port") value_ss >> config.port;
    }
    return config;
}

struct User {
    std::string name;
    int age;
    std::string email;
};

// 写入CSV文件
void write_csv(const std::string& filename, const std::vector<User>& users) {
    std::ofstream file(filename);
    file << "Name,Age,Email\n";
    for (const auto& user : users) {
        file << std::quoted(user.name) << ","
             << user.age << ","
             << std::quoted(user.email) << "\n";
    }
}

// 读取CSV文件
std::vector<User> read_csv(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);
    std::string line;
    std::getline(file, line); // 跳过表头

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        User user;
        char comma;
        ss >> std::quoted(user.name) >> comma
           >> user.age >> comma
           >> std::quoted(user.email);
        users.push_back(user);
    }
    return users;
}

// // 简化版实现
// template<typename CharT>
// struct quoted_proxy {
//     const CharT* str;
//     CharT quote;
//     CharT escape;
// };

// template<typename CharT>
// quoted_proxy<CharT> quoted(const CharT* str, CharT quote = '"', CharT escape = '\\') {
//     return {str, quote, escape};
// }

// template<typename OStream, typename CharT>
// OStream& operator<<(OStream& os, const quoted_proxy<CharT>& proxy) {
//     os << proxy.quote;
//     for (const CharT* p = proxy.str; *p; ++p) {
//         if (*p == proxy.quote || *p == proxy.escape) {
//             os << proxy.escape;
//         }
//         os << *p;
//     }
//     os << proxy.quote;
//     return os;
// }

// int main()
// {
//     // 1输出：自动添加双引号
//     std::string text = "Hello World";
//     std::cout << "Without quoted" << text << "\n";
//     std::cout << "With quoted" << std::quoted(text) << std::endl;

//     // 2输入：自动除双引号
//     std::istringstream input("\"Hello World!\"");
//     std::string ex;
//     input >> std::quoted(ex);
//     std::cout << "Ex:" << ex << "\n";

//     // 3自定义分隔符：使用单引号
//     std::string s = "It's a test";
//     std::cout << "Single quotes:" << std::quoted(s, '\'') << "\n";
// }

// // 一个接受多个参数的函数
// int sum(int a, int b, int c) {
//     return a + b + c;
// }

// // 将数组的元素展开为函数参数
// template<typename T, std::size_t N, std::size_t... Indices>
// T apply_array(const std::array<T, N>& arr, std::index_sequence<Indices...>) {
//     return sum(arr[Indices]...);
// }

// int main() {
//     std::array<int, 3> arr = {1, 2, 3};
//     int result = apply_array(arr, std::make_index_sequence<3>{});
//     std::cout << "sum: " << result << "\n"; // 6
//     return 0;
// }

// // 编译期生成0到N-1的数组
// template<std::size_t N>
// constexpr std::array<int, N> make_iota_array() {
//     return []<std::size_t... Indices>(std::index_sequence<Indices...>) {
//         return std::array<int, N>{Indices...};
//     }(std::make_index_sequence<N>{});
// }

// int main() {
//     // 编译期生成数组{0,1,2,3,4}
//     constexpr auto arr = make_iota_array<5>();
//     static_assert(arr[0] == 0 && arr[4] == 4);
//     return 0;
// }

// // 辅助函数：使用index_sequence遍历元组
// template<typename Tuple, std::size_t... Indices>
// void print_tuple_impl(const Tuple& t, std::index_sequence<Indices...>) {
//     // C++17折叠表达式：依次打印每个元素
//     ((std::cout << std::get<Indices>(t) << " "), ...);
//     std::cout << "\n";
// }

// // 对外接口
// template<typename... Args>
// void print_tuple(const std::tuple<Args...>& t) {
//     // 生成与元组长度相同的index_sequence
//     print_tuple_impl(t, std::index_sequence_for<Args...>{});
// }

// int main() {
//     auto t = std::make_tuple(10, 3.14, "Hello", 'A');
//     print_tuple(t); // 输出：10 3.14 Hello A
//     return 0;
// }

// // 1基础类定义
// template <class T, T... Ints>
// class integer_sequence;

// // 2辅助模版：快速生成序列
// template <std::size_t N>
// using make_index_sequence = integer_sequence<std::size_t, 0, 1, ..., N-1>;

// template <typename... Ts>
// using index_sequence_for = make_index_sequence<sizeof...(Ts)>;

// // 打印整数序列
// template <typename T, T... Ints>
// void print_sequence(std::integer_sequence<T, Ints...>)
// {
//     ((std::cout << Ints << " "), ...); // C++17的折叠表达式
//     std::cout << "\n";
// }

// int main()
// {
//      // 手动创建序列
//     print_sequence(std::integer_sequence<int, 9, 2, 5, 1>{}); // 9 2 5 1

//     // 生成0到11的序列
//     print_sequence(std::make_integer_sequence<int, 12>{}); // 0 1 2 ... 11

//     // 生成0到9的size_t序列（最常用）
//     print_sequence(std::make_index_sequence<10>{}); // 0 1 2 ... 9

//     // 生成与参数包长度相同的序列
//     print_sequence(std::index_sequence_for<int, double, std::string>{}); // 0 1 2

//     return 0;
// }

// 错误：make_unique不支持自定义删除器
// auto ptr = std::make_unique<FILE>(fopen("file.txt", "r"), fclose);

// 正确：直接构造
// std::unique_ptr<FILE, decltype(&fclose)> ptr(fopen("file.txt", "r"), fclose);

// auto arr1 = std::make_unique<int[]>(5);

// auto arr2= std::make_unique_for_overwrite<int[]>(5);
// for(int i=0;i<5;++i)
// {
//     arr2[i]=i;
// }

// struct Vec3
// {
//     int x, y, z;
//     Vec3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
//     friend std::ostream &operator<<(std::ostream &os, const Vec3 &v)
//     {
//         return os << "{" << v.x << "," << v.y << "," << v.z << "}";
//     }
// };

// int main()
// {
//     // 1创建一个对象
//     std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
//     std::cout << "v1:" << *v1 << "\n";

//     // 2抽创建单个对象
//     std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(1, 2, 3);
//     std::cout << "v2:" << *v2 << "\n";

//     // 3创建数组
//     std::unique_ptr<Vec3[]> arr = std::make_unique<Vec3[]>(5);
//     std::cout << "arr[0]" << arr[0] << "\n";

//     // 4auto自动推导
//     auto ptr = std::make_unique<int>(42);
//     std::cout << "*ptr:" << *ptr << "\n";
// }
// // 手动释放
// class MyClass
// {
//     int *data;

// public:
//     MyClass &operator=(MyClass &&other) noexcept
//     {
//         if (this != &other)
//         {
//             delete data; // 释放当前对象
//             data = other.data;
//             other.data = nullptr;
//         }
//         return *this;
//     }
// };

// // 用std::exchange
// class Myclass
// {
//     int *data;

// public:
//     Myclass& operator=(Myclass &&other) noexcept{
//         if(this!=nullptr)
//         {
//             delete std::exchange(data,other.data);
//             other.data=nullptr;
//         }
//         return *this;
//     }
// };

// template<class T,class U = T>
// T exchange(T& obj,U&& new_value)
// {
//     T old_value = std::move(obj);//移动构造旧值
//     obj = std::forward<U>(new_value);//完美转发新值给obj
//     return old_value;
// }

// // 函数签名
// template<class T, class U = T>
// T exchange(T& obj, U&& new_value);

// int main() {
//     // 1. 基础用法：替换基本类型
//     int x = 10;
//     int old_x = std::exchange(x, 20);
//     std::cout << "old_x: " << old_x << ", new_x: " << x << "\n"; // 10, 20

//     // 2. 替换容器
//     std::vector<int> v1 = {1, 2, 3};
//     std::vector<int> old_v = std::exchange(v1, {4, 5, 6});
//     std::cout << "old_v size: " << old_v.size() << ", new_v size: " << v1.size() << "\n"; // 3, 3

//     // 3. 简洁实现斐波那契数列
//     std::cout << "斐波那契数列: ";
//     for (int a{0}, b{1}; a < 100; a = std::exchange(b, a + b)) {
//         std::cout << a << ", ";
//     }
//     std::cout << "...\n";

//     // 4. 替换类成员变量
//     class Stream {
//         int flags_ = 0;
//     public:
//         int flags() const { return flags_; }
//         int flags(int newf) { return std::exchange(flags_, newf); }
//     };

//     Stream s;
//     std::cout << "初始flags: " << s.flags() << "\n"; // 0
//     std::cout << "旧flags: " << s.flags(12) << "\n"; // 0
//     std::cout << "新flags: " << s.flags() << "\n"; // 12

//     return 0;
// }