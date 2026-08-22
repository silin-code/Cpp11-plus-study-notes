#include <iostream>
#include <cassert>
#include "Graph.hpp"
using namespace std;
using namespace matrix;

// Test1: directed graph, verify all-pairs distances
void TestFloyd_Directed()
{
    cout << "===== Test1: Floyd-Warshall - directed =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    vector<vector<int>> dist;
    vector<vector<int>> parentPath;
    g.FloydWarshall(dist, parentPath);

    cout << "Distance matrix:" << endl;
    cout << "    0  1  2  3" << endl;
    for (size_t i = 0; i < 4; i++)
    {
        cout << i << ": ";
        for (size_t j = 0; j < 4; j++)
        {
            if (dist[i][j] == INT_MAX) cout << "INF ";
            else printf("%3d ", dist[i][j]);
        }
        cout << endl;
    }
    cout << endl;

    g.PrintFloydPaths(dist, parentPath);

    assert(dist[0][0] == 0);
    assert(dist[0][1] == 1);
    assert(dist[0][2] == 9);   // 0->1->3->2
    assert(dist[0][3] == 3);   // 0->1->3
    assert(dist[2][0] == 3);
    assert(dist[2][1] == 4);   // 2->0->1
    assert(dist[2][3] == 6);   // 2->0->1->3
    assert(dist[3][0] == 9);   // 3->2->0
    assert(dist[3][1] == 10);  // 3->2->0->1
    assert(dist[3][2] == 6);

    cout << "Test1 PASSED!" << endl << endl;
}

// Test2: undirected graph
void TestFloyd_Undirected()
{
    cout << "===== Test2: Floyd-Warshall - undirected =====" << endl;
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

    vector<vector<int>> dist;
    vector<vector<int>> parentPath;
    g.FloydWarshall(dist, parentPath);

    g.PrintFloydPaths(dist, parentPath);

    assert(dist[0][2] == 7);    // A->E->C
    assert(dist[0][3] == 8);    // A->E->D
    assert(dist[1][4] == 10);   // B->A->E
    assert(dist[0][2] == dist[2][0]);  // symmetric
    assert(dist[1][4] == dist[4][1]);

    cout << "Test2 PASSED!" << endl << endl;
}

// Test3: unreachable vertices
void TestFloyd_Unreachable()
{
    cout << "===== Test3: Floyd-Warshall - unreachable =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, true> g(a, 4);
    g.AddEdge('0', '1', 5);
    g.AddEdge('1', '2', 3);

    vector<vector<int>> dist;
    vector<vector<int>> parentPath;
    g.FloydWarshall(dist, parentPath);

    g.PrintFloydPaths(dist, parentPath);

    assert(dist[0][1] == 5);
    assert(dist[0][2] == 8);
    assert(dist[0][3] == INT_MAX);
    assert(dist[3][0] == INT_MAX);
    assert(dist[2][0] == INT_MAX);

    cout << "Test3 PASSED!" << endl << endl;
}

// Test4: negative weights (no negative cycle)
void TestFloyd_NegativeWeight()
{
    cout << "===== Test4: Floyd-Warshall - negative weights =====" << endl;
    char a[] = { 'A', 'B', 'C', 'D' };
    Graph<char, int, INT_MAX, true> g(a, 4);

    g.AddEdge('A', 'B', 4);
    g.AddEdge('A', 'C', 5);
    g.AddEdge('B', 'C', -3);
    g.AddEdge('C', 'D', 2);
    g.AddEdge('B', 'D', 10);

    vector<vector<int>> dist;
    vector<vector<int>> parentPath;
    g.FloydWarshall(dist, parentPath);

    g.PrintFloydPaths(dist, parentPath);

    assert(dist[0][1] == 4);
    assert(dist[0][2] == 1);   // A->B->C: 4+(-3)
    assert(dist[0][3] == 3);   // A->B->C->D: 4-3+2

    cout << "Test4 PASSED!" << endl << endl;
}

// Test5: single vertex
void TestFloyd_SingleVertex()
{
    cout << "===== Test5: Floyd-Warshall - single vertex =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, true> g(a, 1);

    vector<vector<int>> dist;
    vector<vector<int>> parentPath;
    g.FloydWarshall(dist, parentPath);

    assert(dist.size() == 1);
    assert(dist[0][0] == 0);
    assert(parentPath[0][0] == -1);
    cout << "dist[0][0] = " << dist[0][0] << endl;
    cout << "Test5 PASSED!" << endl << endl;
}

// Test6: compare with Dijkstra on all 16 pairs
void TestFloyd_CompareDijkstra()
{
    cout << "===== Test6: Floyd vs Dijkstra =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    vector<vector<int>> fDist;
    vector<vector<int>> fParent;
    g.FloydWarshall(fDist, fParent);

    for (size_t src = 0; src < 4; src++)
    {
        vector<int> dDist;
        vector<int> dParent;
        g.Dijkstra((char)('0' + src), dDist, dParent);
        for (size_t dst = 0; dst < 4; dst++)
        {
            assert(fDist[src][dst] == dDist[dst]);
        }
    }
    cout << "All 16 pairs match between Floyd and Dijkstra" << endl;
    cout << "Test6 PASSED!" << endl << endl;
}

int main()
{
    TestFloyd_Directed();
    TestFloyd_Undirected();
    TestFloyd_Unreachable();
    TestFloyd_NegativeWeight();
    TestFloyd_SingleVertex();
    TestFloyd_CompareDijkstra();

    cout << "==============================" << endl;
    cout << "  ALL 6 TESTS PASSED!" << endl;
    cout << "==============================" << endl;
    return 0;
}
