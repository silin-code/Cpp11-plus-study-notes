#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <climits>
#include <stdexcept> // invalid_argument
using namespace std;

// 邻接矩阵实现的带权图
namespace matrix
{
	// V: 顶点类型  W: 权值类型  max_w: 权值最大值(表示无边)  Direction: true=有向图, false=无向图
	template<class V, class W, W max_w = INT_MAX, bool Direction = true>
	class Graph {
	public:
		// 构造函数：用顶点数组初始化图
		// a: 顶点数组  n: 顶点个数
		Graph(const V* a, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; i++)
			{
				_vertexs.push_back(a[i]);    // 存顶点
				_indexMap[a[i]] = i;         // 建立顶点到下标的映射
			}

			// 初始化邻接矩阵，n×n，默认值为 max_w（表示无边）
			_matrix.resize(n);
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				_matrix[i].resize(n, max_w);
			}
		}

		// 根据顶点值找下标
		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _indexMap.end())
			{
				return it->second;
			}
			else
			{
				throw invalid_argument("vertex now exist"); // 抛出异常
			}
		}

		// 添加边
		// src: 起点  dst: 终点  w: 权值
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src); // 起点下标
			size_t dsti = GetVertexIndex(dst); // 终点下标

			_matrix[srci][dsti] = w;           // 有向图：只加一条边

			// 无向图：对称位置也要加
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

		// 打印图结构
		void Print()
		{
			// 打印顶点列表
			for (size_t i = 0; i < _vertexs.size(); i++)
			{
				cout << "[" << i << "]->" << _vertexs[i] << endl;
			}
			cout << endl;

			// 打印邻接矩阵
			for (size_t i = 0; i < _matrix.size(); i++)
			{
				for (size_t j = 0; j < _matrix[i].size(); j++)
				{
					if (_matrix[i][j] == max_w)
					{
						cout << "* ";  // 无边用 * 表示
					}
					else
					{
						cout << _matrix[i][j] << " ";
					}
				}
				cout << endl;
			}
		}
	private:
		vector<V> _vertexs;          // 顶点集合
		map<V, size_t> _indexMap;    // 顶点值 -> 下标的映射
		vector<vector<W>> _matrix;   // 邻接矩阵
	};

	// 测试函数
	void TestGraph()
	{
		Graph<char, int, INT_MAX, true> g("0123", 4); // 4个顶点的有向图
		g.AddEdge('0', '1', 1);
		g.AddEdge('0', '3', 4);
		g.AddEdge('1', '3', 2);
		g.AddEdge('1', '2', 9);
		g.AddEdge('2', '3', 8);
		g.AddEdge('2', '1', 5);
		g.AddEdge('2', '0', 3);
		g.AddEdge('3', '2', 6);
		g.Print();
	}
}

namespace LinkTable
{
	template<class W>
	struct LinkEdge {
		int _srcIndex;
		int _dstIndex;//目标点下标
		W _w;//权值

		LinkEdge<W>* _next;

		LinkEdge(const W& w)
			:_srcIndex(-1),
			_dstIndex(-1),
			_w(w),
			_next(nullptr)
		{
		}
	};

	template<class V, class W, bool Direction = false>
	class Graph {
		using Edge = LinkEdge<W>;
	public:
		Graph(const V* vertexs, size_t n)
		{

		}

		size_t GetVertexIndex(const V& v)
		{

		}

		void AddEdge(const V& src,const V& dst,const W& w)
		{

		}
	private:
		map<string, int> _vIndexMap;
		vector<V> _vertex;//顶点集合
		vector<Edge*> _linkTable;//边的集合的邻接表
	};
}