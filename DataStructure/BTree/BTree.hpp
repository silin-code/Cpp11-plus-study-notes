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
			_root->_n = 1;
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

	/*
	什么是 underflow？
	B 树规定非根节点最少有 `⌈M/2⌉ - 1` 个 key。删除后如果低于这个数，就叫 underflow（下溢），必须修复。

	M=3 时，最少 1 个 key
	节点 [20] 删完变 [] → _n=0 < 1 → underflow，要修
	节点 [20|30] 删完变 [30] → _n=1 >= 1 → 没事

	underflow 了怎么办？
	│
	├─ 左兄弟有多余 key？ → 借一个（左旋）
	├─ 右兄弟有多余 key？ → 借一个（右旋）
	└─ 都没有多余 → 合并
		└─ 合并后父节点少一个 key，可能也 underflow → 继续往上修
	*/

	//最少需要的key数
	size_t MinKeys()
	{
		return (M + 1) / 2 - 1;
	}

	//找子树最左节点
	//一个 key 的 "后继" 是比它大的最小 key。在 B 树里，后继就是它**右子树的最左节点**的第一个 key。
	Node* FindLeftMost(Node* node)
	{
		while ((node->_subs[0]))//有左孩子,没有左孩子停止
			node = node->_subs[0];//一直往左走
		return node;//最左节点
	}

	//删除节点里的某个key
	//数组删除元素,后面的元素往前挪,覆盖要删掉的位置。key和它的右孩子屎绑定的,要一起挪
	void RemoveKey(Node* node, size_t pos)
	{
		for (size_t i = pos; i < node->_n - 1; i++)
		{
			node->_keys[i] = node->_keys[i + 1];//后面的key往前挪,覆盖掉pos这个位置
			node->_subs[i + 1] = node->_subs[i + 2];//key的右孩子也往前挪动
		}
		node->_n--;//数量减一
	}

	//查找当前节点是父节点的第几个孩子
	int GetChildeIndex(Node* parent, Node* cur)
	{
		for (size_t i = 0; i <= parent->_n; i++)
		{
			if (parent->_subs[i] == cur)
			{
				return (int)i;
			}
		}
		return -1;
	}

	//删除整体流程
	/*Remove(key)
	  │
	  ├─ Find 查找 → 不存在返回false
	  │
	  ├─ 不是叶子？ → 用后继替换，转成删叶子
	  │
	  ├─ RemoveKey 在叶子删除
	  │
	  └─ while (不是根 且 underflow)
		   │
		   ├─ 左兄弟有多余？ → 借左兄弟（3步：右移→父key下移→兄弟key上移）
		   ├─ 右兄弟有多余？ → 借右兄弟（3步：追加→父key下移→兄弟key上移）
		   └─ 都没有 → 合并（6步：定左右→父key下移→拼右节点→父删key→根降高度检查→cur=parent继续）
	*/
	bool Remove(const K& key)
	{
		pair<Node*, int> ret = Find(key);
		if (ret.second < 0)
		{
			return false;
		}
		Node* cur = ret.first;
		size_t pos = ret.second;

		//如果不是叶子,转成叶子
		if (cur->_subs[0])//有左孩子就不是叶子,(叶子的孩子都是nullptr)
		{
			//找后继:右树的最左节点
			Node* successor = FindLeftMost(cur->_subs[pos + 1]);
			//用后继值覆盖掉要删的key
			cur->_keys[pos] = successor->_keys[0];
			cur = successor;
			pos = 0;
			/*
			* 删之前：
						[50]          ← 要删50，它不是叶子
					   /    \
					 [30]   [70|80]
							/
						  [60]        ← 50的后继是60

			替换后：
						[60]          ← 50被替换成60
					   /    \
					 [30]   [70|80]
							/
						  [60]        ← 现在去删这个叶子里的60

			*/
		}

		RemoveKey(cur, pos);
		//不是叶子
		while (cur != _root && cur->_n < MinKeys())
		{
			/*
				- `cur != _root`：根节点没有最少 key 限制（根可以只有 1 个 key，甚至 0 个然后降高度），所以根不用修
				- `cur->_n < MinKeys()`：确实 underflow 了才进循环
				- `leftBrother`：idx>0 才有左兄弟，就是父节点里前一个孩子指针
				- `rightBrother`：idx <parent->_n 才有右兄弟（因为孩子下标最大是 _n），就是后一个孩子指针
			*/
			Node* parent = cur->_parent;
			int idx = GetChildeIndex(parent, cur);

			Node* leftbrother = (idx > 0) ? parent->_subs[idx - 1] : nullptr;
			Node* rightbrother = (idx < (int)parent->_n) ? parent->_subs[idx + 1] : nullptr;
			//手段一:从左兄弟借
			if (leftbrother && leftbrother->_n > MinKeys())
			{
				//1 cur整体右移一个,腾出0下标的位置
				for (size_t i = cur->_n; i > 0; i--)
				{
					cur->_keys[i] = cur->_keys[i - 1];
					cur->_subs[i + 1] = cur->_subs[i];
				}
				cur->_subs[1] = cur->_subs[0];

				//2 父节点的key下移到cur的[0]
				cur->_keys[0] = parent->_keys[idx - 1];
				//左兄弟最大key的右孩子过继当我的左孩子
				cur->_subs[0] = leftbrother->_subs[leftbrother->_n];
				if (cur->_subs[0])
					cur->_subs[0]->_parent = cur;

				//3 左兄弟最大key上移到父节点
				parent->_keys[idx - 1] = leftbrother->_keys[leftbrother->_n - 1];
				leftbrother->_n--;
				cur->_n++;
				/*借之前：
						[50]              ← parent
					   /    \
				  [20|30]    [cur]          ← leftBrother有多余，cur空了

				① cur右移（本来就是空的，挪了个寂寞）

				② 50下移给cur，左兄弟的c2过继给cur：
						[50]
					   /    \
				  [20|30]   [50]
							/
						   c2

				③ 30上移到父节点：
						[30]
					   /    \
					 [20]   [50]
							/
						   c2

				完成，cur有1个key，不再underflow
				*/
			}//手段二:从右兄弟借
			else if (rightbrother && rightbrother->_n > MinKeys())
			{
				//1 父节点的key追加到cur的末尾
				cur->_keys[cur->_n] = parent->_keys[idx];
				//右兄弟最小key的左孩子过继给我当右孩子
				cur->_subs[cur->_n + 1] = rightbrother->_subs[0];
				if (cur->_subs[cur->_n + 1])
					cur->_subs[cur->_n + 1]->_parent = cur;
				cur->_n++;

				//2 右兄弟最小key上移到父节点
				parent->_keys[idx] = rightbrother->_keys[0];

				//3 右兄弟整体左移一格
				for (size_t i = 0; i < rightbrother->_n - 1; i++)
				{
					rightbrother->_keys[i] = rightbrother->_keys[i + 1];
					rightbrother->_subs[i] = rightbrother->_subs[i + 1];
				}
				rightbrother->_subs[rightbrother->_n - 1] = rightbrother->_subs[rightbrother->_n];
				rightbrother->_n--;
				/*
				借之前：
						[50]
					   /    \
					 [cur]    [70|80]     ← cur空了，右兄弟有多余

				① 50追加到cur，右兄弟的c0过继给cur：
						[50]
					   /    \
					[50]   [70|80]
					  \
					   c0

				② 70上移到父节点：
						[70]
					   /    \
					[50]   [70|80]
					  \
					   c0

				③ 右兄弟左移：
						[70]
					   /    \
					[50]    [80]
					  \     /
					   c0  c1

				完成*/
			}
			else//手段三:合并
			{
				//1 确定左右：有左兄弟就和左合，没有就和右合
				Node* left = leftbrother ? leftbrother : cur;
				Node* right = leftbrother ? cur : rightbrother;
				int leftIdx = leftbrother ? idx - 1 : idx;

				//2 父节点的key下移到左节点末尾
				left->_keys[left->_n] = parent->_keys[leftIdx];
				left->_subs[left->_n + 1] = right->_subs[0];
				if (left->_subs[left->_n + 1])
					left->_subs[left->_n + 1]->_parent = left;
				left->_n++;

				//3 右节点所有内容追加到左节点
				for (size_t i = 0; i < right->_n; i++)
				{
					left->_keys[left->_n] = right->_keys[i];
					left->_subs[left->_n + 1] = right->_subs[i + 1];
					if (left->_subs[left->_n + 1])
						left->_subs[left->_n + 1]->_parent = left;
					left->_n++;
				}

				//4 父节点删掉对应key，释放右节点
				RemoveKey(parent, leftIdx);
				delete right;

				//5 特殊情况：父节点是根且空了，树要降高度
				if (parent == _root && parent->_n == 0)
				{
					_root = left;
					left->_parent = nullptr;
					delete parent;
					break;
				}

				//6 父节点可能也underflow，继续循环
				cur = parent;
			}
			/*合并前：
					[50]              ← parent
				   /    \
				 [20]    []          ← leftBrother=[20], cur=[]
									 左兄弟只有1个key(=最小值)，不能借

			① left=[20], right=[], leftIdx=0

			② 50下移到left末尾：
				 [20 | 50]
					   /
					  right的_subs[0](nullptr)

			③ right是空的，循环不执行

			④ 父节点删key，释放right：
					[]（根空了！）
					 \
				  [20 | 50]

			⑤ parent是根且空了 → 降高度：
				  [20 | 50]        ← 新根

			完成，树高度从2降到1
		*/
		}
		return true;
	}

private:
	Node* _root = nullptr;
};

