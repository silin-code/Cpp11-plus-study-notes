// ============================================================
// LeetCode 47. 全排列 II
// 考点：回溯 · 排列型 + 树层去重（排序 + !visit[i-1]）
// 复杂度：时间 O(n · n!)，空间 O(n)
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// 数组里可能含重复数字，返回所有 不重复 的全排列。
//
// 【为什么 LC 46 的写法会重复】
// 比如 [1,1,2]，两个 1 是不同下标，visit 各自记一次，
// 交换两者会生成两份相同的排列。
//
// 【去重原理：同一层里，值相同的只选第一个】
// 排序后相同数字相邻。对当前层遍历到下标 i 时：
//   若 nums[i] == nums[i-1] 且 !visit[i-1]
//   → 说明前一个同值的数在本层没被用（它已被撤销回到本层），
//     也就是"本层已经用 nums[i-1] 走过一遍了"，跳过 i。
//
// 【判据里每个部分为什么是它】
//   nums[i] == nums[i-1]  —— 值相同，才构成重复
//   !visit[i-1]           —— 前一个同值数"在本层可用却没用"
//                            （若是 true，说明它在上层被选了，是树枝关系，不能跳）
//   i > 0                 —— 防止 nums[i-1] 越界（排列的层边界是 0）
//
// 【易错】
// 1. 必须先 sort，否则相同数字不相邻，判据失效。
// 2. 组合题（LC 40）这里的 i > 0 要换成 i > start，别照搬。
// 3. 撤销和 visit[i]=true 仍要成对，去重判据不影响这部分。
// ============================================================

class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;
    vector<bool> visit;

    void dfs(vector<int>& nums) {
        if (path.size() == nums.size()) {
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (visit[i]) continue;

            // 树层去重：同一层里同值的只用第一个
            if (i > 0 && nums[i] == nums[i - 1] && !visit[i - 1]) continue;

            visit[i] = true;
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();
            visit[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());         // 去重的前提：先排序
        visit.assign(nums.size(), false);
        dfs(nums);
        return ret;
    }
};
