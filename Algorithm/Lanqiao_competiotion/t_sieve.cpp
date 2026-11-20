#include "number_theory.hpp"
#include <cstdio>

// ============================================================
// sieve 自测台
// ------------------------------------------------------------
// 编译：
//   g++ -std=c++11 -Wall -Wextra -o t_sieve.exe t_sieve.cpp
//   .\t_sieve.exe
//
// 三层验证：
//   ① 定点：30 -> 10 个，100 -> 25 个
//   ② 边界：n = 0 / 1 / 2 不能崩、不能越界
//   ③ 对拍：n = 0..5000，逐个数和暴力判断比
// ============================================================

// 暴力：单个数是不是质数
static bool isPrimeSlow(int x) {
    if (x < 2) return false;
    for (int d = 2; (long long)d * d <= x; d++)
        if (x % d == 0) return false;
    return true;
}

// 数一数 [2, n] 里有几个 true
static int countIn(const vector<bool>& v, int n) {
    int c = 0;
    for (int i = 2; i <= n && i < (int)v.size(); i++)
        if (v[i]) c++;
    return c;
}

int main() {
    setbuf(stdout, NULL);
    int fail = 0;

    // ---------- ① 定点 ----------
    struct { int n, e; } cs[] = {
        {30,  10},   // 2 3 5 7 11 13 17 19 23 29
        {100, 25},
        {10,   4},   // 2 3 5 7
        {2,    1},   // 只有 2
        {1,    0},   // 边界：数组里只有下标 0、1
        {0,    0},   // 边界：数组里只有下标 0
    };
    for (auto &c : cs) {
        vector<bool> v = sieve(c.n);
        if ((int)v.size() != c.n + 1) {
            fail++;
            printf("sieve(%d) size = %d  (expected %d)  !!FAIL\n", c.n, (int)v.size(), c.n + 1);
            continue;
        }
        int got = countIn(v, c.n);
        if (got != c.e) {
            fail++;
            printf("sieve(%d) count = %d  (expected %d)  !!FAIL\n", c.n, got, c.e);
        } else {
            printf("sieve(%d) count = %d  OK\n", c.n, got);
        }
    }

    // ---------- ②③ 对拍 ----------
    int diff = 0;
    for (int n = 0; n <= 5000; n++) {
        vector<bool> v = sieve(n);
        if ((int)v.size() != n + 1) { printf("sieve(%d) size wrong\n", n); fail++; break; }
        for (int x = 0; x <= n; x++) {
            if (v[x] != isPrimeSlow(x)) {
                if (++diff <= 10)
                    printf("sieve(%d): isPrime[%d] = %d, expected %d  !!FAIL\n",
                           n, x, (int)v[x], (int)isPrimeSlow(x));
            }
        }
        if (diff > 10) break;
    }
    printf("\n对拍 n=0..5000：%s\n", diff == 0 ? "全部一致" : "有不一致");
    fail += diff;

    printf("\n%s\n", fail == 0 ? "ALL PASSED" : "SOME FAILED");
    return fail ? 1 : 0;
}
