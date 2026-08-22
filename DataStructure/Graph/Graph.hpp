#pragma once
#include <vector>
#include <iostream>
#include <map>
#include <climits>
#include <stdexcept> // invalid_argument
#include <queue>//BFS遍历
#include <algorithm>

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
				for (size_t i = 0; i < n; i++)
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
			for (size_t i = 0; i < _vertexs.size(); i++)
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
			Edge(size_t srci, size_t dsti, const W& w) :
				_srci(srci),
				_dsti(dsti),
				_w(w)
			{}

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
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
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
					minTree._AddEdge(min._dsti, min._srci, min._w);
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

		W Prim(Self& minTree, const V& src)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();

			vector<bool> inX(n, false);
			inX[srci] = true;

			//从X到Y集合里面连接的边选出最小的
			priority_queue<Edge, vector<Edge>, greater<Edge>> minq;
			//先把seci连接的边添加到队列
			for (size_t i = 0; i < n; i++)
			{
				if (_matrix[srci][i] != max_w)
				{
					minq.push(Edge(srci, i, _matrix[srci][i]));
				}
			}

			size_t edgecount = 0;
			W total = W();

			while (!minq.empty())
			{
				Edge min = minq.top();
				minq.pop();

				//目标点在MST中，直接跳过
				if (inX[min._dsti]) continue;

				//目标点不在，加入MST
				minTree._AddEdge(min._srci, min._dsti, min._w);
				inX[min._dsti] = true;
				total += min._w;
				edgecount++;

				if (edgecount == n - 1)
				{
					break;
				}

				//把新加入顶点的所有邻边入队
				for (size_t i = 0; i < n; i++)
				{
					if (_matrix[min._dsti][i] != max_w && !inX[i])
					{
						minq.push(Edge(min._dsti, i, _matrix[min._dsti][i]));
					}
				}
			}

			//不联通返回W()
			if (edgecount == n - 1)return total;
			return W();
		}

		// Dijkstra 单源最短路径算法
		// 参数说明：
		//   src        : 源点（起点）的数据，类型为顶点数据类型 V
		//   dist       : 出参，记录源点到每个顶点的最短距离，类型 W 为权值类型
		//   parentPath : 出参，记录最短路径树上每个顶点的前驱顶点下标，用于回溯路径
		void Dijkstra(const V& src, vector<W>& dist, vector<int>& parentPath)
		{
			// 1. 根据源点数据找到它在顶点数组中的下标
			size_t srci = GetVertexIndex(src);
			// 顶点总数
			size_t n = _vertexs.size();

			// 2. 初始化距离数组：源点到所有顶点的距离先设为无穷大 max_w
			dist.resize(n, max_w);
			// 初始化前驱数组：所有顶点的前驱先设为 -1（表示无前驱）
			parentPath.resize(n, -1);

			// 源点到自身的距离为 0
			dist[srci] = 0;
			// 源点没有前驱，保持 -1
			parentPath[srci] = -1;

			// 3. S 集合：标记已经确定最短路径的顶点
			//    初始时只有源点被确定
			vector<bool> S(n, false);

			// 4. 主循环：总共需要确定 n 个顶点的最短路径
			//    每一轮选出一个当前距离最小、且尚未确定的顶点加入 S
			for (size_t j = 0; j < n; j++)
			{
				// 4.1 在尚未确定最短路径的顶点中，找距离源点最近的顶点 u
				int u = -1;          // 记录选中顶点的下标
				W min = max_w;      // 记录当前最小距离
				for (size_t i = 0; i < n; i++)
				{
					// 只在未确定的顶点中挑选
					if (S[i] == false && dist[i] < min)
					{
						u = (int)i;
						min = dist[i];
					}
				}

				if (u == -1) break;//剩余顶点都不可达

				// 4.2 将顶点 u 加入已确定集合 S，此时 dist[u] 就是源点到 u 的最短距离
				S[u] = true;

				// 4.3 松弛操作：以 u 为中转点，更新源点到 u 的邻接点 v 的距离
				//     逻辑：源点 -> u 的最短距离 + u -> v 的边权 < 源点 -> v 当前距离
				//           则说明经过 u 再到 v 更短，更新 dist[v] 并记录前驱
				for (size_t v = 0; v < n; v++)
				{
					// _matrix[u][v] != max_w 表示 u 到 v 存在边
					// dist[u] + 边权 < dist[v] 表示经过 u 中转更优
					if (_matrix[u][v] != max_w
						&& dist[u] + _matrix[u][v] < dist[v]
						&& S[v] == false
						&& dist[u] != max_w)
					{
						// 更新更短的距离
						dist[v] = dist[u] + _matrix[u][v];
						// 记录 v 的前驱是 u，后续可通过 parentPath 回溯完整路径
						parentPath[v] = u;
					}
				}
			}
		}

		//打印最短路径的逻辑算法
		void PrintShortPath(const V& src, const vector<W>& dist, const vector<int>& parentPath)
		{
			size_t srci = GetVertexIndex(src);
			size_t n = _vertexs.size();
			for (size_t i = 0; i < n; i++)
			{
				if (i != srci)
				{
					//找出i顶点的路径
					vector<int> path;
					int cur = (int)i;
					path.push_back(i);
					while (cur != -1)
					{
						path.push_back(cur);
						cur = parentPath[cur];
					}
					path.push_back(srci);

					reverse(path.begin(), path.end());
					for (auto e : path)
					{
						cout << _vertexs[e] << "->";
					}
					cout << dist[i] << endl;
				}
			}
		}

		bool BellmanFord(const V& src, vector<W>& dist, vector<int>& parentPath)
		{
			size_t n = _vertexs.size();
			size_t srci = GetVertexIndex(src);

			//vector<W> dist,记录srci-其他顶点最短路权值数组
			dist.resize(n, max_w);

			//vector<int> parentPath记录srci-其他顶点最短路径父顶点数组
			parentPath.resize(n, -1);

			//先更新srci->srci为缺省值
			dist[srci] = W();

			//总体更新n轮
			//i->j更新k次
			for (size_t k = 0; k < n - 1; k++)
			{
				bool updated = false;
				//i->j更新松弛
				for (size_t i = 0; i < n; i++)
				{
					if (dist[i] == max_w) continue;
					for (size_t j = 0; j < n; j++)
					{
						// (srci->i + i->j)
						if (_matrix[i][j] != max_w && dist[i] + _matrix[i][j] < dist[j])
						{
							dist[j] = dist[i] + _matrix[i][j];
							parentPath[j] = (int)i;
							updated = true;
						}
					}
				}
				if (!updated)break;//提前收敛
			}

			//第n轮,检测负权环
			for (size_t i = 0; i < n; i++)
			{
				if (dist[i] == max_w) continue;
				for (size_t j = 0; j < n; j++)
				{
					// (srci->i + i->j)
					if (_matrix[i][j] != max_w && dist[i] + _matrix[i][j] < dist[j])
					{
						return false;
					}
				}
			}

			return true;
		}

		void FloydWarshall(vector<vector<W>>& vvDist, vector<vector<int>>& vvparentPath)
		{
			size_t n = _vertexs.size();
			vvDist.resize(n);
			vvparentPath.resize(n);

			//初始化权值和路径矩阵
			for (size_t i = 0; i < n; i++)
			{
				vvDist[i].resize(n, max_w);
				vvparentPath[i].resize(n, -1);
			}

			//直接相邻的边更新一下
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if (_matrix[i][j] != max_w)
					{
						vvDist[i][j] = _matrix[i][j];
						vvparentPath[i][j] = i;
					}
					if (i == j) vvDist[i][j] = W();
				}
			}

			//最短路径更新i->{k个顶点}->j
			for (size_t k = 0; k < n; k++)
			{
				for (size_t i = 0; i < n; i++)
				{
					for (size_t j = 0; j < n; j++)
					{
						//k作为的中间点,k尝试更新i->j的路径
						if (vvDist[i][k] != max_w && vvDist[k][j] != max_w
							&& vvDist[i][k] + vvDist[k][j] < vvDist[i][j])
						{
							vvDist[i][j] = vvDist[i][k] + vvDist[k][j];
							//找跟j相连大的上一个邻接顶点
							//如果k->j直接相连,上一个点就是k,vvparentPath[k][j]存的就是k
							//如果k->j没有直接相连
							vvparentPath[i][j] = vvparentPath[k][j];
						}
					}
				}
			}
		}

		// Print all - pairs shortest paths computed by FloydWarshall
		void PrintFloydPaths(const vector<vector<W>>& vvDist,const vector<vector<int>>& vvparentPath)
		{
			size_t n = _vertexs.size();
			for (size_t i = 0; i < n; i++)
			{
				for (size_t j = 0; j < n; j++)
				{
					if (i == j) continue;

					cout << _vertexs[i] << " -> " << _vertexs[j] << " : ";

					if (vvDist[i][j] == max_w)
					{
						cout << "unreachable" << endl;
						continue;
					}

					// Reconstruct path: follow predecessors from j back to i
					vector<int> path;
					int cur = (int)j;
					while (cur != -1 && (size_t)cur != i)
					{
						path.push_back(cur);
						cur = vvparentPath[i][cur];
					}
					if (cur == -1)
					{
						cout << "unreachable" << endl;
						continue;
					}
					path.push_back((int)i);
					reverse(path.begin(), path.end());

					for (size_t idx = 0; idx < path.size(); idx++)
					{
						if (idx > 0) cout << "->";
						cout << _vertexs[path[idx]];
					}
					cout << " (weight=" << vvDist[i][j] << ")" << endl;
				}
			}
		}

	private:
		vector<V> _vertexs;          // 顶点集合
		map<V, size_t> _indexMap;    // 顶点值 -> 下标的映射
		vector<vector<W>> _matrix;   // 邻接矩阵
	};
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
		{}
	};

	template<class V, class W, bool Direction = false>
	class Graph {
		using Edge = LinkEdge<W>;
	public:
		Graph(const V* vertexs, size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0; i < n; i++)
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
			for (size_t i = 0; i < _vertexs.size(); i++)
			{
				cout << "[" << i << "]" << "->" << _vertexs[i] << endl;
			}
			cout << endl;

			for (size_t i = 0; i < _linkTable.size(); i++)
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
}