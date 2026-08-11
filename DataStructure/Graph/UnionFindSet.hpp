#pragma once
#include <vector>
#include <cstdlib>   // abs
using namespace std;

// 并查集（Union-Find / Disjoint Set Union）
// 用一个 vector<int> 来维护所有元素的归属关系。
//
// [下标]代表元素编号（0 ~ n-1），每个下标对应一个"节点"。
// [值]的含义分两种情况：
//   - 值 < 0：该节点是所在集合的"根"，绝对值表示该集合的元素个数（树的大小）。
//             例如 _ufs[3] = -5，表示编号为 3 的节点是根，它所在集合有 5 个元素。
//   - 值 >= 0：该节点不是根，值存储的是它的"父节点"下标，沿着父节点一路向上可找到根。
//             例如 _ufs[2] = 3，表示编号为 2 的节点的父亲是编号为 3 的节点。
//
// 初始化时所有元素各自为一个集合，所以全部填 -1（每个元素自己是根，集合大小为 1）。
class UnionFindSet {
public:
	// 构造函数：n 表示元素总个数
	// 把 _ufs 初始化为 n 个 -1，即每个元素独立成一个集合，大小都是 1
	UnionFindSet(size_t n)
		:_ufs(n, -1) {
	}

	// 合并：把 x1 所在集合 和 x2 所在集合 合并成一个集合
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);  // 找到 x1 的根
		int root2 = FindRoot(x2);  // 找到 x2 的根

		// 如果两个根相同，说明已经在同一个集合里，无需合并
		if (root1 == root2)       
		{
			return;
		}

		// 按"集合大小"合并（加权合并 / union by size）：
		// 小集合往大集合上挂，避免树退化成链表
		// 如果 root1 的集合比 root2 小，就交换，让 root1 始终是较大的那个
		if (abs(_ufs[root1]) < abs(_ufs[root2]))
		{
			swap(root1, root2);
		}

		// root1 是较大集合的根，把 root2 挂到 root1 下面：
		_ufs[root1] += _ufs[root2];  // 大集合的大小 += 小集合的大小（两个负数相加，绝对值变大）
		_ufs[root2] = root1;         // 小集合的根不再是根，父节点指向 root1
	}

	// 查找 x 所在集合的根节点编号
	int FindRoot(int x)
	{
		int root = x;
		// 只要当前节点的值 >= 0，说明它不是根，继续往父节点走
		while (_ufs[root] >= 0)
		{
			root = _ufs[root];
		}

		//路径压缩
		while (x != root)
		{
			int parent = _ufs[x];
			_ufs[x] = root;
			x = parent;
		}

		// 循环结束时 _ufs[root] < 0，root 就是根节点编号
		return root;
	}

	// 判断 x1 和 x2 是否在同一个集合
	// 原理：同一个集合的元素，最终找到的根一定相同
	bool IsInSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}

	// 返回当前一共有多少个独立的集合
	// 原理：只有根节点的值 < 0，统计负数的个数就是集合数量
	size_t SetSize()
	{
		size_t size = 0;
		for (size_t i = 0; i < _ufs.size(); i++)
		{
			if (_ufs[i] < 0)
			{
				size++;
			}
		}
		return size;
	}

private:
	vector<int> _ufs;  // 存储并查集结构的数组
};