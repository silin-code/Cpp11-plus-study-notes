#pragma once

template<typename K, size_t M>
struct BTreeNode {
	/*/K _keys[M - 1];
	BTreeNode<K, M>* _subs[M];*/

	//为了方便插入以后在分裂,可以多给一个空间
	K _keys[M];//存M个key
	BTreeNode<K, M>* _subs[M + 1];//存M+1个孩子指针
	BTreeNode<K, M>* _parent;//存父指针(方便向上分裂)
	size_t _n;//记录实际存储多个关键字

	BTreeNode()
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr;
		_parent = nullptr;
		_n = 0;
	}
};

//数据存在磁盘，K是磁盘地址
template<typename K, size_t M>
class BTree {
	using Node = BTreeNode<K, M>;
public:
	//返回当前的树指针+值
	pair<Node*, int> Find(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			size_t i = 0;
			//找第一个>=key的位置
			while (i < cur->_n && key>cur->_keys[i])
			{
				i++;
			}

			//命中
			if (i < cur->_n && key == cur->_keys[i])
			{
				return { cur,(int)i };
			}

			//没有命中,往孩子去跳
			parent = cur;
			cur = cur->_subs[i];
		}

		return { parent,-1 };
	}

	//往节点里面插入key和child
	/*叶子节点插入时 child 是 nullptr。但分裂的时候，要把 "中间 key + 分裂出的新节点" 一起插进父节点，这时候 child 就是新节点。*/
	void InsertKey(Node* node, const K& key, Node* child)
	{
		//从左往右找插入位置,比key大的都往右移
		int end = node->_n - 1;
		while (end >= 0 && key < node->_keys[end])
		{
			node->_keys[end + 1] = node->_keys[end];
			node->_subs[end + 2] = node->_subs[end + 1];
			end--;

		}
		//插入
		node->_keys[end + 1] = key;
		node->_subs[end + 2] = child;
		node->_n++;
	}

	/*插入流程
	1. 树空 → 直接建根节点
	2. Find 查找 key
	   ├─ 已存在 → 不允许重复，返回 false
	   └─ 不存在 → 拿到要插入的叶子节点
	3. 把 key 插进叶子节点
	4. 检查节点是否满了（_n == M）
	   ├─ 没满 → 结束
	   └─ 满了 → 分裂，中间 key 往上提
	5. 如果父节点也满了，继续分裂，直到某个节点不满或者分裂到根
	*/
	bool Insert(const K& key)
	{
		//1树空
		if (_root == nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			return true;
		}

		//key已经存在,不允许插入
		pair<Node*, int> ret = Find(key);
		if (ret.second >= 0)
		{
			return false;
		}

		//如果没有找到,find顺便带回要插入的那个叶子节点

		//循环每次往cur插入 ,newkey和child
		Node* parent = ret.first;
		K newkey = key;
		Node* child = nullptr;

		while (1) {
			InsertKey(parent, newkey, child);

			//满了就要分裂
			//没有满,插入就结束
			if (parent->_n < M)
			{
				return true;
			}
			else
			{
				/*
				分裂前（M=3，满了有3个key）
						[10 | 20 | 30]
					   /   |    |    \
					 c0   c1   c2    c3

				分裂后：
						[20]          ← 中间的 key 往上提
					   /    \
				   [10]    [30]       ← 左右各一个节点
				   /  \    /  \
				  c0  c1  c2  c3
				*/
				size_t mid = M / 2;//中间位置,M=3时mid = 1

				//分裂一半[mid+1,M-1]给兄弟
				//一:创建兄弟节点
				Node* brother = new Node;
				//二:把[mid+1,M-1]的key和对应的左孩子拷贝给brother
				size_t j = 0;//兄弟节点写入的下标从0开始
				for (size_t i = mid + 1; i <= M - 1; i++)
				{
					//key和key的左孩子
					brother->_keys[j] = parent->_keys[i];
					brother->_subs[j] = parent->_subs[i];
					if (parent->_subs[i])
					{
						parent->_subs[i]->_parent = brother;
					}

					j++;
					//parent->_keys[i] = K();
				}

				//还有最后一个右孩子拷给
				brother->_subs[j] = parent->_subs[M];
				if (parent->_subs[M])
				{
					parent->_subs[M]->_parent = brother;
				}

				brother->_n = j;
				parent->_n -= (brother->_n + 1);

				//情况A,刚刚分裂的parent是根节点(没有父亲)
				//创建一个新的根
				/*          新根: [20]
								  /  \
								 /    \
					 parent: [10]     brother: [30]
						c0 c1           c2 c3
				*/
				if (parent->_parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = parent->_keys[mid];
					_root->_subs[0] = parent;
					_root->_subs[1] = brother;
					_root->_n = 1;
					parent->_parent = _root;
					brother->_parent = _root;
					break;
				}
				//有父节点
				/*
							  [20]
							 /    \
						   [10]   [30 | 40 | 50]   ← 这个节点满了，要分裂
				*/
				else
				{
					//转换成往parent->parent去插入parent->[mid]和brother
					brother->_parent = parent->_parent;
					newkey = parent->_keys[mid];
					child = brother;
					parent = parent->_parent;
				}
			}
		}
		return true;
	}

	void _InOrder(Node* cur)
	{
		if (cur == nullptr) return;

		//按照左根右的中序遍历
		for (size_t i = 0; i < cur->_n; i++)
		{
			_InOrder(cur->_subs[i]);
			cout << cur->_keys[i] << " ";
		}
		_InOrder(cur->_subs[cur->_n]);
	}

	void InOrder()
	{
		_InOrder(_root);
	}
private:
	Node* _root = nullptr;
};

void Test()
{
	int a[] = { 53,139,75,49,145,36,101 };
	BTree<int, 3> t;
	for (auto e : a)
	{
		t.Insert(e);
	}
	t.InOrder();
}