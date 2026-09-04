#pragma once

template<typename K, size_t M>
struct BTreeNode {
	/*/K _keys[M - 1];
	BTreeNode<K, M>* _subs[M];*/

	//为了方便插入以后在分裂,可以多给一个空间
	K _keys[M];
	BTreeNode<K, M>* _subs[M+1];
	size_t _n;//记录实际存储多个关键字

	BTreeNode()
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_subs[i] = nullptr;
		}
		_subs[M] = nullptr;
		_n = 0;
	}
};

//数据存在磁盘，K是磁盘地址
template<typename K, size_t M>
class BTree {
	using Node = BTreeNode<K, M>;
public:
	pair<Node*, int> Find(const K& key)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			size_t i = 0;
			while (i < cur->_n)
			{
				if (key < cur->_keys[i])
				{
					//_key[i]的左孩子,左孩子和他的下标相等
					cur = cur->_subs[i];
				}
				else if (key > cur->_keys[i])
				{
					i++;
				}
				else
				{
					return { cur,i };
				}
			}

			//往孩子去跳
			parent = cur;
			cur = cur->_subs[i];
		}

		return { parent,-1 };
	}

	bool Insert(const K& key)
	{
		if (_root = nullptr)
		{
			_root = new Node;
			_root->_keys[0] = key;
			return true;
		}

		//key已经存在,不允许1插入
		pair<Node*, int> ret = Find(key);
		if (ret->second >= 0)
		{
			return false;
		}

		//如果没有找到,find顺便带回要插入的那个叶子节点

		//循环每次往cur插入 ,newkey和child
		Node* parent = ret->first;
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
				//分裂一半[mid+1,M-1]给兄弟
				size_t mid = M / 2;
				Node* brother = new Node;
				size_t j = 0;
				for (size_t i = mid + 1; i <= M - 1; i++)
				{
					brother->_keys[j++] = parent->_keys[i];
				}
				brother->_n = j;
				parent->_n -= (brother->_n + 1);

				//说明刚刚分裂的是根节点
				if (parent == nullptr)
				{
					_root = new Node;
					_root->_keys[0] = newkey;
					_root->_subs[0] = parent;
					_root->_subs[1] = brother;
					_root->_n = 1;
					return true;
				}
				else
				{
					//转换成往parent->parent去插入parent->[mid]和brother
					newkey = parent ->[mid];
					child = brother;
					parent = parent->parent;
				}
			}
		}
		return true;
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
}