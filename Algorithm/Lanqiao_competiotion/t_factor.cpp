#include "number_theory.hpp"
#include <cstdio>

// ============================================================
// spfTable + factorize 自测台
//   ① spf 与暴力求最小质因子逐个对比（2..100000）
//   ② factorize 定点：360 / 97 / 1 / 12 / 1024
//   ③ factorize 全量自检（2..100000）：
//         - 乘回去必须等于原数
//         - 每个因子都必须是质数
//         - 因子必须严格递增、指数 >= 1
// 编译：g++ -std=c++11 -Wall -Wextra -o t_factor.exe t_factor.cpp
// ============================================================

static int bruteSpf(int x) {
    for (int d = 2; d * d <= x; d++) if (x % d == 0) return d;
    return x;                              // 质数
}

static bool isPrimeSmall(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; d++) if (x % d == 0) return false;
    return true;
}

int main() {
    const int N = 100000;
    int fail = 0;

    vector<int> spf = spfTable(N);

    // ---------- ① spf 正确性 ----------
    int badSpf = 0;
    for (int x = 2; x <= N; x++) {
        if (spf[x] != bruteSpf(x)) {
            if (++badSpf <= 5) printf("spf[%d] = %d, expected %d  !!FAIL\n", x, spf[x], bruteSpf(x));
        }
    }
    printf("spf[2..%d] 与暴力对比：%s\n", N, badSpf ? "有不一致" : "完全一致");
    fail += badSpf;

    // ---------- ② 定点 ----------
    struct { int x; const char* expect; } cs[] = {
        {360,  "2^3 * 3^2 * 5"},
        {97,   "97^1"},
        {1,    "空"},
        {12,   "2^2 * 3^1"},
        {1024, "2^10"},
        {99991,"99991^1（质数）"},
    };
    for (auto &c : cs) {
        vector<pair<int, int>> f = factorize(c.x, spf);
        printf("factorize(%d) = ", c.x);
        if (f.empty()) printf("空");
        for (size_t i = 0; i < f.size(); i++) {
            if (i) printf(" * ");
            printf("%d^%d", f[i].first, f[i].second);
        }
        printf("     期望: %s\n", c.expect);
    }

    // ---------- ③ 全量自检 ----------
    int bad = 0;
    for (int x = 2; x <= N; x++) {
        vector<pair<int, int>> f = factorize(x, spf);
        if (f.empty()) { if (++bad <= 5) printf("factorize(%d) 返回空  !!FAIL\n", x); continue; }

        long long prod = 1;
        int last = 1;
        bool ok = true;
        for (size_t i = 0; i < f.size(); i++) {
            int p = f[i].first, e = f[i].second;
            if (!isPrimeSmall(p)) ok = false;
            if (p <= last) ok = false;      // 严格递增
            if (e < 1) ok = false;
            last = p;
            for (int k = 0; k < e; k++) prod *= p;
        }
        if (!ok || prod != x) {
            if (++bad <= 5) printf("factorize(%d) 自检失败  !!FAIL\n", x);
        }
    }
    printf("\nfactorize 全量自检 2..%d：%s\n", N, bad ? "有问题" : "全部通过（乘回去 = 原数，质因子升序且都是质数）");
    fail += bad;

    printf("\n%s\n", fail == 0 ? "ALL PASSED" : "SOME FAILED");
    return fail ? 1 : 0;
}
