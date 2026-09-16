// ============================================================
// LeetCode 40. 组合总和 II
// 考点：回溯 · 组合型 + 树层去重（start + i > start）
// 复杂度：时间 O(2^n) 量级，空间 O(n)
// 日期：2026-09-16
// ============================================================
//
// 【题意】
// candidates 里可能有重复数字，每个数字 只能用一次，
// 找出所有和为 target 的不重复组合。
//
// 【和 LC 39 的两处差别】
//   1. 每个数只能用一次 → 递归传 i + 1（不是 i）
//   2. 有重复数字 → 需要树层去重
//
// 【去重判据：i > start 而不是 i > 0】
//   if (i > start && candidates[i] == candidates[i-1]) continue;
//
//   语义：本层的候选范围是 [start, n-1]，
//        "同一个值在本层只用第一个"就是拿 i 和 i-1 比，
//        并且要求 i 不是本层的第一个（否则没有前一个可比）。
//   所以边界基准是 start —— 组合的层边界，不是 0。
//
//   实测照搬排列的 i > 0：4 个用例全错，
//   漏掉的都是"需要连续用两个相同数字"的组合。
//
// 【为什么这里不需要 visit】
//   组合题下标只增不减，"本层用了谁"由循环位置本身决定。
//   加了 visit 它恒为 false，是死代码 —— 概念混用。
//
// 【易错】
// 1. 先 sort（去重前提）。
// 2. 去重判据的层边界写 i > start，不是 i > 0。
// 3. 递归传 i + 1，不是 i（传 i 会让同一个数被重复使用）。
// 4. 别加 visit 数组。
// ============================================================

class Solution {
public:
    vector<vector<int>> ret;
    vector<int> path;

    void dfs(vector<int>& candidates, int start, int remain) {
        if (remain == 0) {
            ret.push_back(path);
            return;
        }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remain) break;                      // 升序剪枝

            // 树层去重：本层 [start, n-1] 内，同值只用第一个
            if (i > start && candidates[i] == candidates[i - 1]) continue;

            path.push_back(candidates[i]);
            dfs(candidates, i + 1, remain - candidates[i]);         // i+1：每个数只用一次
            path.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        dfs(candidates, 0, target);
        return ret;
    }
};
