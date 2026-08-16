#include <iostream>
#include <cassert>
#include "Graph.hpp"
using namespace std;
using namespace matrix;

// 测试1: 经典无向图，MST 权值已知 = 4
void TestKruskal_Known()
{
    cout << "===== Test1: 无向图 Kruskal =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);

    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '2', 3);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '2', 2);
    g.AddEdge('1', '3', 5);
    g.AddEdge('2', '3', 1);

    cout << "--- 原图邻接矩阵 ---" << endl;
    g.Print();

    Graph<char, int, INT_MAX, false> minTree(a, 4);
    int total = g.Kruskal(minTree);

    cout << "--- 最小生成树邻接矩阵 ---" << endl;
    minTree.Print();
    cout << "MST 总权值 = " << total << endl;

    assert(total == 4 && "Test1 failed: expected total = 4");
    cout << "Test1 PASSED!" << endl << endl;
}

// 测试2: 不连通图，Kruskal 应返回 0
void TestKruskal_Disconnected()
{
    cout << "===== Test2: 不连通图 =====" << endl;
    char a[] = { '0', '1', '2', '3' };
    Graph<char, int, INT_MAX, false> g(a, 4);

    g.AddEdge('0', '1', 2);
    // 2 和 3 孤立

    Graph<char, int, INT_MAX, false> minTree(a, 4);
    int total = g.Kruskal(minTree);

    cout << "MST 总权值 = " << total << " (不连通应返回0)" << endl;
    assert(total == 0 && "Test2 failed: disconnected graph should return 0");
    cout << "Test2 PASSED!" << endl << endl;
}

// 测试3: 单顶点图
void TestKruskal_SingleVertex()
{
    cout << "===== Test3: 单顶点 =====" << endl;
    char a[] = { '0' };
    Graph<char, int, INT_MAX, false> g(a, 1);

    Graph<char, int, INT_MAX, false> minTree(a, 1);
    int total = g.Kruskal(minTree);

    cout << "MST 总权值 = " << total << " (单顶点应为0)" << endl;
    assert(total == 0 && "Test3 failed: single vertex should return 0");
    cout << "Test3 PASSED!" << endl << endl;
}

// 测试4: 5顶点复杂无向图，MST = 13
void TestKruskal_Complex()
{
    cout << "===== Test4: 5顶点复杂无向图 =====" << endl;
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

    cout << "--- 原图邻接矩阵 ---" << endl;
    g.Print();

    Graph<char, int, INT_MAX, false> minTree(a, 5);
    int total = g.Kruskal(minTree);

    cout << "--- 最小生成树邻接矩阵 ---" << endl;
    minTree.Print();
    cout << "MST 总权值 = " << total << endl;

    // C-E(1) + D-E(2) + A-B(4) + A-E(6) = 13
    assert(total == 13 && "Test4 failed: expected total = 13");
    cout << "Test4 PASSED!" << endl << endl;
}

// 测试5: 你原始的有向图（验证不崩溃）
void TestKruskal_OriginalDirected()
{
    cout << "===== Test5: 用户原始有向图 =====" << endl;
    Graph<char, int, INT_MAX, true> g("0123", 4);
    g.AddEdge('0', '1', 1);
    g.AddEdge('0', '3', 4);
    g.AddEdge('1', '3', 2);
    g.AddEdge('1', '2', 9);
    g.AddEdge('2', '3', 8);
    g.AddEdge('2', '1', 5);
    g.AddEdge('2', '0', 3);
    g.AddEdge('3', '2', 6);

    cout << "--- 原图邻接矩阵 ---" << endl;
    g.Print();

    Graph<char, int, INT_MAX, true> minTree("0123", 4);
    int total = g.Kruskal(minTree);

    cout << "--- 生成树邻接矩阵 ---" << endl;
    minTree.Print();
    cout << "总权值 = " << total << endl;
    cout << "Test5 运行完成（有向图仅验证不崩溃）" << endl << endl;
}

int main()
{
    TestKruskal_Known();
    TestKruskal_Disconnected();
    TestKruskal_SingleVertex();
    TestKruskal_Complex();
    TestKruskal_OriginalDirected();

    cout << "========================================" << endl;
    cout << "  全部测试通过！" << endl;
    cout << "========================================" << endl;
    return 0;
}
//#include "Graph.hpp"
//
//int main()
//{
//	matrix::TestGraph();
//	//LinkTable::TestGraph();
//	return 0;
//}