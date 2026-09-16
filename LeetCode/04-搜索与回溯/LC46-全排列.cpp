// ============================================================
// LeetCode 46. 全排列
// 考点：回溯 · 排列型（visit 数组 + 每层从 0 开始）
// 复杂度：时间 O(n · n!)，空间 O(n)
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// 给定不含重复数字的数组 nums，返回所有可能的全排列（任意顺序）。
//
// 【信号词】
// "返回 所有 可能的排列" → 回溯 A 型（要全部解），void + 成员 ret 累积。
//
// 【形态定型】
//   每层的"选择" = 挑一个还没用过的数放到当前位置
//   循环起点     = 0（排列里下标可以回退：第 3 个位置仍可选第 1 个数）
//   约束         = visit 数组（记住"谁已经被用过"）
//
// 【易错】
// 1. 出口检查写在最前面：path.size() == n 时收集并 return，
//    漏了 return 会继续往下递归。
// 2. 做选择和撤销选择必须成对出现，且撤销要放在递归调用之后。
// 3. 排列题不需要 start 参数；用了 start 就变成组合了。
// ============================================================

class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;
    vector<bool> visit;

    void dfs(vector<int>& nums) {
        if (path.size() == nums.size()) {      // 出口：凑齐一个排列
            ret.push_back(path);
            return;
        }
        for (int i = 0; i < (int)nums.size(); i++) {
            if (visit[i]) continue;             // 已经用过的数跳过
            visit[i] = true;                    // 做选择
            path.push_back(nums[i]);
            dfs(nums);
            path.pop_back();                    // 撤销选择
            visit[i] = false;
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        visit.assign(nums.size(), false);
        dfs(nums);
        return ret;
    }
};
