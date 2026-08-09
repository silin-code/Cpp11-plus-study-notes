#pragma once
#include<vector>
#include<iostream>
#include<map>
using namespace std;

//weight
namespace matrix
{
	template<class V,class W,W max_w=INT_MAX,bool Direction>
	class Graph {
	public:
		//图的创建
		//1:IO输入
		//2:图结构写道文件，读取文件
		//3:手动添加边
		Graph(const V* a,size_t n)
		{
			_vertexs.reserve(n);
			for (size_t i = 0;i < n;i++)
			{
				_vertexs.push_back(a[i]);
				_indexMap[a[i]] = i;
			}

			_matrix.resize(n);;
			for (size_t i = 0;i < _matrix.size();i++)
			{
				_matrix[i].resize(n, INT_MAX);
			}
		}

		//找顶点下标
		size_t GetVertexIndex(const V& v)
		{
			auto it = _indexMap.find(v);
			if (it != _vertexs.end())
			{
				return it->second;
			}
			else
			{
				//assert(false);
				throw invalid_argument("顶点不存在");
				return -1;
			}
		}

		//添加边
		//
		void AddEdge(const V& src, const V& dst, const W& w)
		{
			size_t srci = GetVertexIndex(src);
			size_t dsti = GetVertexIndex(dst);

			_matrixx[srci][dsti] = w;
			//无向图
			if (Direction == false)
			{
				_matrix[dsti][srci] = w;
			}
		}

	private:
		vector<V> _vertexs;//顶点集合
		map<V, size_t> _indexMap;//顶点映射下标
		vector<vector<W>> _matrix;//邻接矩阵
	};
}