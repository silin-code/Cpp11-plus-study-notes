#include <iostream>
#include <cassert>
#include "Graph.hpp"
using namespace std;
using namespace matrix;

// Test1: normal directed graph, compare with Dijkstra
void TestBellmanFord_Normal()
{
    cout << "===== Test1: BellmanFord - normal directed =====" << endl;
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
    bool ok = g.BellmanFord('0', dist, parentPath);

    cout << "ok = " << (ok ? "true" : "false") << endl;
    cout << "dist from '0': ";
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX) cout << "INF ";
        else cout << dist[i] << " ";
    }
    cout << endl;

    assert(ok == true);
    assert(dist[0] == 0);
    assert(dist[1] == 1);
    assert(dist[2] == 9);
    assert(dist[3] == 3);

    g.PrintShortPath('0', dist, parentPath);
    cout << "Test1 PASSED!" << endl << endl;
}

// Test2: graph with negative weights (Dijkstra would fail here)
void TestBellmanFord_NegativeWeight()
{
    cout << "===== Test2: BellmanFord - negative weights =====" << endl;
    char a[] = { 'A', 'B', 'C', 'D' };
    Graph<char, int, INT_MAX, true> g(a, 4);

    g.AddEdge('A', 'B', 4);
    g.AddEdge('A', 'C', 5);
    g.AddEdge('B', 'C', -3);   // negative edge
    g.AddEdge('C', 'D', 2);
    g.AddEdge('B', 'D', 10);

    vector<int> dist;
    vector<int> parentPath;
    bool ok = g.BellmanFord('A', dist, parentPath);

    cout << "ok = " << (ok ? "true" : "false") << endl;
    cout << "dist from 'A': ";
    for (size_t i = 0; i < dist.size(); i++)
        cout << a[i] << "=" << dist[i] << " ";
    cout << endl;

    // A->A=0, A->B=4, A->C=1(A->B->C: 4+(-3)), A->D=3(A->B->C->D: 4-3+2)
    assert(ok == true);
    assert(dist[0] == 0);
    assert(dist[1] == 4);
    assert(dist[2] == 1);
    assert(dist[3] == 3);

    g.PrintShortPath('A', dist, parentPath);
    cout << "Test2 PASSED!" << endl << endl;
}

// Test3: negative cycle - should return false
void TestBellmanFord_NegativeCycle()
{
    cout << "===== Test3: BellmanFord - negative cycle =====" << endl;
    char a[] = { 'A', 'B', 'C' };
    Graph<char, int, INT_MAX, true> g(a, 3);

    g.AddEdge('A', 'B', 1);
    g.AddEdge('B', 'C', -2);
    g.AddEdge('C', 'A', -3);  // A->B->C->A = 1-2-3 = -4, negative cycle

    vector<int> dist;
    vector<int> parentPath;
    bool ok = g.BellmanFord('A', dist, parentPath);

    cout << "ok = " << (ok ? "true" : "false") << endl;
    assert(ok == false);
    cout << "Test3 PASSED!" << endl << endl;
}

// Test4: unreachable vertex
void TestBellmanFord_Unreachable()
{
    cout << "===== Test4: BellmanFord - unreachable =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, true> g(a, 4);
    g.AddEdge('0', '1', 5);
    g.AddEdge('1', '2', 3);
    // vertex 3 isolated

    vector<int> dist;
    vector<int> parentPath;
    bool ok = g.BellmanFord('0', dist, parentPath);

    cout << "ok = " << (ok ? "true" : "false") << endl;
    cout << "dist from '0': ";
    for (size_t i = 0; i < dist.size(); i++)
    {
        if (dist[i] == INT_MAX) cout << a[i] << "=INF ";
        else cout << a[i] << "=" << dist[i] << " ";
    }
    cout << endl;

    assert(ok == true);
    assert(dist[0] == 0);
    assert(dist[1] == 5);
    assert(dist[2] == 8);
    assert(dist[3] == INT_MAX);
    assert(parentPath[3] == -1);

    g.PrintShortPath('0', dist, parentPath);
    cout << "Test4 PASSED!" << endl << endl;
}

// Test5: source is not first vertex
void TestBellmanFord_DifferentSource()
{
    cout << "===== Test5: BellmanFord - source not first =====" << endl;
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
    bool ok = g.BellmanFord('2', dist, parentPath);

    cout << "ok = " << (ok ? "true" : "false") << endl;
    cout << "dist from '2': ";
    for (size_t i = 0; i < dist.size(); i++)
        cout << i << "=" << dist[i] << " ";
    cout << endl;

    assert(ok == true);
    assert(dist[0] == 3);
    assert(dist[1] == 4);
    assert(dist[2] == 0);
    assert(dist[3] == 6);

    g.PrintShortPath('2', dist, parentPath);
    cout << "Test5 PASSED!" << endl << endl;
}

// Test6: single vertex
void TestBellmanFord_SingleVertex()
{
    cout << "===== Test6: BellmanFord - single vertex =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, true> g(a, 1);

    vector<int> dist;
    vector<int> parentPath;
    bool ok = g.BellmanFord('0', dist, parentPath);

    assert(ok == true);
    assert(dist.size() == 1);
    assert(dist[0] == 0);
    assert(parentPath[0] == -1);
    cout << "dist[0] = " << dist[0] << endl;
    cout << "Test6 PASSED!" << endl << endl;
}

int main()
{
    TestBellmanFord_Normal();
    TestBellmanFord_NegativeWeight();
    TestBellmanFord_NegativeCycle();
    TestBellmanFord_Unreachable();
    TestBellmanFord_DifferentSource();
    TestBellmanFord_SingleVertex();

    cout << "==============================" << endl;
    cout << "  ALL 6 TESTS PASSED!" << endl;
    cout << "==============================" << endl;
    return 0;
}
