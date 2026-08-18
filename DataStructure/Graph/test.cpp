#include <iostream>
#include <cassert>
#include "Graph.hpp"
using namespace std;
using namespace matrix;

// ========== Kruskal Tests ==========

void TestKruskal_Known()
{
    cout << "===== Test1: Kruskal - 4-vertex undirected =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);

    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '2', 3);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '2', 2);
    g.AddEdge('1', '3', 5);
    g.AddEdge('2', '3', 1);

    Graph<char, int, INT_MAX, false> minTree(a, 4);
    int total = g.Kruskal(minTree);

    cout << "MST total = " << total << " (expected 4)" << endl;
    minTree.Print();
    assert(total == 4 && "Test1 failed");
    cout << "Test1 PASSED!" << endl << endl;
}

void TestKruskal_Disconnected()
{
    cout << "===== Test2: Kruskal - disconnected =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);
    g.AddEdge('0', '1', 2);

    Graph<char, int, INT_MAX, false> minTree(a, 4);
    int total = g.Kruskal(minTree);

    cout << "MST total = " << total << " (expected 0)" << endl;
    assert(total == 0 && "Test2 failed");
    cout << "Test2 PASSED!" << endl << endl;
}

void TestKruskal_SingleVertex()
{
    cout << "===== Test3: Kruskal - single vertex =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, false> g(a, 1);

    Graph<char, int, INT_MAX, false> minTree(a, 1);
    int total = g.Kruskal(minTree);

    cout << "MST total = " << total << " (expected 0)" << endl;
    assert(total == 0 && "Test3 failed");
    cout << "Test3 PASSED!" << endl << endl;
}

void TestKruskal_Complex()
{
    cout << "===== Test4: Kruskal - 5-vertex complex =====" << endl;
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

    Graph<char, int, INT_MAX, false> minTree(a, 5);
    int total = g.Kruskal(minTree);

    cout << "MST total = " << total << " (expected 13)" << endl;
    minTree.Print();
    assert(total == 13 && "Test4 failed");
    cout << "Test4 PASSED!" << endl << endl;
}

// ========== Prim Tests ==========

void TestPrim_Known()
{
    cout << "===== Test5: Prim - 4-vertex undirected =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);

    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '2', 3);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '2', 2);
    g.AddEdge('1', '3', 5);
    g.AddEdge('2', '3', 1);

    char starts[] = { '0', '1', '2', '3' };
    for (char s : starts)
    {
        Graph<char, int, INT_MAX, false> minTree(a, 4);
        int total = g.Prim(minTree, s);
        cout << "  start=" << s << ", MST total = " << total << " (expected 4)" << endl;
        assert(total == 4 && "Test5 failed");
    }
    cout << "Test5 PASSED!" << endl << endl;
}

void TestPrim_Disconnected()
{
    cout << "===== Test6: Prim - disconnected =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);
    g.AddEdge('0', '1', 2);

    Graph<char, int, INT_MAX, false> minTree(a, 4);
    int total = g.Prim(minTree, '0');

    cout << "MST total = " << total << " (expected 0)" << endl;
    assert(total == 0 && "Test6 failed");
    cout << "Test6 PASSED!" << endl << endl;
}

void TestPrim_SingleVertex()
{
    cout << "===== Test7: Prim - single vertex =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, false> g(a, 1);

    Graph<char, int, INT_MAX, false> minTree(a, 1);
    int total = g.Prim(minTree, '0');

    cout << "MST total = " << total << " (expected 0)" << endl;
    assert(total == 0 && "Test7 failed");
    cout << "Test7 PASSED!" << endl << endl;
}

void TestPrim_Complex()
{
    cout << "===== Test8: Prim - 5-vertex complex =====" << endl;
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

    char starts[] = { 'A', 'B', 'C', 'D', 'E' };
    for (char s : starts)
    {
        Graph<char, int, INT_MAX, false> minTree(a, 5);
        int total = g.Prim(minTree, s);
        cout << "  start=" << s << ", MST total = " << total << " (expected 13)" << endl;
        assert(total == 13 && "Test8 failed");
    }

    Graph<char, int, INT_MAX, false> refTree(a, 5);
    g.Prim(refTree, 'A');
    cout << "  MST (start=A):" << endl;
    refTree.Print();
    cout << "Test8 PASSED!" << endl << endl;
}

// ========== Cross-validation ==========

void Test_Kruskal_vs_Prim()
{
    cout << "===== Test9: Kruskal vs Prim cross-validation =====" << endl;
    char a[] = { 'A', 'B', 'C', 'D', 'E', 'F' };
    Graph<char, int, INT_MAX, false> g(a, 6);

    g.AddEdge('A', 'B', 2);
    g.AddEdge('A', 'C', 5);
    g.AddEdge('B', 'C', 4);
    g.AddEdge('B', 'D', 7);
    g.AddEdge('C', 'D', 9);
    g.AddEdge('C', 'E', 1);
    g.AddEdge('D', 'E', 3);
    g.AddEdge('D', 'F', 6);
    g.AddEdge('E', 'F', 8);
    g.AddEdge('A', 'F', 10);

    Graph<char, int, INT_MAX, false> kTree(a, 6);
    int kTotal = g.Kruskal(kTree);

    Graph<char, int, INT_MAX, false> pTree(a, 6);
    int pTotal = g.Prim(pTree, 'A');

    cout << "Kruskal total = " << kTotal << endl;
    cout << "Prim total    = " << pTotal << endl;
    assert(kTotal == pTotal && "Test9 failed: Kruskal != Prim");
    cout << "Kruskal and Prim agree! Test9 PASSED!" << endl << endl;
}

// ========== Original directed graph smoke test ==========

void Test_OriginalDirected()
{
    cout << "===== Test10: Original directed graph (smoke test) =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    Graph<char, int, INT_MAX, true> kTree("0123", 4);
    int kTotal = g.Kruskal(kTree);
    cout << "Kruskal total = " << kTotal << endl;

    Graph<char, int, INT_MAX, true> pTree("0123", 4);
    int pTotal = g.Prim(pTree, '0');
    cout << "Prim total = " << pTotal << endl;

    cout << "Test10 done (directed, smoke test only)" << endl << endl;
}

int main()
{
    TestKruskal_Known();
    TestKruskal_Disconnected();
    TestKruskal_SingleVertex();
    TestKruskal_Complex();
    TestPrim_Known();
    TestPrim_Disconnected();
    TestPrim_SingleVertex();
    TestPrim_Complex();
    Test_Kruskal_vs_Prim();
    Test_OriginalDirected();

    cout << "==============================" << endl;
    cout << "  ALL 10 TESTS PASSED!" << endl;
    cout << "==============================" << endl;
    return 0;
}