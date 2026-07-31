#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

int main() {
    fs::path p = "/home/user/docs/report.txt";

    std::cout << "完整路径: " << p << '\n';
    std::cout << "根路径: " << p.root_path() << '\n';       // "/"
    std::cout << "根目录: " << p.root_directory() << '\n';  // "/"
    std::cout << "根名称: " << p.root_name() << '\n';       // "" (Windows下是盘符)
    std::cout << "相对路径: " << p.relative_path() << '\n'; // "home/user/docs/report.txt"
    std::cout << "父路径: " << p.parent_path() << '\n';     // "/home/user/docs"
    std::cout << "文件名: " << p.filename() << '\n';        // "report.txt"
    std::cout << "主干名: " << p.stem() << '\n';            // "report"
    std::cout << "扩展名: " << p.extension() << '\n';       // ".txt"

    // 路径修改
    p.replace_extension(".md"); // 替换扩展名，变为 report.md
    p.replace_filename("new.txt"); // 替换文件名

    // 规范化路径（消除 . 和 .. 以及多余分隔符）
    fs::path messy = "/home/./user/../user/docs/./file.txt";
    fs::path clean = fs::weakly_canonical(messy);
    // 结果: /home/user/docs/file.txt

    return 0;
}

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