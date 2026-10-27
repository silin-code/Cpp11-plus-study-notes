// ============================================================
// LC 110 平衡二叉树（简单）
// ------------------------------------------------------------
// 考点：后序遍历求高度 + 顺路检查平衡（自底向上）
// 复杂度：时间 O(n)（每个节点访问一次），空间 O(h)（递归栈）
// 日期：2026-10-27（用户"随便写的一道"，英文题面能看懂后做的第一题）
// ------------------------------------------------------------
// 题意：
//   给一棵二叉树，判断它是否"高度平衡"——
//   每个节点的左右两棵子树高度差不超过 1。
//
//   平衡：   [3,9,20,null,null,15,7]        -> true
//   不平衡： [1,2,2,3,3,null,null,4,4]      -> false
//   空树：   []                             -> true
//
// ------------------------------------------------------------
// 思路：后序遍历（自底向上）
// ------------------------------------------------------------
//   dfs(root) 返回：以 root 为根的子树高度
//
//   在返回之前，顺手检查「左右子树高度差」：
//       abs(left - right) > 1  ->  flag = false
//
//   为什么是后序而不是前序：
//       前序要在每个节点"重新求子树高度" -> O(n²)
//       后序只把高度往上带一次          -> O(n)
//
// ------------------------------------------------------------
// ★ 本题唯一的坑：成员变量 flag 必须在入口复位
// ------------------------------------------------------------
//   `bool flag = true;` 是【成员变量】—— 构造时才是 true。
//   如果 isBalanced 里不复位：
//       第 1 次调用（不平衡树）-> flag = false
//       第 2 次调用（平衡树）  -> 读到的还是 false  ✗
//
//   实测（同一对象连续调用）：
//       第 1 次（不平衡）-> false ✓
//       第 2 次（平衡）  -> false ✗（应 true）
//
//   ⚠️ LeetCode 每题新建一个 Solution 对象，所以提交页面上看不到这个错；
//      但本地多测 / 面试白板 / 蓝桥杯一题多次调用 -> 必炸。
//
//   这是第 5 次踩同类坑：
//       LC 46  ret / path 没清空
//       LC 200 use.resize() 不重置元素
//       LC 486 memo 没复位
//       LC 78  ret 没 clear
//       LC 110 flag 没复位        ← 本次
//
//   ★ 纪律：任何成员变量只要会在多次调用间累积状态，入口第一件事就是复位。
//           `= true` / `clear()` / `assign()` 三选一，别省。
//
// ------------------------------------------------------------
// 另一种写法（更短）：dfs 内部统一判空
// ------------------------------------------------------------
//   int dfs(TreeNode* root) {
//       if (root == nullptr) return 0;      // 空节点高度 0
//       int left  = dfs(root->left);
//       int right = dfs(root->right);
//       if (abs(left - right) > 1) flag = false;
//       return max(left, right) + 1;
//   }
//   好处：「空节点返回什么」只在一处想清楚，调用处不用判空。
//
// ------------------------------------------------------------
// 实测：修正 flag 复位后，连续多次调用全部正确
// ============================================================

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    bool flag = true;

public:
    bool isBalanced(TreeNode* root) {
        flag = true;                        // ★ 入口复位（本题唯一的坑）
        if (root == nullptr) return true;
        dfs(root);
        return flag;
    }

    // 返回以 root 为根的子树高度，顺路检查平衡
    int dfs(TreeNode* root) {
        int left = 0;
        if (root->left != nullptr) left = dfs(root->left);
        int right = 0;
        if (root->right != nullptr) right = dfs(root->right);

        if (abs(left - right) > 1) flag = false;
        return max(left, right) + 1;
    }
};
