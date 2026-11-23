#include "number_theory.hpp"
#include <cstdio>
#include <cstdlib>

// ============================================================
// qpow 自测台
//   ① 定点（含手算过的 3^13）
//   ② 边界：b=0 / a=0 / mod=1
//   ③ 小范围暴力对拍
//   ④ 大指数：与 Python pow() 的参考值比
//   ⑤ 费马小定理：2^(p-1) ≡ 1 (mod p)
// 编译：g++ -std=c++11 -Wall -Wextra -o t_qpow.exe t_qpow.cpp
// ============================================================

static long long brutePow(long long a, long long b, long long mod) {
    long long r = 1 % mod;
    a %= mod;
    for (long long i = 0; i < b; i++) r = r * a % mod;
    return r;
}

int main() {
    int fail = 0;

    // ① 定点
    struct { long long a, b, m, e; const char* note; } cs[] = {
        {3, 13, 1000, 323, "手算那道：13=8+4+1"},
        {2, 10, 1000, 24,  ""},
        {5, 0,  7,    1,   "b=0 -> 1"},
        {0, 5,  7,    0,   "a=0"},
        {7, 100, 1,   0,   "mod=1，必须 1%mod"},
        {2, 63, 1000000007LL, 9223372036854775807LL % 1000000007LL, "占位，下面重算"},
    };
    // 最后一组用暴力算准
    cs[5].e = brutePow(2, 63, 1000000007LL);

    for (auto &c : cs) {
        long long got = qpow(c.a, c.b, c.m);
        if (got != c.e) { fail++; printf("qpow(%lld,%lld,%lld) = %lld (expected %lld)  !!FAIL  %s\n", c.a, c.b, c.m, got, c.e, c.note); }
        else printf("qpow(%lld,%lld,%lld) = %lld  OK  %s\n", c.a, c.b, c.m, got, c.note);
    }

    // ② 暴力对拍
    srand(20261123);
    int bad = 0;
    for (int t = 0; t < 5000; t++) {
        long long a = rand() % 1000;
        long long b = rand() % 500;
        long long m = rand() % 1000 + 1;      // 1..1000，含 m=1
        long long g = qpow(a, b, m), e = brutePow(a, b, m);
        if (g != e) { if (++bad <= 5) printf("MISMATCH qpow(%lld,%lld,%lld) got=%lld brute=%lld\n", a, b, m, g, e); }
    }
    printf("\n对拍 5000 组（a<1000, b<500, m<=1000），不一致 = %d\n", bad);
    fail += bad;

    // ③ 大指数：Python pow() 算出的参考值
    struct { long long a, b, m, e; } big[] = {
        {2,         1000000000000000000LL, 1000000007LL, 719476260LL},
        {123456789, 987654321LL,           1000000007LL, 652541198LL},
    };
    for (auto &c : big) {
        long long got = qpow(c.a, c.b, c.m);
        if (got != c.e) { fail++; printf("BIG qpow(%lld,%lld,%lld) = %lld (expected %lld)  !!FAIL\n", c.a, c.b, c.m, got, c.e); }
        else printf("BIG qpow(%lld,%lld,%lld) = %lld  OK\n", c.a, c.b, c.m, got);
    }

    // ④ 费马小定理：p 为质数，gcd(a,p)=1 -> a^(p-1) ≡ 1
    long long p = 1000000007LL;
    long long f = qpow(2, p - 1, p);
    if (f != 1) { fail++; printf("FERMAT 2^(p-1) mod p = %lld  !!FAIL\n", f); }
    else printf("FERMAT 2^(p-1) mod p = 1  OK\n");

    printf("\n%s\n", fail == 0 ? "ALL PASSED" : "SOME FAILED");
    return fail ? 1 : 0;
}
