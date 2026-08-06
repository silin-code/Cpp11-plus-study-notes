//#include <vector>
//#include <algorithm>
//#include <execution>
//#include <string>
//
//struct LogEntry {
//    std::string message;
//    int level; // 0:debug, 1:info, 2:warn, 3:error
//    uint64_t timestamp;
//};
//
//// 并行过滤错误日志
//std::vector<LogEntry> filterErrors(const std::vector<LogEntry>& logs) {
//    std::vector<LogEntry> errors;
//    std::copy_if(std::execution::par,
//        logs.begin(), logs.end(),
//        std::back_inserter(errors),
//        [](const LogEntry& e) { return e.level >= 3; });
//    return errors;
//}
//
//// 并行统计各等级日志数量
//std::vector<size_t> countByLevel(const std::vector<LogEntry>& logs) {
//    std::vector<size_t> counts(4, 0);
//    std::for_each(std::execution::par, logs.begin(), logs.end(),
//        [&](const LogEntry& e) {
//            // 注意：这里有数据竞争！实际使用需要原子操作或分块统计
//            // counts[e.level]++; 
//        });
//    // 正确做法：用 transform_reduce 或者分块统计
//    return counts;
//}

//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//uintmax_t calculateDirectorySize(const fs::path& dir) {
//    uintmax_t total_size = 0;
//    uintmax_t file_count = 0;
//    uintmax_t dir_count = 0;
//
//    std::error_code ec;
//    for (const auto& entry : fs::recursive_directory_iterator(
//        dir, fs::directory_options::skip_permission_denied, ec)) {
//        if (entry.is_regular_file()) {
//            total_size += entry.file_size();
//            file_count++;
//        }
//        else if (entry.is_directory()) {
//            dir_count++;
//        }
//    }
//
//    std::cout << "文件数: " << file_count << '\n';
//    std::cout << "目录数: " << dir_count << '\n';
//    std::cout << "总大小: " << total_size << " bytes ("
//        << total_size / 1024 / 1024 << " MB)\n";
//
//    return total_size;
//}

//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <execution>
//#include <chrono>
//#include <random>
//#include <numeric>
//
//template<typename Func>
//double benchmark(Func&& func, int iterations = 5) {
//    double total = 0;
//    for (int i = 0; i < iterations; ++i) {
//        auto start = std::chrono::high_resolution_clock::now();
//        func();
//        auto end = std::chrono::high_resolution_clock::now();
//        total += std::chrono::duration<double, std::milli>(end - start).count();
//    }
//    return total / iterations;
//}
//
//int main() {
//    const int N = 10'000'000;
//    std::vector<int> v(N);
//    std::mt19937 gen(42);
//    std::generate(v.begin(), v.end(), gen);
//
//    std::cout << "数据量: " << N << " 个int\n";
//    std::cout << "==============================\n";
//
//    // ===== 排序性能对比 =====
//    auto v1 = v;
//    double t_sort_seq = benchmark([&]() {
//        auto tmp = v1;
//        std::sort(tmp.begin(), tmp.end());
//        });
//
//    double t_sort_par = benchmark([&]() {
//        auto tmp = v1;
//        std::sort(std::execution::par, tmp.begin(), tmp.end());
//        });
//
//    std::cout << "排序 - 顺序: " << t_sort_seq << "ms\n";
//    std::cout << "排序 - 并行: " << t_sort_par << "ms\n";
//    std::cout << "加速比: " << t_sort_seq / t_sort_par << "x\n\n";
//
//    // ===== 求和性能对比 =====
//    double t_sum_seq = benchmark([&]() {
//        volatile long long sum = std::accumulate(v.begin(), v.end(), 0LL);
//        });
//
//    double t_sum_par = benchmark([&]() {
//        volatile long long sum = std::reduce(std::execution::par, v.begin(), v.end(), 0LL);
//        });
//
//    std::cout << "求和 - 顺序: " << t_sum_seq << "ms\n";
//    std::cout << "求和 - 并行: " << t_sum_par << "ms\n";
//    std::cout << "加速比: " << t_sum_seq / t_sum_par << "x\n\n";
//
//    // ===== 变换性能对比 =====
//    std::vector<int> output(N);
//    double t_trans_seq = benchmark([&]() {
//        std::transform(v.begin(), v.end(), output.begin(),
//            [](int x) { return x * x + 2 * x + 1; });
//        });
//
//    double t_trans_par = benchmark([&]() {
//        std::transform(std::execution::par, v.begin(), v.end(), output.begin(),
//            [](int x) { return x * x + 2 * x + 1; });
//        });
//
//    std::cout << "变换 - 顺序: " << t_trans_seq << "ms\n";
//    std::cout << "变换 - 并行: " << t_trans_par << "ms\n";
//    std::cout << "加速比: " << t_trans_seq / t_trans_par << "x\n";
//
//    return 0;
//}

//#include <vector>
//#include <algorithm>
//#include <execution>
//
//int main() {
//    std::vector<int> v(1000000);
//
//    // remove/remove_if：移除满足条件的元素
//    auto new_end = std::remove_if(std::execution::par,
//        v.begin(), v.end(),
//        [](int x) { return x < 0; });
//    v.erase(new_end, v.end());
//
//    // unique：去重（需要先排序）
//    std::sort(std::execution::par, v.begin(), v.end());
//    auto last = std::unique(std::execution::par, v.begin(), v.end());
//    v.erase(last, v.end());
//
//    // partition：分区
//    std::partition(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x % 2 == 0; });
//
//    return 0;
//}

//#include <vector>
//#include <algorithm>
//#include <execution>
//
//int main() {
//    std::vector<int> input(1000000);
//    std::vector<int> output(1000000);
//
//    // ===== 变换算法 =====
//    std::transform(std::execution::par,
//        input.begin(), input.end(),
//        output.begin(),
//        [](int x) { return x * x; });
//
//    // 二元变换
//    std::vector<int> a(1000000), b(1000000), c(1000000);
//    std::transform(std::execution::par,
//        a.begin(), a.end(), b.begin(), c.begin(),
//        [](int x, int y) { return x + y; });
//
//    // ===== 遍历算法 =====
//    std::for_each(std::execution::par, input.begin(), input.end(),
//        [](int& x) { x *= 2; });
//
//    // for_each_n：遍历前n个元素
//    std::for_each_n(std::execution::par, input.begin(), 1000,
//        [](int& x) { x += 1; });
//
//    // ===== 复制与填充 =====
//    std::copy(std::execution::par, input.begin(), input.end(), output.begin());
//    std::fill(std::execution::par, output.begin(), output.end(), 0);
//    std::generate(std::execution::par, output.begin(), output.end(), std::rand);
//
//    return 0;
//}

//#include <vector>
//#include <numeric>
//#include <execution>
//
//int main() {
//    std::vector<double> v(1000000, 1.0);
//
//    // ===== 归约算法 =====
//    // reduce：并行版的 accumulate，不保证累加顺序
//    double sum = std::reduce(std::execution::par, v.begin(), v.end());
//    // 注意：浮点数求和顺序不同结果可能有微小差异！
//
//    // 带初始值的 reduce
//    double sum2 = std::reduce(std::execution::par, v.begin(), v.end(), 0.0);
//
//    // transform_reduce：变换+归约组合
//    double dot_product = std::transform_reduce(
//        std::execution::par,
//        v.begin(), v.end(),  // 第一个序列
//        v.begin(),           // 第二个序列
//        0.0                  // 初始值
//    );
//
//    // 自定义操作的 transform_reduce
//    auto sum_of_squares = std::transform_reduce(
//        std::execution::par,
//        v.begin(), v.end(),
//        0.0,
//        std::plus<>(),                    // 归约操作：加法
//        [](double x) { return x * x; }    // 变换操作：平方
//    );
//
//    // ===== 前缀和（扫描算法） =====
//    std::vector<double> result(v.size());
//
//    // inclusive_scan：包含当前元素的前缀和
//    std::inclusive_scan(std::execution::par,
//        v.begin(), v.end(),
//        result.begin());
//
//    // exclusive_scan：不包含当前元素的前缀和
//    std::exclusive_scan(std::execution::par,
//        v.begin(), v.end(),
//        result.begin(),
//        0.0); // 初始值
//
//    return 0;
//}

//#include <vector>
//#include <algorithm>
//#include <execution>
//#include <numeric>
//
//int main() {
//    std::vector<int> v(1000000);
//
//    // ===== 排序算法 =====
//    std::sort(std::execution::par, v.begin(), v.end());
//    std::stable_sort(std::execution::par, v.begin(), v.end());
//    std::partial_sort(std::execution::par, v.begin(), v.begin() + 100, v.end());
//    std::nth_element(std::execution::par, v.begin(), v.begin() + 500, v.end());
//
//    // ===== 查找算法 =====
//    auto it = std::find(std::execution::par, v.begin(), v.end(), 42);
//    auto it2 = std::find_if(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x > 100; });
//
//    auto count = std::count(std::execution::par, v.begin(), v.end(), 42);
//    auto count2 = std::count_if(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x % 2 == 0; });
//
//    bool all_pos = std::all_of(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x >= 0; });
//    bool any_neg = std::any_of(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x < 0; });
//    bool none_zero = std::none_of(std::execution::par, v.begin(), v.end(),
//        [](int x) { return x == 0; });
//
//    // ===== 二分查找（注意：要求已排序） =====
//    // 二分查找本身是O(log n)，并行收益不大，通常不需要并行
//    bool found = std::binary_search(v.begin(), v.end(), 42);
//
//    return 0;
//}
//#include <vector>
//#include <algorithm>
//#include <execution>
//
//int main() {
//    std::vector<int> v(1000000);
//
//    // 传统顺序排序（和C++14完全一样）
//    std::sort(v.begin(), v.end());
//
//    // C++17 并行排序
//    std::sort(std::execution::par, v.begin(), v.end());
//
//    // 并行+向量化排序（性能最高）
//    std::sort(std::execution::par_unseq, v.begin(), v.end());
//
//    return 0;
//}
//#include<filesystem>
//#include<system_error>
//#include<iostream>
//namespace fs = std::filesystem;
//
//int mian()
//{
//	// ===== 方式1：异常方式（默认） =====
//	// 操作失败抛出 fs::filesystem_error 异常
//	try {
//		fs::copy("nonexistent.txt", "dst.txt");
//	}
//	catch(const fs::filesystem_error& e)
//	{
//		std::cout << "错误信息: " << e.what() << '\n';
//		std::cout << "路径1: " << e.path1() << '\n';
//		std::cout << "路径2: " << e.path2() << '\n';
//		std::cout << "错误码: " << e.code() << '\n';
//		std::cout << "错误类别: " << e.code().category().name() << '\n';
//	}
//
//	// ===== 方式2：错误码方式 =====
//	// 传入 std::error_code& 参数，失败不抛异常，错误码写入参数
//	std::error_code ec;
//	fs::copy("nonexistent.txt", "dst.txt", ec);
//	if (ec) {
//		std::cout << "错误码值: " << ec.value() << '\n';
//		std::cout << "错误信息: " << ec.message() << '\n';
//		std::cout << "错误类别: " << ec.category().name() << '\n';
//	}
//
//	// 无错误时 ec.value() == 0，ec 转换为 bool 为 false
//	return 0;
//}

//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    fs::path root = ".";
//
//    // 递归遍历所有文件和子目录
//    for (const auto& entry : fs::recursive_directory_iterator(root)) {
//        // depth() 获取当前递归深度（从0开始）
//        std::cout << entry.path().relative_path() << '\n';
//    }
//
//    // 高级用法：控制遍历深度
//    auto it = fs::recursive_directory_iterator(root);
//    for (; it != fs::recursive_directory_iterator(); ++it) {
//        if (it.depth() >= 2) {
//            it.disable_recursion_pending();
//            // 跳过当前条目的子目录，不进入递归
//        }
//
//        if (it->is_directory() && it->path().filename() == ".git") {
//            it.pop(); // 直接弹出当前目录，跳过整个.git目录
//        }
//    }
//
//    // 递归遍历选项
//    // directory_options::skip_permission_denied - 跳过无权限的条目
//    // directory_options::follow_directory_symlink - 跟随目录符号链接（注意循环风险）
//
//    return 0;
//}
//#include<iostream>
//#include<filesystem>
//namespace fs = std::filesystem;
//
//int main()
//{
//	fs::path dir_path = ".";
//	// 方式1：范围for遍历（最常用）
//	for (const auto& entry : fs::directory_iterator(dir_path))
//	{
//		// entry 是 fs::directory_entry 类型
//		std::cout << entry.path().filename();
//
//		// directory_entry 会缓存状态，减少系统调用
//		if (entry.is_directory()) {
//			std::cout << "  [目录]";
//		}
//		else if (entry.is_regular_file()) {
//			std::cout << "  " << entry.file_size() << " bytes";
//		}
//		std::cout << '\n';
//	}
//	// 方式2：迭代器遍历
//	auto it = fs::directory_iterator(dir_path);
//	auto end = fs::directory_iterator(); // 默认构造就是end迭代器
//	for (; it != end; ++it) {
//		// 处理每个条目
//	}
//
//	// 遍历选项
//	// directory_options::none           - 默认行为
//	// directory_options::skip_permission_denied - 跳过无权限访问的条目
//	// directory_options::follow_directory_symlink - 跟随目录符号链接
//
//	return 0;
//}
//#include <filesystem>
//#include <chrono>
//#include<iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    fs::path p = "test.txt";
//
//    // 文件大小（仅普通文件有效）
//    uintmax_t size = fs::file_size(p);
//
//    // 最后修改时间
//    fs::file_time_type ftime = fs::last_write_time(p);
//    // file_time_type 是 std::chrono::time_point 类型
//
//    // 修改最后修改时间
//    fs::last_write_time(p, fs::file_time_type::clock::now());
//
//    // 磁盘空间查询
//    fs::space_info si = fs::space("/");
//    std::cout << "总容量: " << si.capacity << " bytes\n";
//    std::cout << "空闲空间: " << si.free << " bytes\n";
//    std::cout << "可用空间: " << si.available << " bytes\n";
//    // free 是物理空闲空间，available 是当前用户可用的空间（可能更小）
//
//    // 可用空间考虑了磁盘配额、保留空间等因素
//
//    return 0;
//}
//#include<filesystem>
//#include<iostream>
//namespace fs = std::filesystem;
//
//int main()
//{
//	//创建目录
//	fs::create_directory("mydir");//创建单个目录
//	fs::create_directories("a/b/c");//创建多级目录
//
//	//删除
//	fs::remove("file.txt");//删除单个文件或者空目录
//	fs::remove_all("mydir");//递归删除目录的整个内容
//	//remove_all返回删除的目录条数
//
//	//拷贝
//	fs::copy("src.txt", "dst.txt");//拷贝文件
//
//	//拷贝目录
//	fs::copy_options opts =
//		fs::copy_options::recursive |//递归拷贝
//		fs::copy_options::overwrite_existing |//覆盖已存在文件
//		fs::copy_options::copy_symlinks;//拷贝符号链接本身，不跟随
//	fs::copy("src_dir", "dst.txt", opts);
//
//	// copy_options 其他常用选项:
//	//   skip_existing       - 跳过已存在的文件
//	//   update_existing     - 只在源文件更新时覆盖
//	//   directories::skip   - 跳过目录
//	//   create_symlinks     - 创建符号链接代替拷贝
//	//   hard_links          - 创建硬链接代替拷贝
//
//	// ===== 重命名/移动 =====
//	fs::rename("old_name.txt", "new_name.txt");
//	// rename 也可以用来移动文件到不同目录
//
//	// ===== 创建符号链接/硬链接 =====
//	fs::create_symlink("target.txt", "link.txt");   // 符号链接
//	fs::create_hard_link("target.txt", "link.txt"); // 硬链接
//	return 0;
//}

//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    fs::path p = "test.txt";
//
//    // 1. 完全替换：设置为 0644（所有者读写，其他只读）
//    fs::permissions(p,
//        fs::perms::owner_read | fs::perms::owner_write
//        | fs::perms::group_read | fs::perms::others_read);
//
//    // 2. 添加权限：给所有用户加上执行权限（等价于 chmod +x）
//    fs::permissions(p,
//        fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec,
//        fs::perm_options::add);
//
//    // 3. 移除权限：移除其他用户的写权限（等价于 chmod o-w）
//    fs::permissions(p, fs::perms::others_write, fs::perm_options::remove);
//
//    // 4. 不跟随符号链接，修改链接本身
//    fs::permissions("link.txt", fs::perms::owner_read,
//        fs::perm_options::replace | fs::perm_options::nofollow);
//
//    // 5. 错误码方式（推荐用于批量操作）
//    std::error_code ec;
//    fs::permissions("/etc/passwd", fs::perms::all, ec);
//    if (ec) {
//        std::cerr << "修改失败: " << ec.message() << '\n';
//    }
//
//    return 0;
//}
//#include<filesystem>
//#include<iostream>
//#include<iomanip>
//namespace fs = std::filesystem;
//
////// 函数签名
////void permissions(const path& p, perms prms);
////void permissions(const path& p, perms prms, std::error_code& ec) noexcept;
////void permissions(const path& p, perms prms, perm_options opts);
////void permissions(const path& p, perms prms, perm_options opts, std::error_code& ec) noexcept;
//
//void printPermissions(const fs::path& p)
//{
//	fs::perms perm = fs::status(p).permissions();
//
//    // 八进制输出
//    std::cout << "文件: " << p.filename() << '\n';
//    std::cout << "  八进制权限: 0" << std::oct << std::setw(3) << std::setfill('0')
//        << static_cast<unsigned>(perm & fs::perms::mask) << std::dec << '\n';
//
//    // 类似 ls -l 的 rwx 格式输出
//    auto rwx = [&](fs::perms r, fs::perms w, fs::perms x) {
//        std::cout << ((perm & r) != fs::perms::none ? 'r' : '-');
//        std::cout << ((perm & w) != fs::perms::none ? 'w' : '-');
//        std::cout << ((perm & x) != fs::perms::none ? 'x' : '-');
//        };
//
//    std::cout << "  rwx格式: ";
//    rwx(fs::perms::owner_read, fs::perms::owner_write, fs::perms::owner_exec);
//    rwx(fs::perms::group_read, fs::perms::group_write, fs::perms::group_exec);
//    rwx(fs::perms::others_read, fs::perms::others_write, fs::perms::others_exec);
//    std::cout << '\n';
//
//    // 特殊权限位
//    std::cout << "  setuid: " << ((perm & fs::perms::set_uid) != fs::perms::none) << '\n';
//    std::cout << "  setgid: " << ((perm & fs::perms::set_gid) != fs::perms::none) << '\n';
//    std::cout << "  sticky: " << ((perm & fs::perms::sticky_bit) != fs::perms::none) << '\n';
//}
//
//int main() {
//    printPermissions("test.txt");
//    printPermissions("/usr/bin/passwd"); // 典型的setuid文件
//    printPermissions("/tmp");            // 典型的sticky目录
//    return 0;
//}

//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//void printFileType(const fs::path& p) {
//    std::cout << "文件: " << p.filename() << '\n';
//    std::cout << "  存在: " << fs::exists(p) << '\n';
//
//    if (fs::exists(p)) {
//        std::cout << "  普通文件: " << fs::is_regular_file(p) << '\n';
//        std::cout << "  目录: " << fs::is_directory(p) << '\n';
//        std::cout << "  符号链接: " << fs::is_symlink(p) << '\n';
//        std::cout << "  空: " << fs::is_empty(p) << '\n';
//
//        if (fs::is_regular_file(p)) {
//            std::cout << "  文件大小: " << fs::file_size(p) << " bytes\n";
//        }
//    }
//}
//
//int main() {
//    printFileType("test.txt");
//    printFileType("mydir");
//    printFileType("link_to_test"); // 符号链接
//    return 0;
//}
//fs::perms p = fs::perms::owner_read | fs::perms::owner_write; // 组合权限
//p |= fs::perms::owner_exec;        // 添加执行权限
//p &= ~fs::perms::owner_write;      // 移除写权限
//
//// 检查是否有某权限
//bool can_read = (p & fs::perms::owner_read) != fs::perms::none;
//bool can_write = (p & fs::perms::owner_write) != fs::perms::none;
//fs::file_status status = fs::status("test.txt");
//
//// 文件类型
//fs::file_type type = status.type();
//// type 可以是:
////   fs::file_type::none       - 状态无效
////   fs::file_type::not_found  - 文件不存在
////   fs::file_type::regular    - 普通文件
////   fs::file_type::directory  - 目录
////   fs::file_type::symlink    - 符号链接
////   fs::file_type::block      - 块设备
////   fs::file_type::character  - 字符设备
////   fs::file_type::fifo       - 管道
////   fs::file_type::socket     - 套接字
////   fs::file_type::unknown    - 存在但类型未知
//
//// 权限
//fs::perms perm = status.permissions();

//#include <filesystem>
//namespace fs = std::filesystem;
//
//int main() {
//    // 创建目录
//    fs::create_directory("mydir");           // 创建单个目录，父目录必须存在
//    fs::create_directories("a/b/c/d");       // 递归创建所有层级目录
//
//    // 删除
//    fs::remove("file.txt");                  // 删除单个文件或空目录
//    fs::remove_all("mydir");                 // 递归删除目录及其所有内容
//
//    // 拷贝
//    fs::copy("src.txt", "dst.txt");          // 拷贝文件
//    fs::copy("src_dir", "dst_dir",           // 递归拷贝目录
//        fs::copy_options::recursive);
//
//    // 拷贝选项组合
//    fs::copy_options opts =
//        fs::copy_options::recursive |        // 递归拷贝子目录
//        fs::copy_options::overwrite_existing; // 覆盖已存在文件
//
//    // 重命名/移动
//    fs::rename("old_name.txt", "new_name.txt");
//
//    // 创建符号链接（需要对应平台权限）
//    fs::create_symlink("target.txt", "link.txt");
//
//    return 0;
//}
//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    fs::path p = "test.txt";
//
//    // 基本存在性与类型判断
//    std::cout << "存在: " << fs::exists(p) << '\n';
//    std::cout << "是普通文件: " << fs::is_regular_file(p) << '\n';
//    std::cout << "是目录: " << fs::is_directory(p) << '\n';
//    std::cout << "是符号链接: " << fs::is_symlink(p) << '\n';
//    std::cout << "是空文件/目录: " << fs::is_empty(p) << '\n';
//
//    // 文件大小（字节）
//    if (fs::is_regular_file(p)) {
//        std::cout << "文件大小: " << fs::file_size(p) << " bytes\n";
//    }
//
//    // 最后修改时间
//    auto ftime = fs::last_write_time(p);
//
//    // 磁盘空间查询
//    fs::space_info si = fs::space("/");
//    std::cout << "总容量: " << si.capacity << '\n';
//    std::cout << "可用空间: " << si.available << '\n';
//    std::cout << "空闲空间: " << si.free << '\n';
//
//    return 0;
//}
//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    fs::path p = "/home/user/docs/report.txt";
//
//    std::cout << "完整路径: " << p << '\n';
//    std::cout << "根路径: " << p.root_path() << '\n';       // "/"
//    std::cout << "根目录: " << p.root_directory() << '\n';  // "/"
//    std::cout << "根名称: " << p.root_name() << '\n';       // "" (Windows下是盘符)
//    std::cout << "相对路径: " << p.relative_path() << '\n'; // "home/user/docs/report.txt"
//    std::cout << "父路径: " << p.parent_path() << '\n';     // "/home/user/docs"
//    std::cout << "文件名: " << p.filename() << '\n';        // "report.txt"
//    std::cout << "主干名: " << p.stem() << '\n';            // "report"
//    std::cout << "扩展名: " << p.extension() << '\n';       // ".txt"
//
//    // 路径修改
//    p.replace_extension(".md"); // 替换扩展名，变为 report.md
//    p.replace_filename("new.txt"); // 替换文件名
//
//    // 规范化路径（消除 . 和 .. 以及多余分隔符）
//    fs::path messy = "/home/./user/../user/docs/./file.txt";
//    fs::path clean = fs::weakly_canonical(messy);
//    // 结果: /home/user/docs/file.txt
//
//    return 0;
//}

//#include <filesystem>
//#include <iostream>
//namespace fs = std::filesystem;
//
//int main() {
//    // 1. 从字符串构造
//    fs::path p1 = "/home/user/documents";
//    fs::path p2("C:\\Users\\name\\file.txt");
//
//    // 2. 路径拼接：使用 / 运算符（推荐）
//    fs::path p3 = p1 / "subdir" / "file.txt";
//    // 自动处理分隔符，POSIX下得到 /home/user/documents/subdir/file.txt
//
//    // 3. 追加：使用 += 或 /=
//    fs::path p4 = "dir";
//    p4 += "_name";   // 字符串追加，得到 "dir_name"
//    p4 /= "subdir";  // 路径追加，得到 "dir_name/subdir"
//
//    return 0;
//}