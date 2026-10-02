#pragma once

#include<vector>
#include<cmath>
using namespace std;

// ============================================================
// 并查集（负数约定：p[i] < 0 表示 i 是根，且 -p[i] = 这一组的人数）
// ------------------------------------------------------------
// 用法：
//     UnionFind uf(n);          // 节点编号 0..n-1
//     uf.unoin(a, b);           // 合并
//     uf.issame(a, b);          // 是否同组
//     uf.countSets();           // 一共有几组
//
// ⚠️ 两处易错（都是实测踩过的）：
//   ① 不要和「根自指（p[i] == i 判根）」那套混用 ——
//      初始化 / 判根 / find 的循环条件必须来自同一套。
//      混用会走到 p[-1]，越界【写】→ 堆损坏 0xC0000374（LC 547 实测）。
//   ② 节点编号若是 1..n（如 LC 684），构造时要传 n+1，
//      否则访问 p[n] 越界（LC 684 实测：答案"恰好"对，但探针显示越界读 8 次）。
// ============================================================

//struct UF {
//    vector<int> p;
//    UF(int n)
//    {
//        p.resize(n);
//        for (int i = 0; i < n; i++) {
//            p[i] = i;
//        }
//    }
//    int find(int x)
//    {
//        while (p[x] != x) x = p[x];
//        return x;
//    }
//
//    void unite(int a, int b)
//    {
//        int r1 = find(a);
//        int r2 = find(b);
//        p[r1] = r2;
//    }
//    bool same(int a, int b)
//    {
//        return find(a) == find(b);
//    }
//};


class UnionFind
{
public:
	UnionFind(int size)
	{
		p.resize(size, -1);
	}

	int find(int x)
	{
		if (p[x] < 0) return x;
		return p[x] = find(p[x]);
	}

	void unoin(int x, int y)
	{
		int f1 = find(x);
		int f2 = find(y);
		if (f1 == f2) return;
		if (p[f1]>p[f2])
		{
			swap(f1, f2);
		}
		p[f1] += p[f2];
		p[f2] = f1;
	}

	bool issame(int x, int y)
	{
		return find(x) == find(y);
	}

	// 一共有几组 = 数 p[i] < 0 的个数（547 那种"数省份"的题要用）
	int countSets()
	{
		int c = 0;
		for (int i = 0; i < (int)p.size(); i++)
			if (p[i] < 0) c++;
		return c;
	}
private:
	vector<int> p;
};
