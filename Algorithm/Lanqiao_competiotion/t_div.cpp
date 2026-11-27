#include "number_theory.hpp"
#include <cstdio>

// ============================================================
// divisorCount 自测台
//   ① 定点：12/16/36/360/97/1
//   ② 全量对拍 x = 1..100000：与暴力枚举约数逐个比
// 编译：g++ -std=c++11 -Wall -Wextra -o t_div.exe t_div.cpp
// ============================================================

// 暴力：枚举约数对（i 和 x/i），与公式法路径不同
static int brute(int x) {
    int c = 0;
    for (int d = 1; d * d <= x; d++)
        if (x % d == 0) { c++; if (d != x / d) c++; }
    return c;
}

// 真·独立暴力：1..x 全枚举（只用于小范围交叉验证）
static int bruteSlow(int x) {
    int c = 0;
    for (int d = 1; d <= x; d++) if (x % d == 0) c++;
    return c;
}

int main() {
    int fail = 0;

    // ---------- ① 定点 ----------
    int xs[] = {12, 16, 36, 360, 97, 1, 1024, 100000};
    int es[] = {6,  5,  9,  24,  2,  1, 11,  36};
    for (int k = 0; k < 8; k++) {
        int got = divisorCount(xs[k]);
        if (got != es[k]) { fail++; printf("divisorCount(%6d) = %3d  expected %3d  !!FAIL\n", xs[k], got, es[k]); }
        else printf("divisorCount(%6d) = %3d  OK\n", xs[k], got);
    }

    // ---------- ② 全量对拍 ----------
    int bad = 0;
    for (int x = 1; x <= 100000; x++) {
        int g = divisorCount(x), e = brute(x);
        if (g != e) {
            if (++bad <= 5) printf("MISMATCH x=%d got=%d brute=%d  !!FAIL\n", x, g, e);
        }
    }
    printf("\n对拍 x=1..100000（枚举约数对）：%s\n", bad ? "有不一致" : "完全一致");
    fail += bad;

    // ---------- ③ 小范围真·独立交叉验证 ----------
    int bad2 = 0;
    for (int x = 1; x <= 5000; x++) {
        if (divisorCount(x) != bruteSlow(x)) {
            if (++bad2 <= 5) printf("MISMATCH x=%d (slow)  !!FAIL\n", x);
        }
    }
    printf("对拍 x=1..5000（1..x 全枚举）：%s\n", bad2 ? "有不一致" : "完全一致");
    fail += bad2;

    printf("\n%s\n", fail == 0 ? "ALL PASSED" : "SOME FAILED");
    return fail ? 1 : 0;
}
