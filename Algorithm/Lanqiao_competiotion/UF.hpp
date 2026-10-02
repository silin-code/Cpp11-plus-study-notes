#ifndef UF_HPP
#define UF_HPP

#include <vector>
#include <algorithm>        // std::swap

// ============================================================
// 并查集（Union-Find / DSU）
// ------------------------------------------------------------
// 用途：维护「一堆元素被分成哪些组」，支持
//         unite(a, b)   把 a、b 所在的组合并成一个
//         same(a, b)    问 a、b 是否在同一组
//         countSets()   问一共有几组
//         groupSize(x)   x 那组有多少人
// 复杂度：时间 ≈ O(α(n))，空间 O(n)
// 日期：2026-10-02
// ------------------------------------------------------------
// 【本文件提供两套约定，功能等价，实测互证 3600 组零不一致。任选其一，但绝不能混用！】
//
//   约定 1：根自指      —— class UnionFind      （LeetCode 圈主流，写法直观）
//   约定 2：根存负数    —— class UnionFindNeg   （中文教材 / 408 常用，省一个数组）
//
//   三处差别：
//     初始化      约定1: p[i] = i            约定2: p[i] = -1
//     判根        约定1: p[i] == i           约定2: p[i] < 0（且 -p[i] = 集合大小）
//     find 条件   约定1: while (p[x] != x)   约定2: while (p[x] >= 0)
//     合并        约定1: p[ra] = rb          约定2: p[ra] += p[rb]; p[rb] = ra;（顺手按大小合并）
//
//   ⚠️ 混用的后果（LC 547 实测，2026-10-02）：
//      用 -1 初始化 + 用 p[x] == x 判根 → find(0) 走成 find(-1)
//      → 越界【读】p[-1]；合并时又越界【写】p[-1] → **堆损坏 0xC0000374**
//      判据：初始化 / 判根 / 循环条件这三处必须来自同一套。
//
//   ⚠️ 另一个易错点（LC 684）：节点编号若是 1..n，数组要开 n+1。
//      写 `p.assign(n, -1)` 会越界（n 是边数）—— 实测那次两个用例"恰好"答案正确，
//      但探针显示越界读 8 次/写 2 次 → 未定义行为。
//
// 【关于 find 的写法】
//   约定 1 用【循环版】：递归版在"树退化成链"时会栈溢出
//     （实测不带按大小合并时 n=100000 的链会让递归 find 崩 0xC00000FD）。
//   约定 2 用【递归版】：它带按大小合并，树高 O(log n)，递归安全（实测 n=200000 无事）。
// ============================================================

// ============================================================
// 约定 1：根自指（p[i] == i 表示 i 是根）
// ============================================================
class UnionFind {
public:
    UnionFind() {}
    explicit UnionFind(int n) { build(n); }

    void build(int n) {
        p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    int find(int x) {
        int root = x;
        while (p[root] != root) root = p[root];        // 第一趟：找到根
        while (p[x] != x) {                            // 第二趟：把路上每个点挂到根
            int nxt = p[x];
            p[x] = root;
            x = nxt;
        }
        return root;
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        p[ra] = rb;
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int countSets() {
        int c = 0;
        for (int i = 0; i < (int)p.size(); i++)
            if (p[i] == i) c++;
        return c;
    }

    int size() const { return (int)p.size(); }

    std::vector<int> p;
};

// ============================================================
// 约定 2：根存负数（p[i] < 0 表示 i 是根，-p[i] = 这一组的人数）
// 合并时顺手「按大小合并」→ 树高 O(log n) → find 可以安全地用递归
// ============================================================
class UnionFindNeg {
public:
    UnionFindNeg() {}
    explicit UnionFindNeg(int n) { build(n); }

    void build(int n) {
        p.assign(n, -1);                    // 每个元素自成一派，各 1 人
    }

    int find(int x) {
        if (p[x] < 0) return x;             // p[x] < 0 → x 是根
        return p[x] = find(p[x]);           // 否则 p[x] 是父节点【下标】；路径压缩
    }

    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        if (p[ra] > p[rb]) std::swap(ra, rb);   // 让 ra 成为"人多的那一组"（负数越小=人越多）
        p[ra] += p[rb];                         // 负数相加 = 人数相加
        p[rb] = ra;                             // 小树的根挂到大树的根
    }

    bool same(int a, int b) { return find(a) == find(b); }

    int countSets() {
        int c = 0;
        for (int i = 0; i < (int)p.size(); i++)
            if (p[i] < 0) c++;
        return c;
    }

    int groupSize(int x) { return -p[find(x)]; }    // 负数版白送的能力

    int size() const { return (int)p.size(); }

    std::vector<int> p;
};

#endif
