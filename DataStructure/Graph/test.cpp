#include <iostream>
#include <cassert>
#include "Graph.hpp"
using namespace std;
using namespace matrix;

// Test1: 有向图，验证 dist 数组
void TestDijkstra_Directed()
{
    cout << "===== Test1: Dijkstra - directed =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('0', dist, parentPath);

    cout << "dist from '0': ";
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << endl;

    cout << "parentPath: ";
    for (int p : parentPath) cout << p << " ";
    cout << endl;

    // 0->0=0, 0->1=1, 0->2=9(0->1->3->2), 0->3=3(0->1->3)
    assert(dist[0] == 0);
    assert(dist[1] == 1);
    assert(dist[2] == 9);
    assert(dist[3] == 3);
    cout << "Test1 PASSED!" << endl << endl;
}

// Test2: PrintShortPath 输出验证
void TestDijkstra_PrintPath()
{
    cout << "===== Test2: PrintShortPath =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('0', dist, parentPath);

    cout << "Shortest paths from '0':" << endl;
    g.PrintShortPath('0', dist, parentPath);
    cout << "Test2 PASSED!" << endl << endl;
}

// Test3: 无向图
void TestDijkstra_Undirected()
{
    cout << "===== Test3: Dijkstra - undirected =====" << endl;
    char a[] = { 'A', 'B', 'C', 'D', 'E' };
    Graph<char, int, INT_MAX, false> g(a, 5);

    g.AddEdge('A', 'B', 4);
    g.AddEdge('A', 'C', 8);
    g.AddEdge('B', 'C', 11);
    g.AddEdge('B', 'D', 8);
    g.AddEdge('C', 'D', 7);
    g.AddEdge('C', 'E', 1);
    g.AddEdge('D', 'E', 2);
    g.AddEdge('A', 'E', 6);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('A', dist, parentPath);

    cout << "dist from 'A': ";
    for (size_t i = 0; i < dist.size(); i++)
        cout << a[i] << "=" << dist[i] << " ";
    cout << endl;

    // A=0, B=4, C=7(A->E->C), D=8(A->E->D), E=6
    assert(dist[0] == 0);
    assert(dist[1] == 4);
    assert(dist[2] == 7);
    assert(dist[3] == 8);
    assert(dist[4] == 6);

    g.PrintShortPath('A', dist, parentPath);
    cout << "Test3 PASSED!" << endl << endl;
}

// Test4: 不可达顶点
void TestDijkstra_Unreachable()
{
    cout << "===== Test4: Dijkstra - unreachable =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, true> g(a, 4);
    g.AddEdge('0', '1', 5);
    g.AddEdge('1', '2', 3);
    // vertex 3 isolated

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('0', dist, parentPath);

    cout << "dist from '0': ";
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX) cout << a[i] << "=INF ";
        else cout << a[i] << "=" << dist[i] << " ";
    }
    cout << endl;

    assert(dist[0] == 0);
    assert(dist[1] == 5);
    assert(dist[2] == 8);
    assert(dist[3] == INT_MAX);
    assert(parentPath[3] == -1);

    g.PrintShortPath('0', dist, parentPath);
    cout << "Test4 PASSED!" << endl << endl;
}

// Test5: 源点不是第一个顶点
void TestDijkstra_DifferentSource()
{
    cout << "===== Test5: Dijkstra - source not first =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('2', dist, parentPath);

    cout << "dist from '2': ";
    for (size_t i = 0; i < dist.size(); i++)
        cout << i << "=" << dist[i] << " ";
    cout << endl;

    // 2->0=3, 2->1=4(2->0->1), 2->2=0, 2->3=6(2->0->1->3)
    assert(dist[0] == 3);
    assert(dist[1] == 4);
    assert(dist[2] == 0);
    assert(dist[3] == 6);

    g.PrintShortPath('2', dist, parentPath);
    cout << "Test5 PASSED!" << endl << endl;
}

// Test6: 单顶点
void TestDijkstra_SingleVertex()
{
    cout << "===== Test6: Dijkstra - single vertex =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, true> g(a, 1);

    vector<int> dist;
    vector<int> parentPath;
    g.Dijkstra('0', dist, parentPath);

    assert(dist.size() == 1);
    assert(dist[0] == 0);
    assert(parentPath[0] == -1);
    cout << "dist[0] = " << dist[0] << endl;
    cout << "Test6 PASSED!" << endl << endl;
}

int main()
{
    TestDijkstra_Directed();
    TestDijkstra_PrintPath();
    TestDijkstra_Undirected();
    TestDijkstra_Unreachable();
    TestDijkstra_DifferentSource();
    TestDijkstra_SingleVertex();

    cout << "==============================" << endl;
    cout << "  ALL 6 TESTS PASSED!" << endl;
    cout << "==============================" << endl;
    return 0;
}