#include "number_theory.hpp"
#include <cstdio>

// ============================================================
// number_theory.hpp 的自测台
// ------------------------------------------------------------
// 用法：把 number_theory.hpp 里的 TODO 填完，编译运行本文件。
//      每一行末尾必须打出 OK；出现 !!FAIL 就停下来找原因。
//
// 编译（PowerShell）：
//   & E:\GCC\mingw64\bin\g++.exe -std=c++11 -Wall -o t_nt.exe t_nt.cpp
//   .\t_nt.exe
//
// 期望值全部是用标准库 __gcd 实算过的，不是手推的。
// ============================================================

int main() {
    setbuf(stdout, NULL);

    struct Case { long long a, b, e; };
    Case cs[] = {
        {     1071,        462,       21},   // 昨天那道手算题
        {       48,         18,        6},   // 教科书例子
        {       17,          5,        1},   // 互质
        {      100,         25,       25},   // 倍数关系
        {        0,          7,        7},   // gcd(0,b) = b
        {      -12,         18,        6},   // 负数：必须取绝对值
        {        0,          0,        0},   // 双零，返回 0
        {999999937LL, 1000000007LL,    1},   // 两个大质数，测 long long
        {123456789,  987654321,        9},   // 大数非平凡答案
        {1LL << 40,  1LL << 20, 1048576},    // 2^40 和 2^20

        // ---- 以下 3 组专打「临时变量用 int」的溢出 ----
        // 第一轮余数分别是 4e9 / 4e9 / 4e9，全部超过 int 上限 2147483647
        { 10000000000LL, 6000000000LL, 2000000000LL},
        {  9000000000LL, 5000000000LL, 1000000000LL},
        {1000000000000000000LL, 6000000000LL, 2000000000LL},
    };

    int fail = 0;
    for (auto &c : cs) {
        long long got = gcd(c.a, c.b);
        if (got != c.e) {
            fail++;
            printf("gcd(%lld, %lld) = %lld   (expected %lld)  !!FAIL\n", c.a, c.b, got, c.e);
        } else {
            printf("gcd(%lld, %lld) = %lld   OK\n", c.a, c.b, got);
        }
    }

    // ===== lcm =====
    printf("\n--- lcm ---\n");
    struct LCase { long long a, b, e; };
    LCase ls[] = {
        {            4,             6,                   12},
        {         1071,           462,                23562},
        {            0,             5,                    0},   // gcd(0,5)=5，不崩
        {            0,             0,                    0},   // 不拦 0 会 a/0 崩溃
        {1000000000LL, 999999937LL, 999999937000000000LL},      // 结果 ~1e18，测是否溢出
        {10000000000LL, 6000000000LL,           30000000000LL},  // 参数超 2.1e9，测 long 截断
    };
    int lfail = 0;
    for (auto &c : ls) {
        long long got = lcm(c.a, c.b);
        if (got != c.e) {
            lfail++;
            printf("lcm(%lld, %lld) = %lld   (expected %lld)  !!FAIL\n", c.a, c.b, got, c.e);
        } else {
            printf("lcm(%lld, %lld) = %lld   OK\n", c.a, c.b, got);
        }
    }

    printf("\n%d / %d passed\n", (int)(sizeof(cs) / sizeof(cs[0])) - fail,
           (int)(sizeof(cs) / sizeof(cs[0])));
    printf("%d / %d passed  (lcm)\n", (int)(sizeof(ls) / sizeof(ls[0])) - lfail,
           (int)(sizeof(ls) / sizeof(ls[0])));
    return (fail + lfail) ? 1 : 0;
}
