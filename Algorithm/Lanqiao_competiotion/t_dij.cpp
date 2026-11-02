#include "Dijkstra.hpp"
#include <iostream>
int main() {
    setbuf(stdout, NULL);
    // 用例1：4 点图，从 1 出发
    {
        int n = 5;
        vector<vector<pair<int,int>>> g(n);
        addEdge(g, 1, 2, 1); addEdge(g, 1, 3, 4);
        addEdge(g, 2, 3, 2); addEdge(g, 2, 4, 5);
        addEdge(g, 3, 4, 1);
        vector<long long> d = dijkstra(n, g, 1);
        printf("用例1: ");
        for (int i = 1; i < n; i++) printf("%lld ", d[i]);
        printf("  (期望 1 3 4)\n");
    }
    // 用例2：3 点，2 不可达
    {
        int n = 3;
        vector<vector<pair<int,int>>> g(n);
        addEdge(g, 0, 1, 7);
        vector<long long> d = dijkstra(n, g, 0);
        printf("用例2: d[0]=%lld d[1]=%lld d[2]=%lld  (期望 0 7 INF)\n", d[0], d[1], d[2]);
    }
    // 用例3：无向边
    {
        int n = 3;
        vector<vector<pair<int,int>>> g(n);
        addEdge(g, 0, 1, 2, true);
        addEdge(g, 1, 2, 3, true);
        vector<long long> d = dijkstra(n, g, 0);
        printf("用例3: d[0]=%lld d[1]=%lld d[2]=%lld  (期望 0 2 5)\n", d[0], d[1], d[2]);
    }
    return 0;
}
