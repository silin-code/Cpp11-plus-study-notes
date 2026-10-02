#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

#include <vector>

// ============================================================
// 并查集（Union-Find / Disjoint Set Union）
// ------------------------------------------------------------
// 用途：维护「一堆元素被分成哪些组」，支持两种操作
//         unite(a, b)   把 a、b 所在的组合并成一个
//         same(a, b)    问 a、b 是否在同一组
//         countSets()   问一共有几组
// 复杂度：时间 ≈ O(1)（路径压缩后均摊很低，理论上 O(log n)、接近 O(α(n))）
//         空间 O(n)
// 日期：2026-10-02
// ------------------------------------------------------------
// 【约定】本项目统一用下面这一套：
//        初始化    p[i] = i         每个人自己就是根
//        判根      p[i] == i        「自己是自己的上级」
//        find      while (p[x] != x) x = p[x];
//
//   ※ 另一套常见约定（中文教材 / 408 常用）：
//        初始化    p[i] = -1
//        判根      p[i] < 0         负数同时表示「我是根」和「集合大小 = -p[i]」
//        合并      p[ra] += p[rb]; p[rb] = ra;    ← 顺手完成「按大小合并」
//     两套【都正确】，但绝不能混用：
//        用 -1 初始化 + 用 p[x] == x 判根  → 会走到 p[-1]，越界【写】→ 堆损坏
//     （实测退出码 0xC0000374 = HEAP_CORRUPTION）
//
//   ※ 还有「按秩合并」（额外开一个 rank 数组，把小树挂到大树下），
//     与路径压缩可以叠加。408 会考这两种优化对树高的影响。
// ------------------------------------------------------------
// 【多组数据的复位】本类每次 build(n) 都会重新填 p，可以复用同一个对象。
// ============================================================

class UnionFind {
public:
    UnionFind() {}
    explicit UnionFind(int n) { build(n); }

    // 建一个 n 个元素的并查集：每个元素各自成组
    void build(int n) {
        p.resize(n);
        for (int i = 0; i < n; i++) p[i] = i;
    }

    // 找 x 所在的根（带路径压缩：把路上经过的每个点都直接挂到根上）
    //
    // 这里用【循环版】而不是递归版 —— 原因实测：
    //   不带「按秩合并」时，树可能退化成一条链（如一直 unite(i, i+1)）；
    //   递归版 find 的递归深度 = 链长，n = 100000 时实测栈溢出
    //   （退出码 0xC0000374 / 0xC00000FD 一类的崩溃）。
    //   循环版没有这个限制。
    //
    // 两版等价，递归版更短（理解路径压缩时看它更直观）：
    //     int find(int x) {
    //         if (p[x] == x) return x;
    //         return p[x] = find(p[x]);      // 返回根的同时把 x 直接挂到根上
    //     }
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

    // 合并 a、b 所在的两个组
    void unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return;
        p[ra] = rb;                     // 把 a 的根挂到 b 的根下面
    }

    bool same(int a, int b) { return find(a) == find(b); }

    // 一共有几组 = 有几个「自己是自己的上级」的点
    int countSets() {
        int c = 0;
        for (int i = 0; i < (int)p.size(); i++)
            if (p[i] == i) c++;
        return c;
    }

    int size() const { return (int)p.size(); }

    std::vector<int> p;
};

#endif
