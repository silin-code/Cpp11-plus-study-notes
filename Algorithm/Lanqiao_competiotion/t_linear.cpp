#include "number_theory.hpp"
#include <cstdio>

// ============================================================
// linearSieve 自测台
//   ① 定点：30 -> 10 个、100 -> 25 个、1 -> 0 个
//   ② 与 sieve 全量对拍：n = 1..5000，两边质数表逐个比
//   ③ 性能：与 sieve 各跑 1e7 一次
// 编译：g++ -std=c++11 -Wall -Wextra -o t_linear.exe t_linear.cpp
// ============================================================

int main() {
    int fail = 0;

    // ---------- ① 定点 ----------
    struct { int n, e; } cs[] = {{30, 10}, {100, 25}, {10, 4}, {2, 1}, {1, 0}, {0, 0}};
    for (auto &c : cs) {
        vector<int> p = linearSieve(c.n);
        if ((int)p.size() != c.e) {
            fail++;
            printf("linearSieve(%d) = %d 个  (expected %d)  !!FAIL\n", c.n, (int)p.size(), c.e);
        } else {
            printf("linearSieve(%d) = %d 个  OK\n", c.n, (int)p.size());
        }
    }

    // 打印 30 以内，肉眼确认
    {
        vector<int> p = linearSieve(30);
        printf("  n=30: ");
        for (int x : p) printf("%d ", x);
        printf("\n");
    }

    // ---------- ② 与 sieve 全量对拍 ----------
    int bad = 0;
    for (int n = 0; n <= 5000; n++) {
        vector<bool> table = sieve(n);
        vector<int> fromSieve;
        for (int i = 2; i <= n; i++) if (table[i]) fromSieve.push_back(i);

        vector<int> fromLinear = linearSieve(n);

        if (fromSieve != fromLinear) {
            if (++bad <= 5) printf("n=%d 两种筛法结果不同（sieve %d 个 / linear %d 个）!!FAIL\n",
                                   n, (int)fromSieve.size(), (int)fromLinear.size());
        }
    }
    printf("\n与 sieve 对拍 n=1..5000：%s\n", bad ? "有不一致" : "完全一致");
    fail += bad;

    // ---------- ③ 顺便确认 1e7 不唐（不测时间，只测不崩） ----------
    {
        vector<int> p = linearSieve(10000000);
        printf("linearSieve(1e7) = %d 个质数 (expect 664579) %s\n",
               (int)p.size(), (int)p.size() == 664579 ? "OK" : "!!FAIL");
        if ((int)p.size() != 664579) fail++;
    }

    printf("\n%s\n", fail == 0 ? "ALL PASSED" : "SOME FAILED");
    return fail ? 1 : 0;
}
