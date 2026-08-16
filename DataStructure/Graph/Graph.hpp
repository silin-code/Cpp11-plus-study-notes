#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <climits>
#include <stdexcept> // invalid_argument
#include <queue>//BFS遍历

#include "UnionFindSet.hpp"//并查集+最小生成树
using namespace std;

// 邻接矩阵实现的带权图
namespace matrix
{
	// V: 顶点类型  W: 权值类型  max_w: 权值最大值(表示无边)  Direction: true=有向图, false=无向图
	template<class V, class W, W max_w = INT_MAX, bool Direction = true>
	class Graph {
		using Self = Graph<V, W, max_w, Direction>;//最小生成树的self
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
				throw invalid_argument("vertex not exist"); // 抛出异常
			}
		}

		//以下标添加
		void _AddEdge(size_t srci, size_t dsti, const W& w)
		{
			_matrix[srci][dsti] = w;           // 有向图：只加一条边

			// 无向图：对称位置也要加
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

		// 添加边
		// src: 起点  dst: 终点  w: 权值
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src); // 起点下标
			size_t dsti = GetVertexIndex(dst); // 终点下标
			_AddEdge(srci, dsti, w);
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

		void BFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);

			//队列和标记数组
			queue<size_t> q;
			vector<bool> visited(_vertexs.size(), false);

			q.push(srci);
			visited[srci] = true;
			int n = _vertexs.size();
			while (q.size())
			{
				size_t front = q.front();
				q.pop();
				cout << "[" << front << "]:" << _vertexs[front] << endl;
				//把front顶点的邻接点入队
				for (size_t i = 0;i < n;i++)
				{
					if (_matrix[front][i] != max_w && visited[i] == false)
					{
						q.push(i);
						visited[i] = true;
					}
				}
			}
			cout << endl;
		}

		void _DFS(size_t srci, vector<bool>& visited)
		{
			cout << "[" << srci << "]:" << _vertexs[srci] << endl;
			visited[srci] = true;

			//找srci相邻的点,而且没有访问过
			for (size_t i = 0;i < _vertexs.size();i++)
			{
				if (_matrix[srci][i] != max_w && visited[i] == false)
				{
					_DFS(i, visited);
				}
			}
		}

		void DFS(const V& src)
		{
			size_t srci = GetVertexIndex(src);
			vector<bool> visited(_vertexs.size(), false);
			_DFS(srci, visited);
		}


		struct Edge
		{
			size_t _srci;
			size_t _dsti;
			W _w;
			Edge(size_t srci, size_t dsti,const W& w) :
				_srci(srci),
				_dsti(dsti),
				_w(w)
			{
			}

			bool operator>(const Edge& e) const
			{
				return _w > (e._w);
			}
		};


		//最小生成树算法
		W Kruskal(Self& minTree)
		{
			priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
			size_t n = _vertexs.size();
			for (size_t i = 0;i < n;i++)
			{
				for (size_t j = 0;j < n;j++)
				{
					if (_matrix[i][j] != max_w)
					{
						minque.push(Edge(i, j, _matrix[i][j]));
					}
				}
			}

			//选出一条边
			size_t size = 0;
			W total = W();
			UnionFindSet ufs(n);
			while (!minque.empty())
			{
				Edge min = minque.top();
				minque.pop();

				if (!ufs.IsInSet(min._srci, min._dsti))
				{
					minTree._AddEdge(min._dsti, min._srci,min._w);
					ufs.Union(min._dsti, min._srci);
					++size;
					total += min._w;
				}
			}

			if (size == n - 1)
			{
				return total;
			}
			else
			{
				return W();
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
		//g.Print();
		//g.BFS('0');
		g.DFS('0');
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
			_vertexs.reserve(n);
			for (size_t i = 0;i < n;i++)
			{
				_vertexs.push_back(vertexs[i]);
				_vIndexMap[vertexs[i]] = i;
			}
			_linkTable.resize(n, nullptr);
		}

		size_t GetVertexIndex(const V& v)
		{
			auto ret = _vIndexMap.find(v);
			if (ret != _vIndexMap.end())
			{
				return ret->second;
			}
			else
			{
				throw invalid_argument("Not exist");
				return -1;
			}
		}

		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);

			//0 1
			Edge* sd_edge = new Edge(w);
			sd_edge->_srcIndex = srci;
			sd_edge->_dstIndex = dsti;

			sd_edge->_next = _linkTable[srci];
			_linkTable[srci] = sd_edge;

			//1 0
			//无向图
			if (Direction == false)
			{
				Edge* ds_edge = new Edge(w);
				ds_edge->_dstIndex = dsti;
				ds_edge->_srcIndex = srci;
				ds_edge->_next = _linkTable[dsti];
				_linkTable[dsti] = ds_edge;
			}
		}

		void Print()
		{
			//顶点
			for (size_t i = 0;i < _vertexs.size();i++)
			{
				cout << "[" << i << "]" << "->" << _vertexs[i] << endl;
			}
			cout << endl;

			for (size_t i = 0;i < _linkTable.size();i++)
			{
				cout << _vertexs[i] << "[" << i << "]->";
				Edge* cur = _linkTable[i];
				while (cur)
				{
					cout << _vertexs[cur->_dstIndex] << "[" << cur->_dstIndex << "]" << cur->_w << "->";
					cur = cur->_next;
				}
				cout << "nullptr" << endl;
			}
		}

	private:
		map<V, int> _vIndexMap;
		vector<V> _vertexs;//顶点集合
		vector<Edge*> _linkTable;//边的集合的邻接表
	};

	void TestGraph()
	{
		string a[] = { "张三", "李四", "王五", "赵六" };
		Graph<string, int> g1(a, 4);
		g1.AddEdge("张三", "李四", 100);
		g1.AddEdge("张三", "王五", 200);
		g1.AddEdge("王五", "赵六", 30);
		g1.Print();
	}
}