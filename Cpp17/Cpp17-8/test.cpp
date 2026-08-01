#include <filesystem>
namespace fs = std::filesystem;

int main() {
    // 创建目录
    fs::create_directory("mydir");           // 创建单个目录，父目录必须存在
    fs::create_directories("a/b/c/d");       // 递归创建所有层级目录

    // 删除
    fs::remove("file.txt");                  // 删除单个文件或空目录
    fs::remove_all("mydir");                 // 递归删除目录及其所有内容

    // 拷贝
    fs::copy("src.txt", "dst.txt");          // 拷贝文件
    fs::copy("src_dir", "dst_dir",           // 递归拷贝目录
        fs::copy_options::recursive);

    // 拷贝选项组合
    fs::copy_options opts =
        fs::copy_options::recursive |        // 递归拷贝子目录
        fs::copy_options::overwrite_existing; // 覆盖已存在文件

    // 重命名/移动
    fs::rename("old_name.txt", "new_name.txt");

    // 创建符号链接（需要对应平台权限）
    fs::create_symlink("target.txt", "link.txt");

    return 0;
}
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