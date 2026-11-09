#include "Kruskal.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

// LC 1584 的样例：给坐标造完全图的边
long long solve1584(vector<vector<int>> points) {
    int n = points.size();
    vector<Edge> es;
    es.reserve(n * (n - 1) / 2);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) {
            int w = abs(points[i][0] - points[j][0])
                  + abs(points[i][1] - points[j][1]);
            es.push_back({i, j, w});
        }
    return kruskal(n, es);
}

int main() {
    setbuf(stdout, NULL);

    // 用例 1：4 点图（手算过，答案 7）
    {
        int n = 4;
        vector<Edge> es = {
            {0,1,1}, {1,2,2}, {0,2,3}, {2,3,4}, {1,3,5}
        };
        printf("用例1 (4点图)        = %lld   期望 7\n", kruskal(n, es));
    }

    // 用例 2：3 点，只有 0-1 一条边（不连通）
    {
        int n = 3;
        vector<Edge> es = { {0,1,5} };
        printf("用例2 (不连通)       = %lld   期望 -1\n", kruskal(n, es));
    }

    // 用例 3：单点
    {
        int n = 1;
        vector<Edge> es;
        printf("用例3 (单点)         = %lld   期望 0\n", kruskal(n, es));
    }

    // 用例 4：LC 1584 官方样例 1 -> 20
    {
        vector<vector<int>> p = {{0,0},{2,2},{3,10},{5,2},{7,0}};
        printf("用例4 (LC1584样例)   = %lld   期望 20\n", solve1584(p));
    }

    // 用例 5：LC 1584 官方样例 2 -> 10
    {
        vector<vector<int>> p = {{3,12},{-2,5},{-4,1}};
        printf("用例5 (LC1584样例2)  = %lld   期望 18\n", solve1584(p));
    }

    // 用例 6：所有点重合 -> 0
    {
        vector<vector<int>> p = {{0,0},{0,0},{0,0}};
        printf("用例6 (全重合)       = %lld   期望 0\n", solve1584(p));
    }

    return 0;
}
